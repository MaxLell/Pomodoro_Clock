#include "../User/MessageBroker/MessageBroker.h"
#include "unity.h"

extern msgTopic_t *pasMsgTopicLib[E_TOPIC_LAST_TOPIC];
extern msgTopic_t saMsg[E_TOPIC_LAST_TOPIC];

void setUp(void)
{
  /*
  Reset the callback arrays with the init function
  */
  MessageBroker_init();
}

void tearDown(void) {}

uint32_t u32CallbackTestMessage1Counter_1;
status_e testyMsg1Callback_1(msg_t *in_sMessage)
{
  u32CallbackTestMessage1Counter_1++;
  return STATUS_OK;
}

uint32_t u32CallbackTestMessage2Counter_2;
status_e testyMsg2Callback_2(msg_t *in_sMessage)
{
  u32CallbackTestMessage2Counter_2++;
  return STATUS_OK;
}

uint32_t u32CallbackMsg0204Counter;
status_e testyMsgCallback(msg_t *in_sMessage)
{
  u32CallbackMsg0204Counter++;
  return STATUS_OK;
}

void test_MessageBroker_init_shall_InitializeAllCallbackArraysToBeZero()
{
  // Set some dummy function into the callback array before hand
  saMsg[MSG_0001].aCallbackArray[0] = testyMsgCallback;
  saMsg[MSG_0002].aCallbackArray[0] = testyMsgCallback;

  // run the init function
  MessageBroker_init();

  // make sure that afterwards the Callbacks are all pointing to NULL
  TEST_ASSERT_EQUAL(NULL, saMsg[MSG_0001].aCallbackArray[0]);
  TEST_ASSERT_EQUAL(NULL, saMsg[MSG_0002].aCallbackArray[0]);
}

void test_MessageBroker_subscribe_shall_PlaceFunctionPointerAtEmptySpot()
{
  /* Clears all the Callback Arrays and sets all of its entries to NULL*/
  MessageBroker_init();
  status_e tStatus;

  /* Write one Callback function into the first spot */
  MessageBroker_subscribe(MSG_0001, testyMsgCallback);
  MessageBroker_subscribe(MSG_0002, testyMsgCallback);

  TEST_ASSERT_NOT_EQUAL(NULL, saMsg[MSG_0001].aCallbackArray[0]);
  TEST_ASSERT_NOT_EQUAL(NULL, saMsg[MSG_0002].aCallbackArray[0]);

  /* Clears all the Callback Arrays */
  MessageBroker_init();

  TEST_ASSERT_EQUAL(NULL, saMsg[MSG_0001].aCallbackArray[0]);
  TEST_ASSERT_EQUAL(NULL, saMsg[MSG_0002].aCallbackArray[0]);

  /* Only transform a portion of the array */
  for (uint8_t i = 0; i < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; i++)
  {
    if (i < (MESSAGE_BROKER_CALLBACK_ARRAY_SIZE - 2))
    {
      MessageBroker_subscribe(MSG_0002, testyMsgCallback);
      MessageBroker_subscribe(MSG_0001, testyMsgCallback);
    }
  }

  for (uint8_t i = 0; i < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; i++)
  {
    if (i < (MESSAGE_BROKER_CALLBACK_ARRAY_SIZE - 2))
    {
      TEST_ASSERT_NOT_EQUAL(NULL, saMsg[MSG_0001].aCallbackArray[i]);
      TEST_ASSERT_NOT_EQUAL(NULL, saMsg[MSG_0002].aCallbackArray[i]);
    }
    else
    {
      TEST_ASSERT_EQUAL(NULL, saMsg[MSG_0001].aCallbackArray[i]);
      TEST_ASSERT_EQUAL(NULL, saMsg[MSG_0002].aCallbackArray[i]);
    }
  }
}

void test_MessageBroker_subscribe_shall_ReturnStatusNullPointer_when_ProvidedWithANullPointerArgument()
{
  status_e status = MessageBroker_subscribe(MSG_0001, NULL);
  TEST_ASSERT_EQUAL(STATUS_ERROR, status);
}

void test_MessageBroker_publish_shall_PublishItsMessagesOnlyToItsSubscribers()
{
  msg_t tTestMessage1;
  msg_t tTestMessage2;

  tTestMessage1.eMsgId = MSG_0001;
  tTestMessage2.eMsgId = MSG_0002;

  u32CallbackTestMessage1Counter_1 = 0;
  u32CallbackTestMessage2Counter_2 = 0;
  u32CallbackMsg0204Counter = 0;

  MessageBroker_init();

  /* One Module subscribes to the Topic MSG_0002 */
  MessageBroker_subscribe(MSG_0002, testyMsgCallback);

  /**
   * Two Modules subscribe to the Topic MSG_0001
   * This means that the Callback Array now contains
   * two function pointers (in this case they are pointing to the
   * same function)
   */
  MessageBroker_subscribe(MSG_0001, testyMsg1Callback_1);
  MessageBroker_subscribe(MSG_0001, testyMsg1Callback_1);

  /**
   * Add a different callback function that is triggered by
   * the same message.
   */
  MessageBroker_subscribe(MSG_0001, testyMsg2Callback_2);

  /**
   * Publish the messages
   */
  MessageBroker_publish(&tTestMessage1);
  MessageBroker_publish(&tTestMessage2);

  /**
   * The behaviour described above is encapsulated in the
   * values of the TargetCallbackMsg Counter variables.
   * These match the number of subscribe function calls
   */

  uint32_t u32TargetCallbackMsg2010Counter_1 = 2;
  TEST_ASSERT_EQUAL(u32TargetCallbackMsg2010Counter_1,
                    u32CallbackTestMessage1Counter_1);

  uint32_t u32TargetCallbackMsg2010Counter_2 = 1;
  TEST_ASSERT_EQUAL(u32TargetCallbackMsg2010Counter_2,
                    u32CallbackTestMessage2Counter_2);

  uint32_t u32TargetCallbackMsg0204Counter = 1;
  TEST_ASSERT_EQUAL(u32TargetCallbackMsg0204Counter, u32CallbackMsg0204Counter);
}

void test_MessageBroker_publish_should_ReturnError_when_invalidMessageIdIsProvided()
{
  msg_t tTestMessage1;
  tTestMessage1.eMsgId = E_TOPIC_LAST_TOPIC;

  status_e tStatus = MessageBroker_publish(&tTestMessage1);
  TEST_ASSERT_EQUAL(STATUS_ERROR, tStatus);
}

// have 5 subscribers to one topic -> The Message Broker subscribe function
// shall respond with an error

void test_MessageBroker_subscribe_should_ReturnError_when_TooManySubscribersAreAdded()
{
  MessageBroker_init();
  status_e tStatus = STATUS_OK;
  for (uint8_t i = 0; i < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE - 1; i++)
  {
    tStatus = MessageBroker_subscribe(MSG_0001, testyMsgCallback);
    TEST_ASSERT_EQUAL(STATUS_OK, tStatus);
  }

  // Add a sixth subscriber
  tStatus = MessageBroker_subscribe(MSG_0001, testyMsgCallback);
  TEST_ASSERT_EQUAL(STATUS_ERROR, tStatus);
}
