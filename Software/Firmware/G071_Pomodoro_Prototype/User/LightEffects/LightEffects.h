#ifndef LIGHTEFFECTS_H
#define LIGHTEFFECTS_H

#include "Common.h"

/************************************************************
 * Public Defines
 ************************************************************/

typedef enum
{
    E_RING_COUNTDOWN_EFFECT__INVALID = 0U,
    E_RING_COUNTDOWN_EFFECT__SNOOZE,
    E_RING_COUNTDOWN_EFFECT__WARNING,
    E_RING_COUNTDOWN_EFFECT__CANCEL_SEQ,
    E_RING_COUNTDOWN_EFFECT__LAST
} LightControl_RingCountdownEffect_e;

typedef struct
{
    uint16_t u16PeriodPerIncrementMsec;
    uint8_t u8CurrentFillingMin;
    LightControl_RingCountdownEffect_e eEffect; // Snooze / Warning / CancelSeq
    BOOL bIsComplete;
} LightControl_RingCountdown_s;

/************************************************************
 * Public functions
 ************************************************************/
void LightEffects_scaleArray(const uint8_t *const in_au8SourceArray, uint8_t in_u8SourceArraySize,
                             uint8_t *out_au8TargetArray, uint8_t in_u8TargetArraySize);

void LightEffects_RenderRings(const uint8_t *const in_au8MiddleRingArray, uint8_t in_u8MiddleRingArraySize,
                              const uint8_t *const in_au8OuterRingArray, uint8_t in_u8OuterRingArraySize);

void LightEffects_ClearPomodoroProgressRings(void);

void LightEffects_RenderPomodoro(const uint8_t *const in_au8MinuteArray, const uint8_t in_u8ArraySize,
                                 BOOL bIsWorktimeOver);

void LightEffects_ClearAllRingLeds(void);

void LightEffects_RenderRingCountdown(LightControl_RingCountdown_s *const psSelf);

void LightEffects_UpdateRingCountdown(LightControl_RingCountdown_s *const psSelf);

#endif // LIGHTEFFECTS_H