#include "LightEffects.h"
#include "RgbLed_Config.h"
#include "mock_Delay.h"
#include "mock_RgbLed.h"
#include "unity.h"

/*********************************************
 * external static functions
 *********************************************/

/*********************************************
 * external static variables
 *********************************************/

/*********************************************
 * implementation
 *********************************************/

void setUp(void) {}

void tearDown(void) {}

/**
 * Helper functions
 * lubendu-function = <3
 */

void helper_printArray(uint8_t* in_au8Array, uint8_t in_u8ArraySize) {
  /**
   * This function prints the index of the array next to the value line by line
   * Example:
   * 0 - 0
   * 1 - 2
   * 2 - 2
   * 3 - 2
   * ...
   */
  for (uint8_t i = 0; i < in_u8ArraySize; i++) {
    if (i < 10) {
      printf("%d ---> %d\n", i, in_au8Array[i]);
    } else if ((i < 100) && (i >= 10)) {
      printf("%d --> %d\n", i, in_au8Array[i]);
    } else {
      printf("%d -> %d\n", i, in_au8Array[i]);
    }
  }
  printf("\n");
}

///////////////////////////////////////////////
// Data Structure Experiments
///////////////////////////////////////////////
void LightEffects_getInitialPomodoroSetting(
    LightEffects_PomodoroRingPhaseCfg_t* out_sEffect,
    uint8_t* const inout_u8ArraySize,
    LightEffect_Effect_e in_eEffectType) {
  {
    // Input Checks
    ASSERT_MSG(!(out_sEffect == NULL), "out_sEffect is NULL");
    ASSERT_MSG(!(inout_u8ArraySize == NULL), "inout_u8ArraySize is NULL");
    ASSERT_MSG(!(in_eEffectType >= E_EFFECT_LAST), "in_eEffectType is invalid");
  }

  switch (in_eEffectType) {
    case E_EFFECT_25_5: {
      uint8_t u8idx = 0;
      // Worktime
      out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_WORK_TIME;
      out_sEffect[u8idx].eRingType = E_INNER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 25;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
      out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME;
      out_sEffect[u8idx].eRingType = E_INNER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 5;
      out_sEffect[u8idx].u8MinuteOffset = 25;
      u8idx++;
      ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
      // Breaktime
      out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME_BRIGHT;
      out_sEffect[u8idx].eRingType = E_INNER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 5;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
      out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_FLASHLIGHT;
      out_sEffect[u8idx].eRingType = E_OUTER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 59;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
      *inout_u8ArraySize = u8idx;
    } break;

    case E_EFFECT_51_17: {
      uint8_t u8idx = 0;
      // Worktime
      out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_WORK_TIME;
      out_sEffect[u8idx].eRingType = E_INNER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 51;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
      out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME;
      out_sEffect[u8idx].eRingType = E_OUTER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 17;
      out_sEffect[u8idx].u8MinuteOffset = 51;
      u8idx++;
      ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
      // Breaktime
      out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME_BRIGHT;
      out_sEffect[u8idx].eRingType = E_INNER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 17;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
      out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_FLASHLIGHT;
      out_sEffect[u8idx].eRingType = E_OUTER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 59;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
      *inout_u8ArraySize = u8idx;
    } break;

    case E_EFFECT_90_15: {
      uint8_t u8idx = 0;
      // Worktime
      out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_WORK_TIME;
      out_sEffect[u8idx].eRingType = E_INNER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 59;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
      out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_WORK_TIME;
      out_sEffect[u8idx].eRingType = E_OUTER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 30;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
      out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME;
      out_sEffect[u8idx].eRingType = E_OUTER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 15;
      out_sEffect[u8idx].u8MinuteOffset = 30;
      u8idx++;
      ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
      // Breaktime
      out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME_BRIGHT;
      out_sEffect[u8idx].eRingType = E_INNER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 15;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
      out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_FLASHLIGHT;
      out_sEffect[u8idx].eRingType = E_OUTER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 59;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
      *inout_u8ArraySize = u8idx;
    } break;

    default:
      ASSERT_MSG(FALSE, "Unknown Effect");
      break;
  }
}

void test_getInitialPomodoroSetting_receivesSettings(void) {
  LightEffects_PomodoroRingPhaseCfg_t sEffect[MAX_SETTINGS];
  uint8_t u8ArraySize = 0;
  LightEffect_Effect_e eEffectType = E_EFFECT_25_5;
  LightEffects_getInitialPomodoroSetting(sEffect, &u8ArraySize, eEffectType);
  TEST_ASSERT_EQUAL_UINT8(4, u8ArraySize);
  TEST_ASSERT_EQUAL_UINT8(E_PHASE_WORK_TIME, sEffect[0].ePhase);
  TEST_ASSERT_EQUAL_UINT8(E_ANIMATION_WORK_TIME, sEffect[0].eAnimationType);
  TEST_ASSERT_EQUAL_UINT8(E_INNER_RING, sEffect[0].eRingType);
  TEST_ASSERT_EQUAL_UINT8(25, sEffect[0].u8DuratationInMinutes);
  TEST_ASSERT_EQUAL_UINT8(0, sEffect[0].u8MinuteOffset);
  TEST_ASSERT_EQUAL_UINT8(E_PHASE_WORK_TIME, sEffect[1].ePhase);
  TEST_ASSERT_EQUAL_UINT8(E_ANIMATION_BREAK_TIME, sEffect[1].eAnimationType);
  TEST_ASSERT_EQUAL_UINT8(E_INNER_RING, sEffect[1].eRingType);
  TEST_ASSERT_EQUAL_UINT8(5, sEffect[1].u8DuratationInMinutes);
  TEST_ASSERT_EQUAL_UINT8(25, sEffect[1].u8MinuteOffset);
  TEST_ASSERT_EQUAL_UINT8(E_PHASE_BREAK_TIME, sEffect[2].ePhase);
  TEST_ASSERT_EQUAL_UINT8(E_ANIMATION_BREAK_TIME_BRIGHT,
                          sEffect[2].eAnimationType);
  TEST_ASSERT_EQUAL_UINT8(E_INNER_RING, sEffect[2].eRingType);
  TEST_ASSERT_EQUAL_UINT8(5, sEffect[2].u8DuratationInMinutes);
  TEST_ASSERT_EQUAL_UINT8(0, sEffect[2].u8MinuteOffset);
  TEST_ASSERT_EQUAL_UINT8(E_PHASE_BREAK_TIME, sEffect[3].ePhase);
  TEST_ASSERT_EQUAL_UINT8(E_ANIMATION_FLASHLIGHT, sEffect[3].eAnimationType);
  TEST_ASSERT_EQUAL_UINT8(E_OUTER_RING, sEffect[3].eRingType);
  TEST_ASSERT_EQUAL_UINT8(59, sEffect[3].u8DuratationInMinutes);
  TEST_ASSERT_EQUAL_UINT8(0, sEffect[3].u8MinuteOffset);
}

// Get the original pattern (getInitialPomodoroSetting) -> this happens in the
// Init State

// Copy the entries into the minute array -> This is the structure on which is
// worked on

// Transform the Minute array into the LED Phase array (Compressed)

// Iterate over this array and set the RgbLeds to their respective colors
// (According to the phases)

void setAnimationInRingMinuteArray(uint8_t* out_au8RingArray,
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

void test_setAnimationInRingMinuteArray(void) {
  uint8_t au8RingArray[MINUTES_IN_HOUR] = {E_ANIMATION_OFF};

  uint8_t u8Duration = 20;
  uint8_t u8Offset = 0;
  LightEffects_Animation_e eAnimation = E_ANIMATION_WORK_TIME;
  setAnimationInRingMinuteArray(au8RingArray, MINUTES_IN_HOUR, u8Duration,
                                u8Offset, eAnimation);

  u8Duration = 10;
  u8Offset = 20;
  eAnimation = E_ANIMATION_BREAK_TIME;
  setAnimationInRingMinuteArray(au8RingArray, MINUTES_IN_HOUR, u8Duration,
                                u8Offset, eAnimation);
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
      setAnimationInRingMinuteArray(
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

void test_initSequence(void) {
  // Get 51_17 Effect Array
  LightEffects_PomodoroRingPhaseCfg_t asEffects[MAX_SETTINGS];
  uint8_t u8EffectArraySize = MAX_SETTINGS;
  LightEffects_getInitialPomodoroSetting(asEffects, &u8EffectArraySize,
                                         E_EFFECT_51_17);

  // Parse only the Effect Array Entries, which correspond to the current phase
  uint8_t au8InnerRingCompressedArray[TOTAL_LEDS_INNER_RING] = {0};
  uint8_t au8OuterRingCompressedArray[TOTAL_LEDS_OUTER_RING] = {0};
  LightEffects_PomodoroPhase_e ePhase = E_PHASE_WORK_TIME;

  LightEffects_getCompressedArraysForCurrentPhase(
      asEffects, u8EffectArraySize, ePhase, au8InnerRingCompressedArray,
      au8OuterRingCompressedArray);

  // Print the Compressed Array
  helper_printArray(au8InnerRingCompressedArray, TOTAL_LEDS_INNER_RING);
  helper_printArray(au8OuterRingCompressedArray, TOTAL_LEDS_OUTER_RING);
}

void AreThereActiveMinutesLeft(
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

void updateWorktimeCfgForCurrentMinute(
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
      AreThereActiveMinutesLeft(&inout_asEffects[i], &bActiveMinutesLeft);
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

void test_updateSequence(void) {
  // Get the initial sequence -> 51_17
  LightEffects_PomodoroRingPhaseCfg_t asEffects[MAX_SETTINGS];
  uint8_t u8EffectArraySize = MAX_SETTINGS;
  LightEffects_getInitialPomodoroSetting(asEffects, &u8EffectArraySize,
                                         E_EFFECT_51_17);

  // update the current Minute 5 times
  for (uint8_t i = 0; i < 5; i++) {
    updateWorktimeCfgForCurrentMinute(asEffects, u8EffectArraySize,
                                      E_PHASE_WORK_TIME);
  }

  // Print the updated sequence
  for (uint8_t i = 0; i < u8EffectArraySize; i++) {
    printf("Phase: %d, Animation: %d, Ring: %d, Duration: %d, Offset: %d\n",
           asEffects[i].ePhase, asEffects[i].eAnimationType,
           asEffects[i].eRingType, asEffects[i].u8DuratationInMinutes,
           asEffects[i].u8MinuteOffset);
  }

  // Print the compressed array
  // Parse only the Effect Array Entries, which correspond to the current phase
  uint8_t au8InnerRingCompressedArray[TOTAL_LEDS_INNER_RING] = {0};
  uint8_t au8OuterRingCompressedArray[TOTAL_LEDS_OUTER_RING] = {0};
  LightEffects_PomodoroPhase_e ePhase = E_PHASE_WORK_TIME;

  LightEffects_getCompressedArraysForCurrentPhase(
      asEffects, u8EffectArraySize, ePhase, au8InnerRingCompressedArray,
      au8OuterRingCompressedArray);

  // Print the Compressed Array
  helper_printArray(au8InnerRingCompressedArray, TOTAL_LEDS_INNER_RING);
  helper_printArray(au8OuterRingCompressedArray, TOTAL_LEDS_OUTER_RING);
}

void isPhaseOver(const LightEffects_PomodoroRingPhaseCfg_t* const in_saEffect,
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

void test_transitionFromWorktimeToBreaktime(void) {
  /**
   * Worktime Init
   */
  LightEffects_PomodoroPhase_e ePhase = E_PHASE_WORK_TIME;
  // Get initial config for the 51_17
  LightEffects_PomodoroRingPhaseCfg_t asEffects[MAX_SETTINGS];
  uint8_t u8EffectArraySize = MAX_SETTINGS;
  LightEffects_getInitialPomodoroSetting(asEffects, &u8EffectArraySize,
                                         E_EFFECT_51_17);

  // Print the updated sequence
  printf("Initial Sequence:\n");
  for (uint8_t i = 0; i < u8EffectArraySize; i++) {
    printf("Phase: %d, Animation: %d, Ring: %d, Duration: %d, Offset: %d\n",
           asEffects[i].ePhase, asEffects[i].eAnimationType,
           asEffects[i].eRingType, asEffects[i].u8DuratationInMinutes,
           asEffects[i].u8MinuteOffset);
  }
  printf("\n");

  /**
   * Worktime
   */

  // Process 51 Minutes (update 51 times) - In Worktime Phase
  for (uint8_t i = 0; i < 51; i++) {
    updateWorktimeCfgForCurrentMinute(asEffects, u8EffectArraySize, ePhase);

    /*
    (Usually the Cfg would be compressed to the LED Array here) and rendered
    accordingly:

    uint8_t au8InnerRingCompressedArray[TOTAL_LEDS_INNER_RING] = {0};
    uint8_t au8OuterRingCompressedArray[TOTAL_LEDS_OUTER_RING] = {0};

    LightEffects_getCompressedArraysForCurrentPhase(
        asEffects, u8EffectArraySize, ePhase, au8InnerRingCompressedArray,
        au8OuterRingCompressedArray);

    // Send of to rendering with the LEDs
    */

    BOOL bWorktimeOver;
    isPhaseOver(asEffects, u8EffectArraySize, &bWorktimeOver, ePhase,
                E_ANIMATION_WORK_TIME);
    if (bWorktimeOver == TRUE) {
      ePhase = E_PHASE_BREAK_TIME;
    }
  }

  printf("Updated Sequence - Worktime:\n");
  for (uint8_t i = 0; i < u8EffectArraySize; i++) {
    printf("Phase: %d, Animation: %d, Ring: %d, Duration: %d, Offset: %d\n",
           asEffects[i].ePhase, asEffects[i].eAnimationType,
           asEffects[i].eRingType, asEffects[i].u8DuratationInMinutes,
           asEffects[i].u8MinuteOffset);
  }
  printf("\n");

  TEST_ASSERT_EQUAL_UINT8(E_PHASE_BREAK_TIME, ePhase);

  // Process 17 Minutes (update 17 times) - In Breaktime Phase
  for (uint8_t i = 0; i < 17; i++) {
    updateWorktimeCfgForCurrentMinute(asEffects, u8EffectArraySize, ePhase);
  }

  // Print the updated sequence
  printf("Updated Sequence - Breaktime:\n");
  for (uint8_t i = 0; i < u8EffectArraySize; i++) {
    printf("Phase: %d, Animation: %d, Ring: %d, Duration: %d, Offset: %d\n",
           asEffects[i].ePhase, asEffects[i].eAnimationType,
           asEffects[i].eRingType, asEffects[i].u8DuratationInMinutes,
           asEffects[i].u8MinuteOffset);
  }
  printf("\n");

  // Check if the Breaktime is over
  BOOL bBreaktimeOver;
  isPhaseOver(asEffects, u8EffectArraySize, &bBreaktimeOver, ePhase,
              E_ANIMATION_BREAK_TIME_BRIGHT);
  TEST_ASSERT_EQUAL_UINT8(TRUE, bBreaktimeOver);
}