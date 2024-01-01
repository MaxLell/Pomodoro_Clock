#include "PomodoroControl.h"

#include "Common.h"
#include "FSM.h"
#include "LightEffects.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "PomodoroControl_Datatypes.h"
#include "PomodoroStateActions.h"

/********************************************************
 * Private Variables
 ********************************************************/

STATIC PomodoroControl_internalStatus_t sInternalState = {0};

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
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_WORKTIME_INIT,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_WORKTIME_INIT,
            [EVENT_SEQUENCE_COMPLETE] = STATE_WORKTIME,
            [EVENT_SEQUENCE_PENDING] = STATE_WORKTIME_INIT,
        },
    // Current State
    [STATE_WORKTIME] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_WORKTIME,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_RUNNING,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_WORKTIME,
            [EVENT_SEQUENCE_COMPLETE] = STATE_WARNING,
            [EVENT_SEQUENCE_PENDING] = STATE_WORKTIME,
        },
    // Current State
    [STATE_WARNING] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_WARNING,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_WARNING,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_WARNING,
            [EVENT_SEQUENCE_COMPLETE] = STATE_BREAKTIME_INIT,
            [EVENT_SEQUENCE_PENDING] = STATE_WARNING,
        },
    // Current State
    [STATE_BREAKTIME_INIT] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_BREAKTIME_INIT,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_BREAKTIME_INIT,
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_BREAKTIME_INIT,
            [EVENT_SEQUENCE_COMPLETE] = STATE_BREAKTIME,
            [EVENT_SEQUENCE_PENDING] = STATE_BREAKTIME_INIT,
        },
    // Current State
    [STATE_BREAKTIME] =
        {
            // Event -----------> Next State
            [EVENT_POMODORO_SEQUENCE_START] = STATE_BREAKTIME,
            [EVENT_TRIGGER_BTN_LONG_PRESS] = STATE_CANCEL_SEQUENCE_RUNNING,
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
            [EVENT_TRIGGER_BTN_RELEASED] = STATE_IDLE,
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
            [EVENT_SEQUENCE_COMPLETE] = STATE_CANCEL_SEQUENCE_HALTED,
            [EVENT_SEQUENCE_PENDING] = STATE_CANCEL_SEQUENCE_HALTED,
        },
};

void StateActionIdle(void) {}
void StateActionWorktimeInit(void) {}
void StateActionWorktime(void) {}
void StateActionWarning(void) {}
void StateActionBreaktimeInit(void) {}
void StateActionBreaktime(void) {}
void StateActionCancelSequenceRunning(void) {}
void StateActionCancelSequenceHalted(void) {}

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
    [STATE_CANCEL_SEQUENCE_RUNNING] = StateActionCancelSequenceRunning,
    [STATE_CANCEL_SEQUENCE_HALTED] = StateActionCancelSequenceHalted,
};

/**
 * FSM Initial Configuration
 */
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
      FSM_setTriggerEvent(&sFsmConfig, EVENT_POMODORO_SEQUENCE_START);
    } break;

    case MSG_ID_0101:  // Trigger Button: is Pressed Down Continuously
    {
    } break;

    case MSG_ID_0102:  // Trigger Button: is Released after a Long Press
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

status_e PomodoroControl_execute(void) {
  status_e eStatus = STATUS_SUCCESS;
  FSM_execute(&sFsmConfig);
  return eStatus;
}