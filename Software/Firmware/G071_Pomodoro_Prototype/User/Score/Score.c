#include "Score.h"

#include "CountdownTimer.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "LightEffects.h"

#define ONE_MINUTE 60000
#define TEN_MINUTES 600000
#define FOUR_HOURS 14400000

/*************************************************************
 * Private Data
 *************************************************************/

STATIC TestData_0006_s sScoreTimeStamps = {
    .u32MinutePeriod = ONE_MINUTE,
    .u32TimeoutPeriod = TEN_MINUTES,
    .u32WatchdogPeriod = FOUR_HOURS,
};

STATIC timer_t sMinuteTimer;
STATIC timer_t sWatchdogTimer;
STATIC timer_t sTimeoutTimer;

STATIC BOOL bPomodoroActive = FALSE;

STATIC uint32_t u32TotalDailyScoreInMinutes = 0U;

/*************************************************************
 * Implementation
 *************************************************************/

status_e Score_MsgCb(const msg_t *const in_psMessage)
{
    { // Input Checks
        ASSERT_MSG(!(NULL == in_psMessage), "Null Pointer");
        if (NULL == in_psMessage)
        {
            return STATUS_ERROR;
        }
    }

    switch (in_psMessage->eMsgId)
    {
    case MSG_0006:
    {
        // Parse out the TestData_0006_s struct from the message
        TestData_0006_s *psScoreTimeStamps = (TestData_0006_s *)in_psMessage->au8DataBytes;

        // Update the global TestData_0006_s struct
        sScoreTimeStamps.u32MinutePeriod = psScoreTimeStamps->u32MinutePeriod;
        sScoreTimeStamps.u32TimeoutPeriod = psScoreTimeStamps->u32TimeoutPeriod;
        sScoreTimeStamps.u32WatchdogPeriod = psScoreTimeStamps->u32WatchdogPeriod;

        // Initialize the Timers
        Countdown_initTimerMs(&sMinuteTimer, sScoreTimeStamps.u32MinutePeriod, E_OPERATIONAL_MODE_CONTIUNOUS);
        Countdown_initTimerMs(&sWatchdogTimer, sScoreTimeStamps.u32WatchdogPeriod, E_OPERATIONAL_MODE_CONTIUNOUS);
        Countdown_initTimerMs(&sTimeoutTimer, sScoreTimeStamps.u32TimeoutPeriod, E_OPERATIONAL_MODE_CONTIUNOUS);

        // Start the Watchdog Timer and the Timeout Timer
        Countdown_resetAndStartTimer(&sWatchdogTimer);
        Countdown_resetAndStartTimer(&sTimeoutTimer);
    }

    break;

    case MSG_0200: // Pomodoro Start
    {
        // Check that the Minute Timer is not Enabled
        ASSERT_MSG(!(E_COUNTDOWN_TIMER_NOT_ENABLED != Countdown_getTimerStatus(&sMinuteTimer)), "Minute Timer is already enabled");

        // Check that the Pomodoro Active Flag is FALSE
        ASSERT_MSG(!(TRUE == bPomodoroActive), "Pomodoro is already active");

        // Set the Pomodoro Active Flag to TRUE
        bPomodoroActive = TRUE;

        // Reset and Start the Minute Counter Timer
        Countdown_resetAndStartTimer(&sMinuteTimer);

        // Reset the Watchdog and the Timout Timer
        Countdown_resetAndStartTimer(&sWatchdogTimer);
        Countdown_resetAndStartTimer(&sTimeoutTimer);
    }
    break;

    case MSG_0204: // Pomodoro Complete
    {
        // Check that the Pomodoro is active
        ASSERT_MSG(!(FALSE == bPomodoroActive), "Pomodoro is not active, but should be!");

        // Check that the Minute Timer is Active
        ASSERT_MSG(!(E_COUNTDOWN_TIMER_NOT_ENABLED == Countdown_getTimerStatus(&sMinuteTimer)), "Minute Timer is not enabled");

        // Set the Pomodoro Active Flag to FALSE
        bPomodoroActive = FALSE;

        // Stop the Minute Countdown Timer
        Countdown_stopTimer(&sMinuteTimer);

        // Reset the Watchdog and the Timout Timer
        Countdown_resetTimer(&sWatchdogTimer);
        Countdown_resetTimer(&sTimeoutTimer);
    }
    break;

    default:
        ASSERT_MSG(FALSE, "Invalid Message ID: %d", in_psMessage->eMsgId);
        return STATUS_ERROR;
    }
    return STATUS_OK;
}

void Score_init(void)
{
    // Subscribe to the Messages
    // Test Message
    status_e eStatus = MessageBroker_subscribe(MSG_0006, Score_MsgCb);
    ASSERT_MSG(STATUS_OK == eStatus, "Failed to Subscribe to MSG_0003");

    // Pomodoro Start
    eStatus = MessageBroker_subscribe(MSG_0200, Score_MsgCb);
    ASSERT_MSG(STATUS_OK == eStatus, "Failed to Subscribe to MSG_0200");

    // Pomodoro Complete
    eStatus = MessageBroker_subscribe(MSG_0204, Score_MsgCb);
    ASSERT_MSG(STATUS_OK == eStatus, "Failed to Subscribe to MSG_0204");
    unused(eStatus);

    // Initialize the Timers
    Countdown_initTimerMs(&sMinuteTimer, sScoreTimeStamps.u32MinutePeriod, E_OPERATIONAL_MODE_CONTIUNOUS);
    Countdown_initTimerMs(&sWatchdogTimer, sScoreTimeStamps.u32WatchdogPeriod, E_OPERATIONAL_MODE_CONTIUNOUS);
    Countdown_initTimerMs(&sTimeoutTimer, sScoreTimeStamps.u32TimeoutPeriod, E_OPERATIONAL_MODE_CONTIUNOUS);

    // Reset the Pomodoro Active Flag
    bPomodoroActive = FALSE;

    // Reset the Daily Score
    u32TotalDailyScoreInMinutes = 0U;
}

status_e Score_execute(void)
{
    if (TRUE == bPomodoroActive)
    { // Pomodoro is active
        // Reset the Watchdog Timer
        Countdown_resetTimer(&sWatchdogTimer);

        // Reset the Timeout Timer
        Countdown_resetTimer(&sTimeoutTimer);

        if (E_COUNTDOWN_TIMER_EXPIRED == Countdown_getTimerStatus(&sMinuteTimer))
        {
            // Increment the Total Daily Score
            u32TotalDailyScoreInMinutes++;

            // Render the Minutes on the Inner Ring (Score)
            LightEffects_RenderScore(u32TotalDailyScoreInMinutes);
        }
    }
    else
    { // Pomodoro is NOT active
        if (E_COUNTDOWN_TIMER_EXPIRED == Countdown_getTimerStatus(&sWatchdogTimer))
        {
            // Reset the Total Daily Score
            u32TotalDailyScoreInMinutes = 0U;

            // Clear the Score Ring
            LightEffects_ClearScore();

            // Stop the Watchdog Timer
            Countdown_stopTimer(&sWatchdogTimer);

            log_info("Score Watchdog Timer Expired - Resetting Score");
        }

        if (E_COUNTDOWN_TIMER_EXPIRED == Countdown_getTimerStatus(&sTimeoutTimer))
        {
            // Clear the Score Ring
            LightEffects_ClearScore();

            // Stop the Timeout Timer
            Countdown_stopTimer(&sTimeoutTimer);

            log_info("Timeout Timer Expired - Disabling Score Indicator");
        }
    }

    return STATUS_OK;
}