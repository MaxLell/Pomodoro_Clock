#include "unity.h"
#include "PomodoroFsm.h"
#include "PomodoroFsm_Interface.h"
#include "mock_MessageBroker.h"
#include "MessageTopics.h"
#include "Config.h"

extern PomodoroFsm_state_e ePomodoroFsmState;
extern PomodoroFsm_inputs_t sPomodoroFsmInputs;
extern MessageBroker_message_t sPublishingMessage;
extern BOOL bRunOnce;

extern status_t PomodoroFsm_callback(MessageBroker_message_t in_sMessage);
extern void PomodoroFsm_calculateTimeStampsForChangingStates(
    uint8_t *inout_u8WorktimeEndMinute,
    uint8_t *inout_u8BreaktimeEndMinute,
    uint8_t *in_u8CurrentMinute);

void helper_cleanInputs(void)
{
    sPomodoroFsmInputs.bButtonPressed = FALSE;
    sPomodoroFsmInputs.u8CurrentMinute = 100;
    sPomodoroFsmInputs.u8WorktimeEndMin = 100;
    sPomodoroFsmInputs.u8BreaktimeEndMin = 100;

    ePomodoroFsmState = E_PFSM_STATE_IDLE;

    sPublishingMessage.eMsgTopic = E_TOPIC_LAST_TOPIC;
    sPublishingMessage.u16DataSize = 100;
    sPublishingMessage.au8DataBytes = NULL;

    bRunOnce = FALSE;
}

void setUp(void)
{
    helper_cleanInputs();
}

void tearDown(void)
{
}

/**
 * PomodoroFsm_init()
 */

void test_PomodoroFsm_init_should_SetInitialStateToIdle(void)
{
    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;
    MessageBroker_subscribe_IgnoreAndReturn(STATUS_OK);
    PomodoroFsm_init();
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, ePomodoroFsmState);
}

void test_PomodoroFsm_init_should_SubscribeToTopics(void)
{
    MessageBroker_subscribe_ExpectAndReturn(
        E_TOPIC_TRIGGER_BUTTON_PRESSED,
        PomodoroFsm_callback,
        STATUS_OK);

    MessageBroker_subscribe_ExpectAndReturn(
        E_TOPIC_TIME_AND_DATE,
        PomodoroFsm_callback,
        STATUS_OK);

    // If the init function is called, the subscribe function shall be called
    // This is setup with the ExpectAndReturn function
    PomodoroFsm_init();
}

/**
 * PomodoroFsm_callback()
 */

void test_PomodoroFsm_callback_should_SetButtonPressedFlagInInputStruct(void)
{
    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_TOPIC_TRIGGER_BUTTON_PRESSED;
    PomodoroFsm_callback(sMessage);

    TEST_ASSERT_TRUE(sPomodoroFsmInputs.bButtonPressed);
}

void test_PomodoroFsm_callback_should_SetCurrentMinuteInInputStruct(void)
{
    // Test 1: Set current Minute to 5
    uint8_t u8CurrentMinute = 5;

    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_TOPIC_TIME_AND_DATE;

    uint8_t mockData[2] = {0, u8CurrentMinute};

    sMessage.au8DataBytes = mockData;
    PomodoroFsm_callback(sMessage);

    TEST_ASSERT_EQUAL(u8CurrentMinute, sPomodoroFsmInputs.u8CurrentMinute);

    // Test 2: Set current Minute to 10
    u8CurrentMinute = 10;
    mockData[1] = u8CurrentMinute;
    PomodoroFsm_callback(sMessage);
    TEST_ASSERT_EQUAL(u8CurrentMinute, sPomodoroFsmInputs.u8CurrentMinute);
}

/**
 * PomodoroFsm_execute() (FSM)
 */

void test_PomodoroFsm_execute_should_ChangeStateFromIdleToWorktime_when_TriggerButtonPressedMessage(void)
{
    /**
     * Idle -> Worktime (Button pressed)
     */

    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    // Starting State
    ePomodoroFsmState = E_PFSM_STATE_IDLE;

    // This sets the Button Pressed flag in the Input struct
    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_TOPIC_TRIGGER_BUTTON_PRESSED;
    PomodoroFsm_callback(sMessage);

    // Execute the FSM
    PomodoroFsm_execute();

    // Check the published message
    TEST_ASSERT_EQUAL(E_TOPIC_PFSM_STATE_CHANGED, sPublishingMessage.eMsgTopic);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_WORKTIME, sPublishingMessage.au8DataBytes[0]);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, sPublishingMessage.au8DataBytes[1]);

    // Check the new state
    TEST_ASSERT_EQUAL(E_PFSM_STATE_WORKTIME, ePomodoroFsmState);
}

void test_PomodoroFsm_execute_should_ChangeStateFromIdleToSeekingAttention_when_5MinutesPassedWithoutButtonPressed(void)
{
    /**
     * Idle -> Seeking Attention (5 Minutes passed without button pressed)
     */

    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_TOPIC_TIME_AND_DATE;
    uint8_t u8CurrentMinute = 10;

    // Starting State
    ePomodoroFsmState = E_PFSM_STATE_IDLE;

    // Call the callback and the PomodoroFsm for 5 times, so that the
    // counter is incremented 5 times
    for (uint8_t u8Counter = u8CurrentMinute; u8Counter < (5 + u8CurrentMinute + 1); u8Counter++)
    {
        // This sets the Button Pressed flag in the Input struct
        uint8_t mockData[2] = {0, u8Counter};
        sMessage.au8DataBytes = mockData;
        PomodoroFsm_callback(sMessage);

        // Execute the FSM
        PomodoroFsm_execute();
    }

    // Check the new state
    TEST_ASSERT_EQUAL(E_PFSM_STATE_SEEKING_ATTENTION, ePomodoroFsmState);
}

void test_PomodoroFsm_execute_should_ChangeStateFromSeekingAttentionToWorktime_when_TriggerButtonPressedMessage(void)
{
    /**
     * Seeking Attention -> Worktime (Button Pressed)
     */

    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);
    // Starting State
    ePomodoroFsmState = E_PFSM_STATE_SEEKING_ATTENTION;

    // This sets the Button Pressed flag in the Input struct
    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_TOPIC_TRIGGER_BUTTON_PRESSED;
    PomodoroFsm_callback(sMessage);

    // Execute the FSM
    PomodoroFsm_execute();

    // Check the published message
    TEST_ASSERT_EQUAL(E_TOPIC_PFSM_STATE_CHANGED, sPublishingMessage.eMsgTopic);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_WORKTIME, sPublishingMessage.au8DataBytes[0]);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_SEEKING_ATTENTION, sPublishingMessage.au8DataBytes[1]);

    // Check the new state
    TEST_ASSERT_EQUAL(E_PFSM_STATE_WORKTIME, ePomodoroFsmState);
}

void test_PomodoroFsm_execute_should_ChangeStateFromWorktimeToIdle_when_TriggerButtonPressedMessage(void)
{
    /**
     * Worktime -> Idle (Button Pressed)
     */

    // Set the Flag so that the timestamps are not calculated
    bRunOnce = TRUE;

    // The right Message needs to be sent out.
    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    // Starting State
    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;

    // This sets the Button Pressed flag in the Input struct
    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_TOPIC_TRIGGER_BUTTON_PRESSED;
    PomodoroFsm_callback(sMessage);

    // // Update the current Minute
    // sPomodoroFsmInputs.u8CurrentMinute = 10;
    // sPomodoroFsmInputs.u8WorktimeEndMin = sPomodoroFsmInputs.u8CurrentMinute;

    // Execute the FSM
    PomodoroFsm_execute();

    // Check the published message
    TEST_ASSERT_EQUAL(E_TOPIC_PFSM_STATE_CHANGED, sPublishingMessage.eMsgTopic);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, sPublishingMessage.au8DataBytes[0]);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_WORKTIME, sPublishingMessage.au8DataBytes[1]);

    // Check the new state
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, ePomodoroFsmState);
}

void test_PomodoroFsm_execute_should_ChangeStateFromWorktimeToBreaktime_when_WorktimeElapsed(void)
{
    /**
     * Worktime -> Idle (Button Pressed)
     */

    // Set the Flag so that the timestamps are not calculated
    bRunOnce = TRUE;

    // The right Message needs to be sent out.
    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    // Starting State
    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;

    // Update the current Minute
    sPomodoroFsmInputs.u8CurrentMinute = 10;
    sPomodoroFsmInputs.u8WorktimeEndMin = sPomodoroFsmInputs.u8CurrentMinute;

    // Execute the FSM
    PomodoroFsm_execute();

    // Check the published message
    TEST_ASSERT_EQUAL(E_TOPIC_PFSM_STATE_CHANGED, sPublishingMessage.eMsgTopic);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_BREAKTIME, sPublishingMessage.au8DataBytes[0]);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_WORKTIME, sPublishingMessage.au8DataBytes[1]);

    // Check the new state
    TEST_ASSERT_EQUAL(E_PFSM_STATE_BREAKTIME, ePomodoroFsmState);
}

void test_PomodoroFsm_execute_should_ChangeStateFromBreaktimeToIdle_when_BreaktimeIsOver(void)
{
    /**
     * Breaktime -> Idle (Breaktime is over)
     */

    // The right Message needs to be sent out.
    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    // Starting State
    ePomodoroFsmState = E_PFSM_STATE_BREAKTIME;

    // Update the current Minute
    sPomodoroFsmInputs.u8CurrentMinute = 10;
    sPomodoroFsmInputs.u8BreaktimeEndMin = sPomodoroFsmInputs.u8CurrentMinute;

    // Execute the FSM
    PomodoroFsm_execute();

    // Check the published message
    TEST_ASSERT_EQUAL(E_TOPIC_PFSM_STATE_CHANGED, sPublishingMessage.eMsgTopic);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, sPublishingMessage.au8DataBytes[0]);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_BREAKTIME, sPublishingMessage.au8DataBytes[1]);

    // Check the new state
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, ePomodoroFsmState);
}

void test_PomodoroFsm_execute_should_ChangeStateFromBreaktimeToIdle_when_TriggerButtonPressedMessage(void)
{
    /**
     * Breaktime -> Idle (Button Pressed)
     */

    // The right Message needs to be sent out.
    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);
    // This sets the Button Pressed flag in the Input struct
    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_TOPIC_TRIGGER_BUTTON_PRESSED;
    PomodoroFsm_callback(sMessage);

    // Starting State
    ePomodoroFsmState = E_PFSM_STATE_BREAKTIME;

    // Execute the FSM
    PomodoroFsm_execute();

    // Check the published message
    TEST_ASSERT_EQUAL(E_TOPIC_PFSM_STATE_CHANGED, sPublishingMessage.eMsgTopic);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, sPublishingMessage.au8DataBytes[0]);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_BREAKTIME, sPublishingMessage.au8DataBytes[1]);

    // Check the new state
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, ePomodoroFsmState);
}

/**
 * The PomodoroFsm State Worktime shall initially calculate the timestamps for
 * changing the states (Set the timestamp for when Worktime and Breaktime is over)
 */

void test_PomodoroFsm_execute_should_SetTheTimestampsInitiallyInWorktimeState(void)
{
    // Set initial state to Worktime
    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;

    // Set the before parameters - as for the timestamps
    uint8_t u8CurrentMinute = 17;
    uint8_t u8WorktimeEndMin = 0;
    uint8_t u8BreaktimeEndMin = 0;

    // Call the callback with a specific message, to set the initial Minute to 17 (otherwise it would be 100)
    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_TOPIC_TIME_AND_DATE;
    uint8_t au8TmpData[6] = {0};
    au8TmpData[1] = u8CurrentMinute;
    sMessage.au8DataBytes = au8TmpData;

    PomodoroFsm_callback(sMessage);

    // Verify that the current minute has been set
    TEST_ASSERT_EQUAL(u8CurrentMinute, sPomodoroFsmInputs.u8CurrentMinute);

    // run the execute function
    PomodoroFsm_execute();

    // Check the timestamps - have they#ve been updated? (They should not be the same as before)
    TEST_ASSERT_NOT_EQUAL(u8WorktimeEndMin, sPomodoroFsmInputs.u8WorktimeEndMin);
    TEST_ASSERT_NOT_EQUAL(u8BreaktimeEndMin, sPomodoroFsmInputs.u8BreaktimeEndMin);

    // Change the initial conditions for the timestamp calculation (Some random values)
    u8CurrentMinute = 40;
    u8WorktimeEndMin = 56;
    u8BreaktimeEndMin = 58;

    // Call the callback with a specific message, to set the initial Minute to 17 (otherwise it would be 100)
    sMessage.eMsgTopic = E_TOPIC_TIME_AND_DATE;
    au8TmpData[1] = u8CurrentMinute;
    sMessage.au8DataBytes = au8TmpData;

    PomodoroFsm_callback(sMessage);

    // rerun the execute function
    PomodoroFsm_execute();

    // make sure that the timestamps have not been updated
    TEST_ASSERT_NOT_EQUAL(u8WorktimeEndMin, sPomodoroFsmInputs.u8WorktimeEndMin);
    TEST_ASSERT_NOT_EQUAL(u8BreaktimeEndMin, sPomodoroFsmInputs.u8BreaktimeEndMin);
}

/**
 * calculateTimeStampsForChangingStates function
 */

void test_PomodoroFsm_calculateTimeStampsForChangingStates_should_CalculateTimeStamps(void)
{
    uint8_t u8CurrentMinute = 17;
    uint8_t u8WorktimeEndMin = 0;
    uint8_t u8BreaktimeEndMin = 0;

    PomodoroFsm_calculateTimeStampsForChangingStates(
        &u8WorktimeEndMin, &u8BreaktimeEndMin, &u8CurrentMinute);

    TEST_ASSERT_EQUAL(7, u8WorktimeEndMin);
    TEST_ASSERT_EQUAL(17, u8BreaktimeEndMin);
}