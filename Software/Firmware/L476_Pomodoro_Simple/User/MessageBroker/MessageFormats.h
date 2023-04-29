#ifndef MESSAGEFORMATS_H
#define MESSAGEFORMATS_H

#include "Common.h"
#include "MessageTopics.h"

typedef struct
{
    MessageTopics_e eMsgTopic;
    uint16_t u16DataSize;
    uint8_t *au8DataBytes;
} MessageBroker_message_t;

/* Function Callback Type */
typedef status_t (*Module_msgCallback_t)(MessageBroker_message_t in_sMessage);

/**
 * Time and Date Message Format
 */
#define TIME_DATE_SECOND 0
#define TIME_DATE_MINUTE 1
#define TIME_DATE_HOUR 2
#define TIME_DATE_DAY 3
#define TIME_DATE_MONTH 4
#define TIME_DATE_YEAR 5

#endif // MESSAGEFORMATS_H