#include "PomodoroControl.h"

#include "Common.h"
#include "FSM.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "PomodoroControl_Datatypes.h"
#include "PomodoroControl_StateFunctions.h"

/********************************************************
 * Private Variables
 ********************************************************/

STATIC PomodoroControl_internalStatus_t sInternalState = {0};

/********************************************************
 * FSM Setup
 ********************************************************/

STATIC const uint16_t au16FsmTransitionMatrix[STATE_LAST][EVENT_LAST] = {
    // Current State
    [STATE_IDLE] =
        {
            // Event -----------> Next State
            [EVENT_TRIGGER_BTN_PRESSED] = STATE_WORKTIME_INIT,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_IDLE,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_IDLE,
            [EVENT_SEQUENCE_COMPLETE] = STATE_IDLE,
            [EVENT_SEQUENCE_PENDING] = STATE_IDLE,
        },
    // Current State
    [STATE_WORKTIME_INIT] =
        {
            // Event -----------> Next State
            [EVENT_TRIGGER_BTN_PRESSED] = STATE_WORKTIME_INIT,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_WORKTIME_INIT,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_WORKTIME_INIT,
            [EVENT_SEQUENCE_COMPLETE] = STATE_WORKTIME,
            [EVENT_SEQUENCE_PENDING] = STATE_WORKTIME_INIT,
        },
    // Current State
    [STATE_WORKTIME] =
        {
            // Event -----------> Next State
            [EVENT_TRIGGER_BTN_PRESSED] = STATE_WORKTIME,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_RUNNING,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_WORKTIME,
            [EVENT_SEQUENCE_COMPLETE] = STATE_WARNING,
            [EVENT_SEQUENCE_PENDING] = STATE_WORKTIME,
        },
    // Current State
    [STATE_WARNING] =
        {
            // Event -----------> Next State
            [EVENT_TRIGGER_BTN_PRESSED] = STATE_WARNING,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_WARNING,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_WARNING,
            [EVENT_SEQUENCE_COMPLETE] = STATE_BREAKTIME_INIT,
            [EVENT_SEQUENCE_PENDING] = STATE_WARNING,
        },
    // Current State
    [STATE_BREAKTIME_INIT] =
        {
            // Event -----------> Next State
            [EVENT_TRIGGER_BTN_PRESSED] = STATE_BREAKTIME_INIT,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_BREAKTIME_INIT,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_BREAKTIME_INIT,
            [EVENT_SEQUENCE_COMPLETE] = STATE_BREAKTIME,
            [EVENT_SEQUENCE_PENDING] = STATE_BREAKTIME_INIT,
        },
    // Current State
    [STATE_BREAKTIME] =
        {
            // Event -----------> Next State
            [EVENT_TRIGGER_BTN_PRESSED] = STATE_BREAKTIME,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_RUNNING,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_BREAKTIME,
            [EVENT_SEQUENCE_COMPLETE] = STATE_IDLE,
            [EVENT_SEQUENCE_PENDING] = STATE_BREAKTIME,
        },
    // Current State
    [STATE_CANCEL_SEQUENCE_RUNNING] =
        {
            // Event ----------------------> Next State
            [EVENT_TRIGGER_BTN_PRESSED] = STATE_CANCEL_SEQUENCE_RUNNING,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_RUNNING,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_IDLE,
            [EVENT_SEQUENCE_COMPLETE] = STATE_IDLE,
            [EVENT_SEQUENCE_PENDING] = STATE_CANCEL_SEQUENCE_RUNNING,
        },
    // Current State
    [STATE_CANCEL_SEQUENCE_HALTED] =
        {
            // Event ----------------------> Next State
            [EVENT_TRIGGER_BTN_PRESSED] = STATE_CANCEL_SEQUENCE_HALTED,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_RUNNING,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_CANCEL_SEQUENCE_HALTED,
            [EVENT_SEQUENCE_COMPLETE] = STATE_CANCEL_SEQUENCE_HALTED,
            [EVENT_SEQUENCE_PENDING] = STATE_CANCEL_SEQUENCE_HALTED,
        },
};

STATIC void StateActionIdle(void) {}
STATIC void StateActionWorktimeInit(void) {}
STATIC void StateActionWorktime(void) {}
STATIC void StateActionWarning(void) {}
STATIC void StateActionBreaktimeInit(void) {}
STATIC void StateActionBreaktime(void) {}
STATIC void StateActionCancelSequenceRunning(void) {}
STATIC void StateActionCancelSequenceHalted(void) {}

STATIC const FSM_StateActionCb aStateActions[] = {
    [STATE_IDLE] = StateActionIdle,
    [STATE_WORKTIME_INIT] = StateActionWorktimeInit,
    [STATE_WORKTIME] = StateActionWorktime,
    [STATE_WARNING] = StateActionWarning,
    [STATE_BREAKTIME_INIT] = StateActionBreaktimeInit,
    [STATE_BREAKTIME] = StateActionBreaktime,
    [STATE_CANCEL_SEQUENCE_RUNNING] = StateActionCancelSequenceRunning,
    [STATE_CANCEL_SEQUENCE_HALTED] = StateActionCancelSequenceHalted,
};

STATIC FSM_Config_t sFsmConfig = {
    .NUMBER_OF_STATES = STATE_LAST,
    .NUMBER_OF_EVENTS = EVENT_LAST,
    .au16TransitionMatrix = (uint16_t*)&au16FsmTransitionMatrix,
    .asStateActions = aStateActions,
    .u16CurrentState = STATE_IDLE,
    .u16CurrentEvent = EVENT_SEQUENCE_PENDING,
};

/********************************************************
 * Function Prototypes
 ********************************************************/

/**
 * Message Callback
 */

STATIC status_e PomodoroControl_MessageCallback(msg_t sMsg);

/********************************************************
 * Implementation
 ********************************************************/

STATIC status_e PomodoroControl_MessageCallback(msg_t sMsg) {
  status_e eStatus = STATUS_SUCCESS;
  switch (sMsg.eMsgId) {
    case MSG_ID_0200:  // Pomodoro Sequence Start Event
    {
      FSM_setTriggerEvent(&sFsmConfig, EVENT_TRIGGER_BTN_PRESSED);
    } break;

    case MSG_ID_0101:  // Trigger Button: is Pressed Down Continuously
    {
    } break;

    case MSG_ID_0102:  // Trigger Button: is Released
    {
    } break;

    case MSG_ID_0400:  // Pomodoro Configuration: Worktime and Breaktime Periods
    {
      sInternalState.u8MinutesWorktimePeriod =
          ((PomodoroPeriodConfiguration_t*)sMsg.au8DataBytes)
              ->u8MinutesWorktimePeriod;
      sInternalState.u8MinutesBreaktimePeriod =
          ((PomodoroPeriodConfiguration_t*)sMsg.au8DataBytes)
              ->u8MinutesBreaktimePeriod;
    } break;

    default:
      ASSERT_MSG(FALSE,
                 "This Callback should not be called for this message, but it "
                 "was with the following message ID: %d",
                 sMsg.eMsgId);
      eStatus = STATUS_ERROR;
      break;
  }
  return eStatus;
}

void PomodoroControl_init(void) {
  // Subscribe to Messages

  // Reset the internal Data Structure
}

status_e PomodoroControl_execute(void) {}