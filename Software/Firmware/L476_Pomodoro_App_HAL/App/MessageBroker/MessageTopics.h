#ifndef MESSAGETOPICS_H
#define MESSAGETOPICS_H

#include "Common.h"

typedef enum {
  E_TEST_1 = 0U,
  E_TEST_2,
  E_TRIGGER_BUTTON_EVENT,
} MessageTopics_e;

/* This is to be updated with each new message */
#define MESSAGE_TOPIC_TOTAL_NUMBER 3

typedef struct {
  uint8_t u8Hour;
  uint8_t u8Minute;
  uint8_t u8Second;
} MessageTopics_Time_t;

#endif /* Message Topics.h */