#ifndef LIGHTEFFECTS_H
#define LIGHTEFFECTS_H

#include "Common.h"

/************************************************************
 * Public Defines
 ************************************************************/
#define MINUTES_IN_HOUR 60
#define TOTAL_MINUTES (MINUTES_IN_HOUR * 2)

#define LIGHTEFFECTS_LED_OFF 0
#define LIGHTEFFECTS_BREAK_TIME 1
#define LIGHTEFFECTS_WORK_TIME 2
#define LIGHTEFFECTS_WARNING 3

#define TOTAL_LEDS_OUTER_RING 24
#define TOTAL_LEDS_MIDDLE_RING 16
#define TOTAL_LEDS_INNER_RING 8
#define TOTAL_LEDS (24 + 26 + 8)

typedef enum {
  E_LIGHT_EFFECTS_STATUS_SEQUENCE_COMPLETE = 0U,
  E_LIGHT_EFFECTS_STATUS_SEQUENCE_IN_PROGRESS = 1U,
  E_LIGHT_EFFECTS_STATUS_ERROR = 2U
} LightEffects_SequenceStatus_e;

/************************************************************
 * Public functions
 ************************************************************/

void LightEffects_DotAroundTheCircle(
    LightEffects_SequenceStatus_e* out_eSequenceStatus,
    uint16_t u16PeriodPerIncrementMs);

void LightEffects_ClearAllRingLeds(void);

#endif  // LIGHTEFFECTS_H
