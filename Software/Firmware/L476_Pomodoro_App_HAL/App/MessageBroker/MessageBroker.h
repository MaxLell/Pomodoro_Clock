#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include "Common.h"

/*
 * The number of Message Topics needs to match the number of enumsthere are
 * in the messageTopics enum
 */

#define MESSAGE_BROKER_NUMBER_OF_MESSAGE_TOPICS 3
#define MESSAGE_BROKER_CALLBACK_ARRAY_SIZE 5

typedef enum
{
    E_TEST_1 = 0U,
    E_TEST_2,
    E_TRIGGER_BUTTON_EVENT,
} MessageBroker_messageTopics_e;

typedef struct
{
    MessageBroker_messageTopics_e eMsgTopic;
    uint16_t u16DataSize;
    uint32_t *au32Data;
} MessageBroker_message_t;

/* Function Callback Type */
typedef status_t (*Module_msgCallback_t)(MessageBroker_message_t in_sMessage);

/**
 * Standard Message Dictinary
 */
typedef struct
{
    MessageBroker_messageTopics_e eMsgTopic;
    Module_msgCallback_t aCallbackArray[MESSAGE_BROKER_CALLBACK_ARRAY_SIZE];
} MessageBroker_msgDictinary_t;

/**
 * Function Declerations
 */
status_t MessageBroker_init(void);

status_t MessageBroker_subscribe(
    MessageBroker_messageTopics_e in_eMsgTopic,
    Module_msgCallback_t in_p32FunctionCallback);

status_t MessageBroker_publish(MessageBroker_message_t in_tMessage);

#endif // MESSAGEBROKER_H
