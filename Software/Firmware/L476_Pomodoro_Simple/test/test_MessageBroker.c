#include "unity.h"

#include "MessageBroker.h"

void setUp(void)
{
    /*
    Reset the callback arrays with the init function
    */

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
    for (uint8_t i = 0; i < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; i++)
    {
        sTestTopic_1.aCallbackArray[i] = (Module_msgCallback_t)0x1a1a1a1a;
        sTestTopic_2.aCallbackArray[i] = (Module_msgCallback_t)0x1a1a1a1a;
    }

    MessageBroker_init();

    for (uint8_t i = 0; i < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; i++)
    {
        TEST_ASSERT_EQUAL(NULL, sTestTopic_1.aCallbackArray[i]);
        TEST_ASSERT_EQUAL(NULL, sTestTopic_2.aCallbackArray[i]);
    }
}

status_t dummyMsg2010Callback(MessageBroker_message_t in_sMessage)
{
    return STATUS_OK;
}

status_t dummyMsg0204Callback(MessageBroker_message_t in_sMessage)
{
    return STATUS_OK;
}

void test_MessageBroker_subscribe_shall_PlaceFunctionPointerAtEmptySpot()
{
    /* Clears all the Callback Arrays and sets all of its entries to NULL*/
    MessageBroker_init();

    /* Write one Callback function into the first spot */
    MessageBroker_subscribe(E_TEST_2, dummyMsg0204Callback);
    MessageBroker_subscribe(E_TEST_1, dummyMsg2010Callback);

    TEST_ASSERT_NOT_EQUAL(NULL, sTestTopic_2.aCallbackArray[0]);
    TEST_ASSERT_NOT_EQUAL(NULL, sTestTopic_1.aCallbackArray[0]);

    /* Clears all the Callback Arrays */
    MessageBroker_init();
    TEST_ASSERT_EQUAL(NULL, sTestTopic_2.aCallbackArray[0]);
    TEST_ASSERT_EQUAL(NULL, sTestTopic_1.aCallbackArray[0]);

    /* Only transform a portion of the array */
    for (uint8_t i = 0; i < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; i++)
    {
        if (i < (MESSAGE_BROKER_CALLBACK_ARRAY_SIZE - 2))
        {
            MessageBroker_subscribe(E_TEST_2, dummyMsg0204Callback);
            MessageBroker_subscribe(E_TEST_1, dummyMsg2010Callback);
        }
    }

    for (uint8_t i = 0; i < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; i++)
    {
        if (i < (MESSAGE_BROKER_CALLBACK_ARRAY_SIZE - 2))
        {
            TEST_ASSERT_NOT_EQUAL(NULL, sTestTopic_2.aCallbackArray[i]);
            TEST_ASSERT_NOT_EQUAL(NULL, sTestTopic_1.aCallbackArray[i]);
        }
        else
        {
            TEST_ASSERT_EQUAL(NULL, sTestTopic_2.aCallbackArray[i]);
            TEST_ASSERT_EQUAL(NULL, sTestTopic_1.aCallbackArray[i]);
        }
    }
}

void test_MessageBroker_subscribe_shall_ReturnStatusNullPointer_when_ProvidedWithANullPointerArgument()
{
    status_t status = MessageBroker_subscribe(E_TEST_1, NULL);
    TEST_ASSERT_EQUAL(STATUS_NULL_POINTER, status);
}

uint32_t u32CallbackTestMessage1Counter_1;
status_t testyMsg1Callback_1(MessageBroker_message_t in_sMessage)
{
    u32CallbackTestMessage1Counter_1++;
    return STATUS_OK;
}

uint32_t u32CallbackTestMessage2Counter_2;
status_t testyMsg2Callback_2(MessageBroker_message_t in_sMessage)
{
    u32CallbackTestMessage2Counter_2++;
    return STATUS_OK;
}

uint32_t u32CallbackMsg0204Counter;
status_t testyMsg0204Callback(MessageBroker_message_t in_sMessage)
{
    u32CallbackMsg0204Counter++;
    return STATUS_OK;
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

    /* One Module subscribes to the Topic E_TEST_2 */
    MessageBroker_subscribe(E_TEST_2, testyMsg0204Callback);

    /**
     * Two Modules subscribe to the Topic E_TEST_1
     * This means that the Callback Array now contains
     * two function pointers (in this case they are pointing to the
     * same function)
     */
    MessageBroker_subscribe(E_TEST_1, testyMsg1Callback_1);
    MessageBroker_subscribe(E_TEST_1, testyMsg1Callback_1);

    /**
     * Add a different callback function that is triggered by
     * the same message.
     */
    MessageBroker_subscribe(E_TEST_1, testyMsg2Callback_2);

    /**
     * Publish the messages
     */
    MessageBroker_publish(tTestMessage1);
    MessageBroker_publish(tTestMessage2);

    /**
     * The behaviour described above is encapsulated in the
     * values of the TargetCallbackMsg Counter variables.
     * These match the number of subscribe function calls
     */

    uint32_t u32TargetCallbackMsg2010Counter_1 = 2;
    TEST_ASSERT_EQUAL(u32TargetCallbackMsg2010Counter_1, u32CallbackTestMessage1Counter_1);

    uint32_t u32TargetCallbackMsg2010Counter_2 = 1;
    TEST_ASSERT_EQUAL(u32TargetCallbackMsg2010Counter_2, u32CallbackTestMessage2Counter_2);

    uint32_t u32TargetCallbackMsg0204Counter = 1;
    TEST_ASSERT_EQUAL(u32TargetCallbackMsg0204Counter, u32CallbackMsg0204Counter);
}