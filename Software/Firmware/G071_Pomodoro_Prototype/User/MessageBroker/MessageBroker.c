#include "MessageBroker.h"

/* Contains all dictinaries, so that they can be searched through iterativly */
STATIC msgTopic_t *pasMsgTopicLib[E_TOPIC_LAST_TOPIC] = {NULL};
STATIC msgTopic_t saMsg[E_TOPIC_LAST_TOPIC] = {0};

void MessageBroker_init() {
  for (uint16_t msgId = 0; msgId < E_TOPIC_LAST_TOPIC; msgId++) {
    // Set the msgId in the respective Message Topic
    saMsg[msgId].eMsgId = msgId;

    // Clear out all Callback Array Entries (if there are any)
    for (uint16_t i = 0; i < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; i++) {
      saMsg[msgId].aCallbackArray[i] = NULL;
    }

    // Assign the msg topic to the Library as an entry
    pasMsgTopicLib[msgId] = &saMsg[msgId];
  }
}

status_t MessageBroker_subscribe(msgId_e in_eMsgTopic,
                                 msgCallback_t in_p32FunctionCallback) {
  {  // Input Verfication
    ASSERT_MSG(!(in_eMsgTopic >= E_TOPIC_LAST_TOPIC),
               "Topic is out of bounds!");
    if (in_eMsgTopic >= E_TOPIC_LAST_TOPIC) {
      return STATUS_ERROR;
    }
    ASSERT_MSG(!(in_p32FunctionCallback == NULL), "Function pointer is NULL!");
    if (in_p32FunctionCallback == NULL) {
      return STATUS_ERROR;
    }
  }

  uint16_t u16EmptyPointerPositionIndex = 0;
  for (uint16_t u16ArrayIndex = 0;
       u16ArrayIndex < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; u16ArrayIndex++) {
    /* Find the first empty spot in the callback array, */
    if (pasMsgTopicLib[in_eMsgTopic]->aCallbackArray[u16ArrayIndex] == 0) {
      u16EmptyPointerPositionIndex = u16ArrayIndex;
      break;
    }
  }
  /* Send out a warning, when there are too many subscribers */
  ASSERT_MSG(!(u16EmptyPointerPositionIndex ==
               (MESSAGE_BROKER_CALLBACK_ARRAY_SIZE - 1)),
             "Too many subscribers!");
  if (u16EmptyPointerPositionIndex ==
      (MESSAGE_BROKER_CALLBACK_ARRAY_SIZE - 1)) {
    return STATUS_ERROR;
  }

  /* Add in the provided Callback, so that later messages can be sent to that
   * callback */
  pasMsgTopicLib[in_eMsgTopic]->aCallbackArray[u16EmptyPointerPositionIndex] =
      in_p32FunctionCallback;
  return STATUS_OK;
}

status_t MessageBroker_publish(msg_t in_tMessage) {
  {  // Input Verification
    ASSERT_MSG(!(in_tMessage.eMsgId >= E_TOPIC_LAST_TOPIC),
               "Topic is out of bounds!");
    if (in_tMessage.eMsgId >= E_TOPIC_LAST_TOPIC) {
      return STATUS_ERROR;
    }
  }
  /* find the dictinary that corresponds to the message's Topic */
  msgId_e eTopic = in_tMessage.eMsgId;

  /* Run all the Callback functions there are in the Callback Array and pass the
   * Message over */
  for (uint8_t u8CallbackIndex = 0;
       u8CallbackIndex < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE;
       u8CallbackIndex++) {
    if (pasMsgTopicLib[eTopic]->aCallbackArray[u8CallbackIndex] != NULL) {
      /* Run the function pointers and provide the specified argument */
      pasMsgTopicLib[eTopic]->aCallbackArray[u8CallbackIndex](in_tMessage);
    }
  }
  return STATUS_OK;
}