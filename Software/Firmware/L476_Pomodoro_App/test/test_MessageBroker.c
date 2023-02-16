#include "unity.h"

#include "MessageBroker.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_MessageBroker_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement MessageBroker");
}

/**
 * Message Broker
 * Message_getCallbackFunctions is to be tested first
 */

void test_MessageBroker_getCallbackFunctions_shall_ReturnAnArrayOfFunctionPointers()
{
    TEST_IGNORE_MESSAGE("Need to Implement MessageBroker");
}
extern status_t MessageBroker_addCallbackToArray(
    uint16_t in_u16MsgID,
    Module_msgCallback in_p32FunctionCallback);

void test_MessageBroker_MessageBroker_addCallbackToArray_shall_ReturnAStatusThatIndicatesANullPointer_when_ProvidedWithNullPtr()
{
    status_t status = MessageBroker_addCallbackToArray(10, NULL);
    TEST_ASSERT_EQUAL(STATUS_NULL_POINTER, status);
}
