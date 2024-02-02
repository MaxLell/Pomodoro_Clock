#ifndef LIGHTEFFECTS_H
#define LIGHTEFFECTS_H

#include "Common.h"

/************************************************************
 * Public Defines
 ************************************************************/

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

#endif // LIGHTEFFECTS_H