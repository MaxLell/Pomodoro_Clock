#include "TimerNonBlocking.h"

#include "ClockTower_Hardware.h"

uint32_t getSysTick() {
  uint32_t u32SysTickCount;
  ClockTower_Hardware_getSysTickCount(&u32SysTickCount);
  return u32SysTickCount;
}

void initTimer(timer_t *psTimer, uint32_t u32PeriodMs, uint8_t u8UserMode) {
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

void startTimer(timer_t *psTimer) {
  {  // Input Checks
    ASSERT_MSG(!(NULL == psTimer), "Timer cannot be NULL");
  }
  psTimer->u32StartTimeMs = getSysTick();
  psTimer->bTimerEnabled = TRUE;
}

void stopTimer(timer_t *psTimer) {
  {  // Input Checks
    ASSERT_MSG(!(NULL == psTimer), "Timer cannot be NULL");
  }
  psTimer->bTimerEnabled = FALSE;
}

uint8_t isTimerExpired(timer_t *psTimer) {
  {  // Input Checks
    ASSERT_MSG(!(NULL == psTimer), "Timer cannot be NULL");
  }
  if (psTimer->bTimerEnabled == TRUE) {
    if ((getSysTick() - psTimer->u32StartTimeMs) >=
        psTimer->u32TimerPeriod)  // accounts for buffer overflow
    {
      if (psTimer->u8Mode == CONTINOUS_MODE) {
        startTimer(psTimer);  // Restart Timer for user in Continuous mode
      }
      return TIMER_EXPIRED;
    } else {
      return TIMER_NOT_EXPIRED;
    }
  }
  return TIMER_NOT_ENABLED;
}
