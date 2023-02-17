#include "MessageBroker.h"

#define MESSAGE_BROKER_CALLBACK_ARRAY_SIZE 10
#define MESSAGE_BROKER_NUMBER_OF_MESSAGES 20

/**
 * Message 2010
 * This is only a dummy message for experimentation.
 */
STATIC MessageBroker_msgDictinary_t sMsg2010;
STATIC status_t (*ptMsg2010Callbacks[MESSAGE_BROKER_CALLBACK_ARRAY_SIZE])(MessageBroker_message_t in_sMessage) = {NULL};

/**
 * Message 0204
 * This is only a dummy message for testing
 */
STATIC MessageBroker_msgDictinary_t sMsg0204;
STATIC status_t (*ptMsg0204Callbacks[MESSAGE_BROKER_CALLBACK_ARRAY_SIZE])(MessageBroker_message_t in_sMessage) = {NULL};

/* Contains all dictinaries, so that they can be searched through iterativly */
STATIC MessageBroker_msgDictinary_t *msgLibrary[MESSAGE_BROKER_NUMBER_OF_MESSAGES];

status_t MessageBroker_init()
{
    sMsg2010.u16Id = 2010;
    sMsg2010.au32CallbackArray = ptMsg2010Callbacks;
    sMsg2010.u16HighWaterMark = 0;
    sMsg2010.u16MaxSize = MESSAGE_BROKER_CALLBACK_ARRAY_SIZE;

    sMsg0204.u16Id = 0204;
    sMsg0204.au32CallbackArray = ptMsg2010Callbacks;
    sMsg0204.u16HighWaterMark = 0;
    sMsg0204.u16MaxSize = MESSAGE_BROKER_CALLBACK_ARRAY_SIZE;

    return STATUS_OK;
}

status_t MessageBroker_subscribe(
    uint16_t in_u16MsgID,
    Module_msgCallback_t in_p32FunctionCallback)
{
    /* Check whether a NULL Pointer is provided */
    check((in_p32FunctionCallback != NULL), "Module_msgCallback is NULL");

    /* Get the correct callback array */

    /* Add the callback function at the position Watermark */
    sMsg2010.au32CallbackArray[sMsg2010.u16HighWaterMark] = in_p32FunctionCallback;

    /* Increment the High Water Mark */
    sMsg2010.u16HighWaterMark++;

    /* If the High Water Mark == Max Array size: Produce an error */
    return STATUS_OK;

error:
    return STATUS_NULL_POINTER;
}