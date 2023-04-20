#ifndef MESSAGETOPICS_H_
#define MESSAGETOPICS_H_

#include "Common.h"

/**
 * Message Topics
 */
typedef enum
{
#ifdef TEST
    E_TEST_1 = 0U,
    E_TEST_2,
#endif
    E_TOPIC_TRIGGER_BUTTON_PRESSED,
    E_TOPIC_CURRENT_MINUTE,
    E_TOPIC_TIME_AND_DATE,
    E_TOPIC_ONE_SECOND_PASSED,
    E_TOPIC_PFSM_STATE_CHANGED,
    E_TOPIC_LCTRL_STATE_CHANGED,

    E_TOPIC_LAST_TOPIC
} MessageTopics_e;

#endif /* MESSAGETOPICS_H_ */