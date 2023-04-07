#include "unity.h"
#include "PomodoroFsm.h"
#include "mock_MessageBroker.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * Test the init function
 * Test that the initial state is 'Idle'
 */
extern PomodoroFsm_state_e ePomodoroFsmState;
void test_PomodoroFsm_init_should_SetInitialStateToIdle(void)
{
    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;
    MessageBroker_subscribe_IgnoreAndReturn(STATUS_OK);
    PomodoroFsm_init();
    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, ePomodoroFsmState);
}

/**
 * The init function shall subscribe to the 'trigger button was pressed' topic
 */
extern status_t PomodoroFsm_buttonPressedCallback(MessageBroker_message_t in_sMessage);
void test_PomodoroFsm_init_should_SubscribeToTriggerButtonPressedTopic(void)
{
    MessageBroker_subscribe_ExpectAndReturn(
        E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED,
        PomodoroFsm_buttonPressedCallback,
        STATUS_OK);

    PomodoroFsm_init();
}

/**
 * Test the state transition
 * - Change state from 'Idle' to 'Worktime' when Button was pressed
 */
void test_PomodoroFsm_execute_should_ChangeStateFromIdleToWorktime_when_TriggerButtonPressedMessage(void)
{
}

/**
 * Test the state transition
 * - Change state from 'Idle' to 'Seeking Attention' when 5 Minutes passed without the Button being pressed
 */

/**
 * Test the state transition
 * - Change state from 'Seeking Attention' to 'Worktime' when Button was pressed
 */

/**
 * Test the state transition
 * - Change state from 'Worktime' to 'Idle' when the Button was pressed
 */

/**
 * Test the state transition
 * - Change state from 'Worktime' to 'Breaktime' when LightControl publishes, that "Worktime completed"
 */

/**
 * Test the state transition
 * - Change state from 'Breaktime' to 'Idle' when LightControl publishes, that "Breaktime completed"
 */

/**
 * Test the state transition
 * - Change state from 'Worktime' to 'Idle' when the Button was pressed
 */

/**
 * Test the state transition
 * - Change state from 'Worktime' to 'Idle' when the Button was pressed
 */