#ifndef TIMER_NON_BLOCKING_H
#define TIMER_NON_BLOCKING_H

#include "Common.h"

#define TIMER_NOT_EXPIRED 0U
#define TIMER_EXPIRED 1U
#define TIMER_NOT_ENABLED 2U

#define ONE_SHOT_MODE 0U   // Timer fires once
#define CONTINOUS_MODE 1U  // Timer will restart itself once elapsed

typedef struct {
  uint32_t u32StartTimeMs;  // Stores start time
  uint32_t u32TimerPeriod;
  uint8_t u8Mode;
  BOOL bTimerEnabled;
} timer_t;

uint32_t getSysTick();
void initTimer(timer_t *timer, uint32_t time_period, uint8_t u8_user_mode);
void startTimer(timer_t *timer);
void stopTimer(timer_t *timer);
uint8_t isTimerExpired(timer_t *timer);

#endif  // TIMER_NON_BLOCKING_H
