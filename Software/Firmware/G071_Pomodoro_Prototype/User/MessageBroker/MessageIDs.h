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
    E_TOPIC_FIRST_TOPIC = 0U, // First Topic - DO NOT USE (Only for boundary checks)

    // Test Messages
    MSG_0001, // Chaos Elephant
    MSG_0002, // Tickly Giraffe
    MSG_0003, // Generic and obsolete Test Message
    MSG_0004, // Test Message for the Pomodoro Sequence
    MSG_0005, // Test Message for the Seeking Attention Module
    MSG_0006, // Test Message for the Score Module

    // Button Messages
    MSG_0103, // Button Event

    // Pomodoro Control Messages
    MSG_0200, // Pomodoro Sequence Start
    MSG_0201, // Pomodoro Work Time Sequence Complete
    MSG_0202, // Pomodoro Break Time Sequence Complete
    MSG_0203, // Pomodoro Cancel Sequence Complete
    MSG_0204, // Pomodoro Sequence Complete

    // Real Time Clock Messages0101
    MSG_0300, // RTC: 1 Second Tick

    // CfgStore Messages
    MSG_0400, // Respond Current Worktime and Breaktime Periods of the active config
    MSG_0401, // Request Pomodoro Configuration
    MSG_0402, // Request all Pomodoro Configurations
    MSG_0403, // Respond all Pomodoro Configurations

    // Encoder
    MSG_0600, // Reset Encoder Value
    MSG_0601, // Encoder Value Changed

    // Setting Message
    MSG_0700, // Setting Procedure Start
    MSG_0701, // Setting Procedure finished

    // Seeking Attention
    MSG_0900, // Seeking Attention: Start
    MSG_0901, // Seeking Attention: Stop
    MSG_0902, // Seeking Attention: Finished

    E_TOPIC_LAST_TOPIC // Last Topic - DO NOT USE (Only for boundary checks)
} msgId_e;

#endif /* MESSAGETOPICS_H_ */