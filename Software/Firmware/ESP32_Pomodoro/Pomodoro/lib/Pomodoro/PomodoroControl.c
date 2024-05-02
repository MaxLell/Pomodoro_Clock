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
#include "Delay.h"

/********************************************************
 * Private Defines
 ********************************************************/

#define LEDS_PER_RING 60

#define TIMER_PERIOD_MIN 60000
#define TIMER_PERIOD_SEC 1000
#define TIMER_PERIOD_SNOOZE_MS 5000    // 5 Minute Snooze Interval (5000ms * 60 Increments = 5 Minutes)
#define TIMER_PERIOD_CANCEL_SEQ_MS 150 // (150ms * 60 Increments = 9 Seconds)
#define TIMER_PERIOD_WARNING_MS 300    // (300ms * 60 Increments = 30 Seconds)
#define TIMEOUT_PERIOD_MIN 5

/********************************************************
 * Private Variables
 ********************************************************/

STATIC CountdownTimer_t sTimerWtBtHandler = {0};
STATIC CountdownTimer_t sTimerWarningHandler = {0};
STATIC CountdownTimer_t sTimerCancelSeqHandler = {0};
STATIC CountdownTimer_t sTimerCancelSeqTimeoutHandler = {0};
STATIC CountdownTimer_t sTimerSnoozeHandler = {0};

STATIC PCTRL_Progress_t sPomodoroProgress = {0};

STATIC LightEffects_RingCountdown_s sRingCountdown = {0};

STATIC TestData_0004_s sPomodoroTimingCfg = {0};

STATIC PomodoroPeriodConfiguration_s sPomodoroPeriodCfg = {0};

/********************************************************
 * Private Function Prototypes
 ********************************************************/

STATIC void PomodoroControl_getMinuteArray(PCTRL_Progress_t *const inout_sSelf);
STATIC void PomodoroControl_updateSequence(PCTRL_Progress_t *const inout_sSelf);
STATIC void PomodoroControl_isWorktimeOver(PCTRL_Progress_t *const inout_sSelf, bool *const out_bIsWorktimeOver);
STATIC void PomodoroControl_isBreaktimeOver(PCTRL_Progress_t *const inout_sSelf, bool *const out_bIsBreaktimeOver);

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
STATIC void StateActionSnooze(void);
STATIC void StateActionCleanUp(void);

/**
 * Old State ----(Event)-----> New State Matrix
 */
STATIC const u16 au16FsmTransitionMatrix[STATE_LAST][EVENT_LAST] = {
    // Current State
    [STATE_IDLE] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_WORKTIME_INIT,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_IDLE,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_IDLE,
            [EVENT_TRIGGER_BTN_SHORT_PRESS] = STATE_IDLE,
            [EVENT_SEQUENCE_COMPLETE] = STATE_IDLE,
            [EVENT_SEQUENCE_PENDING] = STATE_IDLE,
        },
    // Current State
    [STATE_WORKTIME_INIT] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_WORKTIME_INIT,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_IDLE,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_WORKTIME_INIT,
            [EVENT_TRIGGER_BTN_SHORT_PRESS] = STATE_WORKTIME_INIT,
            [EVENT_SEQUENCE_COMPLETE] = STATE_WORKTIME,
            [EVENT_SEQUENCE_PENDING] = STATE_WORKTIME_INIT,
        },
    // Current State
    [STATE_WORKTIME] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_WORKTIME,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CLEAN_UP,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_WORKTIME,
            [EVENT_TRIGGER_BTN_SHORT_PRESS] = STATE_WORKTIME,
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
            [EVENT_TRIGGER_BTN_SHORT_PRESS] = STATE_SNOOZE,
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
            [EVENT_TRIGGER_BTN_SHORT_PRESS] = STATE_BREAKTIME_INIT,
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
            [EVENT_TRIGGER_BTN_SHORT_PRESS] = STATE_SNOOZE,
            [EVENT_SEQUENCE_COMPLETE] = STATE_CLEAN_UP,
            [EVENT_SEQUENCE_PENDING] = STATE_BREAKTIME,
        },

    [STATE_CANCEL_SEQUENCE_INIT] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_CANCEL_SEQUENCE_INIT,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_INIT,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_CANCEL_SEQUENCE_INIT,
            [EVENT_TRIGGER_BTN_SHORT_PRESS] = STATE_CANCEL_SEQUENCE_INIT,
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
            [EVENT_TRIGGER_BTN_SHORT_PRESS] = STATE_CANCEL_SEQUENCE_RUNNING,
            [EVENT_SEQUENCE_COMPLETE] = STATE_CLEAN_UP,
            [EVENT_SEQUENCE_PENDING] = STATE_CANCEL_SEQUENCE_RUNNING,
        },
    // Current State
    [STATE_CANCEL_SEQUENCE_HALTED] =
        {
            // Event ----------------------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_CANCEL_SEQUENCE_HALTED,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_RUNNING,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_CANCEL_SEQUENCE_HALTED,
            [EVENT_TRIGGER_BTN_SHORT_PRESS] = STATE_CANCEL_SEQUENCE_HALTED,
            [EVENT_SEQUENCE_COMPLETE] = STATE_CLEAN_UP,
            [EVENT_SEQUENCE_PENDING] = STATE_CANCEL_SEQUENCE_HALTED,
        },
    // Current State
    [STATE_SNOOZE] =
        {
            // Event ----------------------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_SNOOZE,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_INIT,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_SNOOZE,
            [EVENT_TRIGGER_BTN_SHORT_PRESS] = STATE_SNOOZE,
            [EVENT_SEQUENCE_COMPLETE] = STATE_BREAKTIME_INIT,
            [EVENT_SEQUENCE_PENDING] = STATE_SNOOZE,
        },
    // Current State
    [STATE_CLEAN_UP] =
        {
            // Event ----------------------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_CLEAN_UP,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CLEAN_UP,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_CLEAN_UP,
            [EVENT_TRIGGER_BTN_SHORT_PRESS] = STATE_CLEAN_UP,
            [EVENT_SEQUENCE_COMPLETE] = STATE_IDLE,
            [EVENT_SEQUENCE_PENDING] = STATE_CLEAN_UP,
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
    [STATE_SNOOZE] = StateActionSnooze,
    [STATE_CLEAN_UP] = StateActionCleanUp,
};

/**
 * FSM Initial Configuration
 * This needs to be done outside of the init function, since this struct
 * contains a couple of const members.
 */

STATIC FSM_Config_t sFsmConfig = {

    .NUMBER_OF_STATES = STATE_LAST,
    .NUMBER_OF_EVENTS = EVENT_LAST,
    .au16TransitionMatrix = (u16 *)&au16FsmTransitionMatrix,
    .asStateActions = aStateActions,
    .u16CurrentState = STATE_IDLE,
    .u16CurrentEvent = EVENT_SEQUENCE_PENDING,
};

void StateActionIdle(void)
{
    /**
     * You do nuthin Jon Snow!
     * Wait around and watch the pain dry on the wall
     */
}

void StateActionWorktimeInit(void)
{
    // Request the Pomodoro Configuration and only move forward when the config was received
    if (true == sPomodoroPeriodCfg.bConfigWasUpdated)
    {
        // Get the initial Pomodoro Setting
        PomodoroControl_getMinuteArray(&sPomodoroProgress);

        // Check if the Worktime is over
        bool bWorktimeIsOver = false;
        PomodoroControl_isWorktimeOver(&sPomodoroProgress, &bWorktimeIsOver);
        LightEffects_RenderPomodoro(sPomodoroProgress.au8MinuteArray, TOTAL_MINUTES, bWorktimeIsOver);

        // Initialize and start the Countdown Timer
        Countdown_initTimerMs(&sTimerWtBtHandler, sPomodoroTimingCfg.u16TimerPeriodMin, E_OPERATIONAL_MODE_CONTIUNOUS);
        Countdown_resetAndStartTimer(&sTimerWtBtHandler);

        // Update the trigger event
        FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);

        // Reset the updated flag
        sPomodoroPeriodCfg.bConfigWasUpdated = false;
    }
    else
    {
        // Request the Pomodoro Configuration
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0401; // Request Pomodoro Configuration
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish: %d", eStatus);
        unused(eStatus); // Avoid compiler warning
    }
}

void StateActionWorktime(void)
{
    // Set the default trigger event
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_PENDING);

    // Check if the Worktime is over
    bool bWorktimeIsOver = false;
    PomodoroControl_isWorktimeOver(&sPomodoroProgress, &bWorktimeIsOver);

    // If Worktime is not over
    if (false == bWorktimeIsOver)
    {
        // If one Minute is over - only then run the code
        CountdownTimer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerWtBtHandler);
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
        sMsg.eMsgId = MSG_0201; // Pomodoro Work Time Sequence Complete
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish: %d", eStatus);
        unused(eStatus); // Avoid compiler warning
    }
}

void StateActionWarning(void)
{
    static bool bRunOnce = false;

    if (!bRunOnce)
    {
        // Set a new Timer Instance
        Countdown_initTimerMs(&sTimerWarningHandler, sPomodoroTimingCfg.u16TimerPeriodWarningMs, E_OPERATIONAL_MODE_CONTIUNOUS);
        Countdown_resetAndStartTimer(&sTimerWarningHandler);

        // Clear the Pomodoro Progress Rings
        LightEffects_ClearPomodoroProgressRings();

        // Set the initial config
        sRingCountdown.eEffect = E_RING_COUNTDOWN_EFFECT__WARNING;
        sRingCountdown.u8CurrentFillingMin = MINUTES_IN_HOUR;
        sRingCountdown.bIsComplete = false;

        LightEffects_RenderRingCountdown(&sRingCountdown);

        // Set the Flag
        bRunOnce = true;
    }

    // Set Trigger Event to Pending
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_PENDING);

    bool bWarningPeriodIsOver = sRingCountdown.bIsComplete;

    // If Warning Period is not over
    if (false == bWarningPeriodIsOver)
    {
        // If one Minute is over - only then run the code
        CountdownTimer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerWarningHandler);
        if (E_COUNTDOWN_TIMER_EXPIRED == sTimerStatus)
        {
            // Update the CFGs
            LightEffects_UpdateRingCountdown(&sRingCountdown);

            // Render the compressed Arrays on the Rings
            LightEffects_RenderRingCountdown(&sRingCountdown);
        }
    }
    else
    { // If Warning Period is over
      // Set Event -> Seq Complete
        FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);

        // Reset the flag
        bRunOnce = false;
    }
}

void StateActionBreaktimeInit(void)
{
    // Generate the updated Minute Array
    PomodoroControl_getMinuteArray(&sPomodoroProgress);

    // Render the compressed Arrays on the Rings
    LightEffects_RenderPomodoro(sPomodoroProgress.au8MinuteArray, TOTAL_MINUTES, true);

    // Set Trigger Event to Sequence Complete
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);
}

void StateActionBreaktime(void)
{
    // Set Trigger Event to Pending
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_PENDING);

    bool bBreaktimeIsOver = false;
    PomodoroControl_isBreaktimeOver(&sPomodoroProgress, &bBreaktimeIsOver);

    // If Breaktime is not over
    if (false == bBreaktimeIsOver)
    {
        // If one Minute is over - only then run the code
        CountdownTimer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerWtBtHandler);
        if (E_COUNTDOWN_TIMER_EXPIRED == sTimerStatus)
        {
            // Update the CFGs
            PomodoroControl_updateSequence(&sPomodoroProgress);

            // Generate the updated Minute Array
            PomodoroControl_getMinuteArray(&sPomodoroProgress);
        }
        // Render the compressed Arrays on the Rings
        LightEffects_RenderPomodoro(sPomodoroProgress.au8MinuteArray, TOTAL_MINUTES, true);
    }
    else
    { // If Breaktime is over
      // Set Event -> Seq Complete
        FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);

        // Publish Message: Breaktime Complete via the MsgBroker
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0202; // Pomodoro Break Time Sequence Complete
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish: %d", eStatus);
        unused(eStatus); // Avoid compiler warning

        // Clear the Progress Rings
        LightEffects_ClearPomodoroProgressRings();
    }
}

void StateActionCancelSequenceInit(void)
{
    // Set the Cancel Sequence Timer
    Countdown_initTimerMs(&sTimerCancelSeqHandler, sPomodoroTimingCfg.u16TimerPeriodCancelSeqMs, E_OPERATIONAL_MODE_CONTIUNOUS);
    Countdown_resetAndStartTimer(&sTimerCancelSeqHandler);

    // Start the timeout timer
    Countdown_initTimerMs(&sTimerCancelSeqTimeoutHandler, sPomodoroTimingCfg.u16TimerPeriodMin, E_OPERATIONAL_MODE_CONTIUNOUS);
    Countdown_resetAndStartTimer(&sTimerCancelSeqTimeoutHandler);

    // Clear all existing Progress LEDs
    LightEffects_ClearPomodoroProgressRings();

    // Set the initial config
    sRingCountdown.eEffect = E_RING_COUNTDOWN_EFFECT__CANCEL_SEQ;
    sRingCountdown.u8CurrentFillingMin = MINUTES_IN_HOUR;
    sRingCountdown.bIsComplete = false;

    // Render the initial config
    LightEffects_RenderRingCountdown(&sRingCountdown);

    // Set the Trigger Event to Sequence Complete
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);
}
void StateActionCancelSequenceRunning(void)
{
    // Set the Trigger Event to Pending
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_PENDING);

    // Check if the Cancel Sequence is over
    bool bCancelSequenceIsOver = sRingCountdown.bIsComplete;

    // If Cancel Sequence is not over
    if (false == bCancelSequenceIsOver)
    {
        // If one Minute is over - only then run the code
        CountdownTimer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerCancelSeqHandler);
        if (E_COUNTDOWN_TIMER_EXPIRED == sTimerStatus)
        {
            // Update the CFGs
            LightEffects_UpdateRingCountdown(&sRingCountdown);

            // Render the compressed Arrays on the Rings
            LightEffects_RenderRingCountdown(&sRingCountdown);
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

    LightEffects_RenderRingCountdown(&sRingCountdown);

    static uint8_t u8TimoutMinuteCounter = 0;
    CountdownTimer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerCancelSeqTimeoutHandler);
    if (E_COUNTDOWN_TIMER_EXPIRED == sTimerStatus)
    {
        u8TimoutMinuteCounter++;
    }

    if (u8TimoutMinuteCounter >= sPomodoroTimingCfg.u16TimeOutPeriodMin)
    {
        // Reset the Timeout Counter
        u8TimoutMinuteCounter = 0;
        FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE); // transitions to Idle

        // Clear the Progress Rings
        LightEffects_ClearPomodoroProgressRings();
    }
}

void StateActionSnooze(void)
{
    static bool bRunOnce = false;

    // Set Trigger Event to Pending
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_PENDING);

    if (!bRunOnce)
    {

        // Set a new Timer Instance
        Countdown_initTimerMs(&sTimerSnoozeHandler, sPomodoroTimingCfg.u16TimerPeriodSnoozeMs, E_OPERATIONAL_MODE_CONTIUNOUS);
        Countdown_resetAndStartTimer(&sTimerSnoozeHandler);

        // Clear the Pomodoro Progress Rings
        LightEffects_ClearPomodoroProgressRings();

        // Set the initial config
        sRingCountdown.eEffect = E_RING_COUNTDOWN_EFFECT__SNOOZE;
        sRingCountdown.u8CurrentFillingMin = MINUTES_IN_HOUR;
        sRingCountdown.bIsComplete = false;

        LightEffects_RenderRingCountdown(&sRingCountdown);

        // Set the Flag
        bRunOnce = true;
    }

    bool bSnoozePeriodIsOver = sRingCountdown.bIsComplete;

    // If Warning Period is not over
    if (false == bSnoozePeriodIsOver)
    {
        // If one Minute is over - only then run the code
        CountdownTimer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimerSnoozeHandler);
        if (E_COUNTDOWN_TIMER_EXPIRED == sTimerStatus)
        {
            // Update the CFGs
            LightEffects_UpdateRingCountdown(&sRingCountdown);

            // Render the compressed Arrays on the Rings
            LightEffects_RenderRingCountdown(&sRingCountdown);
        }
    }
    else
    { // If Warning Period is over
      // Set Event -> Seq Complete
        FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);

        // Reset the flag
        bRunOnce = false;
    }
}

void StateActionCleanUp(void)
{
    // Set the Trigger Event to Pending
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_PENDING);

    // Clear the Progress Rings
    LightEffects_ClearPomodoroProgressRings();

    // Publish the Pomodoro Sequence Complete Message
    msg_t sMsg = {0};
    sMsg.eMsgId = MSG_0204; // Pomodoro Sequence Complete
    status_e eStatus = MessageBroker_publish(&sMsg);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish: %d", eStatus);
    unused(eStatus); // Avoid compiler warning

    // Stop the Countdown Timer
    Countdown_stopTimer(&sTimerCancelSeqTimeoutHandler);

    // Reset the Pomodoro Timestamps for Worktime and Breaktime
    sPomodoroProgress.u8Worktime = sPomodoroPeriodCfg.u8MinutesWorktimePeriod;
    sPomodoroProgress.u8Breaktime = sPomodoroPeriodCfg.u8MinutesBreaktimePeriod;
    // Reset the Progress Array
    for (uint8_t i = 0; i < TOTAL_MINUTES; i++)
    {
        sPomodoroProgress.au8MinuteArray[i] = 0;
    }

    // Set the Sequence to Complete
    FSM_setTriggerEvent(&sFsmConfig, EVENT_SEQUENCE_COMPLETE);
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

void PomodoroControl_getMinuteArray(PCTRL_Progress_t *const inout_sSelf)
{
    { // Input checks
      // Check against NULL Pointers
        ASSERT_MSG(!(NULL == inout_sSelf), "NULL Pointer");

        // Make sure that the Worktime is smaller then 121
        ASSERT_MSG(!(inout_sSelf->u8Worktime > TOTAL_MINUTES), "Worktime is bigger then 120, Worktime is %d", inout_sSelf->u8Worktime);

        // Make sure that the Breaktime is smaller then 61
        ASSERT_MSG(!(inout_sSelf->u8Breaktime > MINUTES_IN_HOUR), "Breaktime is bigger then 60, Breaktime is %d", inout_sSelf->u8Breaktime);
    }

    // Just for extra safety to make sure that the original config is not changed
    uint8_t u8LocalCopyWortime = inout_sSelf->u8Worktime;
    uint8_t u8LocalCopyBreaktime = inout_sSelf->u8Breaktime;

    int8_t i8CurrentWorktime = (int8_t)inout_sSelf->u8Worktime;
    int8_t i8CurrentBreaktime = (int8_t)inout_sSelf->u8Breaktime;

    uint8_t u8Sum = i8CurrentWorktime + i8CurrentBreaktime;

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

    if (u8Sum > LEDS_PER_RING)
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
    unused(u8LocalCopyWortime); // Avoid compiler warning
    ASSERT_MSG(!(u8LocalCopyBreaktime != inout_sSelf->u8Breaktime), "Breaktime has changed");
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

STATIC void PomodoroControl_isWorktimeOver(PCTRL_Progress_t *const inout_sSelf, bool *const out_bIsWorktimeOver)
{
    {
        // Input Checks
        ASSERT_MSG(!(NULL == inout_sSelf), "NULL Pointer");
        ASSERT_MSG(!(NULL == out_bIsWorktimeOver), "NULL Pointer");
    }

    // Number Check
    bool bNumberCheck = false;
    if (inout_sSelf->u8Worktime == 0)
    {
        bNumberCheck = true;
    }

    // Iterate through the Array and check again - there must be no discrepancy
    bool bArrayCheck = true;
    for (uint8_t i = 0; i < TOTAL_MINUTES; i++)
    {
        if (inout_sSelf->au8MinuteArray[i] == E_CFG_WORKTIME)
        {
            bArrayCheck = false;
            break;
        }
    }

    ASSERT_MSG(!(bNumberCheck != bArrayCheck), "Number Check and Array Check are not equal");

    *out_bIsWorktimeOver = bNumberCheck;
    unused(bArrayCheck); // Avoid compiler warning
}

STATIC void PomodoroControl_isBreaktimeOver(PCTRL_Progress_t *const inout_sSelf, bool *const out_bIsBreaktimeOver)
{
    {
        // Input Checks
        ASSERT_MSG(!(NULL == inout_sSelf), "NULL Pointer");
        ASSERT_MSG(!(NULL == out_bIsBreaktimeOver), "NULL Pointer");
    }

    // Number Check
    bool bNumberCheck = false;
    if (inout_sSelf->u8Breaktime == 0)
    {
        bNumberCheck = true;
    }

    // Iterate through the Array and check again - there must be no discrepancy
    bool bArrayCheck = true;
    for (uint8_t i = 0; i < TOTAL_MINUTES; i++)
    {
        if (inout_sSelf->au8MinuteArray[i] == E_CFG_BREAKTIME)
        {
            bArrayCheck = false;
            break;
        }
    }

    ASSERT_MSG(!(bNumberCheck != bArrayCheck), "Number Check and Array Check are not equal");

    *out_bIsBreaktimeOver = bNumberCheck;
    unused(bArrayCheck); // Avoid compiler warning
}

STATIC status_e PomodoroControl_MessageCallback(const msg_t *const psMsg)
{
    { // Input Verification
        ASSERT_MSG(!(psMsg == NULL), "Message is NULL!");
        if (psMsg == NULL)
        {
            return STATUS_ERROR;
        }
    }

    switch (psMsg->eMsgId)
    {
    case MSG_0200: // Pomodoro Sequence Start Event
    {
        /**
         * Keep this log statement in here. The reason being that the current
         * implementation requires the small delay which is introduced by the statement
         * to properly render the RgbLeds.
         * It is not pretty but for the moment works, until a better solution is found.
         * (Basically the RGBLED driver needs to be rewritten).
         */
        log_info("Pomodoro Sequence Start Event received - On we go");
        FSM_setTriggerEvent(&sFsmConfig, EVENT_POMODORO_SEQUENCE_START);
    }
    break;

    case MSG_0103: // Button Event
    {
        ButtonMessage_s *psButtonMsg = (ButtonMessage_s *)psMsg->au8DataBytes;
        if (psButtonMsg->eButton == E_BTN_TRIGGER)
        {
            if (psButtonMsg->eEvent == E_BTN_EVENT_LONG_PRESSED)
            {
                FSM_setTriggerEvent(&sFsmConfig, EVENT_TRIGGER_BTN_LONG_PRESS);
            }

            if (psButtonMsg->eEvent == E_BTN_EVENT_RELEASED)
            {
                FSM_setTriggerEvent(&sFsmConfig, EVENT_TRIGGER_BTN_RELEASED);
            }
        }
        // else if (psButtonMsg->eButton == E_BTN_ENCODER)
        // {
        //     if (psButtonMsg->eEvent == E_BTN_EVENT_RELEASED)
        //     {
        //         log_info("Encoder Button Released");
        //         FSM_setTriggerEvent(&sFsmConfig, EVENT_TRIGGER_BTN_SHORT_PRESS);
        //     }
        // }
    }
    break;

    case MSG_0400: // Pomodoro Configuration: Worktime and Breaktime
                   // Periods
    {
        // Get the Pomodoro Configuration
        PomodoroPeriodConfiguration_s *psPomodoroConfig = (PomodoroPeriodConfiguration_s *)psMsg->au8DataBytes;
        sPomodoroProgress.u8Worktime = psPomodoroConfig->u8MinutesWorktimePeriod;
        sPomodoroProgress.u8Breaktime = psPomodoroConfig->u8MinutesBreaktimePeriod;

        // Update the Period Configuration -> Needed in the CleanUp State
        sPomodoroPeriodCfg.u8MinutesWorktimePeriod = psPomodoroConfig->u8MinutesWorktimePeriod;
        sPomodoroPeriodCfg.u8MinutesBreaktimePeriod = psPomodoroConfig->u8MinutesBreaktimePeriod;
        sPomodoroPeriodCfg.bConfigWasUpdated = psPomodoroConfig->bConfigWasUpdated;
    }
    break;

    case MSG_0004:
    {
        // Parse the Pomodoro Timing Configuration
        TestData_0004_s *psTestPomodoroTimingCfg = (TestData_0004_s *)psMsg->au8DataBytes;

        // Update the Timing Configuration
        sPomodoroTimingCfg.u16TimeOutPeriodMin = psTestPomodoroTimingCfg->u16TimeOutPeriodMin;
        sPomodoroTimingCfg.u16TimerPeriodMin = psTestPomodoroTimingCfg->u16TimerPeriodMin;
        sPomodoroTimingCfg.u16TimerPeriodSnoozeMs = psTestPomodoroTimingCfg->u16TimerPeriodSnoozeMs;
        sPomodoroTimingCfg.u16TimerPeriodCancelSeqMs = psTestPomodoroTimingCfg->u16TimerPeriodCancelSeqMs;
        sPomodoroTimingCfg.u16TimerPeriodWarningMs = psTestPomodoroTimingCfg->u16TimerPeriodWarningMs;
    }
    break;

    default:
    {
        ASSERT_MSG(false,
                   "This Callback should not be called for this message, but it "
                   "was with the following message ID: %d",
                   psMsg->eMsgId);
        return STATUS_ERROR;
    }
    break;
    }

    return STATUS_OK;
}

void PomodoroControl_init(void)
{
    // Subscribe to Messages
    status_e eStatus = STATUS_OK;
    eStatus = MessageBroker_subscribe(MSG_0004, PomodoroControl_MessageCallback);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe: %d", eStatus);

    eStatus = MessageBroker_subscribe(MSG_0103, PomodoroControl_MessageCallback);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe: %d", eStatus);

    eStatus = MessageBroker_subscribe(MSG_0200, PomodoroControl_MessageCallback);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe: %d", eStatus);

    eStatus = MessageBroker_subscribe(MSG_0400, PomodoroControl_MessageCallback);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe: %d", eStatus);

    unused(eStatus); // Avoid compiler warning

    // Initialize the Pomodoro Timing Configuration
    sPomodoroTimingCfg.u16TimerPeriodMin = TIMER_PERIOD_MIN;
    sPomodoroTimingCfg.u16TimerPeriodSec = TIMER_PERIOD_SEC;
    sPomodoroTimingCfg.u16TimerPeriodSnoozeMs = TIMER_PERIOD_SNOOZE_MS;
    sPomodoroTimingCfg.u16TimerPeriodCancelSeqMs = TIMER_PERIOD_CANCEL_SEQ_MS;
    sPomodoroTimingCfg.u16TimerPeriodWarningMs = TIMER_PERIOD_WARNING_MS;
    sPomodoroTimingCfg.u16TimeOutPeriodMin = TIMEOUT_PERIOD_MIN;
}

status_e PomodoroControl_execute(void)
{
    status_e eStatus = STATUS_OK;
    FSM_execute(&sFsmConfig);

    return eStatus;
}
