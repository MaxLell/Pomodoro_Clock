#include "PomodoroControl.h"
#include "PomodoroControl_Datatypes.h"
#include "mock_MessageBroker.h"
#include "mock_PomodoroControl_StateFunctions.h"
#include "unity.h"

/********************************************************
 * extern static functions
 ********************************************************/

extern status_t PomodoroControl_MessageCallback(msg_t sMsg);

/********************************************************
 * extern private static variables
 ********************************************************/

extern PomodoroControl_internalStatus_t sInternalState;
extern PomodoroControl_State_t eState;

/********************************************************
 * Implementation
 ********************************************************/

void setUp(void) {}

void tearDown(void) {}

/**
 * Execute function -> State Transitions
 */

// [Idle] ================(MSG_ID_0200)======> [Starting Sequence]
void test_PomodoroControl_execute_should_ChangeStateFromIdleToStaringSequnce_when_MSG0200IsReceived(
    void) {
  // Setup
  eState = POMDOORO_CONTROL_STATE__IDLE;

  // Create the Inputs
  msg_t sMsg = {0};
  sMsg.eMsgId = MSG_ID_0200;

  // Execute
  status_t eStatus = PomodoroControl_MessageCallback(sMsg);
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__STARTING_SEQUENCE, eState);
}

// [Idle] ================()================> [Idle]
void test_PomodoroControl_execute_should_StayInIdle_when_NoMessageIsReceived(
    void) {
  // Setup
  eState = POMDOORO_CONTROL_STATE__IDLE;

  // Execute
  status_t eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMDOORO_CONTROL_STATE__IDLE, eState);
}

// [Starting Sequence] ===(StateFn-SUCCESS)==> [Worktime]
void test_PomodoroControl_execute_should_ChangeStateFromStartingSequenceToWorktime_when_StateFnReturnsSuccess(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__STARTING_SEQUENCE;

  // Set expectations for the mock
  PomodoroControl_StateFn_StartingSequence_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__SUCCESS);

  // Execute
  status_t eStatus;
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__WORKTIME, eState);
}

// [Starting Sequence] ======(StateFn-PENDING)=====> [Starting Sequence]
void test_PomodoroControl_execute_should_StayInStartingSequence_when_StateFnReturnsPending(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__STARTING_SEQUENCE;

  // Set expectations for the mock
  PomodoroControl_StateFn_StartingSequence_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__PENDING);

  // Execute
  status_t eStatus;
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__STARTING_SEQUENCE, eState);
}

// [Worktime] ============(StateFn-SUCCESS)==> [Warning]
void test_PomodoroControl_execute_should_ChangeStateFromWorktimeToWarning_when_StateFnReturnsSuccess(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__WORKTIME;

  // Set expectations for the mock
  PomodoroControl_StateFn_WorkTime_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__SUCCESS);

  // Execute
  status_t eStatus;
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__WARNING, eState);
}

// [Worktime] ============(StateFn-PENDING)===> [Worktime]
void test_PomodoroControl_execute_should_StayInWorktime_when_StateFnReturnsPending(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__WORKTIME;

  // Set expectations for the mock
  PomodoroControl_StateFn_WorkTime_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__PENDING);

  // Execute
  status_t eStatus;
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__WORKTIME, eState);
}

// [Warning] =============(StateFn-SUCCESS)==> [Breaktime]
void test_PomodoroControl_execute_should_ChangeStateFromWarningToBreaktime_when_StateFnReturnsSuccess(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__WARNING;

  // Set expectations for the mock
  PomodoroControl_StateFn_Warning_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__SUCCESS);

  // Execute
  status_t eStatus;
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__BREAKTIME, eState);
}

// [Warning] =============(StateFn-PENDING)===> [Warning]
void test_PomodoroControl_execute_should_StayInWarning_when_StateFnReturnsPending(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__WARNING;

  // Set expectations for the mock
  PomodoroControl_StateFn_Warning_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__PENDING);

  // Execute
  status_t eStatus;
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__WARNING, eState);
}

// [Starting Sequence] ===(MSG_ID_0101)======> [Cancel Sequence]

// [Worktime] ============(MSG_ID_0102)======> [Cancel Sequence]

// [Warning] =============(MSG_ID_0102)======> [Cancel Sequence]

// [Breaktime] ===========(MSG_ID_0101)======> [Cancel Sequence]

/**
 * Idle function
 * - Subscribe to MSG_ID_0200
 * - Subscribe to MSG_ID_0101
 * - Set the internal state to Idle
 */

/**
 * Message Callback
 * - set the respective internal status flags (TBDs)
 */