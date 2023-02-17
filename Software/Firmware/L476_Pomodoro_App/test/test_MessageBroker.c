#include "unity.h"

#include "MessageBroker.h"

void setUp(void)
{
}

void tearDown(void)
{
}

extern status_t MessageBroker_addCallbackToArray(
    uint16_t in_u16MsgID,
    Module_msgCallback in_p32FunctionCallback);

extern MessageBroker_msgDictinary_t sMsg2010;
void test_MessageBroker_init_shall_initializeADictinariesID()
{
    /* Checi */
    uint16_t u16PrevId = sMsg2010.u16Id;

    status_t status = MessageBroker_init();
    TEST_ASSERT_EQUAL(STATUS_OK, status);

    uint16_t u16AfterId = sMsg2010.u16Id;

    TEST_ASSERT_NOT_EQUAL(u16PrevId, u16AfterId);
}

void test_MessageBroker_init_shall_initializeADictinariesCallbackArray()
{
    Module_msgCallback *callbackArrayPointer = sMsg2010.au32CallbackArray;
    uint16_t callbackArrayLength = sMsg2010.u16MaxSize;
    uint16_t callbackArrayHighWaterMark = sMsg2010.u16HighWaterMark;

    // log_info("Array Pointer    = %p", callbackArrayPointer);
    // log_info("Array Length     = %d", callbackArrayLength);
    // log_info("Array Water Mark = %d", callbackArrayHighWaterMark);

    status_t status = MessageBroker_init();
    TEST_ASSERT_EQUAL(STATUS_OK, status);

    // log_info("Array Pointer    = %p", callbackArrayPointer);
    // log_info("Array Length     = %d", callbackArrayLength);
    // log_info("Array Water Mark = %d", callbackArrayHighWaterMark);

    /* Check whether all elements are initialized to 0 */
    for (uint8_t i = 0; i < callbackArrayLength; i++)
    {
        TEST_ASSERT_EQUAL(NULL, callbackArrayPointer[i]);
    }
}

/* Prepare the Callback */
status_t dummy_callback(MessageBroker_message_t in_sMessage)
{
    return STATUS_OK;
}

void test_MessageBroker_MessageBroker_addCallbackToArray_shall_AddACallbackToItsArray()
{
    Module_msgCallback *callbackArrayPointer = sMsg2010.au32CallbackArray;
    uint16_t callbackArrayLength = sMsg2010.u16MaxSize;
    uint16_t callbackArrayHighWaterMark = sMsg2010.u16HighWaterMark;

    // log_info("Array Pointer    = %p", callbackArrayPointer);
    // log_info("Array Length     = %d", callbackArrayLength);
    // log_info("Array Water Mark = %d", callbackArrayHighWaterMark);

    status_t status = MessageBroker_init();
    TEST_ASSERT_EQUAL(STATUS_OK, status);

    TEST_ASSERT_NOT_EQUAL(NULL, dummy_callback);

    MessageBroker_addCallbackToArray(2010, dummy_callback);

    /* When the callback is added to the array at least one element is no longer pointing to 0 */
    uint8_t ctr = 0;
    for (uint8_t i = 0; i < callbackArrayLength; i++)
    {
        /* Run through the array and count the number
           of changed pointer locations */
        // log_info("callback pointer = %p", (callbackArrayPointer)[i]);

        if (NULL != (callbackArrayPointer)[i])
        {
            ctr++;
        }
    }
    TEST_ASSERT_NOT_EQUAL(0, ctr);
    TEST_ASSERT_EQUAL(callbackArrayHighWaterMark + 1, sMsg2010.u16HighWaterMark);
}

void test_MessageBroker_MessageBroker_addCallbackToArray_shall_ReturnStatusNULL_when_NULLPtrProvided()
{
    status_t status = MessageBroker_init();
    TEST_ASSERT_EQUAL(STATUS_OK, status);

    status = MessageBroker_addCallbackToArray(2010, NULL);
    TEST_ASSERT_EQUAL(STATUS_NULL_POINTER, status);
}
