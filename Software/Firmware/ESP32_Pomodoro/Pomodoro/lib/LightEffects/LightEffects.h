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
    u8 u8CurrentFillingMin;
    LightControl_RingCountdownEffect_e eEffect; // Snooze / Warning / CancelSeq
    BOOL bIsComplete;
} LightControl_RingCountdown_s;

typedef struct
{
    BOOL bInitialized;
    BOOL bSequenceComplete;
    BOOL bDecline;
    u8 u8CurrentBrightness;
    u8 u8CurrentLedIdx;
} LightEffects_SeekingAttention_s;

/************************************************************
 * Public functions
 ************************************************************/
void LightEffects_scaleArray(const u8 *const in_au8SourceArray, u8 in_u8SourceArraySize,
                             u8 *out_au8TargetArray, u8 in_u8TargetArraySize);

void LightEffects_RenderMiddleAndOuterRings(const u8 *const in_au8MiddleRingArray, u8 in_u8MiddleRingArraySize,
                                            const u8 *const in_au8OuterRingArray, u8 in_u8OuterRingArraySize);

void LightEffects_ClearPomodoroProgressRings(void);

void LightEffects_RenderPomodoro(const u8 *const in_au8MinuteArray, const u8 in_u8ArraySize,
                                 bool bIsWorktimeOver);

void LightEffects_ClearAllRingLeds(void);

void LightEffects_RenderRingCountdown(LightControl_RingCountdown_s *const psSelf);

void LightEffects_UpdateRingCountdown(LightControl_RingCountdown_s *const psSelf);

void LightEffects_RenderSeekingAttention(LightEffects_SeekingAttention_s *const psSelf);

void LightEffects_RenderScore(u32 in_u32ScoreInMinutes);

void LightEffects_ClearScore(void);

#endif // LIGHTEFFECTS_H