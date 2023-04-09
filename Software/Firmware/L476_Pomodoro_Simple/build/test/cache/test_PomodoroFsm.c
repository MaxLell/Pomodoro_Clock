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

    helper_cleanInputs();



    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;

    MessageBroker_subscribe_CMockIgnoreAndReturn(43, (0));

    PomodoroFsm_init();

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_INT);

}











void test_PomodoroFsm_init_should_SubscribeToTriggerButtonPressedTopic(void)

{

    MessageBroker_subscribe_CMockExpectAndReturn(57, E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED, PomodoroFsm_callback, (0));









    MessageBroker_subscribe_CMockExpectAndReturn(62, E_MESSAGE_BROKER_TOPIC_CURRENT_MINUTE, PomodoroFsm_callback, (0));









    MessageBroker_subscribe_CMockExpectAndReturn(67, E_MESSAGE_BROKER_TOPIC_LCTRL_STATE_CHANGED, PomodoroFsm_callback, (0));













    PomodoroFsm_init();

}















void test_PomodoroFsm_buttonPressedCallback_should_SetButtonPressedFlagInInputStruct(void)

{

    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);



    do {if ((sPomodoroFsmInputs.bButtonPressed)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(86)));}} while(0);

}













void test_PomodoroFsm_execute_should_ChangeStateFromIdleToWorktime_when_TriggerButtonPressedMessage(void)

{



    MessageBroker_publish_CMockIgnoreAndReturn(97, (0));





    ePomodoroFsmState = E_PFSM_STATE_IDLE;





    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(111), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(112), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(113), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(116), UNITY_DISPLAY_STYLE_INT);

}















void test_PomodoroFsm_init_should_SubscribeToCurrentMinuteTopic(void)

{

    MessageBroker_subscribe_CMockExpectAndReturn(130, E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED, PomodoroFsm_callback, (0));









    MessageBroker_subscribe_CMockExpectAndReturn(135, E_MESSAGE_BROKER_TOPIC_CURRENT_MINUTE, PomodoroFsm_callback, (0));









    MessageBroker_subscribe_CMockExpectAndReturn(140, E_MESSAGE_BROKER_TOPIC_LCTRL_STATE_CHANGED, PomodoroFsm_callback, (0));









    PomodoroFsm_init();

}



void test_PomodoroFsm_currentMinuteCallback_should_SetCurrentMinuteInInputStruct(void)

{



    uint8_t u8CurrentMinute = 5;



    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_CURRENT_MINUTE;

    sMessage.au8DataBytes = &u8CurrentMinute;

    PomodoroFsm_callback(sMessage);



    UnityAssertEqualNumber((UNITY_INT)((u8CurrentMinute)), (UNITY_INT)((sPomodoroFsmInputs.u8CurrentMinute)), (((void*)0)), (UNITY_UINT)(155), UNITY_DISPLAY_STYLE_INT);

}











void test_PomodoroFsm_execute_should_ChangeStateFromIdleToSeekingAttention_when_5MinutesPassedWithoutButtonPressed(void)

{



    MessageBroker_publish_CMockIgnoreAndReturn(165, (0));



    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_CURRENT_MINUTE;

    uint8_t u8CurrentMinute = 10;





    ePomodoroFsmState = E_PFSM_STATE_IDLE;







    for (uint8_t u8Counter = u8CurrentMinute; u8Counter < (5 + u8CurrentMinute + 1); u8Counter++)

    {



        sMessage.au8DataBytes = &u8Counter;

        PomodoroFsm_callback(sMessage);





        PomodoroFsm_execute();

    }





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_SEEKING_ATTENTION)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(187), UNITY_DISPLAY_STYLE_INT);

}











void test_PomodoroFsm_execute_should_ChangeStateFromSeekingAttentionToWorktime_when_TriggerButtonPressedMessage(void)

{



    MessageBroker_publish_CMockIgnoreAndReturn(197, (0));



    ePomodoroFsmState = E_PFSM_STATE_SEEKING_ATTENTION;





    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(210), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(211), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_SEEKING_ATTENTION)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(212), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(215), UNITY_DISPLAY_STYLE_INT);

}











void test_PomodoroFsm_execute_should_ChangeStateFromWorktimeToIdle_when_TriggerButtonPressedMessage(void)

{



    MessageBroker_publish_CMockIgnoreAndReturn(225, (0));





    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;





    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(239), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(240), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(241), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(244), UNITY_DISPLAY_STYLE_INT);

}











void test_PomodoroFsm_init_should_SubscribeToLightControlStateChanges(void)

{

    MessageBroker_subscribe_CMockExpectAndReturn(256, E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED, PomodoroFsm_callback, (0));









    MessageBroker_subscribe_CMockExpectAndReturn(261, E_MESSAGE_BROKER_TOPIC_CURRENT_MINUTE, PomodoroFsm_callback, (0));









    MessageBroker_subscribe_CMockExpectAndReturn(266, E_MESSAGE_BROKER_TOPIC_LCTRL_STATE_CHANGED, PomodoroFsm_callback, (0));









    PomodoroFsm_init();

}











void test_PomodoroFsm_execute_should_ChangeStateFromWorktimeToBreaktime_when_LightControlPublishesWorktimeCompleted(void)

{

    MessageBroker_publish_CMockIgnoreAndReturn(277, (0));





    sPublishingMessage.eMsgTopic = E_MESSAGE_BROKER_LAST_TOPIC;





    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;



    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_LCTRL_STATE_CHANGED;

    uint8_t u8Data[2] = {

        E_LCTRL_STATE_BREAKTIME,

        E_LCTRL_STATE_WORKTIME};

    sMessage.au8DataBytes = u8Data;

    status_t sStatus = PomodoroFsm_callback(sMessage);

    UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((sStatus)), (((void*)0)), (UNITY_UINT)(292), UNITY_DISPLAY_STYLE_INT);





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(298), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_BREAKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(299), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(300), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_BREAKTIME)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(303), UNITY_DISPLAY_STYLE_INT);

}











void test_PomodoroFsm_execute_should_ChangeStateFromBreaktimeToIdle_when_LightControlPublishesBreaktimeCompleted(void)

{

    MessageBroker_publish_CMockIgnoreAndReturn(312, (0));





    sPublishingMessage.eMsgTopic = E_MESSAGE_BROKER_LAST_TOPIC;





    ePomodoroFsmState = E_PFSM_STATE_BREAKTIME;



    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_LCTRL_STATE_CHANGED;

    uint8_t u8Data[2] = {

        E_LCTRL_STATE_IDLE,

        E_LCTRL_STATE_BREAKTIME};

    sMessage.au8DataBytes = u8Data;

    status_t sStatus = PomodoroFsm_callback(sMessage);

    UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((sStatus)), (((void*)0)), (UNITY_UINT)(327), UNITY_DISPLAY_STYLE_INT);





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(333), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(334), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_BREAKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(335), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(338), UNITY_DISPLAY_STYLE_INT);

}













void test_PomodoroFsm_execute_should_ChangeStateFromBreaktimeToIdle_when_TriggerButtonPressedMessage(void)

{





    MessageBroker_publish_CMockIgnoreAndReturn(350, (0));





    ePomodoroFsmState = E_PFSM_STATE_BREAKTIME;





    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(364), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(365), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_BREAKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(366), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(369), UNITY_DISPLAY_STYLE_INT);

}
