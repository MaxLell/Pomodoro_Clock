#include "Button_Model.h"
#include "MessageBroker.h"
#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

uint8_t u8CallCounter = 0;

status_t ButtonEventCallback(MessageBroker_message_t in_tMessage) {
  /**
   * The function shall only called once - there is only one subscriber
   * in this Test Case
   */

  u8CallCounter++;
  TEST_ASSERT_EQUAL(1, u8CallCounter);

  /**
   * Disassemble the message and check on the content
   * The content must be
   *
   * typedef struct
   * {
   *   MessageTopics_e eMsgTopic; <- E_TRIGGER_BUTTON_EVENT
   *   uint16_t u16DataSize;                    <- 1
   *   uint32_t *au32Data;                      <- an array of the length of 1,
   * which contains a BOOL of TRUE } MessageBroker_message_t;
   */
  TEST_ASSERT_EQUAL(E_TRIGGER_BUTTON_EVENT, in_tMessage.eMsgTopic);
  TEST_ASSERT_EQUAL(1, in_tMessage.u16DataSize);
  TEST_ASSERT_EQUAL(TRUE, in_tMessage.au32Data[0]);

  return STATUS_OK;
}

void test_Button_Model_publishData_ShallSendOutAValidMessage(void) {
  MessageBroker_init();
  MessageBroker_subscribe(E_TRIGGER_BUTTON_EVENT, ButtonEventCallback);
  u8CallCounter = 0;

  BOOL bButtonWasPressed = TRUE;
  Button_Model_publishData(bButtonWasPressed);

  /* The function shall be called exactly once */
  TEST_ASSERT_EQUAL(1, u8CallCounter);
}

void test_Button_Model_publishData_ShallNotSendOutAnInvalidMessage(void) {
  MessageBroker_init();
  MessageBroker_subscribe(E_TRIGGER_BUTTON_EVENT, ButtonEventCallback);
  u8CallCounter = 0;

  BOOL bButtonWasPressed = FALSE;
  Button_Model_publishData(bButtonWasPressed);

  /* The function shall be called exactly once */
  TEST_ASSERT_EQUAL(0, u8CallCounter);
}
