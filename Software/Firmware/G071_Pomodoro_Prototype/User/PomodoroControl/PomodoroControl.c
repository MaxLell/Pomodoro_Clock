#include "PomodoroControl.h"

#include "Common.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "PomodoroControl_Datatypes.h"
#include "PomodoroControl_StateFunctions.h"
#include "RealTimeClock_Datatypes.h"

/********************************************************
 * Private Variables
 ********************************************************/

STATIC PomodoroControl_internalStatus_t sInternalState = {0};
STATIC PomodoroControl_State_t eState;

/********************************************************
 * Function Prototypes
 ********************************************************/

/**
 * Message Callback
 */

STATIC status_t PomodoroControl_MessageCallback(msg_t sMsg);

/********************************************************
 * Implementation
 ********************************************************/

STATIC status_t PomodoroControl_MessageCallback(msg_t sMsg) {
  switch (sMsg.eMsgId) {
    case MSG_ID_0200:  // Pomodoro Sequence Start Event
      sInternalState.bStartPomodoroEventReceived = TRUE;
      break;

    case MSG_ID_0101:  // Trigger Button: is Pressed Down Continuously
      sInternalState.bTriggerButtonIsPressedContinuously =
          (BOOL)*sMsg.au8DataBytes;
      break;

    case MSG_ID_0102:  // Trigger Button: is Released
      sInternalState.bTriggerButtonIsReleased = (BOOL)*sMsg.au8DataBytes;
      sInternalState.bTriggerButtonIsPressedContinuously = FALSE;
      break;

    case MSG_ID_0300:  // Current time Tick from the RTC
                       // Parse out the current minute from the message struct
      sInternalState.u8CurrentMinuteOfTheHour =
          ((TimeAndDate_t *)sMsg.au8DataBytes)->u8Minute;
      break;

    case MSG_ID_0400:  // Pomodoro Configuration: Worktime and Breaktime Periods
      sInternalState.u8WorktimePeriodMin =
          ((PomodoroPeriodConfiguration_t *)sMsg.au8DataBytes)
              ->u8WorktimePeriodMin;
      sInternalState.u8BreaktimePeriodMin =
          ((PomodoroPeriodConfiguration_t *)sMsg.au8DataBytes)
              ->u8BreaktimePeriodMin;
      break;

    default:
      ASSERT_MSG(FALSE,
                 "This Callback should not be called for this message, but it "
                 "was with the following message ID: %d",
                 sMsg.eMsgId);
      return STATUS_ERROR;
      break;
  }
  return STATUS_OK;
}

void PomodoroControl_init(void) {
  // Set up the initial internal state
  sInternalState.bStartPomodoroEventReceived = FALSE;

  // Set the starting state
  eState = POMDOORO_CONTROL_STATE__IDLE;

  // Subscribe to Messages
  status_t eStatus = STATUS_OK;
  eStatus =
      MessageBroker_subscribe(MSG_ID_0200, PomodoroControl_MessageCallback);
  eStatus =
      MessageBroker_subscribe(MSG_ID_0101, PomodoroControl_MessageCallback);
  ASSERT_MSG(!(eStatus == STATUS_ERROR), "Error in MessageBroker_subscribe");
}

status_t PomodoroControl_execute(void) {
  switch (eState) {
    case POMDOORO_CONTROL_STATE__IDLE: {
      if (TRUE == sInternalState.bStartPomodoroEventReceived) {
        // Update the state
        eState = POMODORO_CONTROL_STATE__STARTING_SEQUENCE;
        // Reset the internal state of this state
        sInternalState.bStartPomodoroEventReceived = FALSE;
      } else {
        // Do nothing and wait
      }
    } break;

    case POMODORO_CONTROL_STATE__STARTING_SEQUENCE: {
      // Call the State function
      PomodoroControl_StateFn_status_t eFnStatus =
          PomodoroControl_StateFn_StartingSequence(
              sInternalState.u8CurrentMinuteOfTheHour,
              sInternalState.u8WorktimePeriodMin,
              sInternalState.u8BreaktimePeriodMin);

      // Update the state - if necessary
      if (eFnStatus == POMODORO_CONTROL_STATE_FN_STATE__SUCCESS) {
        eState = POMODORO_CONTROL_STATE__WORKTIME;
      } else if (eFnStatus == POMODORO_CONTROL_STATE_FN_STATE__ERROR) {
        ASSERT_MSG(FALSE, "Error in the State Function");
        return STATUS_ERROR;
      } else {  // POMODORO_CONTROL_STATE_FN_STATE__PENDING
        // Do nothing and wait
      }
    } break;

    case POMODORO_CONTROL_STATE__WORKTIME: {
      // Call the State function
      PomodoroControl_StateFn_status_t eFnStatus =
          PomodoroControl_StateFn_WorkTime(
              sInternalState.u8CurrentMinuteOfTheHour);

      // Update the state - if necessary
      if (eFnStatus == POMODORO_CONTROL_STATE_FN_STATE__SUCCESS) {
        eState = POMODORO_CONTROL_STATE__WARNING;
      } else if (eFnStatus == POMODORO_CONTROL_STATE_FN_STATE__ERROR) {
        ASSERT_MSG(FALSE, "Error in the State Function");
        return STATUS_ERROR;
      } else {  // POMODORO_CONTROL_STATE_FN_STATE__PENDING
        // Do nothing and wait
      }
    } break;

    case POMODORO_CONTROL_STATE__WARNING: {
      // Call the State function
      PomodoroControl_StateFn_status_t eFnStatus =
          PomodoroControl_StateFn_Warning();

      // Update the state - if necessary
      if (eFnStatus == POMODORO_CONTROL_STATE_FN_STATE__SUCCESS) {
        eState = POMODORO_CONTROL_STATE__BREAKTIME;
      } else if (eFnStatus == POMODORO_CONTROL_STATE_FN_STATE__ERROR) {
        ASSERT_MSG(FALSE, "Error in the State Function");
        return STATUS_ERROR;
      } else {  // POMODORO_CONTROL_STATE_FN_STATE__PENDING
        // Do nothing and wait
      }
    } break;
    case POMODORO_CONTROL_STATE__BREAKTIME: {
      // Call the State function
      PomodoroControl_StateFn_status_t eFnStatus =
          PomodoroControl_StateFn_BreakTime();

      // Update the state - if necessary
      if (eFnStatus == POMODORO_CONTROL_STATE_FN_STATE__SUCCESS) {
        eState = POMDOORO_CONTROL_STATE__IDLE;
      } else if (eFnStatus == POMODORO_CONTROL_STATE_FN_STATE__ERROR) {
        ASSERT_MSG(FALSE, "Error in the State Function");
        return STATUS_ERROR;
      } else {  // POMODORO_CONTROL_STATE_FN_STATE__PENDING
        // Do nothing and wait
      }
    }

    break;

    case POMODORO_CONTROL_STATE__CANCEL_SEQUENCE:
      break;
    default:
      break;
  }
  return STATUS_OK;
}