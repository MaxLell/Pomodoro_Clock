#include "CountdownTimer.h"

#include "CountdownTimer_Hardware.h"

STATIC uint32_t Countdown_getSysTick();

uint32_t Countdown_getSysTick() {
  uint32_t u32SysTickCount;
  CountdownTimer_Hardware_getSysTickCount(&u32SysTickCount);
  return u32SysTickCount;
}

void Countdown_initTimer(timer_t *psTimer, uint32_t u32PeriodMs,
                         uint8_t u8UserMode) {
  {  // Input Checks
    ASSERT_MSG(!(u32PeriodMs == 0U), "Timer period cannot be 0");
    ASSERT_MSG(!(u8UserMode > CONTINOUS_MODE), "Invalid Timer Mode");
    ASSERT_MSG(!(NULL == psTimer), "Timer cannot be NULL");
  }
  psTimer->u32StartTimeMs = 0U;
  psTimer->u32TimerPeriod = u32PeriodMs;
  psTimer->bTimerEnabled = FALSE;
  psTimer->u8Mode = u8UserMode;
}

void Countdown_startTimer(timer_t *psTimer) {
  {  // Input Checks
    ASSERT_MSG(!(NULL == psTimer), "Timer cannot be NULL");
  }
  psTimer->u32StartTimeMs = Countdown_getSysTick();
  psTimer->bTimerEnabled = TRUE;
}

void Countdown_stopTimer(timer_t *psTimer) {
  {  // Input Checks
    ASSERT_MSG(!(NULL == psTimer), "Timer cannot be NULL");
  }
  psTimer->bTimerEnabled = FALSE;
}

timer_status_t Countdown_getTimerStatus(timer_t *psTimer) {
  {  // Input Checks
    ASSERT_MSG(!(NULL == psTimer), "Timer cannot be NULL");
  }
  if (psTimer->bTimerEnabled == TRUE) {
    if ((Countdown_getSysTick() - psTimer->u32StartTimeMs) >=
        psTimer->u32TimerPeriod)  // accounts for buffer overflow
    {
      if (psTimer->u8Mode == CONTINOUS_MODE) {
        Countdown_startTimer(
            psTimer);  // Restart Timer for user in Continuous mode
      }
      return E_COUNTDOWN_TIMER_EXPIRED;
    } else {
      return E_COUNTDOWN_TIMER_NOT_EXPIRED;
    }
  }
  return E_COUNTDOWN_TIMER_NOT_ENABLED;
}
