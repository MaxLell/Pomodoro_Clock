#include "src/MessageBroker.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}



extern MessageBroker_msgDictinary_t sMsg2010;

void test_MessageBroker_init_shall_initializeADictinariesID()

{



    uint16_t u16PrevId = sMsg2010.u16Id;



    status_t status = MessageBroker_init();

    UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((status)), (((void*)0)), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_INT);



    uint16_t u16AfterId = sMsg2010.u16Id;



    do {if (((u16PrevId) != (u16AfterId))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(24)));}} while(0);

}



void test_MessageBroker_init_shall_initializeADictinariesCallbackArray()

{

    Module_msgCallback_t *callbackArrayPointer = sMsg2010.au32CallbackArray;

    uint16_t callbackArrayLength = sMsg2010.u16MaxSize;

    uint16_t callbackArrayHighWaterMark = sMsg2010.u16HighWaterMark;



    status_t status = MessageBroker_init();

    UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((status)), (((void*)0)), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_INT);





    for (uint8_t i = 0; i < callbackArrayLength; i++)

    {

        UnityAssertEqualNumber((UNITY_INT)((((void*)0))), (UNITY_INT)((callbackArrayPointer[i])), (((void*)0)), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_INT);

    }

}



void test_MessageBroker_MessageBroker_addCallbackToArray_shall_ReturnStatusNULL_when_NULLPtrProvided()

{

    status_t status = MessageBroker_init();

    UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((status)), (((void*)0)), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_INT);



    status = MessageBroker_subscribe(2010, ((void*)0));

    UnityAssertEqualNumber((UNITY_INT)(((31))), (UNITY_INT)((status)), (((void*)0)), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_INT);

}





status_t dummy_callback(MessageBroker_message_t in_sMessage)

{

    return (0);

}



void test_MessageBroker_MessageBroker_addCallbackToArray_shall_AddACallbackToItsArray()

{

    Module_msgCallback_t *callbackArrayPointer = sMsg2010.au32CallbackArray;

    uint16_t callbackArrayLength = sMsg2010.u16MaxSize;

    uint16_t callbackArrayHighWaterMark = sMsg2010.u16HighWaterMark;



    status_t status = MessageBroker_init();

    UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((status)), (((void*)0)), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_INT);



    do {if (((((void*)0)) != (dummy_callback))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(67)));}} while(0);



    MessageBroker_subscribe(2010, dummy_callback);





    uint8_t ctr = 0;

    for (uint8_t i = 0; i < callbackArrayLength; i++)

    {





        if (((void*)0) != (callbackArrayPointer)[i])

        {

            ctr++;

        }

    }

    do {if (((0) != (ctr))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(82)));}} while(0);

}
