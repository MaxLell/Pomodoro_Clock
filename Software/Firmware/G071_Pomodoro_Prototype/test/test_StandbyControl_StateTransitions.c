
#include "StandbyControl.h"
#include "StandbyControl_Datatypes.h"
#include "mock_CountdownTimer.h"
#include "mock_LightEffects.h"
#include "mock_MessageBroker.h"
#include "unity.h"

/**********************************************************************
 * external variables
 **********************************************************************/
extern BOOL bTriggerButtonPressed;
extern BOOL bPomodoroSequenceComplete;
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

void tearDown(void) {}

/**********************************************************************
 * Implementation
 **********************************************************************/

// Test: [Idle] =====(Timer expired)=====> [Seeking Attention]
void test_StandbyControl_execute_should_ChangeToSeekingAttentionState_when_TimerIsExpired() {
  // Set the Timer Status to expired
  Countdown_getTimerStatus_IgnoreAndReturn(TIMER_EXPIRED);
  MessageBroker_subscribe_IgnoreAndReturn(STATUS_OK);

  StandbyControl_init();
  TEST_ASSERT_EQUAL(E_STANDBY_STATE_IDLE, eState);

  StandbyControl_execute();
  TEST_ASSERT_EQUAL(E_STANDBY_STATE_SEEKING_ATTENTION, eState);
}
// Test: [Idle] =====(Trigger pressed)=====> [Pomodoro]
void test_StandbyControl_execute_should_ChangeStateFromIdleToPomodoroState_when_TriggerButtonIsPressed() {
  // Set the Trigger Button Pressed Flag
  bTriggerButtonPressed = TRUE;
  MessageBroker_subscribe_IgnoreAndReturn(STATUS_OK);

  StandbyControl_init();
  TEST_ASSERT_EQUAL(E_STANDBY_STATE_IDLE, eState);

  StandbyControl_execute();
  TEST_ASSERT_EQUAL(E_STANDBY_STATE_POMODORO, eState);
}

// Test: [Seeking Attention] =====(Sequence Complete)=====> [Idle]
void test_StandbyControl_execute_should_ChangeToIdleState_when_SequenceIsComplete() {
  // Set the Timer Status to expired
  eState = E_STANDBY_STATE_SEEKING_ATTENTION;

  LightEffects_SequenceStatus_e eSequenceStatus =
      E_LIGHT_EFFECTS_STATUS_SEQUENCE_COMPLETE;
  LightEffects_DotAroundTheCircle_Expect(NULL, 0);
  LightEffects_DotAroundTheCircle_IgnoreArg_out_eSequenceStatus();
  LightEffects_DotAroundTheCircle_ReturnArrayThruPtr_out_eSequenceStatus(
      &eSequenceStatus, 0);
  LightEffects_DotAroundTheCircle_IgnoreArg_u16PeriodPerIncrementMs();

  StandbyControl_execute();
  TEST_ASSERT_EQUAL(E_STANDBY_STATE_IDLE, eState);
}

// Test: [Seeking Attention] =====(Trigger pressed)=====> [Pomodoro]
void test_StandbyControl_execute_should_ChangeStateFromSeekingAttentionToPomodoroState_when_TriggerButtonIsPressed() {
  // Set the Trigger Button Pressed Flag
  bTriggerButtonPressed = TRUE;
  eState = E_STANDBY_STATE_SEEKING_ATTENTION;

  MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

  StandbyControl_execute();
  TEST_ASSERT_EQUAL(E_STANDBY_STATE_POMODORO, eState);
}

// Test: [Pomodoro] =====(Sequence Complete Msg)======> [Idle]
void test_StandbyControl_execute_should_ChangeStateFromPomodoroToIdleState_when_SequenceCompleteMsgIsReceived() {
  // Set initial State to Pomodoro
  eState = E_STANDBY_STATE_POMODORO;

  // Set the Pomodoro Complete Flag
  bPomodoroSequenceComplete = TRUE;

  // Check that after execution the new state is now Idle
  StandbyControl_execute();
  TEST_ASSERT_EQUAL(E_STANDBY_STATE_IDLE, eState);

  // Check that the Pomodoro Sequence Flag is cleared
  TEST_ASSERT_EQUAL(FALSE, bPomodoroSequenceComplete);
}