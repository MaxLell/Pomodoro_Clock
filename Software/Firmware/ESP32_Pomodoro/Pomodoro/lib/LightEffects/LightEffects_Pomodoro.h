#ifndef LIGHTEFFECTS_POMODORO_H
#define LIGHTEFFECTS_POMODORO_H

#include "LightEffects.h"

/************************************************************
 * Public Data Structures for the Pomodoro
 ************************************************************/

typedef enum
{
    E_MIDDLE_RING,
    E_OUTER_RING,
    E_INNER_RING,
    E_UNDEFINED_RING
} LightEffects_Ring_e;

typedef enum
{
    E_ANIMATION_OFF = 0U,
    E_ANIMATION_WORK_TIME,
    E_ANIMATION_BREAK_TIME,
    E_ANIMATION_BREAK_TIME_BRIGHT,
    E_ANIMATION_WARNING,
    E_ANIMATION_FLASHLIGHT,
    E_ANIMATION_CANCEL_SEQUENCE,
    E_ANIMATION_SNOOZE,
    E_ANIMATION_NOT_DEFINED
} LightEffects_Animation_e;

/************************************************************
 * Public functions for the Pomodoro Sequence
 ************************************************************/

#endif // LIGHTEFFECTS_POMODORO_H
