#ifndef MESSAGETOPICS_H_
#define MESSAGETOPICS_H_

/**
 * Message Topic Definitions
 * - 0XXX: System Messages / Test Messsages
 * - 01XX: Button Messages
 * - 02XX: State Machine Messages
 * - 03XX: SequenceControl Messages
 */

#include "Common.h"

/**
 * Message Topics
 */
typedef enum {
  MSG_ID_0001 = 0U,   // Chaos Elephant
  MSG_ID_0002,        // Tickly Giraffe
  MSG_ID_0100,        // Trigger Button: was pressed once
  MSG_ID_0200,        // Pomodoro Sequence Start
  MSG_ID_0201,        // Pomodoro Sequence Complete
  E_TOPIC_LAST_TOPIC  // Last Topic - DO NOT USE (Only for boundary checks)
} msgId_e;

#endif /* MESSAGETOPICS_H_ */