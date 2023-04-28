#include "User/Common/Config.h"
#include "User/MessageBroker/MessageTopics.h"
#include "build/test/mocks/mock_MessageBroker.h"
#include "User/PomodoroFsm/PomodoroFsm_Interface.h"
#include "User/PomodoroFsm/PomodoroFsm.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"






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

    sPomodoroFsmInputs.bButtonPressed = 0;

    sPomodoroFsmInputs.u8CurrentMinute = 100;

    sPomodoroFsmInputs.u8WorktimeEndMin = 100;

    sPomodoroFsmInputs.u8BreaktimeEndMin = 100;



    ePomodoroFsmState = E_PFSM_STATE_IDLE;



    sPublishingMessage.eMsgTopic = E_TOPIC_LAST_TOPIC;

    sPublishingMessage.u16DataSize = 100;

    sPublishingMessage.au8DataBytes = ((void*)0);



    bRunOnce = 0;

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

    MessageBroker_subscribe_CMockIgnoreAndReturn(51, (0));

    PomodoroFsm_init();

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_INT);

}



void test_PomodoroFsm_init_should_SubscribeToTopics(void)

{

    MessageBroker_subscribe_CMockExpectAndReturn(61, E_TOPIC_TRIGGER_BUTTON_PRESSED, PomodoroFsm_callback, (0));









    MessageBroker_subscribe_CMockExpectAndReturn(66, E_TOPIC_TIME_AND_DATE, PomodoroFsm_callback, (0));













    PomodoroFsm_init();

}











void test_PomodoroFsm_callback_should_SetButtonPressedFlagInInputStruct(void)

{

    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);



    do {if ((sPomodoroFsmInputs.bButtonPressed)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(83)));}} while(0);

}



void test_PomodoroFsm_callback_should_SetCurrentMinuteInInputStruct(void)

{



    uint8_t u8CurrentMinute = 5;



    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_TOPIC_TIME_AND_DATE;



    uint8_t mockData[2] = {0, u8CurrentMinute};



    sMessage.au8DataBytes = mockData;

    PomodoroFsm_callback(sMessage);



    UnityAssertEqualNumber((UNITY_INT)((u8CurrentMinute)), (UNITY_INT)((sPomodoroFsmInputs.u8CurrentMinute)), (((void*)0)), (UNITY_UINT)(99), UNITY_DISPLAY_STYLE_INT);





    u8CurrentMinute = 10;

    mockData[1] = u8CurrentMinute;

    PomodoroFsm_callback(sMessage);

    UnityAssertEqualNumber((UNITY_INT)((u8CurrentMinute)), (UNITY_INT)((sPomodoroFsmInputs.u8CurrentMinute)), (((void*)0)), (UNITY_UINT)(105), UNITY_DISPLAY_STYLE_INT);

}











void test_PomodoroFsm_execute_should_ChangeStateFromIdleToWorktime_when_TriggerButtonPressedMessage(void)

{









    MessageBroker_publish_CMockIgnoreAndReturn(118, (0));





    ePomodoroFsmState = E_PFSM_STATE_IDLE;





    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(133), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(134), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(137), UNITY_DISPLAY_STYLE_INT);

}



void test_PomodoroFsm_execute_should_ChangeStateFromIdleToSeekingAttention_when_5MinutesPassedWithoutButtonPressed(void)

{









    MessageBroker_publish_CMockIgnoreAndReturn(146, (0));



    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_TOPIC_TIME_AND_DATE;

    uint8_t u8CurrentMinute = 10;





    ePomodoroFsmState = E_PFSM_STATE_IDLE;







    for (uint8_t u8Counter = u8CurrentMinute; u8Counter < (5 + u8CurrentMinute + 1); u8Counter++)

    {



        uint8_t mockData[2] = {0, u8Counter};

        sMessage.au8DataBytes = mockData;

        PomodoroFsm_callback(sMessage);





        PomodoroFsm_execute();

    }





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_SEEKING_ATTENTION)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(169), UNITY_DISPLAY_STYLE_INT);

}



void test_PomodoroFsm_execute_should_ChangeStateFromSeekingAttentionToWorktime_when_TriggerButtonPressedMessage(void)

{









    MessageBroker_publish_CMockIgnoreAndReturn(178, (0));



    ePomodoroFsmState = E_PFSM_STATE_SEEKING_ATTENTION;





    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(191), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(192), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_SEEKING_ATTENTION)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(193), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(196), UNITY_DISPLAY_STYLE_INT);

}



void test_PomodoroFsm_execute_should_ChangeStateFromWorktimeToIdle_when_TriggerButtonPressedMessage(void)

{











    bRunOnce = 1;





    MessageBroker_publish_CMockIgnoreAndReturn(209, (0));





    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;





    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);













    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(227), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(228), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(229), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(232), UNITY_DISPLAY_STYLE_INT);

}



void test_PomodoroFsm_execute_should_ChangeStateFromWorktimeToBreaktime_when_WorktimeElapsed(void)

{











    bRunOnce = 1;





    MessageBroker_publish_CMockIgnoreAndReturn(245, (0));





    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;





    sPomodoroFsmInputs.u8CurrentMinute = 10;

    sPomodoroFsmInputs.u8WorktimeEndMin = sPomodoroFsmInputs.u8CurrentMinute;





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(258), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_BREAKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(259), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_WORKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(260), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_BREAKTIME)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(263), UNITY_DISPLAY_STYLE_INT);

}



void test_PomodoroFsm_execute_should_ChangeStateFromBreaktimeToIdle_when_BreaktimeIsOver(void)

{











    MessageBroker_publish_CMockIgnoreAndReturn(273, (0));





    ePomodoroFsmState = E_PFSM_STATE_BREAKTIME;





    sPomodoroFsmInputs.u8CurrentMinute = 10;

    sPomodoroFsmInputs.u8BreaktimeEndMin = sPomodoroFsmInputs.u8CurrentMinute;





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(286), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(287), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_BREAKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(288), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(291), UNITY_DISPLAY_STYLE_INT);

}



void test_PomodoroFsm_execute_should_ChangeStateFromBreaktimeToIdle_when_TriggerButtonPressedMessage(void)

{











    MessageBroker_publish_CMockIgnoreAndReturn(301, (0));



    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_TOPIC_TRIGGER_BUTTON_PRESSED;

    PomodoroFsm_callback(sMessage);





    ePomodoroFsmState = E_PFSM_STATE_BREAKTIME;





    PomodoroFsm_execute();





    UnityAssertEqualNumber((UNITY_INT)((E_TOPIC_PFSM_STATE_CHANGED)), (UNITY_INT)((sPublishingMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(314), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((sPublishingMessage.au8DataBytes[0])), (((void*)0)), (UNITY_UINT)(315), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_BREAKTIME)), (UNITY_INT)((sPublishingMessage.au8DataBytes[1])), (((void*)0)), (UNITY_UINT)(316), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((ePomodoroFsmState)), (((void*)0)), (UNITY_UINT)(319), UNITY_DISPLAY_STYLE_INT);

}













void test_PomodoroFsm_execute_should_SetTheTimestampsInitiallyInWorktimeState(void)

{



    ePomodoroFsmState = E_PFSM_STATE_WORKTIME;





    uint8_t u8CurrentMinute = 17;

    uint8_t u8WorktimeEndMin = 0;

    uint8_t u8BreaktimeEndMin = 0;





    MessageBroker_message_t sMessage;

    sMessage.eMsgTopic = E_TOPIC_TIME_AND_DATE;

    uint8_t au8TmpData[6] = {0};

    au8TmpData[1] = u8CurrentMinute;

    sMessage.au8DataBytes = au8TmpData;



    PomodoroFsm_callback(sMessage);





    UnityAssertEqualNumber((UNITY_INT)((u8CurrentMinute)), (UNITY_INT)((sPomodoroFsmInputs.u8CurrentMinute)), (((void*)0)), (UNITY_UINT)(347), UNITY_DISPLAY_STYLE_INT);





    PomodoroFsm_execute();





    do {if (((u8WorktimeEndMin) != (sPomodoroFsmInputs.u8WorktimeEndMin))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(353)));}} while(0);

    do {if (((u8BreaktimeEndMin) != (sPomodoroFsmInputs.u8BreaktimeEndMin))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(354)));}} while(0);





    u8CurrentMinute = 40;

    u8WorktimeEndMin = 56;

    u8BreaktimeEndMin = 58;





    sMessage.eMsgTopic = E_TOPIC_TIME_AND_DATE;

    au8TmpData[1] = u8CurrentMinute;

    sMessage.au8DataBytes = au8TmpData;



    PomodoroFsm_callback(sMessage);





    PomodoroFsm_execute();





    do {if (((u8WorktimeEndMin) != (sPomodoroFsmInputs.u8WorktimeEndMin))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(372)));}} while(0);

    do {if (((u8BreaktimeEndMin) != (sPomodoroFsmInputs.u8BreaktimeEndMin))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(373)));}} while(0);

}











void test_PomodoroFsm_calculateTimeStampsForChangingStates_should_CalculateTimeStamps(void)

{

    uint8_t u8CurrentMinute = 17;

    uint8_t u8WorktimeEndMin = 0;

    uint8_t u8BreaktimeEndMin = 0;



    PomodoroFsm_calculateTimeStampsForChangingStates(

        &u8WorktimeEndMin, &u8BreaktimeEndMin, &u8CurrentMinute);



    UnityAssertEqualNumber((UNITY_INT)((7)), (UNITY_INT)((u8WorktimeEndMin)), (((void*)0)), (UNITY_UINT)(389), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((17)), (UNITY_INT)((u8BreaktimeEndMin)), (((void*)0)), (UNITY_UINT)(390), UNITY_DISPLAY_STYLE_INT);

}
