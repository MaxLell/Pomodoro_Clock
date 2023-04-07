#include "User/MessageBroker/MessageBroker.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




void setUp(void)

{









    MessageBroker_init();

}



void tearDown(void)

{

}



extern MessageBroker_msgDictinary_t sTestTopic_1;

extern MessageBroker_msgDictinary_t sTestTopic_2;

extern MessageBroker_msgDictinary_t *sMessageTopicIndex;



void test_MessageBroker_init_shall_InitializeAllCallbackArraysToBeZero()

{

    for (uint8_t i = 0; i < 5; i++)

    {

        sTestTopic_1.aCallbackArray[i] = (Module_msgCallback_t)0x1a1a1a1a;

        sTestTopic_2.aCallbackArray[i] = (Module_msgCallback_t)0x1a1a1a1a;

    }



    MessageBroker_init();



    for (uint8_t i = 0; i < 5; i++)

    {

        UnityAssertEqualNumber((UNITY_INT)((((void*)0))), (UNITY_INT)((sTestTopic_1.aCallbackArray[i])), (((void*)0)), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_INT);

        UnityAssertEqualNumber((UNITY_INT)((((void*)0))), (UNITY_INT)((sTestTopic_2.aCallbackArray[i])), (((void*)0)), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_INT);

    }

}



status_t dummyMsg2010Callback(MessageBroker_message_t in_sMessage)

{

    return (0);

}



status_t dummyMsg0204Callback(MessageBroker_message_t in_sMessage)

{

    return (0);

}



void test_MessageBroker_subscribe_shall_PlaceFunctionPointerAtEmptySpot()

{



    MessageBroker_init();





    MessageBroker_subscribe(E_TEST_2, dummyMsg0204Callback);

    MessageBroker_subscribe(E_TEST_1, dummyMsg2010Callback);



    do {if (((((void*)0)) != (sTestTopic_2.aCallbackArray[0]))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(58)));}} while(0);

    do {if (((((void*)0)) != (sTestTopic_1.aCallbackArray[0]))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(59)));}} while(0);





    MessageBroker_init();

    UnityAssertEqualNumber((UNITY_INT)((((void*)0))), (UNITY_INT)((sTestTopic_2.aCallbackArray[0])), (((void*)0)), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((((void*)0))), (UNITY_INT)((sTestTopic_1.aCallbackArray[0])), (((void*)0)), (UNITY_UINT)(64), UNITY_DISPLAY_STYLE_INT);





    for (uint8_t i = 0; i < 5; i++)

    {

        if (i < (5 - 2))

        {

            MessageBroker_subscribe(E_TEST_2, dummyMsg0204Callback);

            MessageBroker_subscribe(E_TEST_1, dummyMsg2010Callback);

        }

    }



    for (uint8_t i = 0; i < 5; i++)

    {

        if (i < (5 - 2))

        {

            do {if (((((void*)0)) != (sTestTopic_2.aCallbackArray[i]))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(80)));}} while(0);

            do {if (((((void*)0)) != (sTestTopic_1.aCallbackArray[i]))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(81)));}} while(0);

        }

        else

        {

            UnityAssertEqualNumber((UNITY_INT)((((void*)0))), (UNITY_INT)((sTestTopic_2.aCallbackArray[i])), (((void*)0)), (UNITY_UINT)(85), UNITY_DISPLAY_STYLE_INT);

            UnityAssertEqualNumber((UNITY_INT)((((void*)0))), (UNITY_INT)((sTestTopic_1.aCallbackArray[i])), (((void*)0)), (UNITY_UINT)(86), UNITY_DISPLAY_STYLE_INT);

        }

    }

}



void test_MessageBroker_subscribe_shall_ReturnStatusNullPointer_when_ProvidedWithANullPointerArgument()

{

    status_t status = MessageBroker_subscribe(E_TEST_1, ((void*)0));

    UnityAssertEqualNumber((UNITY_INT)(((31))), (UNITY_INT)((status)), (((void*)0)), (UNITY_UINT)(94), UNITY_DISPLAY_STYLE_INT);

}



uint32_t u32CallbackTestMessage1Counter_1;

status_t testyMsg1Callback_1(MessageBroker_message_t in_sMessage)

{

    u32CallbackTestMessage1Counter_1++;

    return (0);

}



uint32_t u32CallbackTestMessage2Counter_2;

status_t testyMsg2Callback_2(MessageBroker_message_t in_sMessage)

{

    u32CallbackTestMessage2Counter_2++;

    return (0);

}



uint32_t u32CallbackMsg0204Counter;

status_t testyMsg0204Callback(MessageBroker_message_t in_sMessage)

{

    u32CallbackMsg0204Counter++;

    return (0);

}

void test_MessageBroker_publish_shall_PublishItsMessagesOnlyToItsSubscribers()

{

    MessageBroker_message_t tTestMessage1;

    MessageBroker_message_t tTestMessage2;



    tTestMessage1.eMsgTopic = E_TEST_1;

    tTestMessage2.eMsgTopic = E_TEST_2;



    u32CallbackTestMessage1Counter_1 = 0;

    u32CallbackTestMessage2Counter_2 = 0;

    u32CallbackMsg0204Counter = 0;



    MessageBroker_init();





    MessageBroker_subscribe(E_TEST_2, testyMsg0204Callback);















    MessageBroker_subscribe(E_TEST_1, testyMsg1Callback_1);

    MessageBroker_subscribe(E_TEST_1, testyMsg1Callback_1);











    MessageBroker_subscribe(E_TEST_1, testyMsg2Callback_2);









    MessageBroker_publish(tTestMessage1);

    MessageBroker_publish(tTestMessage2);















    uint32_t u32TargetCallbackMsg2010Counter_1 = 2;

    UnityAssertEqualNumber((UNITY_INT)((u32TargetCallbackMsg2010Counter_1)), (UNITY_INT)((u32CallbackTestMessage1Counter_1)), (((void*)0)), (UNITY_UINT)(162), UNITY_DISPLAY_STYLE_INT);



    uint32_t u32TargetCallbackMsg2010Counter_2 = 1;

    UnityAssertEqualNumber((UNITY_INT)((u32TargetCallbackMsg2010Counter_2)), (UNITY_INT)((u32CallbackTestMessage2Counter_2)), (((void*)0)), (UNITY_UINT)(165), UNITY_DISPLAY_STYLE_INT);



    uint32_t u32TargetCallbackMsg0204Counter = 1;

    UnityAssertEqualNumber((UNITY_INT)((u32TargetCallbackMsg0204Counter)), (UNITY_INT)((u32CallbackMsg0204Counter)), (((void*)0)), (UNITY_UINT)(168), UNITY_DISPLAY_STYLE_INT);

}
