#ifndef LIGHTEFFECTS_H
#define LIGHTEFFECTS_H

#include "Common.h"

typedef enum {
  E_LIGHT_EFFECTS_STATUS_SEQUENCE_COMPLETE = 0U,
  E_LIGHT_EFFECTS_STATUS_SEQUENCE_IN_PROGRESS = 1U,
  E_LIGHT_EFFECTS_STATUS_ERROR = 2U
} LightEffects_SequenceStatus_e;

void LightEffects_DotAroundTheCircle(
    LightEffects_SequenceStatus_e* out_eSequenceStatus,
    uint16_t u16PeriodPerIncrementMs);

#endif  // LIGHTEFFECTS_H
