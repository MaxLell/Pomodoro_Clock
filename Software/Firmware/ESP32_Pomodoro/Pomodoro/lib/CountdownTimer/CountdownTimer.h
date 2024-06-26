#ifndef COUNTDOWN_TIMER_H
#define COUNTDOWN_TIMER_H

#include "Common.h"

typedef enum
{
    E_COUNTDOWN_TIMER_NOT_EXPIRED = 0U,
    E_COUNTDOWN_TIMER_EXPIRED = 1U,
    E_COUNTDOWN_TIMER_NOT_ENABLED = 2U,
    E_COUNTDOWN_TIMER_STATUS_INVALID
} CountdownTimer_status_t;

typedef enum
{

    E_OPERATIONAL_MODE_ONE_SHOT = 0, // Timer fires once
    E_OPERATIONAL_MODE_CONTIUNOUS,   // Timer will restart itself once elapsed
    E_OPERATIONAL_MODE_INVALID,
} CountdownTimer_operationMode_e;

typedef struct
{
    u32 u32StartTimeMs; // Stores start time
    u32 u32TimerPeriod;
    u8 u8Mode;
    bool bTimerEnabled;
} CountdownTimer_t;

void Countdown_initTimerMs(CountdownTimer_t *const inout_psTimer, const u32 in_u32PeriodMs, const u8 in_u8UserMode);
void Countdown_resetAndStartTimer(CountdownTimer_t *const inout_psTimer);
void Countdown_startTimer(CountdownTimer_t *const inout_psTimer);
void Countdown_stopTimer(CountdownTimer_t *const inout_psTimer);
void Countdown_resetTimer(CountdownTimer_t *const inout_psTimer);
CountdownTimer_status_t Countdown_getTimerStatus(CountdownTimer_t *const inout_psTimer);

#endif // COUNTDOWN_TIMER_H
