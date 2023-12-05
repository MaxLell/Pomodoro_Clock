#include "StandbyControl.h"

#include "Common.h"
#include "CountdownTimer.h"
#include "MessageBroker.h"

/**********************************************************************
 * static local variables
 **********************************************************************/
STATIC BOOL bTriggerButtonPressed = FALSE;

#define DELAY_FOR_SEEKING_ATTENTION 17000U
#define STATE_EXECUTION_COMPLETE TRUE
#define STATE_EXECUTION_INCOMPLETE FALSE

typedef enum {
  E_STANDBY_STATE_IDLE = 0U,
  E_STANDBY_STATE_SEEKING_ATTENTION = 1U,
  E_STANDBY_STATE_POMODORO = 2U
} StandbyControl_state_t;

STATIC StandbyControl_state_t eState;

/**********************************************************************
 * static local function prototypes
 **********************************************************************/

STATIC BOOL StandbyControl_IdleStateCb(void);

/**********************************************************************
 * Message Callbacks
 **********************************************************************/
status_t StandbyControl_TriggerBtnPressedCB(msg_t in_sMessage) {
  bTriggerButtonPressed = TRUE;
  return STATUS_OK;
}

/**********************************************************************
 * Implementation
 **********************************************************************/

STATIC BOOL StandbyControl_SeekingAttentionStateCb(void) {
  // Run the Seeking Attention Sequence
}

STATIC BOOL StandbyControl_IdleStateCb(void) {
  // Get Timer status
  static timer_t sTimer;
  timer_status_t tTimerStatus = Countdown_getTimerStatus(&sTimer);
  if (TIMER_NOT_ENABLED == tTimerStatus) {
    // Init Timer
    Countdown_initTimer(&sTimer, DELAY_FOR_SEEKING_ATTENTION, ONE_SHOT_MODE);

    // Start Timer
    Countdown_startTimer(&sTimer);
  } else if (TIMER_EXPIRED == tTimerStatus) {
    return STATE_EXECUTION_COMPLETE;
  }
  return STATE_EXECUTION_INCOMPLETE;
}

void StandbyControl_init(void) {
  // Subscribe to the Trigger Button Pressed Event
  status_t tStatus =
      MessageBroker_subscribe(MSG_ID_0100, StandbyControl_TriggerBtnPressedCB);
  ASSERT_MSG(!(tStatus != STATUS_OK),
             "MessageBroker_subscribe() failed with error code: %d", tStatus);

  // Set the initial state
  eState = E_STANDBY_STATE_IDLE;
}

void StandbyControl_execute() {
  switch (eState) {
    case E_STANDBY_STATE_IDLE:
      if (STATE_EXECUTION_COMPLETE == StandbyControl_IdleStateCb()) {
        eState = E_STANDBY_STATE_SEEKING_ATTENTION;
      }
      if (bTriggerButtonPressed == TRUE) {
        bTriggerButtonPressed = FALSE;
        eState = E_STANDBY_STATE_POMODORO;
      }
      break;

    case E_STANDBY_STATE_SEEKING_ATTENTION:
      if (STATE_EXECUTION_COMPLETE ==
          StandbyControl_SeekingAttentionStateCb()) {
        eState = E_STANDBY_STATE_IDLE;
      }
      if (bTriggerButtonPressed == TRUE) {
        bTriggerButtonPressed = FALSE;
        eState = E_STANDBY_STATE_POMODORO;
      }
      break;

    case E_STANDBY_STATE_POMODORO:
      // Publish a message (TBD)

      // If the Pomodoro Sequence is complete, go back to Idle
      break;

    default:
      ASSERT_MSG(FALSE, "Invalid State");
      break;
  }
}
