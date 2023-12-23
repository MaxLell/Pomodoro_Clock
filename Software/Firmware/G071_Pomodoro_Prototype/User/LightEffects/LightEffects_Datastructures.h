#ifndef LIGHTEFFECTS_DATASTRUCTURES_H
#define LIGHTEFFECTS_DATASTRUCTURES_H

#include "Common.h"

#define MAX_SETTINGS 4

typedef enum {
  E_INNER_RING = 1U,
  E_OUTER_RING = 2U,
  E_UNDEFINED_RING = -1
} RingType_e;

typedef enum {
  E_ANIMATION_WORK_TIME_ = 1U,
  E_ANIMATION_BREAK_TIME,
  E_ANIMATION_WARNING,
  E_ANIMATION_HIGH_BRIGHTNESS,
  E_ANIMATION_NOT_DEFINED
} AnimationType_e;

typedef struct {
  RingType_e sRingType;
  AnimationType_e sAnimationType;
  uint8_t u8NumberOfElements;
  uint8_t u8Offset;
} RingConfig_t;

typedef struct {
  RingConfig_t tWorktimeConfig[MAX_SETTINGS];
  RingConfig_t tBreaktimeConfig[MAX_SETTINGS];
} RingsDisplayConfig_t;

#endif  // LIGHTEFFECTS_DATASTRUCTURES_H
