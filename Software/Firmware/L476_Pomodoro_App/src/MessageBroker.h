#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include "Common.h"

typedef struct
{
    uint16_t u16Id;
    uint32_t *au32Data;
    uint16_t u16DataSize;
} MessageBroker_message_t;

typedef status_t (*Module_msgCallback)(MessageBroker_message_t in_sMessage);

typedef struct
{
    uint16_t u16Id;
    Module_msgCallback *au32CallbackArray;
    uint16_t u16HighWaterMark;
    uint16_t u16MaxSize;
} MessageBroker_msgDictinary_t;

status_t MessageBroker_init(void);

#endif // MESSAGEBROKER_H
