#include "TimerNonBlocking.h"

#include "ClockTower_Hardware.h"

uint32_t getSysTick() {
  uint32_t u32SysTickCount;
  ClockTower_Hardware_getSysTickCount(&u32SysTickCount);
  return u32SysTickCount;
}

void initTimer(timer_t *timer, uint32_t u32_time_period_ms,
               uint8_t u8_user_mode) {
  timer->u32StartTimeMs = 0U;
  timer->u32TimerPeriod = u32_time_period_ms;
  timer->bTimerEnabled = FALSE;
  timer->u8Mode = u8_user_mode;
}

void startTimer(timer_t *timer) {
  timer->u32StartTimeMs = getSysTick();
  timer->bTimerEnabled = TRUE;
}

void stopTimer(timer_t *timer) { timer->bTimerEnabled = FALSE; }

uint8_t isTimerExpired(timer_t *timer) {
  if (timer->bTimerEnabled == TRUE) {
    if ((getSysTick() - timer->u32StartTimeMs) >=
        timer->u32TimerPeriod)  // accounts for buffer overflow
    {
      if (timer->u8Mode == CONTINOUS_MODE) {
        startTimer(timer);  // Restart Timer for user in Continuous mode
      }
      return TIMER_EXPIRED;
    } else {
      return TIMER_NOT_EXPIRED;
    }
  }
  return TIMER_NOT_ENABLED;
}
