#include "StandbyControl.h"

#include "Common.h"
#include "CountdownTimer.h"
#include "LightEffects.h"
#include "MessageBroker.h"
#include "StandbyControl_Datatypes.h"

/**********************************************************************
 * static local variables
 **********************************************************************/
STATIC BOOL bTriggerButtonPressed = FALSE;
STATIC BOOL bPomodoroSequenceComplete = FALSE;

#define DELAY_FOR_SEEKING_ATTENTION 17000U

STATIC StandbyControl_state_t eState;

/**********************************************************************
 * static local function prototypes
 **********************************************************************/

STATIC StandbyControl_SequenceStatus_e StandbyControl_IdleStateCb(void);
STATIC StandbyControl_SequenceStatus_e
StandbyControl_SeekingAttentionStateCb(void);
/**********************************************************************
 * Message Callbacks
 **********************************************************************/
status_t StandbyControl_TriggerBtnPressedCB(msg_t in_sMessage) {
  bTriggerButtonPressed = TRUE;
  return STATUS_OK;
}

status_t StandbyControl_PomodoroSequenceCompleteCB(msg_t in_sMessage) {
  bPomodoroSequenceComplete = TRUE;
  return STATUS_OK;
}

/**********************************************************************
 * Private functions
 **********************************************************************/

STATIC StandbyControl_SequenceStatus_e
StandbyControl_SeekingAttentionStateCb(void) {
  /**
   * Wait for the animation to complete. Only then
   * return E_STANDBY_STATUS_SEQUENCE_COMPLETE otherwise
   * return E_STANDBY_STATUS_SEQUENCE_INCOMPLETE
   */
  LightEffects_SequenceStatus_e eSequenceStatus;
  LightEffects_DotAroundTheCircle(&eSequenceStatus, 100U);
  if (E_LIGHT_EFFECTS_STATUS_SEQUENCE_COMPLETE == eSequenceStatus) {
    return E_STANDBY_STATUS_SEQUENCE_COMPLETE;
  } else {
    return E_STANDBY_STATUS_SEQUENCE_INCOMPLETE;
  }
}

StandbyControl_SequenceStatus_e StandbyControl_IdleStateCb(void) {
  // Get Timer status
  static timer_t sTimer;
  timer_status_t tTimerStatus = Countdown_getTimerStatus(&sTimer);
  if (TIMER_NOT_ENABLED == tTimerStatus) {
    // Init Timer
    Countdown_initTimer(&sTimer, DELAY_FOR_SEEKING_ATTENTION, ONE_SHOT_MODE);

    // Start Timer
    Countdown_startTimer(&sTimer);
  } else if (TIMER_EXPIRED == tTimerStatus) {
    return E_STANDBY_STATUS_SEQUENCE_COMPLETE;
  }
  return E_STANDBY_STATUS_SEQUENCE_INCOMPLETE;
}

/**********************************************************************
 * Public Functions
 **********************************************************************/

void StandbyControl_init(void) {
  // Subscribe to the Trigger Button Pressed Event
  status_t tStatus =
      MessageBroker_subscribe(MSG_ID_0100, StandbyControl_TriggerBtnPressedCB);
  ASSERT_MSG(!(tStatus != STATUS_OK),
             "MessageBroker_subscribe() failed with error code: %d", tStatus);

  // Subscribe to the Pomodoro Sequence Complete Event
  tStatus = MessageBroker_subscribe(MSG_ID_0200,
                                    StandbyControl_PomodoroSequenceCompleteCB);

  ASSERT_MSG(!(tStatus != STATUS_OK),
             "MessageBroker_subscribe() failed with "
             "error code: %d",
             tStatus);

  // Set the initial state
  eState = E_STANDBY_STATE_IDLE;
}

void StandbyControl_execute() {
  StandbyControl_SequenceStatus_e eStateExecutionIsComplete =
      STATE_EXECUTION_INCOMPLETE;

  switch (eState) {
    case E_STANDBY_STATE_IDLE:
      if (bTriggerButtonPressed == TRUE) {
        bTriggerButtonPressed = FALSE;
        eState = E_STANDBY_STATE_POMODORO;
        break;
      }

      eStateExecutionIsComplete = StandbyControl_IdleStateCb();
      if (E_STANDBY_STATUS_SEQUENCE_COMPLETE == eStateExecutionIsComplete) {
        eState = E_STANDBY_STATE_SEEKING_ATTENTION;
        break;
      }
      break;

    case E_STANDBY_STATE_SEEKING_ATTENTION:
      if (bTriggerButtonPressed == TRUE) {
        bTriggerButtonPressed = FALSE;
        eState = E_STANDBY_STATE_POMODORO;

        // Publish the Pomodoro Sequence Start Event
        msg_t sMessage;
        sMessage.eMsgId = MSG_ID_0200;
        sMessage.au8DataBytes = NULL;
        sMessage.u16DataSize = 0U;
        status_t eStatus = MessageBroker_publish(sMessage);
        ASSERT_MSG(!(eStatus != STATUS_OK),
                   "MessageBroker_publish() failed with error code: %d",
                   eStatus);
        break;
      }
      eStateExecutionIsComplete = StandbyControl_SeekingAttentionStateCb();

      if (E_STANDBY_STATUS_SEQUENCE_COMPLETE == eStateExecutionIsComplete) {
        eState = E_STANDBY_STATE_IDLE;
        break;
      }
      break;

    case E_STANDBY_STATE_POMODORO:
      if (bPomodoroSequenceComplete == TRUE) {
        bPomodoroSequenceComplete = FALSE;
        eState = E_STANDBY_STATE_IDLE;
        break;
      }
      break;

    default:
      ASSERT_MSG(FALSE, "Invalid State");
      break;
  }
}
