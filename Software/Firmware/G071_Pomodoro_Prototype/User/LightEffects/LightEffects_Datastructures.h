#ifndef LIGHTEFFECTS_DATASTRUCTURES_H
#define LIGHTEFFECTS_DATASTRUCTURES_H

#include "Common.h"

#define MAX_SETTINGS 3U

typedef enum {
  E_INNER_RING = 1U,
  E_OUTER_RING = 2U,
  E_UNDEFINED_RING = -1
} RingType_e;

typedef enum {
  E_ANIMATION_WORK_TIME_ = 1U,
  E_ANIMATION_BREAK_TIME,
  E_ANIMATION_FLASHLIGHT,
  E_ANIMATION_BREAK_TIME_BRIGHT,
  E_ANIMATION_NOT_DEFINED
} AnimationType_e;

typedef struct {
  RingType_e sRingType;
  AnimationType_e sAnimationType;
  uint8_t u8NumberOfElements;
  uint8_t u8Offset;
} RingPhaseConfig_t;

typedef struct {
  RingPhaseConfig_t tWorktimeRingPhaseConfig[MAX_SETTINGS];
  RingPhaseConfig_t tBreaktimeRingPhaseConfig[MAX_SETTINGS];
} RingsDisplayConfig_t;

#endif  // LIGHTEFFECTS_DATASTRUCTURES_H
