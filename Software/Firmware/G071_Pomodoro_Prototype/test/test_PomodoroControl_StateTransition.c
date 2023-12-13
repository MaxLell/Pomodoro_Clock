#include "PomodoroControl.h"
#include "PomodoroControl_Datatypes.h"
#include "mock_MessageBroker.h"
#include "mock_PomodoroControl_StateFunctions.h"
#include "string.h"
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

void setUp(void) {
  // Reset the internal state
  memset(&sInternalState, 0, sizeof(sInternalState));
  eState = POMODOORO_CONTROL_STATE__IDLE;
}

void tearDown(void) {}

/**
 * Execute function -> State Transitions
 */

////////////////////////////////////////////////////
// Idle
////////////////////////////////////////////////////

// [Idle] ================(MSG_ID_0200)======> [Starting Sequence]
void test_PomodoroControl_execute_should_ChangeStateFromIdleToStaringSequnce_when_MSG0200IsReceived(
    void) {
  // Setup
  eState = POMODOORO_CONTROL_STATE__IDLE;

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
  eState = POMODOORO_CONTROL_STATE__IDLE;

  // Execute
  status_t eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODOORO_CONTROL_STATE__IDLE, eState);
}

////////////////////////////////////////////////////
// Starting Sequence
////////////////////////////////////////////////////

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

// [Starting Sequence] ===(MSG_ID_0101)======> [Cancel Sequence]
void test_PomodoroControl_execute_should_ChangeStateFromStartingSequenceToCancelSequence_when_MSG0101IsReceived(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__STARTING_SEQUENCE;

  // Create the Inputs
  msg_t sMsg = {0};
  sMsg.eMsgId = MSG_ID_0101;

  // Set Mock Expectations
  PomodoroControl_StateFn_StartingSequence_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__SUCCESS);

  // Execute
  status_t eStatus = PomodoroControl_MessageCallback(sMsg);
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__CANCEL_SEQUENCE, eState);
}

////////////////////////////////////////////////////
// Worktime
////////////////////////////////////////////////////

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

// [Worktime] ============(MSG_ID_0101)======> [Cancel Sequence]
void test_PomodoroControl_execute_should_ChangeStateFromWorktimeToCancelSequence_when_MSG0101IsReceived(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__WORKTIME;

  // Create the Inputs
  msg_t sMsg = {0};
  sMsg.eMsgId = MSG_ID_0101;

  // Set Mock Expectations
  PomodoroControl_StateFn_WorkTime_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__SUCCESS);

  // Execute
  status_t eStatus = PomodoroControl_MessageCallback(sMsg);
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__CANCEL_SEQUENCE, eState);
}

////////////////////////////////////////////////////
// Warning
////////////////////////////////////////////////////

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

// [Warning] =============(MSG_ID_0101)======> [Cancel Sequence]
void test_PomodoroControl_execute_should_ChangeStateFromWarningToCancelSequence_when_MSG0101IsReceived(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__WARNING;

  // Create the Inputs
  msg_t sMsg = {0};
  sMsg.eMsgId = MSG_ID_0101;

  // Set Mock Expectations
  PomodoroControl_StateFn_Warning_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__SUCCESS);

  // Execute
  status_t eStatus = PomodoroControl_MessageCallback(sMsg);
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__CANCEL_SEQUENCE, eState);
}

////////////////////////////////////////////////////
// Breaktime
////////////////////////////////////////////////////

// [Breaktime] ===========(MSG_ID_0101)======> [Cancel Sequence]
void test_PomodoroControl_execute_should_ChangeStateFromBreaktimeToCancelSequence_when_MSG0101IsReceived(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__BREAKTIME;

  // Create the Inputs
  msg_t sMsg = {0};
  sMsg.eMsgId = MSG_ID_0101;

  // Set Mock Expectations
  PomodoroControl_StateFn_BreakTime_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__SUCCESS);

  // Execute
  status_t eStatus = PomodoroControl_MessageCallback(sMsg);
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__CANCEL_SEQUENCE, eState);
}

// [Breaktime] ===========(StateFn-SUCCESS)==> [Idle]
void test_PomodoroControl_execute_should_ChangeStateFromBreaktimeToIdle_when_StateFnReturnsSuccess(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__BREAKTIME;

  // Set expectations for the mock
  PomodoroControl_StateFn_BreakTime_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__SUCCESS);

  // Execute
  status_t eStatus;
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODOORO_CONTROL_STATE__IDLE, eState);
}

// [Breaktime] ===========(StateFn-PENDING)===> [Breaktime]
void test_PomodoroControl_execute_should_StayInBreaktime_when_StateFnReturnsPending(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__BREAKTIME;

  // Set expectations for the mock
  PomodoroControl_StateFn_BreakTime_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__PENDING);

  // Execute
  status_t eStatus;
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__BREAKTIME, eState);
}

////////////////////////////////////////////////////
// Cancel Sequence
////////////////////////////////////////////////////

// [Cancel Sequence] =====(StateFn-SUCCESS)===> [Idle]
void test_PomodoroControl_execute_should_ChangeStateFromCancelSequenceToIdle_when_StateFnReturnsSuccess(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__CANCEL_SEQUENCE;
  sInternalState.bTriggerButtonIsPressedContinuously = TRUE;

  // Set expectations for the mock
  PomodoroControl_StateFn_CancelSequence_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__SUCCESS);

  // Execute
  status_t eStatus;
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODOORO_CONTROL_STATE__IDLE, eState);
}

// [Cancel Sequence] =====(StateFn-PENDING)===> [Cancel Sequence]
void test_PomodoroControl_execute_should_StayInCancelSequence_when_StateFnReturnsPending(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__CANCEL_SEQUENCE;
  sInternalState.bTriggerButtonIsPressedContinuously = TRUE;

  // Set expectations for the mock
  PomodoroControl_StateFn_CancelSequence_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__PENDING);

  // Execute
  status_t eStatus;
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__CANCEL_SEQUENCE, eState);
}

// [Cancel Sequence] =====(MSG_ID_0102)======> [Previous State: Idle]
void test_PomodoroControl_execute_should_ChangeStateFromCancelSequenceToIdle_when_MSG0102IsReceived(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__CANCEL_SEQUENCE;
  sInternalState.bTriggerButtonIsPressedContinuously = TRUE;
  sInternalState.ePreviousState = POMODOORO_CONTROL_STATE__IDLE;

  // Create the Inputs
  msg_t sMsg = {0};
  sMsg.eMsgId = MSG_ID_0102;

  // Set Mock Expectations
  PomodoroControl_StateFn_CancelSequence_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__SUCCESS);

  // Execute
  status_t eStatus = PomodoroControl_MessageCallback(sMsg);
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODOORO_CONTROL_STATE__IDLE, eState);
}

// [Cancel Sequence] =====(MSG_ID_0102)======> [Previous State: Starting
// Sequence]
void test_PomodoroControl_execute_should_ChangeStateFromCancelSequenceToStartingSequence_when_MSG0102IsReceived(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__CANCEL_SEQUENCE;
  sInternalState.bTriggerButtonIsPressedContinuously = TRUE;
  sInternalState.ePreviousState = POMODORO_CONTROL_STATE__STARTING_SEQUENCE;

  // Create the Inputs
  msg_t sMsg = {0};
  sMsg.eMsgId = MSG_ID_0102;

  // Set Mock Expectations
  PomodoroControl_StateFn_CancelSequence_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__SUCCESS);

  // Execute
  status_t eStatus = PomodoroControl_MessageCallback(sMsg);
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__STARTING_SEQUENCE, eState);
}

// [Cancel Sequence] =====(MSG_ID_0102)======> [Previous State: Worktime]
void test_PomodoroControl_execute_should_ChangeStateFromCancelSequenceToWorktime_when_MSG0102IsReceived(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__CANCEL_SEQUENCE;
  sInternalState.bTriggerButtonIsPressedContinuously = TRUE;
  sInternalState.ePreviousState = POMODORO_CONTROL_STATE__WORKTIME;

  // Create the Inputs
  msg_t sMsg = {0};
  sMsg.eMsgId = MSG_ID_0102;

  // Set Mock Expectations
  PomodoroControl_StateFn_CancelSequence_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__SUCCESS);

  // Execute
  status_t eStatus = PomodoroControl_MessageCallback(sMsg);
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__WORKTIME, eState);
}

// [Cancel Sequence] =====(MSG_ID_0102)======> [Previous State: Warning]
void test_PomodoroControl_execute_should_ChangeStateFromCancelSequenceToWarning_when_MSG0102IsReceived(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__CANCEL_SEQUENCE;
  sInternalState.bTriggerButtonIsPressedContinuously = TRUE;
  sInternalState.ePreviousState = POMODORO_CONTROL_STATE__WARNING;

  // Create the Inputs
  msg_t sMsg = {0};
  sMsg.eMsgId = MSG_ID_0102;

  // Set Mock Expectations
  PomodoroControl_StateFn_CancelSequence_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__SUCCESS);

  // Execute
  status_t eStatus = PomodoroControl_MessageCallback(sMsg);
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__WARNING, eState);
}

// [Cancel Sequence] =====(MSG_ID_0102)======> [Previous State: Breaktime]
void test_PomodoroControl_execute_should_ChangeStateFromCancelSequenceToBreaktime_when_MSG0102IsReceived(
    void) {
  // Setup
  eState = POMODORO_CONTROL_STATE__CANCEL_SEQUENCE;
  sInternalState.bTriggerButtonIsPressedContinuously = TRUE;
  sInternalState.ePreviousState = POMODORO_CONTROL_STATE__BREAKTIME;

  // Create the Inputs
  msg_t sMsg = {0};
  sMsg.eMsgId = MSG_ID_0102;

  // Set Mock Expectations
  PomodoroControl_StateFn_CancelSequence_IgnoreAndReturn(
      POMODORO_CONTROL_STATE_FN_STATE__SUCCESS);

  // Execute
  status_t eStatus = PomodoroControl_MessageCallback(sMsg);
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);
  eStatus = PomodoroControl_execute();
  TEST_ASSERT_EQUAL(STATUS_OK, eStatus);

  // Verify
  TEST_ASSERT_EQUAL(POMODORO_CONTROL_STATE__BREAKTIME, eState);
}
