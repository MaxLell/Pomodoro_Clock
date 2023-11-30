#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include "Common.h"
#include "MessageIDs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /*
     * The number of Message Topics needs to match the number of enumsthere are
     * in the messageTopics enum
     */

#define MESSAGE_BROKER_CALLBACK_ARRAY_SIZE 5

    /**
     * Message Structure
     */

    typedef struct
    {
        msgId_e eMsgId;
        uint16_t u16DataSize;
        uint8_t *au8DataBytes;
    } msg_t;

    /* Function Callback Type */
    typedef status_t (*msgCallback_t)(msg_t in_sMessage);

    /**
     * Standard Message Dictinary
     */
    typedef struct
    {
        msgId_e eMsgId;
        msgCallback_t aCallbackArray[MESSAGE_BROKER_CALLBACK_ARRAY_SIZE];
    } msgTopics_t;

    /**
     * Function Declerations
     */
    status_t MessageBroker_init(void);

    status_t MessageBroker_subscribe(
        msgId_e in_eMsgTopic,
        msgCallback_t in_p32FunctionCallback);

    status_t MessageBroker_publish(msg_t in_tMessage);

#ifdef __cplusplus
}
#endif

#endif // MESSAGEBROKER_H
