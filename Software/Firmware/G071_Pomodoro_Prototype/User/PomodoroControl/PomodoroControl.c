#include "PomodoroControl.h"
#include "Common.h"
#include "CountdownTimer.h"
#include "FSM.h"
#include "LightEffects.h"
#include "LightEffects_Pomodoro.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "PomodoroControl_Datatypes.h"
#include "RgbLed.h"
#include "RgbLed_Config.h"

/********************************************************
 * Private Defines
 ********************************************************/

#define LEDS_PER_RING 60

// #define POMODORO_CONTROL_TEST

#ifndef POMODORO_CONTROL_TEST
#define TIMER_PERIOD_MIN 60000
#define TIMER_PERIOD_SEC 1000
#define TIMER_PERIOD_X_MS 100
#define TIMEOUT_PERIOD_MIN 5
#else
#define TIMER_PERIOD_MIN 60
#define TIMER_PERIOD_SEC 30
#define TIMER_PERIOD_X_MS 30
#define TIMEOUT_PERIOD_MIN 100
#endif

/********************************************************
 * Private Variables
 ********************************************************/

STATIC uint8_t u8EffectArraySize = 0;

STATIC timer_t sTimerWtBtHandler = {0};
STATIC timer_t sTimerWarningHandler = {0};
STATIC timer_t sTimerCancelSeqHandler = {0};
STATIC timer_t sTimerCancelSeqTimeoutHandler = {0};

STATIC PCTRL_Progress_t sPomodoroProgress = {0};

/********************************************************
 * Private Function Prototypes
 ********************************************************/

STATIC void PomodoroControl_getMinuteArray(PCTRL_Progress_t *const inout_sSelf);
STATIC void PomodoroControl_updateSequence(PCTRL_Progress_t *const inout_sSelf);
STATIC void PomodoroControl_isWorktimeOver(PCTRL_Progress_t *const inout_sSelf, BOOL *const out_bIsWorktimeOver);
STATIC void PomodoroControl_isBreaktimeOver(PCTRL_Progress_t *const inout_sSelf, BOOL *const out_bIsBreaktimeOver);

/********************************************************
 * FSM Setup
 ********************************************************/

STATIC void StateActionIdle(void);
STATIC void StateActionWorktimeInit(void);
STATIC void StateActionWorktime(void);
STATIC void StateActionWarning(void);
STATIC void StateActionBreaktimeInit(void);
STATIC void StateActionBreaktime(void);
STATIC void StateActionCancelSequenceInit(void);
STATIC void StateActionCancelSequenceRunning(void);
STATIC void StateActionCancelSequenceHalted(void);

/**
 * Old State ----(Event)-----> New State Matrix
 */
STATIC const uint16_t au16FsmTransitionMatrix[STATE_LAST][EVENT_LAST] = {
    // Current State
    [STATE_IDLE] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_WORKTIME_INIT,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_IDLE,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_IDLE,
            [EVENT_SEQUENCE_COMPLETE] = STATE_IDLE,
            [EVENT_SEQUENCE_PENDING] = STATE_IDLE,
        },
    // Current State
    [STATE_WORKTIME_INIT] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_WORKTIME_INIT,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_INIT,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_WORKTIME_INIT,
            [EVENT_SEQUENCE_COMPLETE] = STATE_WORKTIME,
            [EVENT_SEQUENCE_PENDING] = STATE_WORKTIME_INIT,
        },
    // Current State
    [STATE_WORKTIME] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_WORKTIME,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_INIT,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_WORKTIME,
            [EVENT_SEQUENCE_COMPLETE] = STATE_WARNING,
            [EVENT_SEQUENCE_PENDING] = STATE_WORKTIME,
        },
    // Current State
    [STATE_WARNING] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_WARNING,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_INIT,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_WARNING,
            [EVENT_SEQUENCE_COMPLETE] = STATE_BREAKTIME_INIT,
            [EVENT_SEQUENCE_PENDING] = STATE_WARNING,
        },
    // Current State
    [STATE_BREAKTIME_INIT] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_BREAKTIME_INIT,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_INIT,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_BREAKTIME_INIT,
            [EVENT_SEQUENCE_COMPLETE] = STATE_BREAKTIME,
            [EVENT_SEQUENCE_PENDING] = STATE_BREAKTIME_INIT,
        },
    // Current State
    [STATE_BREAKTIME] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_BREAKTIME,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_INIT,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_BREAKTIME,
            [EVENT_SEQUENCE_COMPLETE] = STATE_IDLE,
            [EVENT_SEQUENCE_PENDING] = STATE_BREAKTIME,
        },

    [STATE_CANCEL_SEQUENCE_INIT] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_CANCEL_SEQUENCE_INIT,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_INIT,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_CANCEL_SEQUENCE_INIT,
            [EVENT_SEQUENCE_COMPLETE] = STATE_CANCEL_SEQUENCE_RUNNING,
            [EVENT_SEQUENCE_PENDING] = STATE_CANCEL_SEQUENCE_INIT,
        },
    // Current State
    [STATE_CANCEL_SEQUENCE_RUNNING] =
        {
            // Event ----------------------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_CANCEL_SEQUENCE_RUNNING,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_RUNNING,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_CANCEL_SEQUENCE_HALTED,
            [EVENT_SEQUENCE_COMPLETE] = STATE_IDLE,
            [EVENT_SEQUENCE_PENDING] = STATE_CANCEL_SEQUENCE_RUNNING,
        },
    // Current State
    [STATE_CANCEL_SEQUENCE_HALTED] =
        {
            // Event ----------------------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_CANCEL_SEQUENCE_HALTED,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_RUNNING,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_CANCEL_SEQUENCE_HALTED,
            [EVENT_SEQUENCE_COMPLETE] = STATE_IDLE,
            [EVENT_SEQUENCE_PENDING] = STATE_CANCEL_SEQUENCE_HALTED,
        },
};

/**
 * Assignment of the StateAction Callbacks
 */
STATIC const FSM_StateActionCb aStateActions[] = {
    [STATE_IDLE] = StateActionIdle,
    [STATE_WORKTIME_INIT] = StateActionWorktimeInit,
    [STATE_WORKTIME] = StateActionWorktime,
    [STATE_WARNING] = StateActionWarning,
    [STATE_BREAKTIME_INIT] = StateActionBreaktimeInit,
    [STATE_BREAKTIME] = StateActionBreaktime,
    [STATE_CANCEL_SEQUENCE_INIT] = StateActionCancelSequenceInit,
    [STATE_CANCEL_SEQUENCE_RUNNING] = StateActionCancelSequenceRunning,
    [STATE_CANCEL_SEQUENCE_HALTED] = StateActionCancelSequenceHalted,
};

/**
 * FSM Initial Configuration
 * This needs to be done outside of the init function, since this struct
 * contains a couple of const members.
 */

FSM_Config_t sFsmConfig = {

    .NUMBER_OF_STATES = STATE_LAST,
    .NUMBER_OF_EVENTS = EVENT_LAST,
    .au16TransitionMatrix = (uint16_t *)&au16FsmTransitionMatrix,
    .asStateActions = aStateActions,
    .u16CurrentState = STATE_IDLE,
    .u16CurrentEvent = EVENT_SEQUENCE_PENDING,
};

void StateActionIdle(void)
{
    // Do nothing
}

void StateActionWorktimeInit(void)
{
    // Get the initial Pomodoro Setting
    PomodoroControl_getMinuteArray(&sPomodoroProgress);

    // Check if the Worktime is over
    BOOL bWorktimeIsOver = FALSE;
    PomodoroControl_isWorktimeOver(&sPomodoroProgress, &bWorktimeIsOver);
    LightEffects_RenderPomodoro(sPomodoroProgress.au8MinuteArray, TOTAL_MINUTES, bWorktimeIsOver);

    // Initialize and start the Countdown Timer
    Countdown_initTimerMs(&sTimerWtBtHandler, TIMER_PERIOD_MIN, E_OPERATIONAL_MODE_CONTIUNOUS);
    Countdown_startTimer(&sTimerWtBtHandler);

    // Update the trigger event
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);
}

void StateActionWorktime(void)
{
    // Set the default trigger event
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_PENDING);

    // Check if the Worktime is over
    BOOL bWorktimeIsOver = FALSE;
    PomodoroControl_isWorktimeOver(&sPomodoroProgress, &bWorktimeIsOver);

    // If Worktime is not over
    if (FALSE == bWorktimeIsOver)
    {
        // If one Minute is over - only then run the code
        timer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerWtBtHandler);
        if (E_COUNTDOWN_TIMER_EXPIRED == sTimerStatus)
        {
            // Update the Worktime, Breaktime
            PomodoroControl_updateSequence(&sPomodoroProgress);

            // Generate the updated Minute Array
            PomodoroControl_getMinuteArray(&sPomodoroProgress);

            // Render the compressed Arrays on the Rings
            LightEffects_RenderPomodoro(sPomodoroProgress.au8MinuteArray, TOTAL_MINUTES, bWorktimeIsOver);
        }
    }
    else
    { // If Worktime is over
      // Set Event -> Seq Complete
        FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);

        // Publish Message: Worktime Complete via the MsgBroker
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_ID_0201; // Pomodoro Work Time Sequence Complete
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish: %d", eStatus);
    }
}

void StateActionWarning(void)
{
    static BOOL bRunOnce = FALSE;

    if (!bRunOnce)
    {
        // Set a new Timer Instance
        Countdown_initTimerMs(&sTimerWarningHandler, TIMER_PERIOD_SEC, E_OPERATIONAL_MODE_CONTIUNOUS);
        Countdown_startTimer(&sTimerWarningHandler);

        // Set the current Phase to warning

        // Clear the Pomodoro Progress Rings
        LightEffects_ClearPomodoroProgressRings();

        // Set the Flag
        bRunOnce = TRUE;
    }

    // Set Trigger Event to Pending
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_PENDING);

    BOOL bWarningPeriodIsOver = TRUE;

    // If Warning Period is not over
    if (FALSE == bWarningPeriodIsOver)
    {
        // If one Minute is over - only then run the code
        timer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerWarningHandler);
        if (E_COUNTDOWN_TIMER_EXPIRED == sTimerStatus)
        {
            // Update the CFGs

            // Render the compressed Arrays on the Rings
        }
    }
    else
    { // If Warning Period is over
      // Set Event -> Seq Complete
        FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);

        // Reset the flag
        bRunOnce = FALSE;
    }
}

void StateActionBreaktimeInit(void)
{
    // Set Trigger Event to Sequence Complete
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);
}

void StateActionBreaktime(void)
{
    // Set Trigger Event to Pending
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_PENDING);

    BOOL bBreaktimeIsOver = FALSE;
    PomodoroControl_isBreaktimeOver(&sPomodoroProgress, &bBreaktimeIsOver);

    // If Breaktime is not over
    if (FALSE == bBreaktimeIsOver)
    {
        // If one Minute is over - only then run the code
        timer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerWtBtHandler);
        if (E_COUNTDOWN_TIMER_EXPIRED == sTimerStatus)
        {
            // Update the CFGs
            PomodoroControl_updateSequence(&sPomodoroProgress);

            // Generate the updated Minute Array
            PomodoroControl_getMinuteArray(&sPomodoroProgress);

            // Render the compressed Arrays on the Rings
            LightEffects_RenderPomodoro(sPomodoroProgress.au8MinuteArray, TOTAL_MINUTES, TRUE);
        }
    }
    else
    { // If Breaktime is over
      // Set Event -> Seq Complete
        FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);

        // Publish Message: Breaktime Complete via the MsgBroker
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_ID_0202; // Pomodoro Break Time Sequence Complete
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish: %d", eStatus);

        // Clear the Progress Rings
        LightEffects_ClearPomodoroProgressRings();
    }
}

void StateActionCancelSequenceInit(void)
{
    // Clear all existing Progress LEDs
    LightEffects_ClearPomodoroProgressRings();

    // set the Phase to Cancel Sequence

    // Render the Configuration

    // Set the Cancel Sequence Timer
    Countdown_initTimerMs(&sTimerCancelSeqHandler, TIMER_PERIOD_X_MS, E_OPERATIONAL_MODE_CONTIUNOUS);
    Countdown_startTimer(&sTimerCancelSeqHandler);

    // Start the timeout timer
    Countdown_initTimerMs(&sTimerCancelSeqTimeoutHandler, TIMER_PERIOD_MIN, E_OPERATIONAL_MODE_CONTIUNOUS);
    Countdown_startTimer(&sTimerCancelSeqTimeoutHandler);

    // Set the Trigger Event to Sequence Complete
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);
}
void StateActionCancelSequenceRunning(void)
{
    // Set the Trigger Event to Pending
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_PENDING);

    // Check if the Cancel Sequence is over
    BOOL bCancelSequenceIsOver = FALSE;

    // If Cancel Sequence is not over
    if (FALSE == bCancelSequenceIsOver)
    {
        // If one Minute is over - only then run the code
        timer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerCancelSeqHandler);
        if (E_COUNTDOWN_TIMER_EXPIRED == sTimerStatus)
        {
            // Update the CFGs

            // Render the compressed Arrays on the Rings
        }
    }
    else
    { // If Cancel Sequence is over
      // Set Event -> Seq Complete
        FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);
    }
}
void StateActionCancelSequenceHalted(void)
{
    // this event will be overwritten by a Long Press Event of the Trigger Button
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_PENDING);

    static uint8_t u8TimoutMinuteCounter = 0;
    timer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerCancelSeqTimeoutHandler);
    if (E_COUNTDOWN_TIMER_EXPIRED == sTimerStatus)
    {
        u8TimoutMinuteCounter++;
    }

    if (u8TimoutMinuteCounter >= TIMEOUT_PERIOD_MIN)
    {
        // Reset the Timeout Counter
        u8TimoutMinuteCounter = 0;
        FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE); // transitions to Idle

        // Clear the Progress Rings
        LightEffects_ClearPomodoroProgressRings();
    }
}

/********************************************************
 * Function Prototypes
 ********************************************************/

/**
 * Message Callback
 */

STATIC status_e PomodoroControl_MessageCallback(const msg_t *const sMsg);

/********************************************************
 * Implementation
 ********************************************************/

STATIC status_e PomodoroControl_MessageCallback(const msg_t *const psMsg)
{
    { // Input Verification
        ASSERT_MSG(!(psMsg == NULL), "Message is NULL!");
        if (psMsg == NULL)
        {
            return STATUS_ERROR;
        }
    }

    status_e eStatus = STATUS_SUCCESS;

    switch (psMsg->eMsgId)
    {
    case MSG_ID_0200: // Pomodoro Sequence Start Event
    {
        FSM_setTriggerEvent(&sFsmConfig, EVENT_POMODORO_SEQUENCE_START);
    }
    break;

    case MSG_ID_0101: // Trigger Button: is Pressed Down Continuously
    {
        FSM_setTriggerEvent(&sFsmConfig, EVENT_TRIGGER_BTN_LONG_PRESS);
    }
    break;

    case MSG_ID_0102: // Trigger Button: is Released after a Long Press
    {
        FSM_setTriggerEvent(&sFsmConfig, EVENT_TRIGGER_BTN_RELEASED);
    }
    break;

    case MSG_ID_0400: // Pomodoro Configuration: Worktime and Breaktime
                      // Periods
    {
        // Get the Pomodoro Configuration
        PomodoroPeriodConfiguration_t *psPomodoroConfig = (PomodoroPeriodConfiguration_t *)psMsg->au8DataBytes;
        sPomodoroProgress.u8Worktime = psPomodoroConfig->u8MinutesWorktimePeriod;
        sPomodoroProgress.u8Breaktime = psPomodoroConfig->u8MinutesBreaktimePeriod;
    }
    break;

    default:
        ASSERT_MSG(FALSE,
                   "This Callback should not be called for this message, but it "
                   "was with the following message ID: %d",
                   psMsg->eMsgId);
        eStatus = STATUS_ERROR;
        break;
    }
    return eStatus;
}

void PomodoroControl_init(void)
{
    // Subscribe to Messages
    status_e eStatus = MessageBroker_subscribe(MSG_ID_0400, PomodoroControl_MessageCallback);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe: %d", eStatus);

    eStatus = MessageBroker_subscribe(MSG_ID_0200, PomodoroControl_MessageCallback);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe: %d", eStatus);

    eStatus = MessageBroker_subscribe(MSG_ID_0101, PomodoroControl_MessageCallback);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe: %d", eStatus);

    eStatus = MessageBroker_subscribe(MSG_ID_0102, PomodoroControl_MessageCallback);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe: %d", eStatus);
}

status_e PomodoroControl_execute(void)
{
    status_e eStatus = STATUS_SUCCESS;
    FSM_execute(&sFsmConfig);
    return eStatus;
}

void PomodoroControl_getMinuteArray(PCTRL_Progress_t *const inout_sSelf)
{
    { // Input checks
      // Check against NULL Pointers
        ASSERT_MSG(!(NULL == inout_sSelf), "NULL Pointer");

        // Make sure that the Worktime is smaller then 121
        ASSERT_MSG(!(inout_sSelf->u8Worktime > TOTAL_MINUTES), "Worktime is bigger then 120");

        // Make sure that the Breaktime is smaller then 61
        ASSERT_MSG(!(inout_sSelf->u8Breaktime > MINUTES_IN_HOUR), "Breaktime is bigger then 60");
    }

    uint8_t u8LocalCopyWortime = inout_sSelf->u8Worktime;
    uint8_t u8LocalCopyBreaktime = inout_sSelf->u8Breaktime;

    int8_t i8CurrentWorktime = (int8_t)inout_sSelf->u8Worktime;
    int8_t i8CurrentBreaktime = (int8_t)inout_sSelf->u8Breaktime;

    uint8_t u8Sum = i8CurrentWorktime + i8CurrentBreaktime;
    BOOL bRunOnce = FALSE;

    uint8_t u8CurrentIdx = 0;

    // Fill the entire Minute Array with NONE Phase Entries
    for (uint8_t i = 0; i < TOTAL_MINUTES; i++)
    {
        inout_sSelf->au8MinuteArray[i] = E_CFG_OFF;
    }

    // Fill in the Worktime
    while (i8CurrentWorktime > 0)
    {
        i8CurrentWorktime--;
        inout_sSelf->au8MinuteArray[u8CurrentIdx] = E_CFG_WORKTIME;
        u8CurrentIdx++;

        ASSERT_MSG(!(u8CurrentIdx > TOTAL_MINUTES), "u8CurrentIdx >= TOTAL_MINUTES");
    }

    if (u8Sum >= LEDS_PER_RING)
    {
        // Breaktime and Worktime are not fitting into on Ring
        if (u8CurrentIdx < LEDS_PER_RING)
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
            inout_sSelf->au8MinuteArray[u8CurrentIdx] = E_CFG_BREAKTIME;
            u8CurrentIdx++;

            if (u8CurrentIdx >= TOTAL_MINUTES)
            {
                u8CurrentIdx = MINUTES_IN_HOUR;
            }

            ASSERT_MSG(!(u8CurrentIdx >= TOTAL_MINUTES), "u8CurrentIdx >= TOTAL_MINUTES");
        }
    }

    // Make sure that the original config is not changed
    ASSERT_MSG(!(u8LocalCopyWortime != inout_sSelf->u8Worktime), "Worktime has changed");
    ASSERT_MSG(!(u8LocalCopyBreaktime != inout_sSelf->u8Breaktime), "Breaktime has changed");
    unused(u8LocalCopyWortime);   // Avoid compiler warning
    unused(u8LocalCopyBreaktime); // Avoid compiler warning
}

void PomodoroControl_updateSequence(PCTRL_Progress_t *const inout_sSelf)
{
    {
        // Input Checks
        ASSERT_MSG(!(NULL == inout_sSelf), "NULL Pointer");
    }

    // Decrement the Worktime or Breaktime
    if (inout_sSelf->u8Worktime != 0)
    {
        inout_sSelf->u8Worktime--;
    }
    else if (inout_sSelf->u8Breaktime != 0)
    {
        inout_sSelf->u8Breaktime--;
    }
    else
    {
        // Do nothing
    }
}

STATIC void PomodoroControl_isWorktimeOver(PCTRL_Progress_t *const inout_sSelf, BOOL *const out_bIsWorktimeOver)
{
    {
        // Input Checks
        ASSERT_MSG(!(NULL == inout_sSelf), "NULL Pointer");
        ASSERT_MSG(!(NULL == out_bIsWorktimeOver), "NULL Pointer");
    }

    // Number Check
    BOOL bNumberCheck = FALSE;
    if (inout_sSelf->u8Worktime == 0)
    {
        bNumberCheck = TRUE;
    }

    // Iterate through the Array and check again - there must be no discrepancy
    BOOL bArrayCheck = TRUE;
    for (uint8_t i = 0; i < TOTAL_MINUTES; i++)
    {
        if (inout_sSelf->au8MinuteArray[i] == E_CFG_WORKTIME)
        {
            bArrayCheck = FALSE;
            break;
        }
    }

    ASSERT_MSG(!(bNumberCheck != bArrayCheck), "Number Check and Array Check are not equal");

    *out_bIsWorktimeOver = bNumberCheck;
    unused(bArrayCheck); // Avoid compiler warning
}

STATIC void PomodoroControl_isBreaktimeOver(PCTRL_Progress_t *const inout_sSelf, BOOL *const out_bIsBreaktimeOver)
{
    {
        // Input Checks
        ASSERT_MSG(!(NULL == inout_sSelf), "NULL Pointer");
        ASSERT_MSG(!(NULL == out_bIsBreaktimeOver), "NULL Pointer");
    }

    // Number Check
    BOOL bNumberCheck = FALSE;
    if (inout_sSelf->u8Breaktime == 0)
    {
        bNumberCheck = TRUE;
    }

    // Iterate through the Array and check again - there must be no discrepancy
    BOOL bArrayCheck = TRUE;
    for (uint8_t i = 0; i < TOTAL_MINUTES; i++)
    {
        if (inout_sSelf->au8MinuteArray[i] == E_CFG_BREAKTIME)
        {
            bArrayCheck = FALSE;
            break;
        }
    }

    ASSERT_MSG(!(bNumberCheck != bArrayCheck), "Number Check and Array Check are not equal");

    *out_bIsBreaktimeOver = bNumberCheck;
    unused(bArrayCheck); // Avoid compiler warning
}