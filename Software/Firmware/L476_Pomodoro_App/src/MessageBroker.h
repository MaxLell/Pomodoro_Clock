#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include "Common.h"

typedef struct
{
    uint16_t u16ID;
    uint32_t *au32Data;
    uint16_t u16DataSize;
} MessageBroker_Message_s;

typedef status_t (*Module_msgCallback)(MessageBroker_Message_s in_sMessage);

#endif // MESSAGEBROKER_H
