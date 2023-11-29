#include "Score.h"
#include "Common.h"
#include "MessageBroker.h"
#include "PomodoroFsm_Interface.h"
/**
 * Static Functions
 */

STATIC void Score_updateDailyScore(void);
STATIC void Score_resetDailyScore(void);
STATIC status_t Score_callback(MessageBroker_message_t in_sMessage);

/**
 * Static Variables
 */
#define DAILY_MAX_SCORE 8U

// Reset Time Alarm is set to 3:00 AM
#define RESET_TIME_HOUR 3U
#define RESET_TIME_MINUTE 0U

STATIC uint8_t u8DailyScore = 0U;
STATIC BOOL bPomodoroSequenceCompleted = FALSE;
STATIC BOOL bResetTimeAlarm = FALSE;

STATIC void Score_updateDailyScore(void)
{
    u8DailyScore++;
    if (u8DailyScore >= DAILY_MAX_SCORE)
    {
        u8DailyScore = 0U;
    }
}

STATIC void Score_resetDailyScore(void)
{
    u8DailyScore = 0U;
}

STATIC status_t Score_callback(MessageBroker_message_t in_sMessage)
{
    status_t sStatus = STATUS_OK;

    switch (in_sMessage.eMsgTopic)
    {
    case E_TOPIC_PFSM_STATE_CHANGED:

        if ((in_sMessage.au8DataBytes[PFSM_NEW_STATE] == E_PFSM_STATE_BREAKTIME) &&
            (in_sMessage.au8DataBytes[PFSM_OLD_STATE] == E_PFSM_STATE_WORKTIME))
        {
            bPomodoroSequenceCompleted = TRUE;
        }
        break;

    case E_TOPIC_TIME_AND_DATE:
        if ((in_sMessage.au8DataBytes[TIME_DATE_HOUR] == RESET_TIME_HOUR) &&
            (in_sMessage.au8DataBytes[TIME_DATE_MINUTE] == RESET_TIME_MINUTE))
        {
            bResetTimeAlarm = TRUE;
        }
        break;

    default:
        log_error("Unknown Topic");
        sStatus = STATUS_INVALID_ARG;
        break;
    }
    return sStatus;
}
void Score_init(void)
{
    /**
     * Subscribe to to Topics
     * - PFSM State changed
     * - Current Date and Time
     */
    MessageBroker_subscribe(E_TOPIC_PFSM_STATE_CHANGED, Score_callback);
    MessageBroker_subscribe(E_TOPIC_TIME_AND_DATE, Score_callback);

    /**
     * Reset all local static variables
     */
    Score_resetDailyScore();
    bPomodoroSequenceCompleted = FALSE;
    bResetTimeAlarm = FALSE;
}

void Score_execute(void)
{
    if (bPomodoroSequenceCompleted)
    {
        Score_updateDailyScore();
        bPomodoroSequenceCompleted = FALSE;

        // Publish the Daily Score
        MessageBroker_message_t sMessage;
        sMessage.eMsgTopic = E_TOPIC_DAILY_POMODORO_SCORE;
        uint8_t au8TmpDataBytes[1] = {u8DailyScore};
        sMessage.au8DataBytes = au8TmpDataBytes;
        sMessage.u16DataSize = 1U;

        MessageBroker_publish(sMessage);
    }
    else if (bResetTimeAlarm)
    {
        Score_resetDailyScore();
        bResetTimeAlarm = FALSE;

        // Publish the Daily Score
        MessageBroker_message_t sMessage;
        sMessage.eMsgTopic = E_TOPIC_DAILY_POMODORO_SCORE;
        uint8_t au8TmpDataBytes[1] = {u8DailyScore};
        sMessage.au8DataBytes = au8TmpDataBytes;
        sMessage.u16DataSize = 1U;

        MessageBroker_publish(sMessage);
    }
    else // Do nothing
    {
    }
}