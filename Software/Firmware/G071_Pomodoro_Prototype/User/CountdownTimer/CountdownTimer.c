#include "CountdownTimer.h"

#include "CountdownTimer_Hardware.h"

STATIC uint32_t Countdown_getSysTick();

uint32_t Countdown_getSysTick()
{
    uint32_t u32SysTickCount;
    CountdownTimer_Hardware_getSysTickCount(&u32SysTickCount);
    return u32SysTickCount;
}

void Countdown_initTimerMs(timer_t *const inout_psTimer, const uint32_t in_u32PeriodMs, const uint8_t in_u8UserMode)
{
    { // Input Checks
        ASSERT_MSG(!(in_u32PeriodMs == 0U), "Timer period cannot be 0");
        ASSERT_MSG(!(in_u8UserMode < E_OPERATIONAL_MODE_ONE_SHOT), "Invalid Timer Mode");
        ASSERT_MSG(!(in_u8UserMode > E_OPERATIONAL_MODE_CONTIUNOUS), "Invalid Timer Mode");
        ASSERT_MSG(!(NULL == inout_psTimer), "Timer cannot be NULL");
    }
    inout_psTimer->u32StartTimeMs = 0U;
    inout_psTimer->u32TimerPeriod = in_u32PeriodMs;
    inout_psTimer->bTimerEnabled = FALSE;
    inout_psTimer->u8Mode = in_u8UserMode;
}

void Countdown_startTimer(timer_t *const inout_psTimer)
{
    { // Input Checks
        ASSERT_MSG(!(NULL == inout_psTimer), "Timer cannot be NULL");
        // Period must not be 0
        ASSERT_MSG(!(inout_psTimer->u32TimerPeriod == 0U), "Timer period cannot be 0");

        // Mode must not be invalid
        ASSERT_MSG(!(inout_psTimer->u8Mode >= E_OPERATIONAL_MODE_INVALID), "Invalid Timer Mode");
    }
    inout_psTimer->u32StartTimeMs = Countdown_getSysTick();
    inout_psTimer->bTimerEnabled = TRUE;
}

void Countdown_stopTimer(timer_t *const inout_psTimer)
{
    { // Input Checks
        ASSERT_MSG(!(NULL == inout_psTimer), "Timer cannot be NULL");
    }
    inout_psTimer->bTimerEnabled = FALSE;
}

timer_status_t Countdown_getTimerStatus(timer_t *const inout_psTimer)
{
    { // Input Checks
        ASSERT_MSG(!(NULL == inout_psTimer), "Timer cannot be NULL");

        // Make sure that all properties are within Range
        ASSERT_MSG(!(inout_psTimer->u8Mode >= E_OPERATIONAL_MODE_INVALID),
                   "Invalid Timer Mode. The provided mode is %d", inout_psTimer->u8Mode);
        ASSERT_MSG(!(inout_psTimer->u32TimerPeriod == 0U), "Timer period cannot be 0, Timer needs to be started first");
        ASSERT_MSG(!(inout_psTimer->bTimerEnabled > TRUE), "Invalid Enabled Flag Setting");
    }
    if (inout_psTimer->bTimerEnabled == TRUE)
    {
        if ((Countdown_getSysTick() - inout_psTimer->u32StartTimeMs) >=
            inout_psTimer->u32TimerPeriod) // accounts for buffer overflow
        {
            if (inout_psTimer->u8Mode == E_OPERATIONAL_MODE_CONTIUNOUS)
            {
                // Restart Timer for user in Continuous mode
                Countdown_startTimer(inout_psTimer);
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
