#include "User/PomodoroFsm/PomodoroFsm.h"
#include "build/test/mocks/mock_RgbLed.h"
#include "build/test/mocks/mock_MessageBroker.h"
#include "User/LightControl/LightControl.h"
#include "User/Common/Config.h"
#include "User/Common/Common.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


void setUp(void)

{

}



void tearDown(void)

{

}









extern status_t LightControl_fillMinuteToColorArray(uint8_t in_u8CurrentMinute,

                                                    uint8_t in_u8WorktimeIntervalMin,

                                                    uint8_t in_u8BreaktimeIntervalMin,

                                                    uint8_t *inout_au8ColorArray);



extern status_t LightControl_removeColorsFromMinuteArray(uint8_t *inout_au8MinuteToColorArray,

                                                         uint8_t in_u8CurrentMinute);



extern status_t LightControl_fillLedToColorArray(uint8_t *in_au8MinuteToColorArray,

                                                 uint8_t *inout_au8LedToColorArray);



extern status_t LightControl_setLedsToColor(uint8_t *in_au8LedToColorArray);











extern uint8_t u8PFsmState;

extern uint8_t u8CurrentMinute;

extern uint8_t u8PFsmState;

extern uint8_t u8LightControlState;

extern BOOL bPomodoroSequenceInitialized;











void helper_printArray(uint8_t *in_au8Array, uint8_t in_u8ArraySize)

{

    for (uint8_t i = 0; i < in_u8ArraySize; i++)

    {

        if (i < 10)

        {

            printf("%d  ", i);

        }

        else

        {

            printf("%d ", i);

        }

    }

    printf("\n");

    for (uint8_t i = 0; i < in_u8ArraySize; i++)

    {

        printf("%d  ", in_au8Array[i]);

    }

    printf("\n");

}



void test_LightControl_fillMinuteToColorArray_Test4()

{







    uint8_t u8TestCurrentMinute = 17;

    uint8_t u8TestWorktimeIntervalMin = 50;

    uint8_t u8TestBreaktimeIntervalMin = 7;

    uint8_t au8TestMinuteToColorArray[60] = {0};



    LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);





    for (uint8_t u8Index = 0; u8Index < 7; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_RED)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(87), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 7; u8Index < 14; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_GREEN)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(93), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 14; u8Index < 17; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(99), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 17; u8Index < 60; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_RED)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(105), UNITY_DISPLAY_STYLE_INT);

    }

}













void test_LightControl_fillMinuteToColorArray_Test6()

{

    uint8_t u8TestCurrentMinute = 61;

    uint8_t u8TestWorktimeIntervalMin = 0;

    uint8_t u8TestBreaktimeIntervalMin = 0;

    uint8_t au8TestMinuteToColorArray[60] = {0};



    uint8_t u8Status = LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    UnityAssertEqualNumber((UNITY_INT)(((4))), (UNITY_INT)((u8Status)), (((void*)0)), (UNITY_UINT)(127), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_fillMinuteToColorArray_Test7()

{

    uint8_t u8TestCurrentMinute = 0;

    uint8_t u8TestWorktimeIntervalMin = 61;

    uint8_t u8TestBreaktimeIntervalMin = 0;

    uint8_t au8TestMinuteToColorArray[60] = {0};



    uint8_t u8Status = LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    UnityAssertEqualNumber((UNITY_INT)(((4))), (UNITY_INT)((u8Status)), (((void*)0)), (UNITY_UINT)(148), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_fillMinuteToColorArray_Test8()

{

    uint8_t u8TestCurrentMinute = 0;

    uint8_t u8TestWorktimeIntervalMin = 10;

    uint8_t u8TestBreaktimeIntervalMin = 60;

    uint8_t au8TestMinuteToColorArray[60] = {0};



    uint8_t u8Status = LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    UnityAssertEqualNumber((UNITY_INT)(((4))), (UNITY_INT)((u8Status)), (((void*)0)), (UNITY_UINT)(169), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_fillMinuteToColorArray_Test9()

{

    uint8_t u8TestCurrentMinute = 0;

    uint8_t u8TestWorktimeIntervalMin = 67;

    uint8_t u8TestBreaktimeIntervalMin = 10;

    uint8_t au8TestMinuteToColorArray[60] = {0};



    uint8_t u8Status = LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    UnityAssertEqualNumber((UNITY_INT)(((4))), (UNITY_INT)((u8Status)), (((void*)0)), (UNITY_UINT)(190), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_fillLedToColorArray_Test11()

{

    uint8_t u8TestCurrentMinute = 0;

    uint8_t u8TestWorktimeIntervalMin = 30;

    uint8_t u8TestBreaktimeIntervalMin = 20;

    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t au8TestLedToColorArray[24] = {0};



    LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    LightControl_fillLedToColorArray(au8TestMinuteToColorArray, au8TestLedToColorArray);



    float u8LedsPerMinute = (float)24 / (float)60;



    for (float i = 0; i < 60; i++)

    {

        uint8_t index = (uint8_t)(i * u8LedsPerMinute);

        UnityAssertEqualNumber((UNITY_INT)((au8TestMinuteToColorArray[(uint8_t)i])), (UNITY_INT)((au8TestLedToColorArray[index])), (((void*)0)), (UNITY_UINT)(219), UNITY_DISPLAY_STYLE_INT);

    }

}















void test_LightControl_removeColorsFromMinuteArray_Test12()

{

    uint8_t u8TestCurrentMinute = 0;

    uint8_t u8TestWorktimeIntervalMin = 30;

    uint8_t u8TestBreaktimeIntervalMin = 20;

    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t au8TestLedToColorArray[24] = {0};



    LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    LightControl_removeColorsFromMinuteArray(au8TestMinuteToColorArray, u8TestCurrentMinute);

    UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8TestCurrentMinute])), (((void*)0)), (UNITY_UINT)(244), UNITY_DISPLAY_STYLE_INT);





    u8TestCurrentMinute = 12;

    LightControl_removeColorsFromMinuteArray(au8TestMinuteToColorArray, u8TestCurrentMinute);

    UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8TestCurrentMinute])), (((void*)0)), (UNITY_UINT)(249), UNITY_DISPLAY_STYLE_INT);

}















void test_LightControl_removeColorsFromMinuteArray_Test13()

{

    uint8_t u8TestCurrentMinute = 25;

    uint8_t u8TestWorktimeIntervalMin = 30;

    uint8_t u8TestBreaktimeIntervalMin = 20;

    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t au8TestLedToColorArray[24] = {0};



    LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    for (uint8_t i = 0; i < 60; i++)

    {

        LightControl_removeColorsFromMinuteArray(au8TestMinuteToColorArray, i);

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[i])), (((void*)0)), (UNITY_UINT)(275), UNITY_DISPLAY_STYLE_INT);

    }

}













void test_LightControl_init_should_SubscribeToMessageBrokerTopics()

{



    MessageBroker_subscribe_CMockExpectAndReturn(290, E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE, ((void*)0), (0));







    MessageBroker_subscribe_CMockIgnoreArg_in_p32FunctionCallback(291);





    MessageBroker_subscribe_CMockExpectAndReturn(297, E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED, ((void*)0), (0));







    MessageBroker_subscribe_CMockIgnoreArg_in_p32FunctionCallback(298);

    LightControl_init();

}













void test_LightControl_init_should_SetInternalPfsmAndLightControlStateToIdle()

{



    MessageBroker_subscribe_CMockExpectAndReturn(313, E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE, ((void*)0), (0));







    MessageBroker_subscribe_CMockIgnoreArg_in_p32FunctionCallback(314);





    MessageBroker_subscribe_CMockExpectAndReturn(320, E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED, ((void*)0), (0));







    MessageBroker_subscribe_CMockIgnoreArg_in_p32FunctionCallback(321);



    LightControl_init();



    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_IDLE)), (UNITY_INT)((u8PFsmState)), (((void*)0)), (UNITY_UINT)(325), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_LCTRL_STATE_IDLE)), (UNITY_INT)((u8LightControlState)), (((void*)0)), (UNITY_UINT)(326), UNITY_DISPLAY_STYLE_INT);

}













extern status_t LightControl_messageBrokerCallback(MessageBroker_message_t in_tMessage);

void test_LightControl_messageBrokerCallback_should_ParseCurrentTimeAndSetCurrentMinute()

{

    MessageBroker_message_t tTestMessage;

    tTestMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE;

    uint8_t au8TestTime[2] = {0, 50};

    tTestMessage.au8DataBytes = au8TestTime;

    tTestMessage.u16DataSize = 2;

    LightControl_messageBrokerCallback(tTestMessage);



    UnityAssertEqualNumber((UNITY_INT)((50)), (UNITY_INT)((u8CurrentMinute)), (((void*)0)), (UNITY_UINT)(344), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_messageBrokerCallback_should_ParsePFSMState()

{

    u8PFsmState = 0;

    MessageBroker_message_t tTestMessage;

    tTestMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED;

    uint8_t au8TestPFSMStates[2] = {E_PFSM_STATE_SEEKING_ATTENTION, E_PFSM_STATE_IDLE};

    tTestMessage.au8DataBytes = au8TestPFSMStates;

    tTestMessage.u16DataSize = 2;

    LightControl_messageBrokerCallback(tTestMessage);



    UnityAssertEqualNumber((UNITY_INT)((E_PFSM_STATE_SEEKING_ATTENTION)), (UNITY_INT)((u8PFsmState)), (((void*)0)), (UNITY_UINT)(362), UNITY_DISPLAY_STYLE_INT);

}











void test_LightControl_messageBrokerCallback_should_ReturnStatusOk_when_EverythingIsFine()

{

    MessageBroker_message_t tTestMessage;

    tTestMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE;

    uint8_t au8TestTime[2] = {0, 50};

    tTestMessage.au8DataBytes = au8TestTime;

    tTestMessage.u16DataSize = 2;

    UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((LightControl_messageBrokerCallback(tTestMessage))), (((void*)0)), (UNITY_UINT)(376), UNITY_DISPLAY_STYLE_INT);



    tTestMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED;

    uint8_t au8TestPFSMStates[2] = {E_PFSM_STATE_SEEKING_ATTENTION, E_PFSM_STATE_IDLE};

    tTestMessage.au8DataBytes = au8TestPFSMStates;

    tTestMessage.u16DataSize = 2;

    UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((LightControl_messageBrokerCallback(tTestMessage))), (((void*)0)), (UNITY_UINT)(382), UNITY_DISPLAY_STYLE_INT);

}











void test_LightControl_messageBrokerCallback_should_ReturnStatusInvalidArg_when_MessageTopicIsNotSupported()

{

    MessageBroker_message_t tTestMessage;

    tTestMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED + 1;

    uint8_t au8TestTime[2] = {0, 50};

    tTestMessage.au8DataBytes = au8TestTime;

    tTestMessage.u16DataSize = 2;

    UnityAssertEqualNumber((UNITY_INT)(((4))), (UNITY_INT)((LightControl_messageBrokerCallback(tTestMessage))), (((void*)0)), (UNITY_UINT)(396), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_execute_should_ReturnStatusOk_when_EverythingIsFine()

{

    UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((LightControl_execute())), (((void*)0)), (UNITY_UINT)(406), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_execute_should_TransitionFromIdleToSeekingAttention_when_PFSMChangesToSeekingAttention()

{

    u8PFsmState = E_PFSM_STATE_IDLE;

    u8LightControlState = E_LCTRL_STATE_IDLE;

    LightControl_execute();

    UnityAssertEqualNumber((UNITY_INT)((E_LCTRL_STATE_IDLE)), (UNITY_INT)((u8LightControlState)), (((void*)0)), (UNITY_UINT)(419), UNITY_DISPLAY_STYLE_INT);



    u8PFsmState = E_PFSM_STATE_SEEKING_ATTENTION;

    LightControl_execute();

    UnityAssertEqualNumber((UNITY_INT)((E_LCTRL_STATE_SEEKING_ATTENTION)), (UNITY_INT)((u8LightControlState)), (((void*)0)), (UNITY_UINT)(423), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_execute_should_TransitionFromSeekingAttentionToPomodoroWorktime_when_PFSMChangesToWorktime()

{

    u8PFsmState = E_PFSM_STATE_SEEKING_ATTENTION;

    u8LightControlState = E_LCTRL_STATE_SEEKING_ATTENTION;

    LightControl_execute();

    UnityAssertEqualNumber((UNITY_INT)((E_LCTRL_STATE_SEEKING_ATTENTION)), (UNITY_INT)((u8LightControlState)), (((void*)0)), (UNITY_UINT)(436), UNITY_DISPLAY_STYLE_INT);



    u8PFsmState = E_PFSM_STATE_WORKTIME;

    LightControl_execute();

    UnityAssertEqualNumber((UNITY_INT)((E_LCTRL_STATE_POMODORO_WORKTIME)), (UNITY_INT)((u8LightControlState)), (((void*)0)), (UNITY_UINT)(440), UNITY_DISPLAY_STYLE_INT);

}
