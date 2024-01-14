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
// #define POMODORO_CONTROL_TEST

#ifndef POMODORO_CONTROL_TEST
#define TIMER_PERIOD_MIN 60000
#define TIMER_PERIOD_SEC 1000
#define TIMER_PERIOD_X_MS 30
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

STATIC PomodoroControl_internalStatus_t sInternalState = {0};

STATIC LightEffects_PomodoroRingPhaseCfg_t asEffects[MAX_SETTINGS] = {0};
STATIC uint8_t u8EffectArraySize = 0;

STATIC timer_t sTimerWtBtHandler = {0};
STATIC timer_t sTimerWarningHandler = {0};
STATIC timer_t sTimerCancelSeqHandler = {0};
STATIC timer_t sTimerCancelSeqTimeoutHandler = {0};

// TODO - Remove this functionality to the LightEffects Module - These Arrays do
// not need to be exposed here
STATIC uint8_t au8CompressedArrayRing1[NOF_LEDS_OUTER_RING] = {0};
STATIC uint8_t au8CompressedArrayRing2[NOF_LEDS_MIDDLE_RING] = {0};

/********************************************************
 * FSM Setup
 ********************************************************/

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
    LightEffect_PomodoroConfig_e eEffectType = sInternalState.u8PomodoroConfig;
    LightEffects_getInitialPomodoroSetting(asEffects, &u8EffectArraySize, eEffectType);

    // Render the initial configuration
    LightEffects_getCompressedArraysForCurrentPhase(asEffects, u8EffectArraySize, sInternalState.u8CurrentPhase,
                                                    au8CompressedArrayRing2, au8CompressedArrayRing1);

    // Render the compressed Arrays on the Rings
    LightEffects_RenderRings(au8CompressedArrayRing2, NOF_LEDS_MIDDLE_RING, au8CompressedArrayRing1,
                             NOF_LEDS_OUTER_RING);

    // Set the current Phase
    sInternalState.u8CurrentPhase = E_PHASE_WORK_TIME;

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
    BOOL bWorktimeIsOver;
    LightEffects_isPhaseOver(asEffects, u8EffectArraySize, &bWorktimeIsOver, sInternalState.u8CurrentPhase,
                             E_ANIMATION_WORK_TIME);
    // If Worktime is not over
    if (FALSE == bWorktimeIsOver)
    {
        // If one Minute is over - only then run the code
        timer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerWtBtHandler);
        if (E_COUNTDOWN_TIMER_EXPIRED == sTimerStatus)
        {
            // Update the CFGs
            LightEffects_updateWorktimeCfgForCurrentMinute(asEffects, u8EffectArraySize, sInternalState.u8CurrentPhase);

            LightEffects_getCompressedArraysForCurrentPhase(asEffects, u8EffectArraySize, sInternalState.u8CurrentPhase,
                                                            au8CompressedArrayRing2, au8CompressedArrayRing1);

            // Render the compressed Arrays on the Rings
            LightEffects_RenderRings(au8CompressedArrayRing2, NOF_LEDS_MIDDLE_RING, au8CompressedArrayRing1,
                                     NOF_LEDS_OUTER_RING);
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
        sInternalState.u8CurrentPhase = E_PHASE_WARNING;

        // Clear the Pomodoro Progress Rings
        LightEffects_ClearPomodoroProgressRings();

        // Set the Flag
        bRunOnce = TRUE;
    }

    // Set Trigger Event to Pending
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_PENDING);

    BOOL bWarningPeriodIsOver = FALSE;
    LightEffects_isPhaseOver(asEffects, u8EffectArraySize, &bWarningPeriodIsOver, sInternalState.u8CurrentPhase,
                             E_ANIMATION_WARNING);

    // If Warning Period is not over
    if (FALSE == bWarningPeriodIsOver)
    {
        // If one Minute is over - only then run the code
        timer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerWarningHandler);
        if (E_COUNTDOWN_TIMER_EXPIRED == sTimerStatus)
        {
            // Update the CFGs
            LightEffects_updateWorktimeCfgForCurrentMinute(asEffects, u8EffectArraySize, sInternalState.u8CurrentPhase);

            LightEffects_getCompressedArraysForCurrentPhase(asEffects, u8EffectArraySize, sInternalState.u8CurrentPhase,
                                                            au8CompressedArrayRing2, au8CompressedArrayRing1);

            // Render the compressed Arrays on the Rings
            LightEffects_RenderRings(au8CompressedArrayRing2, NOF_LEDS_MIDDLE_RING, au8CompressedArrayRing1,
                                     NOF_LEDS_OUTER_RING);
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
    // Update the Phase to Breaktime
    sInternalState.u8CurrentPhase = E_PHASE_BREAK_TIME;

    // Set Trigger Event to Sequence Complete
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);
}

void StateActionBreaktime(void)
{
    // Set Trigger Event to Pending
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_PENDING);

    BOOL bBreaktimeIsOver = FALSE;
    LightEffects_isPhaseOver(asEffects, u8EffectArraySize, &bBreaktimeIsOver, sInternalState.u8CurrentPhase,
                             E_ANIMATION_BREAK_TIME_BRIGHT);

    // If Breaktime is not over
    if (FALSE == bBreaktimeIsOver)
    {
        // If one Minute is over - only then run the code
        timer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerWtBtHandler);
        if (E_COUNTDOWN_TIMER_EXPIRED == sTimerStatus)
        {
            // Update the CFGs
            LightEffects_updateWorktimeCfgForCurrentMinute(asEffects, u8EffectArraySize, sInternalState.u8CurrentPhase);

            LightEffects_getCompressedArraysForCurrentPhase(asEffects, u8EffectArraySize, sInternalState.u8CurrentPhase,
                                                            au8CompressedArrayRing2, au8CompressedArrayRing1);

            // Render the compressed Arrays on the Rings
            LightEffects_RenderRings(au8CompressedArrayRing2, NOF_LEDS_MIDDLE_RING, au8CompressedArrayRing1,
                                     NOF_LEDS_OUTER_RING);
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
    sInternalState.u8CurrentPhase = E_PHASE_CANCEL_SEQUENCE;

    // Render the Configuration
    LightEffects_getCompressedArraysForCurrentPhase(asEffects, u8EffectArraySize, sInternalState.u8CurrentPhase,
                                                    au8CompressedArrayRing2, au8CompressedArrayRing1);
    LightEffects_RenderRings(au8CompressedArrayRing2, NOF_LEDS_MIDDLE_RING, au8CompressedArrayRing1,
                             NOF_LEDS_OUTER_RING);

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
    LightEffects_isPhaseOver(asEffects, u8EffectArraySize, &bCancelSequenceIsOver, sInternalState.u8CurrentPhase,
                             E_ANIMATION_CANCEL_SEQUENCE);

    // If Cancel Sequence is not over
    if (FALSE == bCancelSequenceIsOver)
    {
        // If one Minute is over - only then run the code
        timer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerCancelSeqHandler);
        if (E_COUNTDOWN_TIMER_EXPIRED == sTimerStatus)
        {
            // Update the CFGs
            LightEffects_updateWorktimeCfgForCurrentMinute(asEffects, u8EffectArraySize, sInternalState.u8CurrentPhase);

            LightEffects_getCompressedArraysForCurrentPhase(asEffects, u8EffectArraySize, sInternalState.u8CurrentPhase,
                                                            au8CompressedArrayRing2, au8CompressedArrayRing1);

            // Render the compressed Arrays on the Rings
            LightEffects_RenderRings(au8CompressedArrayRing2, NOF_LEDS_MIDDLE_RING, au8CompressedArrayRing1,
                                     NOF_LEDS_OUTER_RING);
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

        log_info("Cancel Sequence Timeout");
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
        sInternalState.u8PomodoroConfig = psMsg->au8DataBytes[0];
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