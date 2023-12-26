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
    } break;

    case MSG_ID_0101:  // Trigger Button: is Pressed Down Continuously
    {
    } break;

    case MSG_ID_0102:  // Trigger Button: is Released
    {
    } break;

    case MSG_ID_0400:  // Pomodoro Configuration: Worktime and Breaktime Periods
    {
      sInternalState.u8WorktimePeriodMin =
          ((PomodoroPeriodConfiguration_t*)sMsg.au8DataBytes)
              ->u8WorktimePeriodMin;
      sInternalState.u8BreaktimePeriodMin =
          ((PomodoroPeriodConfiguration_t*)sMsg.au8DataBytes)
              ->u8BreaktimePeriodMin;
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
  // Set the initial state

  // Set the initial Event

  // Subscribe to Messages

  // Reset the internal Data Structure
}

status_e PomodoroControl_execute(void) {}