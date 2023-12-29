#ifndef LIGHTEFFECTS_H
#define LIGHTEFFECTS_H

#include "Common.h"

/************************************************************
 * Public Defines
 ************************************************************/
#define MINUTES_IN_HOUR 60
#define TOTAL_MINUTES (MINUTES_IN_HOUR * 2)
#define MAX_SETTINGS 6U

/************************************************************
 * Public Data Structures
 ************************************************************/

typedef enum {
  //       WT_BT
  E_EFFECT_25_5 = 0U,
  E_EFFECT_51_17,
  E_EFFECT_90_15,
  E_EFFECT_LAST
} LightEffect_Effect_e;

typedef enum {
  E_PHASE_WORK_TIME = 0U,
  E_PHASE_BREAK_TIME
} LightEffects_PomodoroPhase_e;

typedef enum {
  E_INNER_RING = 0U,
  E_OUTER_RING,
  E_UNDEFINED_RING
} LightEffects_Ring_e;

typedef enum {
  E_ANIMATION_OFF = 0U,
  E_ANIMATION_WORK_TIME,
  E_ANIMATION_BREAK_TIME,
  E_ANIMATION_BREAK_TIME_BRIGHT,
  E_ANIMATION_FLASHLIGHT,
  E_ANIMATION_NOT_DEFINED
} LightEffects_Animation_e;

typedef struct {
  LightEffects_PomodoroPhase_e ePhase;
  LightEffects_Ring_e eRingType;
  LightEffects_Animation_e eAnimationType;
  uint8_t u8DuratationInMinutes;
  uint8_t u8MinuteOffset;
} LightEffects_PomodoroRingPhaseCfg_t;

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

void LightEffects_RenderRingConfig(
    LightEffects_PomodoroRingPhaseCfg_t* const inout_psRingPhaseConfig,
    status_e* out_peRenderStatus);

#endif  // LIGHTEFFECTS_H