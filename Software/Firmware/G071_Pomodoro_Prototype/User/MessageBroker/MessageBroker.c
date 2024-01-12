#include "MessageBroker.h"

/* Contains all dictinaries, so that they can be searched through iterativly */
STATIC msgTopic_t *pasMsgTopicLib[E_TOPIC_LAST_TOPIC] = {NULL};
STATIC msgTopic_t saMsg[E_TOPIC_LAST_TOPIC] = {0};

STATIC BOOL u8IsInitializedCounter = 0;

status_e MessageBroker_checkInitCounter()
{
    ASSERT_MSG(!(u8IsInitializedCounter == 0), "Message Broker is not initialized!");
    if (u8IsInitializedCounter == 0)
    {
        return STATUS_ERROR;
    }
    ASSERT_MSG(!(u8IsInitializedCounter > 1), "Message Broker is initialized more than once!");
    if (u8IsInitializedCounter > 1)
    {
        return STATUS_ERROR;
    }
    return STATUS_SUCCESS;
}
void MessageBroker_init()
{

    for (uint16_t msgId = 0; msgId < E_TOPIC_LAST_TOPIC; msgId++)
    {
        // Set the msgId in the respective Message Topic
        saMsg[msgId].eMsgId = msgId;

        // Clear out all Callback Array Entries (if there are any)
        for (uint16_t i = 0; i < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; i++)
        {
            saMsg[msgId].aCallbackArray[i] = NULL;
        }

        // Assign the msg topic to the Library as an entry
        pasMsgTopicLib[msgId] = &saMsg[msgId];
    }
    u8IsInitializedCounter++;

    MessageBroker_checkInitCounter();
}

status_e MessageBroker_subscribe(msgId_e in_eMsgTopic, msgCallback_t in_p32FunctionCallback)
{
    { // Input Verfication
        ASSERT_MSG(!(in_eMsgTopic >= E_TOPIC_LAST_TOPIC), "Topic is out of bounds!");
        if (in_eMsgTopic >= E_TOPIC_LAST_TOPIC)
        {
            return STATUS_ERROR;
        }
        ASSERT_MSG(!(in_p32FunctionCallback == NULL), "Function pointer is NULL!");
        if (in_p32FunctionCallback == NULL)
        {
            return STATUS_ERROR;
        }
        MessageBroker_checkInitCounter();
    }

    uint16_t u16EmptyPointerPositionIndex = 0;
    for (uint16_t u16ArrayIndex = 0; u16ArrayIndex < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; u16ArrayIndex++)
    {
        /* Find the first empty spot in the callback array, */
        if (pasMsgTopicLib[in_eMsgTopic]->aCallbackArray[u16ArrayIndex] == 0)
        {
            u16EmptyPointerPositionIndex = u16ArrayIndex;
            break;
        }
    }
    /* Send out a warning, when there are too many subscribers */
    ASSERT_MSG(!(u16EmptyPointerPositionIndex == (MESSAGE_BROKER_CALLBACK_ARRAY_SIZE - 1)), "Too many subscribers!");
    if (u16EmptyPointerPositionIndex == (MESSAGE_BROKER_CALLBACK_ARRAY_SIZE - 1))
    {
        return STATUS_ERROR;
    }

    /* Add in the provided Callback, so that later messages can be sent to that
     * callback */
    pasMsgTopicLib[in_eMsgTopic]->aCallbackArray[u16EmptyPointerPositionIndex] = in_p32FunctionCallback;
    return STATUS_SUCCESS;
}

status_e MessageBroker_publish(msg_t *in_psMessage)
{
    { // Input Verification
        ASSERT_MSG(!(in_psMessage->eMsgId >= E_TOPIC_LAST_TOPIC), "Topic is out of bounds!");
        if (in_psMessage->eMsgId >= E_TOPIC_LAST_TOPIC)
        {
            return STATUS_ERROR;
        }
        // Make sure no NULL Pointer was Provided
        ASSERT_MSG(!(in_psMessage == NULL), "Message Pointer is NULL!");
        if (in_psMessage == NULL)
        {
            return STATUS_ERROR;
        }
        MessageBroker_checkInitCounter();
    }
    /* find the dictinary that corresponds to the message's Topic */
    msgId_e eTopic = in_psMessage->eMsgId;

    /* Run all the Callback functions there are in the Callback Array and pass the
     * Message over */
    for (uint8_t u8CallbackIndex = 0; u8CallbackIndex < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; u8CallbackIndex++)
    {
        if (pasMsgTopicLib[eTopic]->aCallbackArray[u8CallbackIndex] != NULL)
        {
            /* Run the function pointers and provide the specified argument */
            msgCallback_t msgCallback = pasMsgTopicLib[eTopic]->aCallbackArray[u8CallbackIndex];

            // Run the function pointer
            status_e eStatus = msgCallback(in_psMessage);
            ASSERT_MSG(!(eStatus != STATUS_SUCCESS), "Message Callback Function returned an error!");
        }
    }
    return STATUS_SUCCESS;
}