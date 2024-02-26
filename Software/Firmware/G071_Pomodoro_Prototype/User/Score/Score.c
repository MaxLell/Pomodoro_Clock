#include "Score.h"

#include "CountdownTimer.h"
#include "MessageBroker.h"

#define ONE_SECOND 1000
#define SCORE_WATCHDOG_TIMEOUT 1000 * 60 * 60 * 6 // 6 hours

STATIC uint32_t u32TotalDailyActivePomodoroSeconds = 0U;
STATIC uint32_t u32CurrentSecondCount = 0U;

timer_t sCountdownTimerSec;
timer_t sScoreWatchdogTimer;

void Score_publishScore(void)
{
    // Publish the current daily score
    msg_t sMsg;
    sMsg.eMsgId = MSG_0500;
    uint8_t au8DataBytes[4] = {0U};

    au8DataBytes[0] = (uint8_t)(u32TotalDailyActivePomodoroSeconds >> 24);
    au8DataBytes[1] = (uint8_t)(u32TotalDailyActivePomodoroSeconds >> 16);
    au8DataBytes[2] = (uint8_t)(u32TotalDailyActivePomodoroSeconds >> 8);
    au8DataBytes[3] = (uint8_t)(u32TotalDailyActivePomodoroSeconds);
    sMsg.au8DataBytes = au8DataBytes;
    sMsg.u16DataSize = 4U;

    status_e eStatus = MessageBroker_publish(&sMsg);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "Score_publishScore: Failed to publish MSG_0500");

    unused(eStatus); // To avoid compiler warnings when the code is optimized
}

void Score_kickWatchdog(void)
{
    // Reset the Score Watchdog Timer
    Countdown_resetAndStartTimer(&sScoreWatchdogTimer);
}

status_e Score_MsgCb(const msg_t *const in_psMessage)
{
    status_e eStatus = STATUS_ERROR;

    switch (in_psMessage->eMsgId)
    {
    case MSG_0200: // Pomodoro Sequence Start
    {
        // Reset the currentScore
        u32CurrentSecondCount = 0U;

        // Start the Countdown Timer
        Countdown_resetAndStartTimer(&sCountdownTimerSec);

        // Publish the current daily score
        Score_publishScore();

        // kick the Score Watchdog Timer
        Score_kickWatchdog();

        eStatus = STATUS_SUCCESS;
    }
    break;

    case MSG_0201: // Pomodoro Work Time Sequence Complete
    {
        // Add the currentScore to the daily score
        u32TotalDailyActivePomodoroSeconds += u32CurrentSecondCount;
        u32CurrentSecondCount = 0U;

        // Publish the current daily score
        Score_publishScore();

        // kick the Score Watchdog Timer
        Score_kickWatchdog();

        eStatus = STATUS_SUCCESS;
    }
    break;

    case MSG_0202: // Pomodoro Break Time Sequence Complete
    {
        // Add the currentScore to the daily score
        u32TotalDailyActivePomodoroSeconds += u32CurrentSecondCount;
        u32CurrentSecondCount = 0U;

        // Publish the current daily score
        Score_publishScore();

        // kick the Score Watchdog Timer
        Score_kickWatchdog();

        // Stop the Seconds-counting Countdown Timer
        Countdown_stopTimer(&sCountdownTimerSec);

        eStatus = STATUS_SUCCESS;
    }
    break;

    case MSG_0203: // Pomodoro Cancel Sequence Complete
    {
        // Stop the Seconds-counting Countdown Timer
        Countdown_stopTimer(&sCountdownTimerSec);

        // reset the currentScore
        u32CurrentSecondCount = 0U;

        // publish the current daily score
        Score_publishScore();

        // kick the Score Watchdog Timer
        Score_kickWatchdog();

        eStatus = STATUS_SUCCESS;
    }
    break;

    default:
        ASSERT_MSG(FALSE, "Score_MsgCb: Unhandled message ID");
        break;
    }

    return eStatus;
}

void Score_init(void)
{
    // Subscive to all status messages from the Pomodoro
    status_e eStatus;
    eStatus = MessageBroker_subscribe(MSG_0200, Score_MsgCb); // Pomodoro Sequence Start
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "Score_init: Failed to subscribe to MSG_0200");
    eStatus = MessageBroker_subscribe(MSG_0201, Score_MsgCb); // Pomodoro Work Time Sequence Complete
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "Score_init: Failed to subscribe to MSG_0201");
    eStatus = MessageBroker_subscribe(MSG_0202, Score_MsgCb); // Pomodoro Break Time Sequence Complete
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "Score_init: Failed to subscribe to MSG_0202");
    eStatus = MessageBroker_subscribe(MSG_0203, Score_MsgCb); // Pomodoro Cancel Sequence Complete
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "Score_init: Failed to subscribe to MSG_0203");

    unused(eStatus); // To avoid compiler warnings when the code is optimized

    // Set up the Second Timer
    Countdown_initTimerMs(&sCountdownTimerSec, ONE_SECOND, E_OPERATIONAL_MODE_CONTIUNOUS);

    // Set up the Score Watchdog Timer
    Countdown_initTimerMs(&sScoreWatchdogTimer, SCORE_WATCHDOG_TIMEOUT, E_OPERATIONAL_MODE_CONTIUNOUS);
    Countdown_resetAndStartTimer(&sScoreWatchdogTimer);
}

status_e Score_execute(void)
{
    // Reset the Total Daily Active Pomodoro Seconds if the Watchdog Timer has expired
    if (Countdown_getTimerStatus(&sScoreWatchdogTimer) == E_COUNTDOWN_TIMER_EXPIRED)
    {
        u32TotalDailyActivePomodoroSeconds = 0U;
    }

    // Update the Current Second Count - Update the counter once per second
    if (Countdown_getTimerStatus(&sCountdownTimerSec) == E_COUNTDOWN_TIMER_EXPIRED)
    {
        u32CurrentSecondCount++;
    }

    return STATUS_SUCCESS;
}