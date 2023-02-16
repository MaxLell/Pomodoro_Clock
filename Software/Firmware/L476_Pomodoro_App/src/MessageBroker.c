#include "MessageBroker.h"

#define MESSAGE_BROKER_CALLBACK_ARRAY_SIZE 10

STATIC uint32_t au32Msg_20_10[MESSAGE_BROKER_CALLBACK_ARRAY_SIZE] = {0};

STATIC status_t MessageBroker_addCallbackToArray(
    uint16_t in_u16MsgID,
    Module_msgCallback in_p32FunctionCallback)
{
    /* Check whether a NULL Pointer is provided */
    check(in_p32FunctionCallback, "Module_msgCallback is NULL");
error:
    return STATUS_NULL_POINTER;
}