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
typedef enum
{
    // Test Messages
    MSG_ID_0001 = 0U, // Chaos Elephant
    MSG_ID_0002,      // Tickly Giraffe

    // Trigger Button Messages
    MSG_ID_0100, // Trigger Button: was pressed once
    MSG_ID_0101, // Trigger Button: is Pressed Down Continuously
    MSG_ID_0102, // Trigger Button: was released after being pressed down
    MSG_ID_0103, // Button Event
                 // continuously

    // State Machine Messages
    MSG_ID_0200, // Pomodoro Sequence Start
    MSG_ID_0201, // Pomodoro Work Time Sequence Complete
    MSG_ID_0202, // Pomodoro Break Time Sequence Complete
    MSG_ID_0203, // Pomodoro Cancel Sequence Complete
    MSG_ID_0204, // Pomodoro Sequence Complete

    // Real Time Clock Messages0101
    MSG_ID_0300, // RTC: 1 Second Tick

    // Configuration Messages
    MSG_ID_0400, // Pomodoro Configuration: Worktime and Breaktime Periods

    // Score
    MSG_ID_0500, // Score Updated Message

    // Encoder
    MSG_ID_0600, // Reset Encoder Value
    MSG_ID_0601, // Encoder Value Changed

    E_TOPIC_LAST_TOPIC // Last Topic - DO NOT USE (Only for boundary checks)
} msgId_e;

#endif /* MESSAGETOPICS_H_ */