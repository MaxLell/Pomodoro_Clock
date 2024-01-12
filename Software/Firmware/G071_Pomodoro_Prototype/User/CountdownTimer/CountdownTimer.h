#ifndef COUNTDOWN_TIMER_H
#define COUNTDOWN_TIMER_H

#include "Common.h"

typedef enum
{
    E_COUNTDOWN_TIMER_NOT_EXPIRED = 0U,
    E_COUNTDOWN_TIMER_EXPIRED = 1U,
    E_COUNTDOWN_TIMER_NOT_ENABLED = 2U,
    E_COUNTDOWN_TIMER_STATUS_INVALID
} timer_status_t;

typedef enum
{

    E_OPERATIONAL_MODE_ONE_SHOT = 0, // Timer fires once
    E_OPERATIONAL_MODE_CONTIUNOUS,   // Timer will restart itself once elapsed
    E_OPERATIONAL_MODE_INVALID,
} timer_operationalMode_e;

typedef struct
{
    uint32_t u32StartTimeMs; // Stores start time
    uint32_t u32TimerPeriod;
    uint8_t u8Mode;
    BOOL bTimerEnabled;
} timer_t;

void Countdown_initTimerMs(timer_t *const inout_psTimer, const uint32_t in_u32PeriodMs, const uint8_t in_u8UserMode);
void Countdown_startTimer(timer_t *const inout_psTimer);
void Countdown_stopTimer(timer_t *const inout_psTimer);
timer_status_t Countdown_getTimerStatus(timer_t *const inout_psTimer);

#endif // COUNTDOWN_TIMER_H
