#include "LightEffects.h"
#include "LightEffects_Pomodoro.h"

#include "CountdownTimer.h"
#include "Delay.h"
#include "RgbLed.h"
#include "RgbLed_Config.h"
#include "math.h"

/************************************************************
 * Function Prototypes
 ************************************************************/

STATIC void LightEffects_updateMinuteToLedArray(
    uint8_t in_u8OffsetMin,
    uint8_t* inout_au8MinuteToLedConfigArray);

/************************************************************
 * Implementation
 ************************************************************/

void LightEffects_scaleArray(const uint8_t* const in_au8SourceArray,
                             uint8_t in_u8SourceArraySize,
                             uint8_t* out_au8TargetArray,
                             uint8_t in_u8TargetArraySize) {
  {  // Input Checks
    ASSERT_MSG(!(in_au8SourceArray == NULL), "in_au8SourceArray is NULL Ptr");
    ASSERT_MSG(!(out_au8TargetArray == NULL), "in_au8SourceArray is NULL Ptr");
    ASSERT_MSG(!(in_u8SourceArraySize == 0),
               "Provided in_u8SourceArraySize needs to be larger then 0");
    ASSERT_MSG(!(in_u8TargetArraySize == 0),
               "Provided in_u8TargetArraySize needs to be larger then 0");
  }

  // Calculate the Scale Factor
  float fScaleFactor =
      (float)in_u8SourceArraySize / (float)in_u8TargetArraySize;
  // Scale the Array
  for (uint8_t i = 0; i < in_u8TargetArraySize; i++) {
    out_au8TargetArray[i] = in_au8SourceArray[(uint8_t)(i * fScaleFactor)];
  }
}

/*
 ######### New Implementation #########
*/

void LightEffects_DotAroundTheCircle(status_e* out_eSequenceStatus,
                                     uint16_t u16PeriodPerIncrementMs) {
  {
    // Input Checks
    ASSERT_MSG(!(NULL == out_eSequenceStatus),
               "Sequence Status cannot be NULL");
    ASSERT_MSG(!(u16PeriodPerIncrementMs == 0U), "Period cannot be 0");
  }
  // Variable Declarations
  static uint8_t u8LedIndex = 0;
  uint8_t effect[RGB_LED_TOTAL_LEDS] = {2, 5, 5, 5, 2};
  uint8_t effect_size = sizeof(effect);

  // Increment the ledIndex
  u8LedIndex++;

  if (u8LedIndex == RGB_LED_TOTAL_LEDS) {
    // Set the sequence status to complete
    *out_eSequenceStatus = STATUS_PENDING;

    // Reset the ledIndex
    u8LedIndex = 0;

    // Disable all LEDs
    RgbLed_clear();
  } else {
    for (uint8_t i = 0; i < RGB_LED_TOTAL_LEDS; i++) {
      RgbLed_setPixelColor(i, 0, 0, 0);
    }

    for (uint8_t i = 0; i < effect_size; i++) {
      uint8_t tmp = (u8LedIndex + i) % RGB_LED_TOTAL_LEDS;
      RgbLed_setPixelColor(tmp, effect[i], effect[i], effect[i]);
    }

    // Set the Sequence Status to in progress
    *out_eSequenceStatus = STATUS_PENDING;
  }
  // Wait a fixed delay
  Delay_ms(u16PeriodPerIncrementMs);

  // Show the sequence on the LEDs
  RgbLed_show();
}

void LightEffects_ClearAllRingLeds(void) {
  RgbLed_clear();
  Delay_ms(10);
  RgbLed_show();
}

void LightEffects_isPhaseOver(
    const LightEffects_PomodoroRingPhaseCfg_t* const in_saEffect,
    uint8_t in_u8EffectArraySize,
    BOOL* out_bWorktimeOver,
    LightEffects_PomodoroPhase_e in_ePhase,
    LightEffects_Animation_e in_eAnimationType) {
  {  // Input Checks
    ASSERT_MSG(!(in_saEffect == NULL), "in_saEffect is NULL");
    ASSERT_MSG(!(in_u8EffectArraySize == 0), "in_u8EffectArraySize is 0");
    ASSERT_MSG(!(in_u8EffectArraySize > MAX_SETTINGS),
               "in_u8EffectArraySize is larger then MAX_SETTINGS");
    ASSERT_MSG(!(out_bWorktimeOver == NULL), "out_bWorktimeOver is NULL");
    ASSERT_MSG(!(in_ePhase > E_ANIMATION_BREAK_TIME_BRIGHT),
               "in_ePhase is larger then E_ANIMATION_BREAK_TIME_BRIGHT");
    ASSERT_MSG(!(in_eAnimationType >= E_ANIMATION_NOT_DEFINED),
               "in_eAnimationType is larger then E_ANIMATION_NOT_DEFINED");
  }
  BOOL tmp = TRUE;
  for (uint8_t i = 0; i < in_u8EffectArraySize; i++) {
    if (in_saEffect[i].ePhase == in_ePhase) {
      if (in_saEffect[i].eAnimationType == in_eAnimationType) {
        if (in_saEffect[i].u8DuratationInMinutes != 0) {
          tmp = FALSE;
          break;
        }
      }
    }
  }
  *out_bWorktimeOver = tmp;
}

void LightEffects_getCompressedArraysForCurrentPhase(
    const LightEffects_PomodoroRingPhaseCfg_t* const in_asEffects,
    uint8_t in_u8EffectArraySize,
    LightEffects_PomodoroPhase_e in_ePhase,
    uint8_t* out_InnerRingCompressedArray,
    uint8_t* out_OuterRingCompressedArray) {
  {  // Input Checks
    ASSERT_MSG(!(in_asEffects == NULL), "in_asEffects is NULL");
    ASSERT_MSG(!(in_u8EffectArraySize == 0), "in_u8EffectArraySize is 0");
    ASSERT_MSG(!(in_u8EffectArraySize > MAX_SETTINGS),
               "in_u8EffectArraySize is larger then MAX_SETTINGS");
    ASSERT_MSG(!(in_ePhase >= E_PHASE_BREAK_TIME),
               "in_ePhase is larger then E_PHASE_BREAK_TIME");
    ASSERT_MSG(!(out_InnerRingCompressedArray == NULL),
               "out_InnerRingCompressedArray is NULL");
    ASSERT_MSG(!(out_OuterRingCompressedArray == NULL),
               "out_OuterRingCompressedArray is NULL");
  }
  // Parse only the Effect Array Entries, which correspond to the current phase
  // Create the Minute Array
  uint8_t au8MinuteArray[NUMBER_OF_PROGRESS_RINGS][MINUTES_IN_HOUR] = {0};
  for (uint8_t i = 0; i < in_u8EffectArraySize; i++) {
    if (in_asEffects[i].ePhase == in_ePhase) {
      LightEffects_setAnimationInRingMinuteArray(
          au8MinuteArray[in_asEffects[i].eRingType], MINUTES_IN_HOUR,
          in_asEffects[i].u8DuratationInMinutes, in_asEffects[i].u8MinuteOffset,
          in_asEffects[i].eAnimationType);
    }
  }
  // Compression
  uint8_t* au8CompressedArray[NUMBER_OF_PROGRESS_RINGS] = {0};
  uint8_t au8InnerRingCompressedArray[TOTAL_LEDS_INNER_RING] = {0};
  uint8_t au8OuterRingCompressedArray[TOTAL_LEDS_OUTER_RING] = {0};
  au8CompressedArray[E_INNER_RING] = au8InnerRingCompressedArray;
  au8CompressedArray[E_OUTER_RING] = au8OuterRingCompressedArray;

  LightEffects_scaleArray(au8MinuteArray[E_INNER_RING], MINUTES_IN_HOUR,
                          au8CompressedArray[E_INNER_RING],
                          TOTAL_LEDS_INNER_RING);
  LightEffects_scaleArray(au8MinuteArray[E_OUTER_RING], MINUTES_IN_HOUR,
                          au8CompressedArray[E_OUTER_RING],
                          TOTAL_LEDS_OUTER_RING);

  // Copy the Compressed Array to the Output
  for (uint8_t i = 0; i < TOTAL_LEDS_INNER_RING; i++) {
    out_InnerRingCompressedArray[i] = au8CompressedArray[E_INNER_RING][i];
  }
  for (uint8_t i = 0; i < TOTAL_LEDS_OUTER_RING; i++) {
    out_OuterRingCompressedArray[i] = au8CompressedArray[E_OUTER_RING][i];
  }
}

void LightEffects_setAnimationInRingMinuteArray(
    uint8_t* out_au8RingArray,
    uint8_t u8ArraySize,
    uint8_t in_u8DurationInMinutes,
    uint8_t in_u8MinuteOffset,
    LightEffects_Animation_e eAnimation) {
  {  // input Checks
    // Make sure that the array size is exactly Max Minutes in an hour
    ASSERT_MSG(!(u8ArraySize != MINUTES_IN_HOUR),
               "u8ArraySize is not equal to MINUTES_IN_HOUR");

    // Make sure that none of the existing entries within the provided array
    // exceed the range of animation enums
    for (uint8_t i = 0; i < u8ArraySize; i++) {
      ASSERT_MSG(!(out_au8RingArray[i] > E_ANIMATION_NOT_DEFINED),
                 "out_au8RingArray[i] is larger then E_ANIMATION_NOT_DEFINED");
    }

    // Make sure that the provided Minutes do not exceed the Max Minutes in an
    // hour
    ASSERT_MSG(!(in_u8DurationInMinutes > MINUTES_IN_HOUR),
               "in_u8DurationInMinutes is larger then MINUTES_IN_HOUR");

    // Make sure that the offset is does not exceed the Max Minutes in an hour
    ASSERT_MSG(!(in_u8MinuteOffset > MINUTES_IN_HOUR),
               "in_u8MinuteOffset is larger then MINUTES_IN_HOUR");

    // Run Null Pointer Checks
    ASSERT_MSG(!(out_au8RingArray == NULL), "out_au8RingArray is NULL");

    // Make sure that the animation is within bounds
    ASSERT_MSG(!(eAnimation >= E_ANIMATION_NOT_DEFINED),
               "eAnimation is larger then E_ANIMATION_NOT_DEFINED");
  }
  uint8_t idx = in_u8MinuteOffset;
  // Inset the current Animation
  for (uint8_t i = 0; i < in_u8DurationInMinutes; i++) {
    if (idx > (MINUTES_IN_HOUR - 1)) {
      idx = 0;
    }
    // Make sure that previous Entries are not overwritten
    ASSERT_MSG(!(E_ANIMATION_OFF != out_au8RingArray[idx]),
               "Animation overwritten at idx %d", idx);
    out_au8RingArray[idx] = eAnimation;
    idx++;
  }
}

void LightEffects_updateWorktimeCfgForCurrentMinute(
    LightEffects_PomodoroRingPhaseCfg_t* const inout_asEffects,
    uint8_t in_u8EffectArraySize,
    LightEffects_PomodoroPhase_e in_ePhase) {
  {  // Input Checks
    ASSERT_MSG(!(inout_asEffects == NULL), "inout_asEffects is NULL");
    ASSERT_MSG(!(in_u8EffectArraySize == 0), "in_u8EffectArraySize is 0");
    ASSERT_MSG(!(in_u8EffectArraySize > MAX_SETTINGS),
               "in_u8EffectArraySize is larger then MAX_SETTINGS");
  }

  for (uint8_t i = 0; i < in_u8EffectArraySize; i++) {
    // Only process the entries for the current phase
    if (inout_asEffects[i].ePhase == in_ePhase) {
      // Only process cfgs which still have active Minutes left otherwise skip
      BOOL bActiveMinutesLeft;
      LightEffects_AreThereActiveMinutesLeft(&inout_asEffects[i],
                                             &bActiveMinutesLeft);
      if (bActiveMinutesLeft == FALSE) {
        continue;
      }
      inout_asEffects[i].u8DuratationInMinutes -= 1;
      inout_asEffects[i].u8MinuteOffset += 1;

      // Only process the first element (The inner Ring)
      break;
    }
  }
}

void LightEffects_AreThereActiveMinutesLeft(
    const LightEffects_PomodoroRingPhaseCfg_t* const in_sEffect,
    BOOL* out_bActiveMinutesLeft) {
  {  // Input Checks
    ASSERT_MSG(!(in_sEffect == NULL), "in_sEffect is NULL");
    ASSERT_MSG(!(out_bActiveMinutesLeft == NULL),
               "out_bActiveMinutesLeft is NULL");
  }
  *out_bActiveMinutesLeft =
      (in_sEffect->u8DuratationInMinutes != 0) ? TRUE : FALSE;
}