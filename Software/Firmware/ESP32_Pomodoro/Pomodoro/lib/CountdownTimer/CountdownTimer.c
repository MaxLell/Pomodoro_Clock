#include "CountdownTimer.h"

#include "CountdownTimer_Hardware.h"

u32 Countdown_getTick()
{
    u32 u32SysTickCount;
    CountdownTimer_Hardware_getTickCount(&u32SysTickCount);
    return u32SysTickCount;
}

void Countdown_initTimerMs(CountdownTimer_t *const inout_psTimer, const u32 in_u32PeriodMs, const u8 in_u8UserMode)
{
    { // Input Checks
        ASSERT_MSG(!(in_u32PeriodMs == 0U), "Timer period cannot be 0");
        ASSERT_MSG(!(in_u8UserMode < E_OPERATIONAL_MODE_ONE_SHOT), "Invalid Timer Mode");
        ASSERT_MSG(!(in_u8UserMode > E_OPERATIONAL_MODE_CONTIUNOUS), "Invalid Timer Mode");
        ASSERT_MSG(!(NULL == inout_psTimer), "Timer cannot be NULL");
    }
    inout_psTimer->u32StartTimeMs = 0U;
    inout_psTimer->u32TimerPeriod = in_u32PeriodMs;
    inout_psTimer->bTimerEnabled = false;
    inout_psTimer->u8Mode = in_u8UserMode;
}

void Countdown_resetTimer(CountdownTimer_t *const inout_psTimer)
{
    { // Input Checks
        ASSERT_MSG(!(NULL == inout_psTimer), "Timer cannot be NULL");
    }
    inout_psTimer->u32StartTimeMs = Countdown_getTick();
}

void Countdown_resetAndStartTimer(CountdownTimer_t *const inout_psTimer)
{
    { // Input Checks
        ASSERT_MSG(!(NULL == inout_psTimer), "Timer cannot be NULL");
        // Period must not be 0
        ASSERT_MSG(!(inout_psTimer->u32TimerPeriod == 0U), "Timer period cannot be 0");

        // Mode must not be invalid
        ASSERT_MSG(!(inout_psTimer->u8Mode >= E_OPERATIONAL_MODE_INVALID), "Invalid Timer Mode");
    }

    Countdown_startTimer(inout_psTimer);
    Countdown_resetTimer(inout_psTimer);
}

void Countdown_startTimer(CountdownTimer_t *const inout_psTimer)
{
    { // Input Checks
        ASSERT_MSG(!(NULL == inout_psTimer), "Timer cannot be NULL");
    }
    inout_psTimer->bTimerEnabled = true;
}

void Countdown_stopTimer(CountdownTimer_t *const inout_psTimer)
{
    { // Input Checks
        ASSERT_MSG(!(NULL == inout_psTimer), "Timer cannot be NULL");
    }
    inout_psTimer->bTimerEnabled = false;
}

CountdownTimer_status_t Countdown_getTimerStatus(CountdownTimer_t *const inout_psTimer)
{
    { // Input Checks
        ASSERT_MSG(!(NULL == inout_psTimer), "Timer cannot be NULL");

        // Make sure that all properties are within Range
        ASSERT_MSG(!(inout_psTimer->u8Mode >= E_OPERATIONAL_MODE_INVALID),
                   "Invalid Timer Mode. The provided mode is %d", inout_psTimer->u8Mode);
        ASSERT_MSG(!(inout_psTimer->u32TimerPeriod == 0U), "Timer period cannot be 0, Timer needs to be started first");
        ASSERT_MSG(!(inout_psTimer->bTimerEnabled > true), "Invalid Enabled Flag Setting");
    }
    if (inout_psTimer->bTimerEnabled == true)
    {
        if ((Countdown_getTick() - inout_psTimer->u32StartTimeMs) >=
            inout_psTimer->u32TimerPeriod) // accounts for buffer overflow
        {
            if (inout_psTimer->u8Mode == E_OPERATIONAL_MODE_CONTIUNOUS)
            {
                // Restart Timer for user in Continuous mode
                Countdown_resetAndStartTimer(inout_psTimer);
            }
            else
            {
                // Stop Timer for user in OneShot mode
                Countdown_stopTimer(inout_psTimer);
            }

            return E_COUNTDOWN_TIMER_EXPIRED;
        }
        else
        {
            return E_COUNTDOWN_TIMER_NOT_EXPIRED;
        }
    }
    return E_COUNTDOWN_TIMER_NOT_ENABLED;
}
