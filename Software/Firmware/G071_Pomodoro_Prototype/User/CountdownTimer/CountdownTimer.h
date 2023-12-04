#ifndef COUNTDOWN_TIMER_H
#define COUNTDOWN_TIMER_H

#include "Common.h"

#define TIMER_NOT_EXPIRED 0U
#define TIMER_EXPIRED 1U
#define TIMER_NOT_ENABLED 2U

typedef enum {
  E_COUNTDOWN_TIMER_NOT_EXPIRED = 0U,
  E_COUNTDOWN_TIMER_EXPIRED = 1U,
  E_COUNTDOWN_TIMER_NOT_ENABLED = 2U
} timer_status_t;

#define ONE_SHOT_MODE 0U   // Timer fires once
#define CONTINOUS_MODE 1U  // Timer will restart itself once elapsed

typedef struct {
  uint32_t u32StartTimeMs;  // Stores start time
  uint32_t u32TimerPeriod;
  uint8_t u8Mode;
  BOOL bTimerEnabled;
} timer_t;

void Countdown_initTimer(timer_t *psTimer, uint32_t u32TimerPeriodMs,
                         uint8_t u8UserMode);
void Countdown_startTimer(timer_t *psTimer);
void Countdown_stopTimer(timer_t *psTimer);
timer_status_t Countdown_isTimerExpired(timer_t *psTimer);

#endif  // COUNTDOWN_TIMER_H
