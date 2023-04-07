#include "build/test/mocks/mock_MessageBroker.h"
#include "User/PomodoroFsm/PomodoroFsm.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


void setUp(void)

{

}



void tearDown(void)

{

}











extern PomodoroFsm_state_e ePomodoroFsmState;

void test_PomodoroFsm_init_should_SetInitialStateToIdle(void)

{

    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;

    MessageBroker_subscribe_CMockIgnoreAndReturn(21, (0));

    PomodoroFsm_init();

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_INT);

}









extern status_t PomodoroFsm_buttonPressedCallback(MessageBroker_message_t in_sMessage);

void test_PomodoroFsm_init_should_SubscribeToTriggerButtonPressedTopic(void)

{

    MessageBroker_subscribe_CMockExpectAndReturn(35, E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED, PomodoroFsm_buttonPressedCallback, (0));









    PomodoroFsm_init();

}











void test_PomodoroFsm_execute_should_ChangeStateFromIdleToWorktime_when_TriggerButtonPressedMessage(void)

{

}
