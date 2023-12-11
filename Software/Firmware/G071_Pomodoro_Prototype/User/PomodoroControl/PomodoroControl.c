#include "PomodoroControl.h"

#include "MessageBroker.h"
#include "PomodoroControl_Datatypes.h"
#include "PomodoroControl_StateFunctions.h"

/********************************************************
 * Private Variables
 ********************************************************/

STATIC PomodoroControl_internalStatus_t sInternalState;
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
    case POMDOORO_CONTROL_STATE__IDLE:
      if (sInternalState.bStartPomodoroEventReceived) {
        // Update the state
        eState = POMODORO_CONTROL_STATE__STARTING_SEQUENCE;

        // Reset the internal state of this state
        sInternalState.bStartPomodoroEventReceived = FALSE;
      } else {
        // Do nothing and wait
      }
      break;

    case POMODORO_CONTROL_STATE__WORKTIME:
      // when the state function return SUCCESS, then update the state to the
      // Warning State
      //   PomodoroControl_StateFn_status_t eFnStatus =
      //       PomodoroControl_StateFn_StartingSequence();
      //   if (eFnStatus == POMODORO_CONTROL_STATE_FN_STATE__SUCCESS) {
      //     eState = POMODORO_CONTROL_STATE__WARNING;
      //   } else if (eFnStatus == POMODORO_CONTROL_STATE_FN_STATE__ERROR) {
      //     ASSERT_MSG(FALSE, "Error in the State Function");
      //     return STATUS_ERROR;
      //   } else {  // POMODORO_CONTROL_STATE_FN_STATE__PENDING
      //     // Do nothing and wait
      //   }
      //   // when the sInternalState indicates that the Trigger was pressed
      //   // continously, then update the state to the Cancel State
      //   if (sInternalState.bTriggerButtonIsPressedContinuously) {
      //     eState = POMODORO_CONTROL_STATE__CANCEL;
      //   }
      break;

    case POMODORO_CONTROL_STATE__WARNING:
      break;

    case POMODORO_CONTROL_STATE__BREAKTIME:
      break;

    case POMODORO_CONTROL_STATE__CANCEL:
      break;
    default:
      break;
  }
  return STATUS_OK;
}