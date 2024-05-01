#include "MessageBroker.h"

/* Contains all dictinaries, so that they can be searched through iterativly */
STATIC msgTopic_t *pasMsgTopicLib[E_TOPIC_LAST_TOPIC] = {NULL};
STATIC msgTopic_t saMsg[E_TOPIC_LAST_TOPIC] = {0};

STATIC u8 u8IsInitializedCounter = 0;

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
    return STATUS_OK;
}

void MessageBroker_init()
{
    for (u16 u16MsgId = (E_TOPIC_FIRST_TOPIC + 1); u16MsgId < E_TOPIC_LAST_TOPIC; u16MsgId++)
    {
        // Set the u16MsgId in the respective Message Topic
        saMsg[u16MsgId].eMsgId = (msgId_e)u16MsgId;

        // Clear out all Callback Array Entries (if there are any)
        for (u16 i = 0; i < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; i++)
        {
            saMsg[u16MsgId].aCallbackArray[i] = NULL;
        }

        // Assign the msg topic to the Library as an entry
        pasMsgTopicLib[u16MsgId] = &saMsg[u16MsgId];
    }

    u8IsInitializedCounter++;

    MessageBroker_checkInitCounter();
}

status_e MessageBroker_subscribe(msgId_e in_eMsgTopic, msgCallback_t in_p32FunctionCallback)
{
    { // Input Verfication
        ASSERT_MSG(!(in_eMsgTopic <= E_TOPIC_FIRST_TOPIC), "Topic needs to be different from E_TOPIC_FIRST!");
        if (in_eMsgTopic <= E_TOPIC_FIRST_TOPIC)
        {
            return STATUS_ERROR;
        }
        ASSERT_MSG(!(in_eMsgTopic >= E_TOPIC_LAST_TOPIC), "Topic must not be E_TOPIC_LAST!");
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

    u16 u16EmptyPointerPositionIndex = 0;
    for (u16 u16ArrayIndex = 0; u16ArrayIndex < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; u16ArrayIndex++)
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
    return STATUS_OK;
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
    for (u8 u8CallbackIndex = 0; u8CallbackIndex < MESSAGE_BROKER_CALLBACK_ARRAY_SIZE; u8CallbackIndex++)
    {
        if (pasMsgTopicLib[eTopic]->aCallbackArray[u8CallbackIndex] != NULL)
        {
            /* Run the function pointers and provide the specified argument */
            msgCallback_t msgCallback = pasMsgTopicLib[eTopic]->aCallbackArray[u8CallbackIndex];

            // Run the function pointer
            status_e eStatus = msgCallback(in_psMessage);
            ASSERT_MSG(!(eStatus == STATUS_ERROR), "Message Callback Function returned an error for MSG_ID: %d",
                       eTopic);
            if (eStatus == STATUS_ERROR)
            {
                return STATUS_ERROR;
            }
        }
        else // (pasMsgTopicLib[eTopic]->aCallbackArray[u8CallbackIndex] == NULL)
        {
            if (u8CallbackIndex == 0)
            {
                /* If there are no Callback Functions to call, then raise an error, since noone is listening */
                ASSERT_MSG(false, "No Subscribers for MSG_ID: %d", eTopic);
                return STATUS_ERROR;
            }
        }
    }
    return STATUS_OK;
}