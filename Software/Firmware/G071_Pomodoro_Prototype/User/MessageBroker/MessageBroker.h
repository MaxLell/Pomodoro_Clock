#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include "Common.h"
#include "MessageIDs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MESSAGE_BROKER_CALLBACK_ARRAY_SIZE 10U

/**
 * Message Structure
 */
typedef struct {
  msgId_e eMsgId;
  uint16_t u16DataSize;
  uint8_t *au8DataBytes;
} msg_t;

/* Function Callback Type */
typedef status_e (*msgCallback_t)(msg_t in_sMessage);

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

status_e MessageBroker_subscribe(msgId_e in_eMsgTopic,
                                 msgCallback_t in_p32FunctionCallback);

status_e MessageBroker_publish(msg_t in_tMessage);

#ifdef __cplusplus
}
#endif

#endif  // MESSAGEBROKER_H
