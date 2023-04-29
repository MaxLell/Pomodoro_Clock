#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include "Common.h"
#include "MessageTopics.h"
#include "MessageFormats.h"

/*
 * The number of Message Topics needs to match the number of enumsthere are
 * in the messageTopics enum
 */

#define MESSAGE_BROKER_CALLBACK_ARRAY_SIZE 5

/**
 * Message Structure
 */

/**
 * Standard Message Dictinary
 */
typedef struct
{
    MessageTopics_e eMsgTopic;
    Module_msgCallback_t aCallbackArray[MESSAGE_BROKER_CALLBACK_ARRAY_SIZE];
} MessageBroker_msgDictinary_t;

/**
 * Function Declerations
 */
status_t MessageBroker_init(void);

status_t MessageBroker_subscribe(
    MessageTopics_e in_eMsgTopic,
    Module_msgCallback_t in_p32FunctionCallback);

status_t MessageBroker_publish(MessageBroker_message_t in_tMessage);

#endif // MESSAGEBROKER_H