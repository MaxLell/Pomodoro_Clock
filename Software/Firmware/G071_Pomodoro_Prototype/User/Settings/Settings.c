#include "Settings.h"
#include "Common.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "Delay.h"
#include "PomodoroControl_Datatypes.h"
#include "LightEffects.h"
#include "FSM.h"
#include "CfgStore_Datatypes.h"
#include "CountdownTimer.h"

typedef struct
{
    BOOL bCfgStoreRequested;
    BOOL bCfgCurrentSettingRequested;

    BOOL bCfgStoreReceived;
    BOOL bCfgCurrentSettingReceived;

    BOOL bRotaryEncoderButtonPressed;

} InternalState_t;

/********************************************************
 * Private Variables
 ********************************************************/

STATIC TimeCfg_s sTimeCfg[CFG_LAST] = {0};
STATIC uint8_t u8NofSettings = 3;
STATIC const uint32_t TOGGLE_INTERVAL_MS = 200;
STATIC uint8_t u8CurrentSetting = 0;
STATIC int32_t s32EncoderValue = 0;
STATIC InternalState_t sInternalState = {0};
STATIC timer_t sAnimationTimer = {0};

/********************************************************
 * Private Function Prototypes
 ********************************************************/

void Settings_getMinuteArray(const TimeCfg_s *const in_psTimeCfg, uint8_t *const out_pu8MinuteArray);

uint8_t Settings_getCurrentSettingFromEncoder(int32_t s32CurrentEncoderValue);

/********************************************************
 * FSM
 ********************************************************/

// State Definiton
typedef enum
{
    SETTING_STATE_IDLE = 0U,
    SETTING_STATE_INIT,
    SETTING_STATE_SELECT_SETTING,
    SETTING_STATE_CLEAN_UP,
    SETTING_STATE_LAST
} Settings_State_e;

// Event Defintion
typedef enum
{
    SETTING_EVENT_TRIGGERED = 0U,
    SETTING_EVENT_INIT_COMPLETE,
    SETTING_EVENT_SETTING_SELECTED,
    SETTING_EVENT_SETTING_CLEANED_UP,
    SETTING_EVENT_LAST
} Settings_Event_e;

// Function Prototypes for the State Functions
STATIC void Settings_IdleStateFunction(void);
STATIC void Settings_InitStateFunction(void);
STATIC void Settings_SelectSettingStateFunction(void);
STATIC void Settings_CleanUpStateFunction(void);

// Map State functions to States
STATIC const FSM_StateActionCb aStateActions[] = {
    [SETTING_STATE_IDLE] = Settings_IdleStateFunction,
    [SETTING_STATE_INIT] = Settings_InitStateFunction,
    [SETTING_STATE_SELECT_SETTING] = Settings_SelectSettingStateFunction,
    [SETTING_STATE_CLEAN_UP] = Settings_CleanUpStateFunction,
};

// Transition Matrix
STATIC const uint16_t Settings_transitionMatrix[SETTING_STATE_LAST][SETTING_EVENT_LAST] = {
    [SETTING_STATE_IDLE] = {
        [SETTING_EVENT_TRIGGERED] = SETTING_STATE_INIT,
        [SETTING_EVENT_INIT_COMPLETE] = SETTING_STATE_IDLE,
        [SETTING_EVENT_SETTING_SELECTED] = SETTING_STATE_IDLE,
        [SETTING_EVENT_SETTING_CLEANED_UP] = SETTING_STATE_IDLE,
    },
    [SETTING_STATE_INIT] = {
        [SETTING_EVENT_TRIGGERED] = SETTING_STATE_INIT,
        [SETTING_EVENT_INIT_COMPLETE] = SETTING_STATE_SELECT_SETTING,
        [SETTING_EVENT_SETTING_SELECTED] = SETTING_STATE_INIT,
        [SETTING_EVENT_SETTING_CLEANED_UP] = SETTING_STATE_INIT,
    },
    [SETTING_STATE_SELECT_SETTING] = {
        [SETTING_EVENT_TRIGGERED] = SETTING_STATE_SELECT_SETTING,
        [SETTING_EVENT_INIT_COMPLETE] = SETTING_STATE_SELECT_SETTING,
        [SETTING_EVENT_SETTING_SELECTED] = SETTING_STATE_CLEAN_UP,
        [SETTING_EVENT_SETTING_CLEANED_UP] = SETTING_STATE_SELECT_SETTING,
    },
    [SETTING_STATE_CLEAN_UP] = {
        [SETTING_EVENT_TRIGGERED] = SETTING_STATE_CLEAN_UP,
        [SETTING_EVENT_INIT_COMPLETE] = SETTING_STATE_CLEAN_UP,
        [SETTING_EVENT_SETTING_SELECTED] = SETTING_STATE_CLEAN_UP,
        [SETTING_EVENT_SETTING_CLEANED_UP] = SETTING_STATE_IDLE,
    }};

// Generate the FSM Configuration
STATIC FSM_Config_t sSettingsFsmConfig = {
    .NUMBER_OF_STATES = SETTING_STATE_LAST,
    .NUMBER_OF_EVENTS = SETTING_EVENT_LAST,
    .au16TransitionMatrix = (const uint16_t *)Settings_transitionMatrix,
    .asStateActions = (const FSM_StateActionCb *)aStateActions,
    .u16CurrentState = SETTING_STATE_IDLE,
    .u16CurrentEvent = SETTING_EVENT_SETTING_CLEANED_UP,
};

// State Functions Implementation
void Settings_IdleStateFunction(void)
{
    // Do nothing, but wait - This state is changed from the MessageCallback function
}

void Settings_InitStateFunction(void)
{
    log_info("Settings_InitStateFunction");
    msg_t sMsg = {0};
    status_e eStatus;

    // GET Current CfgStore
    if (!sInternalState.bCfgStoreRequested)
    {
        sMsg.eMsgId = MSG_0402;
        eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");

        sInternalState.bCfgStoreRequested = TRUE;

        log_info("Requesting CfgStore");
    }

    // Wait for the CfgStore to be received - do not move forward
    if (!sInternalState.bCfgStoreReceived)
    {
        return;
    }

    log_info("CfgStore Received");

    // GET Currently Selected Setting (Index) for the CfgStore
    if (!sInternalState.bCfgCurrentSettingRequested)
    {
        sMsg.eMsgId = MSG_0405;
        eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");

        sInternalState.bCfgCurrentSettingRequested = TRUE;

        log_info("Requesting Current Setting");
    }

    // Wait for the Currently selected Index of the CfgStore
    if (!sInternalState.bCfgCurrentSettingReceived)
    {
        return;
    }
    log_info("Current Setting Received");

    // Reset the Encoder
    sMsg.eMsgId = MSG_0600;
    eStatus = MessageBroker_publish(&sMsg);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");

    log_info("Encoder is reset");

    // Reset the Encoder's Button State
    sInternalState.bRotaryEncoderButtonPressed = FALSE;

    // Start the Timer for the toggling Animation of the Progress LED Rings
    Countdown_resetAndStartTimer(&sAnimationTimer);

    // Transition: When all Tasks here have been performed successfully
    FSM_setTriggerEvent(&sSettingsFsmConfig, SETTING_EVENT_INIT_COMPLETE);
}
void Settings_SelectSettingStateFunction(void)
{
    static BOOL bRunOnce = TRUE;
    if (bRunOnce)
    {
        log_info("Settings_SelectSettingStateFunction");
        bRunOnce = FALSE;
    }

    // Determine Setting to render from the current Rotary Encoder Position
    u8CurrentSetting = Settings_getCurrentSettingFromEncoder(s32EncoderValue);

    if (Countdown_getTimerStatus(&sAnimationTimer) == E_COUNTDOWN_TIMER_EXPIRED)
    {
        static BOOL bToggleNow = FALSE;
        // Toggle the Rendering

        if (bToggleNow)
        {
            // Render the selected Setting
            uint8_t au8MinuteArray[TOTAL_MINUTES] = {0};
            Settings_getMinuteArray(&sTimeCfg[u8CurrentSetting], au8MinuteArray);
            LightEffects_RenderPomodoro(au8MinuteArray, TOTAL_MINUTES, FALSE);
        }
        else
        {
            // Clear the Progress Rings
            LightEffects_ClearPomodoroProgressRings();
        }

        bToggleNow = !bToggleNow;
    }

    // Transition: When the Rotary Encoder Button was pressed
    if (sInternalState.bRotaryEncoderButtonPressed)
    {
        // Transition: Trigger the Settings FSM
        FSM_setTriggerEvent(&sSettingsFsmConfig, SETTING_EVENT_SETTING_SELECTED);
    }
}
void Settings_CleanUpStateFunction(void)
{
    log_info("Settings_CleanUpStateFunction");
    status_e eStatus;
    msg_t sMsg = {0};

    // POST the current selected Setting Index
    sMsg.eMsgId = MSG_0404;
    sMsg.au8DataBytes = &u8CurrentSetting;
    eStatus = MessageBroker_publish(&sMsg);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");

    // Clear out the Progress Rings
    LightEffects_ClearPomodoroProgressRings();

    // Reset all local variables
    memset(&sInternalState, 0, sizeof(InternalState_t));

    // Reset the Encoder
    sMsg.eMsgId = MSG_0600;
    eStatus = MessageBroker_publish(&sMsg);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");

    // Reset the Encoder's Button State
    sInternalState.bRotaryEncoderButtonPressed = FALSE;

    // Publish the Setting Complete Message
    sMsg.eMsgId = MSG_0701;
    eStatus = MessageBroker_publish(&sMsg);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");

    // Change current State to Idle
    FSM_setTriggerEvent(&sSettingsFsmConfig, SETTING_EVENT_SETTING_CLEANED_UP);
}

/********************************************************
 * Implementation
 ********************************************************/
void Settings_getMinuteArray(const TimeCfg_s *const in_psTimeCfg, uint8_t *const out_pu8MinuteArray)
{
    // Input Checks
    {
        ASSERT_MSG(!(in_psTimeCfg == NULL), "Input TimeCfg_s Pointer is NULL");
        ASSERT_MSG(!(out_pu8MinuteArray == NULL), "Output MinuteArray Pointer is NULL");

        // Make sure that the provided TimeCfg_s is valid
        ASSERT_MSG(!(in_psTimeCfg->u8WorktimeMinutes == 0), "Worktime is 0");
        ASSERT_MSG(!(in_psTimeCfg->u8BreaktimeMinutes == 0), "Breaktime is 0");
        ASSERT_MSG(!(in_psTimeCfg->u8WorktimeMinutes + in_psTimeCfg->u8BreaktimeMinutes >= TOTAL_MINUTES), "Worktime + Breaktime >= TOTAL_MINUTES");
    }

    int8_t i8CurrentWorktime = in_psTimeCfg->u8WorktimeMinutes;
    int8_t i8CurrentBreaktime = in_psTimeCfg->u8BreaktimeMinutes;

    uint8_t u8Sum = i8CurrentWorktime + i8CurrentBreaktime;

    uint8_t u8CurrentIdx = 0;

    // Fill the entire Minute Array with NONE Phase Entries
    for (uint8_t i = 0; i < TOTAL_MINUTES; i++)
    {
        out_pu8MinuteArray[i] = E_CFG_OFF;
    }

    // Fill in the Worktime
    while (i8CurrentWorktime > 0)
    {
        i8CurrentWorktime--;
        out_pu8MinuteArray[u8CurrentIdx] = E_CFG_WORKTIME;
        u8CurrentIdx++;

        ASSERT_MSG(!(u8CurrentIdx > TOTAL_MINUTES), "u8CurrentIdx >= TOTAL_MINUTES");
    }

    if (u8Sum > MINUTES_IN_HOUR)
    {
        // Breaktime and Worktime are not fitting into on Ring
        if (u8CurrentIdx < MINUTES_IN_HOUR)
        {
            // Add an offset of 60 to the current index
            // So that the Breaktime is rendered on teh second ring
            u8CurrentIdx += MINUTES_IN_HOUR;
        }
    }

    if (u8Sum >= 120)
    {
        // Do Nuthin
        // Do not add in the Breaktime entries - as they would exceed the second ring
    }
    else
    {
        // Fill in the Breaktime entries
        while ((i8CurrentBreaktime > 0) && (u8CurrentIdx < TOTAL_MINUTES))
        {
            i8CurrentBreaktime--;
            out_pu8MinuteArray[u8CurrentIdx] = E_CFG_BREAKTIME;

            u8CurrentIdx++;

            if (u8CurrentIdx >= TOTAL_MINUTES)
            {
                u8CurrentIdx = MINUTES_IN_HOUR;
            }
            ASSERT_MSG(!(u8CurrentIdx >= TOTAL_MINUTES), "u8CurrentIdx >= TOTAL_MINUTES");
        }
    }
}

status_e Settings_MsgCallback(const msg_t *const in_psMsg)
{
    switch (in_psMsg->eMsgId)
    {

    case MSG_0103:
    {
        // Parse the Button Event
        ButtonMessage_s sButtonMessage = *(ButtonMessage_s *)in_psMsg->au8DataBytes;

        if (sButtonMessage.eButton == E_BUTTON_ENCODER)
        {
            if (sButtonMessage.eEvent == E_BTN_EVENT_SHORT_PRESSED)
            {
                sInternalState.bRotaryEncoderButtonPressed = TRUE;
                log_info("Rotary Encoder Button Short Pressed");
            }
        }
    }
    break;

    case MSG_0403:
    {
        // Receive all Pomodoro Configurations
        TimeCfg_s *psTmpTimeCfg = (TimeCfg_s *)in_psMsg->au8DataBytes;
        u8NofSettings = in_psMsg->u16DataSize / sizeof(TimeCfg_s);
        ASSERT_MSG(!(u8NofSettings > CFG_LAST), "u8NofSettings > CFG_LAST - too many Settings Provided");

        // Copy the Settings into the local Store
        for (uint8_t i = 0; i < u8NofSettings; i++)
        {
            sTimeCfg[i] = psTmpTimeCfg[i];
            log_info("Setting %d: Worktime: %d, Breaktime: %d", i, sTimeCfg[i].u8WorktimeMinutes, sTimeCfg[i].u8BreaktimeMinutes);
        }

        sInternalState.bCfgStoreReceived = TRUE;
    }
    break;

    case MSG_0404:
    {
        // Receive the current selected Configuration
        u8CurrentSetting = in_psMsg->au8DataBytes[0];
        sInternalState.bCfgCurrentSettingReceived = TRUE;
        log_info("Current Setting Index: %d", u8CurrentSetting);
    }

    case MSG_0601:
    {
        // Encoder Value Changed - parse the current value from the Encoder from the incoming Message
        s32EncoderValue = in_psMsg->au8DataBytes[0] << 0 | in_psMsg->au8DataBytes[1] << 8 |
                          in_psMsg->au8DataBytes[2] << 16 | in_psMsg->au8DataBytes[3] << 24;

        s32EncoderValue /= 2;
    }
    break;

    case MSG_0700: // Start Settings Message
    {
        // Transition: Trigger the Settings FSM
        FSM_setTriggerEvent(&sSettingsFsmConfig, SETTING_EVENT_TRIGGERED);
        log_info("Settings procedure started");
    }
    break;

    default:
        ASSERT_MSG(FALSE, "Unknown Message ID: %d", in_psMsg->eMsgId);
        return STATUS_ERROR;
    }

    return STATUS_OK;
}

uint8_t Settings_getCurrentSettingFromEncoder(int32_t s32CurrentEncoderValue)
{
    uint8_t u8ReturnValue = 0;
    for (int i = 1; i <= CFG_LAST; i++)
    {
        if (s32CurrentEncoderValue % i == 0)
        {
            u8ReturnValue = i - 1;
        }
    }
    return u8ReturnValue;
}

void Settings_init(void)
{

    status_e eStatus;
    // Subscribe to the Button Event
    eStatus = MessageBroker_subscribe(MSG_0103, Settings_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe to MSG_0103");

    // Subscribe to the CfgStore Message (Response to the Request to recieve all Pomodoro Configurations)
    eStatus = MessageBroker_subscribe(MSG_0403, Settings_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe to MSG_0403");

    // Subscribe to the POST current Setting Index
    eStatus = MessageBroker_subscribe(MSG_0404, Settings_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe to MSG_0404");

    // Subscribe to the Encoder Value Changed Message
    eStatus = MessageBroker_subscribe(MSG_0601, Settings_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe to MSG_0601");

    // Subscribe to the Start Settings Message
    eStatus = MessageBroker_subscribe(MSG_0700, Settings_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe to MSG_0501");

    // Initialize the Timer
    Countdown_initTimerMs(&sAnimationTimer, TOGGLE_INTERVAL_MS, E_OPERATIONAL_MODE_CONTIUNOUS);

    // Reset the Encoder's Button State
    sInternalState.bRotaryEncoderButtonPressed = FALSE;

    unused(eStatus); // To avoid compiler warning
}

void Settings_execute(void)
{
    FSM_execute(&sSettingsFsmConfig);
}
