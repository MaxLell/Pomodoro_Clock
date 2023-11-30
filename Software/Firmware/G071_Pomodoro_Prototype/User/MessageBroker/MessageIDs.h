#ifndef MESSAGETOPICS_H_
#define MESSAGETOPICS_H_

#include "Common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * Message Topics
     */
    typedef enum
    {
        MSG_ID_0001 = 0U, // Test Message 1
        MSG_ID_0002,      // Test Message 2
        MSG_ID_0003,      // Chaos Elephant
        MSG_ID_0004,      // Chaos Giraffe
        E_TOPIC_LAST_TOPIC
    } msgId_e;

#ifdef __cplusplus
}
#endif

#endif /* MESSAGETOPICS_H_ */