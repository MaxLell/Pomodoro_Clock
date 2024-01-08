#include "LightEffects.h"
#include "LightEffects_Pomodoro.h"
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

void test_getInitialPomodoroSetting_receivesSettings(void) {
  LightEffects_PomodoroRingPhaseCfg_t sEffect[MAX_SETTINGS];
  uint8_t u8ArraySize = 0;
  LightEffect_Effect_e eEffectType = E_EFFECT_25_5;
  LightEffects_getInitialPomodoroSetting(sEffect, &u8ArraySize, eEffectType);
  TEST_ASSERT_EQUAL_UINT8(4, u8ArraySize);
  TEST_ASSERT_EQUAL_UINT8(E_PHASE_WORK_TIME, sEffect[0].ePhase);
  TEST_ASSERT_EQUAL_UINT8(E_ANIMATION_WORK_TIME, sEffect[0].eAnimationType);
  TEST_ASSERT_EQUAL_UINT8(E_MIDDLE_RING, sEffect[0].eRingType);
  TEST_ASSERT_EQUAL_UINT8(25, sEffect[0].u8DuratationInMinutes);
  TEST_ASSERT_EQUAL_UINT8(0, sEffect[0].u8MinuteOffset);
  TEST_ASSERT_EQUAL_UINT8(E_PHASE_WORK_TIME, sEffect[1].ePhase);
  TEST_ASSERT_EQUAL_UINT8(E_ANIMATION_BREAK_TIME, sEffect[1].eAnimationType);
  TEST_ASSERT_EQUAL_UINT8(E_MIDDLE_RING, sEffect[1].eRingType);
  TEST_ASSERT_EQUAL_UINT8(5, sEffect[1].u8DuratationInMinutes);
  TEST_ASSERT_EQUAL_UINT8(25, sEffect[1].u8MinuteOffset);
  TEST_ASSERT_EQUAL_UINT8(E_PHASE_BREAK_TIME, sEffect[2].ePhase);
  TEST_ASSERT_EQUAL_UINT8(E_ANIMATION_BREAK_TIME_BRIGHT,
                          sEffect[2].eAnimationType);
  TEST_ASSERT_EQUAL_UINT8(E_MIDDLE_RING, sEffect[2].eRingType);
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

void test_setAnimationInRingMinuteArray(void) {
  uint8_t au8RingArray[MINUTES_IN_HOUR] = {E_ANIMATION_OFF};

  uint8_t u8Duration = 20;
  uint8_t u8Offset = 0;
  LightEffects_Animation_e eAnimation = E_ANIMATION_WORK_TIME;
  LightEffects_setAnimationInRingMinuteArray(au8RingArray, MINUTES_IN_HOUR,
                                             u8Duration, u8Offset, eAnimation);

  u8Duration = 10;
  u8Offset = 20;
  eAnimation = E_ANIMATION_BREAK_TIME;
  LightEffects_setAnimationInRingMinuteArray(au8RingArray, MINUTES_IN_HOUR,
                                             u8Duration, u8Offset, eAnimation);
}

void test_initSequence(void) {
  // Get 51_17 Effect Array
  LightEffects_PomodoroRingPhaseCfg_t asEffects[MAX_SETTINGS];
  uint8_t u8EffectArraySize = MAX_SETTINGS;
  LightEffects_getInitialPomodoroSetting(asEffects, &u8EffectArraySize,
                                         E_EFFECT_51_17);

  // Parse only the Effect Array Entries, which correspond to the current phase
  uint8_t au8InnerRingCompressedArray[NOF_LEDS_INNER_RING] = {0};
  uint8_t au8OuterRingCompressedArray[NOF_LEDS_OUTER_RING] = {0};
  LightEffects_PomodoroPhase_e ePhase = E_PHASE_WORK_TIME;

  LightEffects_getCompressedArraysForCurrentPhase(
      asEffects, u8EffectArraySize, ePhase, au8InnerRingCompressedArray,
      au8OuterRingCompressedArray);

  // Print the Compressed Array
  helper_printArray(au8InnerRingCompressedArray, NOF_LEDS_INNER_RING);
  helper_printArray(au8OuterRingCompressedArray, NOF_LEDS_OUTER_RING);
}

void test_updateSequence(void) {
  // Get the initial sequence -> 51_17
  LightEffects_PomodoroRingPhaseCfg_t asEffects[MAX_SETTINGS];
  uint8_t u8EffectArraySize = MAX_SETTINGS;
  LightEffects_getInitialPomodoroSetting(asEffects, &u8EffectArraySize,
                                         E_EFFECT_51_17);

  // update the current Minute 5 times
  for (uint8_t i = 0; i < 5; i++) {
    LightEffects_updateWorktimeCfgForCurrentMinute(asEffects, u8EffectArraySize,
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
  uint8_t au8InnerRingCompressedArray[NOF_LEDS_INNER_RING] = {0};
  uint8_t au8OuterRingCompressedArray[NOF_LEDS_OUTER_RING] = {0};
  LightEffects_PomodoroPhase_e ePhase = E_PHASE_WORK_TIME;

  LightEffects_getCompressedArraysForCurrentPhase(
      asEffects, u8EffectArraySize, ePhase, au8InnerRingCompressedArray,
      au8OuterRingCompressedArray);

  // Print the Compressed Array
  helper_printArray(au8InnerRingCompressedArray, NOF_LEDS_INNER_RING);
  helper_printArray(au8OuterRingCompressedArray, NOF_LEDS_OUTER_RING);
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
    LightEffects_updateWorktimeCfgForCurrentMinute(asEffects, u8EffectArraySize,
                                                   ePhase);

    /*
    (Usually the Cfg would be compressed to the LED Array here) and rendered
    accordingly:

    uint8_t au8InnerRingCompressedArray[NOF_LEDS_INNER_RING] = {0};
    uint8_t au8OuterRingCompressedArray[NOF_LEDS_OUTER_RING] = {0};

    LightEffects_getCompressedArraysForCurrentPhase(
        asEffects, u8EffectArraySize, ePhase, au8InnerRingCompressedArray,
        au8OuterRingCompressedArray);

    // Send of to rendering with the LEDs
    */

    BOOL bWorktimeOver;
    LightEffects_isPhaseOver(asEffects, u8EffectArraySize, &bWorktimeOver,
                             ePhase, E_ANIMATION_WORK_TIME);
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
    LightEffects_updateWorktimeCfgForCurrentMinute(asEffects, u8EffectArraySize,
                                                   ePhase);
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
  LightEffects_isPhaseOver(asEffects, u8EffectArraySize, &bBreaktimeOver,
                           ePhase, E_ANIMATION_BREAK_TIME_BRIGHT);
  TEST_ASSERT_EQUAL_UINT8(TRUE, bBreaktimeOver);
}