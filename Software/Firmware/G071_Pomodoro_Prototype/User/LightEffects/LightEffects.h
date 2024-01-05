#ifndef LIGHTEFFECTS_H
#define LIGHTEFFECTS_H

#include "Common.h"

/************************************************************
 * Public Defines
 ************************************************************/
#define MINUTES_IN_HOUR 60
#define TOTAL_MINUTES (MINUTES_IN_HOUR * 2)

/************************************************************
 * Public functions
 ************************************************************/
void LightEffects_scaleArray(const uint8_t* const in_au8SourceArray,
                             uint8_t in_u8SourceArraySize,
                             uint8_t* out_au8TargetArray,
                             uint8_t in_u8TargetArraySize);

void LightEffects_DotAroundTheCircle(status_e* out_eSequenceStatus,
                                     uint16_t u16PeriodPerIncrementMs);

void LightEffects_ClearAllRingLeds(void);

void LightEffects_RenderRings(const uint8_t* const in_au8MiddleRingArray,
                              uint8_t in_u8MiddleRingArraySize,
                              const uint8_t* const in_au8OuterRingArray,
                              uint8_t in_u8OuterRingArraySize);

#endif  // LIGHTEFFECTS_H