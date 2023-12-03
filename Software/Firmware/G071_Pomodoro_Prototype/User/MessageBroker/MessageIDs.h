#ifndef MESSAGETOPICS_H_
#define MESSAGETOPICS_H_

#include "Common.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Message Topics
 */
typedef enum {
  MSG_ID_0001 = 0U,   // Chaos Elephant
  MSG_ID_0002,        // Tickly Giraffe
  MSG_ID_0100,        // Trigger Button Single Click
  E_TOPIC_LAST_TOPIC  // Last Topic - DO NOT USE (Only for boundary checks)
} msgId_e;

#ifdef __cplusplus
}
#endif

#endif /* MESSAGETOPICS_H_ */