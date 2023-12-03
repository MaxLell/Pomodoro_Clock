#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include "Common.h"
#include "MessageIDs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The number of Message Topics needs to match the number of enumsthere are
 * in the messageTopics enum
 */

#define MESSAGE_BROKER_CALLBACK_ARRAY_SIZE 5

/**
 * Message Structure
 * - for parsing incoming Messages
 * - and sending out messages
 */
typedef struct {
  msgId_e eMsgId;
  uint16_t u16DataSize;
  uint8_t *au8DataBytes;
} msg_t;

/* Function Callback Type */
typedef status_t (*msgCallback_t)(msg_t in_sMessage);

/**
 * Standard Message Dictinary
 */
typedef struct {
  msgId_e eMsgId;
  msgCallback_t aCallbackArray[MESSAGE_BROKER_CALLBACK_ARRAY_SIZE];
} msgTopic_t;

/**
 * Function Declerations
 */
void MessageBroker_init(void);

status_t MessageBroker_subscribe(msgId_e in_eMsgTopic,
                                 msgCallback_t in_p32FunctionCallback);

status_t MessageBroker_publish(msg_t in_tMessage);

#ifdef __cplusplus
}
#endif

#endif  // MESSAGEBROKER_H
