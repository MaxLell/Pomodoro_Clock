#include "src/MessageBroker.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}



void test_MessageBroker_NeedToImplement(void)

{

    UnityIgnore( (("Need to Implement MessageBroker")), (UNITY_UINT)(15));

}













void test_MessageBroker_getCallbackFunctions_shall_ReturnAnArrayOfFunctionPointers()

{

    UnityIgnore( (("Need to Implement MessageBroker")), (UNITY_UINT)(25));

}

extern status_t MessageBroker_addCallbackToArray(

    uint16_t in_u16MsgID,

    Module_msgCallback in_p32FunctionCallback);



void test_MessageBroker_MessageBroker_addCallbackToArray_shall_ReturnAStatusThatIndicatesANullPointer_when_ProvidedWithNullPtr()

{

    status_t status = MessageBroker_addCallbackToArray(10, ((void*)0));





    UnityAssertEqualNumber((UNITY_INT)(((16))), (UNITY_INT)((status)), (((void*)0)), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_INT);

}
