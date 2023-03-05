#include "MessageBroker.h"

#include "DbgMacros.h"

/**
 * Message 2010, 0204
 * This is only a dummy message for experimentation.
 * You manually need to set these topics here up.
 */
STATIC MessageBroker_msgDictinary_t sTestTopic_1;
STATIC MessageBroker_msgDictinary_t sTestTopic_2;

/**
 * The Message Topics are defined here
 */
STATIC MessageBroker_msgDictinary_t sTopicTriggerButton;

/* Contains all dictinaries, so that they can be searched through iterativly */
STATIC MessageBroker_msgDictinary_t
    *sMessageTopicIndex[MESSAGE_BROKER_NUMBER_OF_MESSAGE_TOPICS] = {NULL};

status_t MessageBroker_init() {
  /* Set the Topics of the respective messages */
  sTestTopic_1.eMsgTopic = E_TEST_1;
  sTestTopic_2.eMsgTopic = E_TEST_2;

  sTopicTriggerButton.eMsgTopic = E_TRIGGER_BUTTON_EVENT;

  /* Place the different topics / message types in the Library */
  sMessageTopicIndex[E_TEST_1] = &sTestTopic_1;
  sMessageTopicIndex[E_TEST_2] = &sTestTopic_2;

  sMessageTopicIndex[E_TRIGGER_BUTTON_EVENT] = &sTopicTriggerButton;

  /* set all the elements of the Callback arrays to zero */
  for (uint16_t topic = 0; topic < MESSAGE_BROKER_NUMBER_OF_MESSAGE_TOPICS;
       topic++) {
    for (uint16_t index = 0; index < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE;
         index++) {
      sMessageTopicIndex[topic]->aCallbackArray[index] = 0;
    }
  }

  return STATUS_OK;
}

status_t MessageBroker_subscribe(MessageBroker_messageTopics_e in_eMsgTopic,
                                 Module_msgCallback_t in_p32FunctionCallback) {
  assert_true(NULL != in_p32FunctionCallback);

  uint16_t u16EmptyPointerPositionIndex = 0;
  for (uint16_t u16ArrayIndex = 0;
       u16ArrayIndex < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; u16ArrayIndex++) {
    /* Find the first element in the callback array, that is not equal 0 */
    if (sMessageTopicIndex[in_eMsgTopic]->aCallbackArray[u16ArrayIndex] == 0) {
      u16EmptyPointerPositionIndex = u16ArrayIndex;
      break;
    }
  }
  if (u16EmptyPointerPositionIndex ==
      (MESSAGE_BROKER_CALLBACK_ARRAY_SIZE - 1)) {
    log_warning("Callback Array for Topic %d is full", in_eMsgTopic);
  }
  sMessageTopicIndex[in_eMsgTopic]
      ->aCallbackArray[u16EmptyPointerPositionIndex] = in_p32FunctionCallback;
  return STATUS_OK;
}

status_t MessageBroker_publish(MessageBroker_message_t in_tMessage) {
  /* find the dictinary that corresponds to the message's Topic */
  MessageBroker_messageTopics_e eTopic = in_tMessage.eMsgTopic;

  /* Run all the Callback functions there are in the Callback Array and pass the
   * Message over */
  for (uint8_t u8CallbackIndex = 0;
       u8CallbackIndex < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE;
       u8CallbackIndex++) {
    if (sMessageTopicIndex[eTopic]->aCallbackArray[u8CallbackIndex] != NULL) {
      /* Run the function pointers and provide the specified argument */
      sMessageTopicIndex[eTopic]->aCallbackArray[u8CallbackIndex](in_tMessage);
    }
  }

  return STATUS_OK;
}