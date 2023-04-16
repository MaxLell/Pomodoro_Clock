#include "unity.h"
#include "PomodoroFsm.h"
#include "mock_MessageBroker.h"
#include "mock_LightControl.h"

extern PomodoroFsm_state_e ePomodoroFsmState;
extern PomodoroFsm_inputs_t sPomodoroFsmInputs;
extern status_t PomodoroFsm_callback(MessageBroker_message_t in_sMessage);
extern MessageBroker_message_t sPublishingMessage;

void helper_cleanInputs(void)
{
    sPomodoroFsmInputs.bButtonPressed = FALSE;
    sPomodoroFsmInputs.u8CurrentMinute = 100;
    sPomodoroFsmInputs.u8LightControlState = 100;

    ePomodoroFsmState = E_PFSM_STATE_IDLE;

    sPublishingMessage.eMsgTopic = E_MESSAGE_BROKER_LAST_TOPIC;
    sPublishingMessage.u16DataSize = 100;
    sPublishingMessage.au8DataBytes = NULL;
}

void setUp(void)
{
    helper_cleanInputs();
}

void tearDown(void)
{
}

/**
 * Test the init function
 * Test that the initial state is 'Idle'
 */

void test_PomodoroFsm_init_should_SetInitialStateToIdle(void)
{
    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;
    MessageBroker_subscribe_IgnoreAndReturn(STATUS_OK);
    PomodoroFsm_init();
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, ePomodoroFsmState);
}

/**
 * Test PomodorFsm_init()
 * - The init function shall subscribe to the trigger button pressed topic
 * - The init function shall subscribe to the TimeAndDate topic
 * - The init function shall subscribe to the LightControlState topic
 */

void test_PomodoroFsm_init_should_SubscribeToTriggerButtonPressedTopic(void)
{
    MessageBroker_subscribe_ExpectAndReturn(
        E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED,
        PomodoroFsm_callback,
        STATUS_OK);

    MessageBroker_subscribe_ExpectAndReturn(
        E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE,
        PomodoroFsm_callback,
        STATUS_OK);

    MessageBroker_subscribe_ExpectAndReturn(
        E_MESSAGE_BROKER_TOPIC_LCTRL_STATE_CHANGED,
        PomodoroFsm_callback,
        STATUS_OK);

    // If the init function is called, the subscribe function shall be called
    // This is setup with the ExpectAndReturn function
    PomodoroFsm_init();
}

/**
 * Test the PomodoroFSM Callback
 * - When the callback is called with the trigger button event, it shall set the flag
 *   in the input data struct
 */

void test_PomodoroFsm_buttonPressedCallback_should_SetButtonPressedFlagInInputStruct(void)
{
    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;
    PomodoroFsm_callback(sMessage);

    TEST_ASSERT_TRUE(sPomodoroFsmInputs.bButtonPressed);
}

/**
 * Test the state transition
 * - Change state from 'Idle' to 'Worktime' when Button was pressed
 */

void test_PomodoroFsm_execute_should_ChangeStateFromIdleToWorktime_when_TriggerButtonPressedMessage(void)
{

    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    // Starting State
    ePomodoroFsmState = E_PFSM_STATE_IDLE;

    // This sets the Button Pressed flag in the Input struct
    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;
    PomodoroFsm_callback(sMessage);

    // Execute the FSM
    PomodoroFsm_execute();

    // Check the published message
    TEST_ASSERT_EQUAL(E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED, sPublishingMessage.eMsgTopic);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_WORKTIME, sPublishingMessage.au8DataBytes[0]);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, sPublishingMessage.au8DataBytes[1]);

    // Check the new state
    TEST_ASSERT_EQUAL(E_PFSM_STATE_WORKTIME, ePomodoroFsmState);
}

void test_PomodoroFsm_currentMinuteCallback_should_SetCurrentMinuteInInputStruct(void)
{

    uint8_t u8CurrentMinute = 5;

    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE;

    uint8_t mockData[2] = {0, u8CurrentMinute};

    sMessage.au8DataBytes = mockData;
    PomodoroFsm_callback(sMessage);

    TEST_ASSERT_EQUAL(u8CurrentMinute, sPomodoroFsmInputs.u8CurrentMinute);
}

/**
 * Test the state transition
 * - Change state from 'Idle' to 'Seeking Attention' when 5 Minutes passed without the Button being pressed
 */
void test_PomodoroFsm_execute_should_ChangeStateFromIdleToSeekingAttention_when_5MinutesPassedWithoutButtonPressed(void)
{

    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE;
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

/**
 * Test the state transition
 * - Change state from 'Seeking Attention' to 'Worktime' when Button was pressed
 */
void test_PomodoroFsm_execute_should_ChangeStateFromSeekingAttentionToWorktime_when_TriggerButtonPressedMessage(void)
{

    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);
    // Starting State
    ePomodoroFsmState = E_PFSM_STATE_SEEKING_ATTENTION;

    // This sets the Button Pressed flag in the Input struct
    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;
    PomodoroFsm_callback(sMessage);

    // Execute the FSM
    PomodoroFsm_execute();

    // Check the published message
    TEST_ASSERT_EQUAL(E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED, sPublishingMessage.eMsgTopic);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_WORKTIME, sPublishingMessage.au8DataBytes[0]);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_SEEKING_ATTENTION, sPublishingMessage.au8DataBytes[1]);

    // Check the new state
    TEST_ASSERT_EQUAL(E_PFSM_STATE_WORKTIME, ePomodoroFsmState);
}

/**
 * Test the state transition
 * - Change state from 'Worktime' to 'Idle' when the Button was pressed
 */
void test_PomodoroFsm_execute_should_ChangeStateFromWorktimeToIdle_when_TriggerButtonPressedMessage(void)
{
    // The right Message needs to be sent out.
    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    // Starting State
    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;

    // This sets the Button Pressed flag in the Input struct
    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;
    PomodoroFsm_callback(sMessage);

    // Execute the FSM
    PomodoroFsm_execute();

    // Check the published message
    TEST_ASSERT_EQUAL(E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED, sPublishingMessage.eMsgTopic);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, sPublishingMessage.au8DataBytes[0]);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_WORKTIME, sPublishingMessage.au8DataBytes[1]);

    // Check the new state
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, ePomodoroFsmState);
}

/**
 * Test the state transition
 * - Change state from 'Worktime' to 'Breaktime' when LightControl publishes, that "Worktime completed"
 */
void test_PomodoroFsm_execute_should_ChangeStateFromWorktimeToBreaktime_when_LightControlPublishesWorktimeCompleted(void)
{
    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    // Reset the publishing message
    sPublishingMessage.eMsgTopic = E_MESSAGE_BROKER_LAST_TOPIC;

    // Starting State
    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;

    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_LCTRL_STATE_CHANGED;
    uint8_t u8Data[2] = {
        E_LCTRL_STATE_POMODORO_BREAKTIME,
        E_LCTRL_STATE_POMODORO_WORKTIME};
    sMessage.au8DataBytes = u8Data;
    status_t sStatus = PomodoroFsm_callback(sMessage);
    TEST_ASSERT_EQUAL(STATUS_OK, sStatus);

    // Execute the FSM
    PomodoroFsm_execute();

    // Check the published message
    TEST_ASSERT_EQUAL(E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED, sPublishingMessage.eMsgTopic);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_BREAKTIME, sPublishingMessage.au8DataBytes[0]);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_WORKTIME, sPublishingMessage.au8DataBytes[1]);

    // Check the new state
    TEST_ASSERT_EQUAL(E_PFSM_STATE_BREAKTIME, ePomodoroFsmState);
}

/**
 * Test the state transition
 * - Change state from 'Breaktime' to 'Idle' when LightControl publishes, that "Breaktime completed"
 */
void test_PomodoroFsm_execute_should_ChangeStateFromBreaktimeToIdle_when_LightControlPublishesBreaktimeCompleted(void)
{
    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    // Reset the publishing message
    sPublishingMessage.eMsgTopic = E_MESSAGE_BROKER_LAST_TOPIC;

    // Starting State
    ePomodoroFsmState = E_PFSM_STATE_BREAKTIME;

    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_LCTRL_STATE_CHANGED;
    uint8_t u8Data[2] = {
        E_LCTRL_STATE_IDLE,
        E_LCTRL_STATE_POMODORO_BREAKTIME};
    sMessage.au8DataBytes = u8Data;
    status_t sStatus = PomodoroFsm_callback(sMessage);
    TEST_ASSERT_EQUAL(STATUS_OK, sStatus);

    // Execute the FSM
    PomodoroFsm_execute();

    // Check the published message
    TEST_ASSERT_EQUAL(E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED, sPublishingMessage.eMsgTopic);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, sPublishingMessage.au8DataBytes[0]);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_BREAKTIME, sPublishingMessage.au8DataBytes[1]);

    // Check the new state
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, ePomodoroFsmState);
}

/**
 * Test the state transition
 * - Change the state from 'Breaktime' to 'Idle' when the Button was pressed
 */

void test_PomodoroFsm_execute_should_ChangeStateFromBreaktimeToIdle_when_TriggerButtonPressedMessage(void)
{
    // The right Message needs to be sent out.
    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    // Starting State
    ePomodoroFsmState = E_PFSM_STATE_BREAKTIME;

    // This sets the Button Pressed flag in the Input struct
    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;
    PomodoroFsm_callback(sMessage);

    // Execute the FSM
    PomodoroFsm_execute();

    // Check the published message
    TEST_ASSERT_EQUAL(E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED, sPublishingMessage.eMsgTopic);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, sPublishingMessage.au8DataBytes[0]);
    TEST_ASSERT_EQUAL(E_PFSM_STATE_BREAKTIME, sPublishingMessage.au8DataBytes[1]);

    // Check the new state
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, ePomodoroFsmState);
}