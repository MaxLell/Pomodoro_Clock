#include "MessageBroker.h"

/**
 * Message 2010, 0204
 * This is only a dummy message for experimentation.
 * You manually need to set these topics here up.
 */
STATIC msgTopics_t sMsg_0001;
STATIC msgTopics_t sMsg_0002;
STATIC msgTopics_t sMsg_0003;
STATIC msgTopics_t sMsg_0004;
/**
 * The Message Topics are defined here
 */

/* Contains all dictinaries, so that they can be searched through iterativly */
STATIC msgTopics_t *sMessageTopicIndex[E_TOPIC_LAST_TOPIC] = {NULL};

status_t MessageBroker_init()
{
    /* Set the Topics of the respective messages */
    sMsg_0001.eMsgId = MSG_ID_0001; // Demo
    sMsg_0002.eMsgId = MSG_ID_0002;
    sMsg_0003.eMsgId = MSG_ID_0003;
    sMsg_0004.eMsgId = MSG_ID_0004;

    /* Set the Topics of the respective messages */
    sMessageTopicIndex[MSG_ID_0001] = &sMsg_0001;
    sMessageTopicIndex[MSG_ID_0002] = &sMsg_0002;
    sMessageTopicIndex[MSG_ID_0003] = &sMsg_0003;
    sMessageTopicIndex[MSG_ID_0004] = &sMsg_0004;

    /* set all the elements of the Callback arrays to zero */
    for (uint16_t topic = 0; topic < E_TOPIC_LAST_TOPIC; topic++)
    {
        for (uint16_t index = 0; index < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; index++)
        {
            // TODO: Add a safeguard in here - so that the application shuts down gracefully
            sMessageTopicIndex[topic]->aCallbackArray[index] = 0;
        }
    }

    return STATUS_OK;
}

status_t MessageBroker_subscribe(
    msgId_e in_eMsgTopic,
    msgCallback_t in_p32FunctionCallback)
{
    { // Input Verfication
        ASSERT_MSG(in_eMsgTopic < E_TOPIC_LAST_TOPIC, "Topic is out of bounds!");
        if (in_eMsgTopic >= E_TOPIC_LAST_TOPIC)
        {
            return STATUS_ERROR;
        }
        ASSERT_MSG(in_p32FunctionCallback != NULL, "Function pointer is NULL!");
        if (in_p32FunctionCallback == NULL)
        {
            return STATUS_ERROR;
        }
    }

    uint16_t u16EmptyPointerPositionIndex = 0;
    for (uint16_t u16ArrayIndex = 0; u16ArrayIndex < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; u16ArrayIndex++)
    {
        /* Find the first element in the callback array, that is not equal 0 */
        if (sMessageTopicIndex[in_eMsgTopic]->aCallbackArray[u16ArrayIndex] == 0)
        {
            u16EmptyPointerPositionIndex = u16ArrayIndex;
            break;
        }
    }
    if (u16EmptyPointerPositionIndex == (MESSAGE_BROKER_CALLBACK_ARRAY_SIZE - 1))
    {
        log_info("Callback Array for Topic %d is full. This is the last possible subscription!", in_eMsgTopic);
    }
    sMessageTopicIndex[in_eMsgTopic]->aCallbackArray[u16EmptyPointerPositionIndex] = in_p32FunctionCallback;
    return STATUS_OK;
}

status_t MessageBroker_publish(msg_t in_tMessage)
{
    { // Input Verification
        ASSERT_MSG(in_tMessage.eMsgId < E_TOPIC_LAST_TOPIC, "Topic is out of bounds!");
        if (in_tMessage.eMsgId >= E_TOPIC_LAST_TOPIC)
        {
            return STATUS_ERROR;
        }
    }
    /* find the dictinary that corresponds to the message's Topic */
    msgId_e eTopic = in_tMessage.eMsgId;

    /* Run all the Callback functions there are in the Callback Array and pass the Message over */
    for (uint8_t u8CallbackIndex = 0; u8CallbackIndex < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; u8CallbackIndex++)
    {
        if (sMessageTopicIndex[eTopic]->aCallbackArray[u8CallbackIndex] != NULL)
        {
            /* Run the function pointers and provide the specified argument */
            sMessageTopicIndex[eTopic]->aCallbackArray[u8CallbackIndex](in_tMessage);
        }
    }
    return STATUS_OK;
}