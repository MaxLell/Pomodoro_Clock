#include "LightEffects.h"
#include "MessageBroker.h"
#include "StandbyControl.h"
#include "StandbyControl_Datatypes.h"
#include "mock_CountdownTimer.h"
#include "mock_RgbLed.h"
#include "unity.h"

/**********************************************************************
 * external variables
 **********************************************************************/
extern BOOL bTriggerButtonPressed;
extern StandbyControl_state_t eState;

/**********************************************************************
 * external function
 **********************************************************************/
extern BOOL StandbyControl_IdleStateCb(void);
extern BOOL StandbyControl_SeekingAttentionStateCb(void);

/**********************************************************************
 * setup and teardown
 **********************************************************************/

void setUp(void) {
  bTriggerButtonPressed = FALSE;
  eState = E_STANDBY_STATE_IDLE;
}

void tearDown(void) { StandbyControl_init(); }

/**********************************************************************
 * Implementation
 **********************************************************************/

void test_StandbyTriggerButtonSinglePress_should_SetItsInternalFlag_when_AButtonPressedEventHappened() {
  msg_t sMsg;
  sMsg.eMsgId = MSG_ID_0100;
  sMsg.u16DataSize = 0;
  sMsg.au8DataBytes = NULL;
  TEST_ASSERT_EQUAL(FALSE, bTriggerButtonPressed);
  Countdown_initTimer_Ignore();
  MessageBroker_init();
  StandbyControl_init();
  MessageBroker_publish(sMsg);
  TEST_ASSERT_EQUAL(TRUE, bTriggerButtonPressed);
}

void test_StandbyControl_execute_should_ClearItsInternalTheTriggerButtonFlag() {
  msg_t sMsg;
  sMsg.eMsgId = MSG_ID_0100;
  sMsg.u16DataSize = 0;
  sMsg.au8DataBytes = NULL;
  bTriggerButtonPressed = FALSE;
  Countdown_initTimer_Ignore();
  Countdown_getTimerStatus_IgnoreAndReturn(TIMER_NOT_EXPIRED);
  MessageBroker_init();
  StandbyControl_init();
  MessageBroker_publish(sMsg);
  TEST_ASSERT_EQUAL(TRUE, bTriggerButtonPressed);
  StandbyControl_execute();
  TEST_ASSERT_EQUAL(FALSE, bTriggerButtonPressed);
}

void test_StandbyControl_IdleStateCb_should_SetANewTimer_when_TheTimerHasNotBeenInitializedBefore() {
  // Set the Timer Status to expired
  Countdown_getTimerStatus_IgnoreAndReturn(TIMER_NOT_ENABLED);
  Countdown_initTimer_Ignore();
  Countdown_startTimer_Ignore();

  StandbyControl_init();
  StandbyControl_SequenceStatus_e eStateExecutionIsComplete =
      StandbyControl_IdleStateCb();
  TEST_ASSERT_EQUAL(E_STANDBY_STATUS_SEQUENCE_INCOMPLETE,
                    eStateExecutionIsComplete);
}

void test_StandbyControl_IdleStateCb_should_ReturnExecutionIncomplete_when_TheTimerHasNotExpiredYet() {
  // Set the Timer Status to expired
  Countdown_getTimerStatus_IgnoreAndReturn(TIMER_NOT_EXPIRED);
  StandbyControl_init();
  StandbyControl_SequenceStatus_e eStateExecutionIsComplete =
      StandbyControl_IdleStateCb();
  TEST_ASSERT_EQUAL(E_STANDBY_STATUS_SEQUENCE_INCOMPLETE,
                    eStateExecutionIsComplete);
}
