#include "build/test/mocks/mock_LightControl.h"
#include "build/test/mocks/mock_MessageBroker.h"
#include "User/PomodoroFsm/PomodoroFsm.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


extern PomodoroFsm_state_e ePomodoroFsmState;

extern PomodoroFsm_inputs_t sPomodoroFsmInputs;

extern status_t PomodoroFsm_callback(MessageBroker_message_t in_sMessage);

extern MessageBroker_message_t sPublishingMessage;



void helper_cleanInputs(void)

{

    sPomodoroFsmInputs.bButtonPressed = 0;

    sPomodoroFsmInputs.u8CurrentMinute = 100;

    sPomodoroFsmInputs.u8LightControlState = 100;



    ePomodoroFsmState = E_PFSM_STATE_IDLE;



    sPublishingMessage.eMsgTopic = E_MESSAGE_BROKER_LAST_TOPIC;

    sPublishingMessage.u16DataSize = 100;

    sPublishingMessage.au8DataBytes = ((void*)0);

}



void setUp(void)

{

    helper_cleanInputs();

}



void tearDown(void)

{

}













void test_PomodoroFsm_init_should_SetInitialStateToIdle(void)

{

    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;

    MessageBroker_subscribe_CMockIgnoreAndReturn(41, (0));

    PomodoroFsm_init();

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_INT);

}

void test_PomodoroFsm_init_should_SubscribeToTriggerButtonPressedTopic(void)

{

    MessageBroker_subscribe_CMockExpectAndReturn(58, E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED, PomodoroFsm_callback, (0));









    MessageBroker_subscribe_CMockExpectAndReturn(63, E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE, PomodoroFsm_callback, (0));









    MessageBroker_subscribe_CMockExpectAndReturn(68, E_MESSAGE_BROKER_TOPIC_LCTRL_STATE_CHANGED, PomodoroFsm_callback, (0));













    PomodoroFsm_init();

}















void test_PomodoroFsm_buttonPressedCallback_should_SetButtonPressedFlagInInputStruct(void)

{

    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);



    do {if ((sPomodoroFsmInputs.bButtonPressed)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(87)));}} while(0);

}













void test_PomodoroFsm_execute_should_ChangeStateFromIdleToWorktime_when_TriggerButtonPressedMessage(void)

{



    MessageBroker_publish_CMockIgnoreAndReturn(98, (0));





    ePomodoroFsmState = E_PFSM_STATE_IDLE;





    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(112), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(113), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(114), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(117), UNITY_DISPLAY_STYLE_INT);

}



void test_PomodoroFsm_currentMinuteCallback_should_SetCurrentMinuteInInputStruct(void)

{



    uint8_t u8CurrentMinute = 5;



    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE;



    uint8_t mockData[2] = {0, u8CurrentMinute};



    sMessage.au8DataBytes = mockData;

    PomodoroFsm_callback(sMessage);



    UnityAssertEqualNumber((UNITY_INT)((u8CurrentMinute)), (UNITY_INT)((sPomodoroFsmInputs.u8CurrentMinute)), (((void*)0)), (UNITY_UINT)(133), UNITY_DISPLAY_STYLE_INT);

}











void test_PomodoroFsm_execute_should_ChangeStateFromIdleToSeekingAttention_when_5MinutesPassedWithoutButtonPressed(void)

{



    MessageBroker_publish_CMockIgnoreAndReturn(143, (0));



    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE;

    uint8_t u8CurrentMinute = 10;





    ePomodoroFsmState = E_PFSM_STATE_IDLE;







    for (uint8_t u8Counter = u8CurrentMinute; u8Counter < (5 + u8CurrentMinute + 1); u8Counter++)

    {



        uint8_t mockData[2] = {0, u8Counter};

        sMessage.au8DataBytes = mockData;

        PomodoroFsm_callback(sMessage);





        PomodoroFsm_execute();

    }





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_SEEKING_ATTENTION)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(166), UNITY_DISPLAY_STYLE_INT);

}











void test_PomodoroFsm_execute_should_ChangeStateFromSeekingAttentionToWorktime_when_TriggerButtonPressedMessage(void)

{



    MessageBroker_publish_CMockIgnoreAndReturn(176, (0));



    ePomodoroFsmState = E_PFSM_STATE_SEEKING_ATTENTION;





    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(189), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(190), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_SEEKING_ATTENTION)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(191), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(194), UNITY_DISPLAY_STYLE_INT);

}











void test_PomodoroFsm_execute_should_ChangeStateFromWorktimeToIdle_when_TriggerButtonPressedMessage(void)

{



    MessageBroker_publish_CMockIgnoreAndReturn(204, (0));





    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;





    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(218), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(219), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(220), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(223), UNITY_DISPLAY_STYLE_INT);

}











void test_PomodoroFsm_execute_should_ChangeStateFromWorktimeToBreaktime_when_LightControlPublishesWorktimeCompleted(void)

{

    MessageBroker_publish_CMockIgnoreAndReturn(232, (0));





    sPublishingMessage.eMsgTopic = E_MESSAGE_BROKER_LAST_TOPIC;





    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;



    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_LCTRL_STATE_CHANGED;

    uint8_t u8Data[2] = {

        E_LCTRL_STATE_POMODORO_BREAKTIME,

        E_LCTRL_STATE_POMODORO_WORKTIME};

    sMessage.au8DataBytes = u8Data;

    status_t sStatus = PomodoroFsm_callback(sMessage);

    UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((sStatus)), (((void*)0)), (UNITY_UINT)(247), UNITY_DISPLAY_STYLE_INT);





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(253), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_BREAKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(254), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(255), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_BREAKTIME)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(258), UNITY_DISPLAY_STYLE_INT);

}











void test_PomodoroFsm_execute_should_ChangeStateFromBreaktimeToIdle_when_LightControlPublishesBreaktimeCompleted(void)

{

    MessageBroker_publish_CMockIgnoreAndReturn(267, (0));





    sPublishingMessage.eMsgTopic = E_MESSAGE_BROKER_LAST_TOPIC;





    ePomodoroFsmState = E_PFSM_STATE_BREAKTIME;



    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_LCTRL_STATE_CHANGED;

    uint8_t u8Data[2] = {

        E_LCTRL_STATE_IDLE,

        E_LCTRL_STATE_POMODORO_BREAKTIME};

    sMessage.au8DataBytes = u8Data;

    status_t sStatus = PomodoroFsm_callback(sMessage);

    UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((sStatus)), (((void*)0)), (UNITY_UINT)(282), UNITY_DISPLAY_STYLE_INT);





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(288), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(289), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_BREAKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(290), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(293), UNITY_DISPLAY_STYLE_INT);

}













void test_PomodoroFsm_execute_should_ChangeStateFromBreaktimeToIdle_when_TriggerButtonPressedMessage(void)

{



    MessageBroker_publish_CMockIgnoreAndReturn(304, (0));





    ePomodoroFsmState = E_PFSM_STATE_BREAKTIME;





    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(318), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(319), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_BREAKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(320), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(323), UNITY_DISPLAY_STYLE_INT);

}
