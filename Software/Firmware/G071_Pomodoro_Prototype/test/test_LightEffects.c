#include "LightEffects.h"
#include "RgbLed_Config.h"
#include "mock_Delay.h"
#include "mock_RgbLed.h"
#include "unity.h"

extern void LightEffects_initMinuteToLedConfigArray(
    uint8_t in_u8CurrentMinute, uint8_t in_u8WorktimeIntervalMin,
    uint8_t in_u8BreaktimeIntervalMin, uint8_t *inout_au8ColorArray);

extern void LightEffects_removeColorsFromMinuteArray(
    uint8_t *inout_au8MinuteToColorArray, uint8_t in_u8CurrentMinute);

extern void LightEffects_scaleArray(uint8_t *in_au8SourceArray,
                                    uint8_t in_u8SourceArraySize,
                                    uint8_t *inout_au8TargetArray,
                                    uint8_t in_u8TargetArraySize);

extern void LightEffects_updateMinuteToLedArray(
    uint8_t in_u8CurrentMinute, uint8_t *inout_au8MinuteToLedConfigArray);

extern uint8_t au8TestPublishedLedArray[TOTAL_LEDS];
extern uint8_t au8MinuteToLedConfigArray[TOTAL_MINUTES];
extern uint8_t u8CurrentMinute;

void setUp(void) {}

void tearDown(void) {}

/**
 * Helper functions
 */

void helper_printArray(uint8_t *in_au8Array, uint8_t in_u8ArraySize) {
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

void test_LightEffects_initMinuteToLedConfigArray_should_InitTwoRingsProperlyVariationOne(
    void) {
  /**
   * t_start = 20min
   * T_worktime = 1h15min
   * T_Breaktime = 30min
   *
   * -> t_worktime = [20...59][0...19][80...94]
   * -> t_breaktime = [95...119][60...64]
   */

  uint8_t u8TestCurrentMinute = 20;
  uint8_t u8TestWorktimeIntervalMin = 75;
  uint8_t u8TestBreaktimeIntervalMin = 30;

  uint8_t au8TestMinuteToColorArray[TOTAL_MINUTES] = {0};

  LightEffects_initMinuteToLedConfigArray(
      u8TestCurrentMinute, u8TestWorktimeIntervalMin,
      u8TestBreaktimeIntervalMin, au8TestMinuteToColorArray);

  // Count the number of occurences of each color in the array
  // These need to match the intial values
  uint8_t u8RedLowCount = 0;
  uint8_t u8GreenLowCount = 0;
  uint8_t u8LedOffCount = 0;

  for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++) {
    if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_WORK_TIME) {
      u8RedLowCount++;
    }
    if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_BREAK_TIME) {
      u8GreenLowCount++;
    }
  }

  TEST_ASSERT_EQUAL(u8TestWorktimeIntervalMin, u8RedLowCount);
  TEST_ASSERT_EQUAL(u8TestBreaktimeIntervalMin, u8GreenLowCount);

  // Check the first Ring - All entries need to be set to RED_LOW
  for (uint8_t u8Index = 0; u8Index < MINUTES_IN_HOUR; u8Index++) {
    TEST_ASSERT_EQUAL(LIGHTEFFECTS_WORK_TIME,
                      au8TestMinuteToColorArray[u8Index]);
  }

  for (uint8_t u8Index = MINUTES_IN_HOUR; u8Index < TOTAL_MINUTES; u8Index++) {
    // Green Low
    if (u8Index < 65) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_BREAK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }
    // LED Off
    if ((u8Index >= 65) && (u8Index < 80)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF,
                        au8TestMinuteToColorArray[u8Index]);
    }

    // Red Low
    if ((u8Index >= 80) && (u8Index < 95)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_WORK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }

    // Green Low
    if ((u8Index >= 95) && (u8Index < 120)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_BREAK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }
  }
}

void test_LightEffects_initMinuteToLedConfigArray_should_InitTwoRingsProperlyVariationTwo(
    void) {
  /**
   * t_start = 50min
   * T_worktime = 50min
   * T_Breaktime = 50min
   *
   * -> t_worktime = [50...40] (Array 1)
   * -> t_breaktime = [40...50](Array 1) [60...40] (Array 2)
   */

  uint8_t u8TestCurrentMinute = 50;
  uint8_t u8TestWorktimeIntervalMin = 50;
  uint8_t u8TestBreaktimeIntervalMin = 50;

  uint8_t au8TestMinuteToColorArray[TOTAL_MINUTES] = {0};

  LightEffects_initMinuteToLedConfigArray(
      u8TestCurrentMinute, u8TestWorktimeIntervalMin,
      u8TestBreaktimeIntervalMin, au8TestMinuteToColorArray);

  // Count the number of occurences of each color in the array
  // These need to match the intial values
  uint8_t u8RedLowCount = 0;
  uint8_t u8GreenLowCount = 0;

  for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++) {
    if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_WORK_TIME) {
      u8RedLowCount++;
    }
    if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_BREAK_TIME) {
      u8GreenLowCount++;
    }
  }

  TEST_ASSERT_EQUAL(u8TestWorktimeIntervalMin, u8RedLowCount);
  TEST_ASSERT_EQUAL(u8TestBreaktimeIntervalMin, u8GreenLowCount);

  // Check the positions of the entries
  for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++) {
    if (u8Index < 40) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_WORK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }
    if ((u8Index >= 40) && (u8Index < 50)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_BREAK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }
    if ((u8Index >= 50) && (u8Index < 60)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_WORK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }
    if ((u8Index >= 60) && (u8Index <= 90)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_BREAK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }
    if ((u8Index > 90) && (u8Index <= 110)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF,
                        au8TestMinuteToColorArray[u8Index]);
    }
    if ((u8Index > 110) && (u8Index < 120)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_BREAK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }
  }
}

void test_LightEffects_initMinuteToLedConfigArray_should_InitTwoRingsProperlyVariationThree(
    void) {
  /**
   * t_start = 20min
   * T_worktime = 50min
   * T_Breaktime = 10min
   *
   * -> t_worktime = [20...60] [0...10] (Array 1)
   * -> t_breaktime = [10...20] (Array 1)
   */

  uint8_t u8TestCurrentMinute = 20;
  uint8_t u8TestWorktimeIntervalMin = 50;
  uint8_t u8TestBreaktimeIntervalMin = 10;

  uint8_t au8TestMinuteToColorArray[TOTAL_MINUTES] = {0};

  LightEffects_initMinuteToLedConfigArray(
      u8TestCurrentMinute, u8TestWorktimeIntervalMin,
      u8TestBreaktimeIntervalMin, au8TestMinuteToColorArray);

  // Count the number of occurences of each color in the array
  // These need to match the intial values
  uint8_t u8RedLowCount = 0;
  uint8_t u8GreenLowCount = 0;

  for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++) {
    if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_WORK_TIME) {
      u8RedLowCount++;
    }
    if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_BREAK_TIME) {
      u8GreenLowCount++;
    }
  }

  TEST_ASSERT_EQUAL(u8TestWorktimeIntervalMin, u8RedLowCount);
  TEST_ASSERT_EQUAL(u8TestBreaktimeIntervalMin, u8GreenLowCount);

  // Check the positions of the entries
  for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++) {
    if ((u8Index >= 0) && (u8Index < 10)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_WORK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }
    if ((u8Index >= 10) && (u8Index < 20)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_BREAK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }
    if ((u8Index >= 20) && (u8Index < 60)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_WORK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }
    if ((u8Index >= 60) && (u8Index < 120)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF,
                        au8TestMinuteToColorArray[u8Index]);
    }
  }
}

void test_LightEffects_initMinuteToLedConfigArray_should_InitTwoRingsProperlyVariationFour(
    void) {
  /**
   * t_start = 10min
   * T_worktime = 52min
   * T_Breaktime = 18min
   *
   * -> t_worktime = [10...60][60...2] (Array 1)
   * -> t_breaktime = [2...10] (Array 1) [10...18] (Array 2)
   */

  uint8_t u8TestCurrentMinute = 10;
  uint8_t u8TestWorktimeIntervalMin = 52;
  uint8_t u8TestBreaktimeIntervalMin = 18;

  uint8_t au8TestMinuteToColorArray[TOTAL_MINUTES] = {0};

  LightEffects_initMinuteToLedConfigArray(
      u8TestCurrentMinute, u8TestWorktimeIntervalMin,
      u8TestBreaktimeIntervalMin, au8TestMinuteToColorArray);

  // Count the number of occurences of each color in the array
  // These need to match the intial values
  uint8_t u8RedLowCount = 0;
  uint8_t u8GreenLowCount = 0;

  for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++) {
    if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_WORK_TIME) {
      u8RedLowCount++;
    }
    if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_BREAK_TIME) {
      u8GreenLowCount++;
    }
  }

  TEST_ASSERT_EQUAL(u8TestWorktimeIntervalMin, u8RedLowCount);
  TEST_ASSERT_EQUAL(u8TestBreaktimeIntervalMin, u8GreenLowCount);

  // Check the positions of the entries
  for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++) {
    if ((u8Index >= 0) && (u8Index < 2)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_WORK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }
    if ((u8Index >= 2) && (u8Index < 10)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_BREAK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }
    if ((u8Index >= 10) && (u8Index < 60)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_WORK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }
    if ((u8Index >= 71) && (u8Index < 81)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_BREAK_TIME,
                        au8TestMinuteToColorArray[u8Index]);
    }
    if ((u8Index >= 81) && (u8Index < 120)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF,
                        au8TestMinuteToColorArray[u8Index]);
    }
  }
}

void test_LightEffects_scaleArray_should_scaleMinuteToColorArray(void) {
  uint8_t u8TestCurrentMinute = 50;
  uint8_t u8TestWorktimeIntervalMin = 50;
  uint8_t u8TestBreaktimeIntervalMin = 50;

  uint8_t au8TestMinuteToColorArray[TOTAL_MINUTES] = {0};

  LightEffects_initMinuteToLedConfigArray(
      u8TestCurrentMinute, u8TestWorktimeIntervalMin,
      u8TestBreaktimeIntervalMin, au8TestMinuteToColorArray);

  uint8_t au8TestOuterRing[MINUTES_IN_HOUR] = {0};
  // Copy the first 60 entries of the minute to color array
  memcpy(au8TestOuterRing, au8TestMinuteToColorArray, MINUTES_IN_HOUR);

  uint8_t au8TestScaledOuterRing[TOTAL_LEDS_OUTER_RING] = {0};
  LightEffects_scaleArray(au8TestOuterRing, MINUTES_IN_HOUR,
                          au8TestScaledOuterRing, TOTAL_LEDS_OUTER_RING);

  // Check the positions of the entries
  for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS_OUTER_RING; u8Index++) {
    if ((u8Index >= 0) && (u8Index <= 15)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_WORK_TIME,
                        au8TestScaledOuterRing[u8Index]);
    }
    if ((u8Index > 15) && (u8Index < 20)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_BREAK_TIME,
                        au8TestScaledOuterRing[u8Index]);
    }
    if ((u8Index >= 20) && (u8Index < 24)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_WORK_TIME,
                        au8TestScaledOuterRing[u8Index]);
    }
  }

  uint8_t au8TestMiddleRing[MINUTES_IN_HOUR] = {0};
  // Copy the second 60 entries of the minute to color array
  memcpy(au8TestMiddleRing, &au8TestMinuteToColorArray[MINUTES_IN_HOUR],
         MINUTES_IN_HOUR);

  uint8_t au8TestScaledMiddleRing[TOTAL_LEDS_MIDDLE_RING] = {0};
  LightEffects_scaleArray(au8TestMiddleRing, MINUTES_IN_HOUR,
                          au8TestScaledMiddleRing, TOTAL_LEDS_MIDDLE_RING);

  // Check the positions of the entries
  for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS_MIDDLE_RING; u8Index++) {
    if ((u8Index >= 0) && (u8Index <= 8)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_BREAK_TIME,
                        au8TestScaledMiddleRing[u8Index]);
    }
    if ((u8Index > 8) && (u8Index < 14)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF, au8TestScaledMiddleRing[u8Index]);
    }
    if ((u8Index >= 14) && (u8Index < 16)) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_BREAK_TIME,
                        au8TestScaledMiddleRing[u8Index]);
    }
  }
}

void test_LightEffects_updateMinuteToLedArray_should_SwitchTheCurrentMinutesLedToOffOne(
    void) {
  // Create a MinuteToLedArray which uses both rings
  uint8_t u8TestCurrentMinute = 50;
  uint8_t u8TestWorktimeIntervalMin = 50;
  uint8_t u8TestBreaktimeIntervalMin = 50;
  uint8_t u8TestDailyPomodoroScore = 5;
  uint8_t au8TestMinuteToColorArray[TOTAL_MINUTES] = {0};
  uint8_t au8BeforeMinuteToLedArray[TOTAL_MINUTES] = {0};
  uint8_t au8AfterMinuteToLedArray[TOTAL_MINUTES] = {0};

  LightEffects_initMinuteToLedConfigArray(
      u8TestCurrentMinute, u8TestWorktimeIntervalMin,
      u8TestBreaktimeIntervalMin, au8TestMinuteToColorArray);

  memcpy(au8BeforeMinuteToLedArray, au8TestMinuteToColorArray, TOTAL_MINUTES);

  uint8_t u8TestCurrentMinuteUpdate = 0;
  LightEffects_updateMinuteToLedArray(u8TestCurrentMinuteUpdate,
                                      au8TestMinuteToColorArray);

  memcpy(au8AfterMinuteToLedArray, au8TestMinuteToColorArray, TOTAL_MINUTES);

  // Compare the 2 Arrays and see whether they are equal (because the must not
  // be)
  BOOL bArraysAreEqual = TRUE;
  for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++) {
    if (au8BeforeMinuteToLedArray[u8Index] !=
        au8AfterMinuteToLedArray[u8Index]) {
      bArraysAreEqual = FALSE;
    }
  }
  TEST_ASSERT_FALSE(bArraysAreEqual);
}

void test_LightEffects_updateMinuteToLedArray_should_SwitchTheCurrentMinutesLedToOffTwo(
    void) {
  /**
   * This test switches off 60 LEDs
   */

  // Create a MinuteToLedArray which uses both rings
  uint8_t u8TestCurrentMinute = 50;
  uint8_t u8TestWorktimeIntervalMin = 50;
  uint8_t u8TestBreaktimeIntervalMin = 50;
  uint8_t u8TestDailyPomodoroScore = 5;
  uint8_t au8TestMinuteToColorArray[TOTAL_MINUTES] = {0};

  LightEffects_initMinuteToLedConfigArray(
      u8TestCurrentMinute, u8TestWorktimeIntervalMin,
      u8TestBreaktimeIntervalMin, au8TestMinuteToColorArray);

  for (uint8_t u8Index = 0; u8Index < MINUTES_IN_HOUR; u8Index++) {
    LightEffects_updateMinuteToLedArray(u8Index, au8TestMinuteToColorArray);
  }

  // Check that the first 60 LEDs are off
  for (uint8_t u8Index = 0; u8Index < MINUTES_IN_HOUR; u8Index++) {
    TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF, au8TestMinuteToColorArray[u8Index]);
  }
}

void test_LightEffects_updateMinuteToLedArray_should_SwitchTheCurrentMinutesLedToOffThree(
    void) {
  /**
   * This test switches off 70 LEDs
   * (The sum of the red leds needs to 0)
   * (The sum of the breaktime leds needs to 30)
   */

  // Create a MinuteToLedArray which uses both rings
  uint8_t u8TestCurrentMinute = 50;
  uint8_t u8TestWorktimeIntervalMin = 50;
  uint8_t u8TestBreaktimeIntervalMin = 50;
  uint8_t u8TestDailyPomodoroScore = 5;
  uint8_t au8TestMinuteToColorArray[TOTAL_MINUTES] = {0};

  LightEffects_initMinuteToLedConfigArray(
      u8TestCurrentMinute, u8TestWorktimeIntervalMin,
      u8TestBreaktimeIntervalMin, au8TestMinuteToColorArray);

  // Run 70 times over the array
  for (uint8_t u8Index = 0; u8Index < MINUTES_IN_HOUR; u8Index++) {
    LightEffects_updateMinuteToLedArray(u8Index, au8TestMinuteToColorArray);
  }
  for (uint8_t u8Index = 0; u8Index < 10; u8Index++) {
    LightEffects_updateMinuteToLedArray(u8Index, au8TestMinuteToColorArray);
  }

  // Count the number of colors
  uint8_t u8RedLedCount = 0;
  uint8_t u8GreenLedCount = 0;

  for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++) {
    if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_WORK_TIME) {
      u8RedLedCount++;
    }
    if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_BREAK_TIME) {
      u8GreenLedCount++;
    }
  }

  TEST_ASSERT_EQUAL(0, u8RedLedCount);
  TEST_ASSERT_EQUAL(30, u8GreenLedCount);
}

void test_LightEffects_updateMinuteToLedArray_should_SwitchTheCurrentMinutesLedToOffFour(
    void) {
  /**
   * Test:
   * Are the right elements taken from the Array?
   * -> Remove 10 Elements from the first Ring (Minute 35 -> 45)
   *    -> Are these gone?
   * -> Remove 60 Elements (make sure that the first ring is cleared)
   *    -> Are these gone, any other writes? (this should not happen)
   * -> Remove 10 Elements from the second ring (Minute 45-55)
   */

  /**
   * Initial Conditions:
   * Ring 1 Minutes
   *  0-40 -> Red
   * 40-50 -> Green
   * 50-60 -> Red
   *
   * Ring 2 Minutes
   *  0-30 -> Green
   * 30-50 -> Off
   * 50-60 -> Green
   */

  uint8_t u8TestCurrentMinute = 50;
  uint8_t u8TestWorktimeIntervalMin = 50;
  uint8_t u8TestBreaktimeIntervalMin = 50;
  uint8_t u8TestDailyPomodoroScore = 5;
  uint8_t au8TestMinuteToColorArray[TOTAL_MINUTES] = {0};

  LightEffects_initMinuteToLedConfigArray(
      u8TestCurrentMinute, u8TestWorktimeIntervalMin,
      u8TestBreaktimeIntervalMin, au8TestMinuteToColorArray);

  /**
   * Take away 10 Elements from the first ring (Minute 35 -> 45)
   */
  for (uint8_t u8CurrentMinuteIndex = 35; u8CurrentMinuteIndex < 45;
       u8CurrentMinuteIndex++) {
    LightEffects_updateMinuteToLedArray(u8CurrentMinuteIndex,
                                        au8TestMinuteToColorArray);
  }
  // Check that the 10 LEDs are off
  for (uint8_t u8Index = 35; u8Index < 45; u8Index++) {
    TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF, au8TestMinuteToColorArray[u8Index]);
  }

  /**
   * Take away 60 Elements (make sure that the first ring is cleared)
   */
  for (uint8_t u8CurrentMinuteIndex = 0; u8CurrentMinuteIndex < 60;
       u8CurrentMinuteIndex++) {
    LightEffects_updateMinuteToLedArray(u8CurrentMinuteIndex,
                                        au8TestMinuteToColorArray);
  }
  // Check that the first 60 LEDs are off
  for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++) {
    if (u8Index < MINUTES_IN_HOUR) {
      TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF,
                        au8TestMinuteToColorArray[u8Index]);
    }
  }

  /**
   * Take away 10 Elements from the second ring (Minute 45-55)
   * 45 to 55
   * (Check index 105 - 115)
   */
  for (uint8_t u8CurrentMinuteIndex = 45; u8CurrentMinuteIndex < 55;
       u8CurrentMinuteIndex++) {
    LightEffects_updateMinuteToLedArray(u8CurrentMinuteIndex,
                                        au8TestMinuteToColorArray);
  }

  // Check that the 10 LEDs are off
  for (uint8_t u8Index = 105; u8Index < 115; u8Index++) {
    TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF, au8TestMinuteToColorArray[u8Index]);
  }
}