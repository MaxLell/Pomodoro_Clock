#include "MessageBroker.h"

#define MESSAGE_BROKER_CALLBACK_ARRAY_SIZE 10

STATIC MessageBroker_msgDictinary_t sMsg2010;
// STATIC void *au32Msg2010Callbacks[MESSAGE_BROKER_CALLBACK_ARRAY_SIZE] = {NULL};

STATIC status_t (*au32Msg2010Callbacks[MESSAGE_BROKER_CALLBACK_ARRAY_SIZE])(MessageBroker_message_t in_sMessage) = {NULL};

status_t MessageBroker_init()
{
    sMsg2010.u16Id = 2010;
    sMsg2010.au32CallbackArray = au32Msg2010Callbacks;
    sMsg2010.u16HighWaterMark = 0;
    sMsg2010.u16MaxSize = MESSAGE_BROKER_CALLBACK_ARRAY_SIZE;
    return STATUS_OK;
}

STATIC status_t MessageBroker_addCallbackToArray(
    uint16_t in_u16MsgID,
    Module_msgCallback in_p32FunctionCallback)
{
    /* Check whether a NULL Pointer is provided */
    check((in_p32FunctionCallback != NULL), "Module_msgCallback is NULL");

    /* Add the callback function at the position Watermark */
    sMsg2010.au32CallbackArray[sMsg2010.u16HighWaterMark] = in_p32FunctionCallback;

    /* Increment the High Water Mark */
    sMsg2010.u16HighWaterMark++;

    /* If the High Water Mark == Max Array size: Produce an error */
    return STATUS_OK;

error:
    return STATUS_NULL_POINTER;
}