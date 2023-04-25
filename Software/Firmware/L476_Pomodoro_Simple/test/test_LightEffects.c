#include "unity.h"

#include "LightEffects.h"
#include "mock_MessageBroker.h"
#include "LightEffects_Interface.h"
#include "Config.h"

void setUp(void)
{
}

void tearDown(void)
{
}

extern void LightEffects_initMinuteToLedConfigArray(uint8_t in_u8CurrentMinute,
                                                    uint8_t in_u8WorktimeIntervalMin,
                                                    uint8_t in_u8BreaktimeIntervalMin,
                                                    uint8_t *inout_au8ColorArray);

extern void LightEffects_removeColorsFromMinuteArray(uint8_t *inout_au8MinuteToColorArray,
                                                     uint8_t in_u8CurrentMinute);

extern void LightEffects_transformMinuteToLedConfigArrayToLedConfigArray(uint8_t *in_au8MinuteToColorArray,
                                                                         uint8_t *inout_au8LedToColorArray);

extern void LightEffects_setLedsToColor(uint8_t *in_au8LedToColorArray);

/**
 * Helper functions
 */

void helper_printArray(uint8_t *in_au8Array, uint8_t in_u8ArraySize)
{
    for (uint8_t i = 0; i < in_u8ArraySize; i++)
    {
        if (i < 10)
        {
            printf("%d  ", i);
        }
        else
        {
            printf("%d ", i);
        }
    }
    printf("\n");
    for (uint8_t i = 0; i < in_u8ArraySize; i++)
    {
        printf("%d  ", in_au8Array[i]);
    }
    printf("\n");
}

void test_LightEffects_LightEffects_initMinuteToLedConfigArray_should_SetInitialWorkBreakAndOffConditions(void)
{
    // - Input: currentMinute = 17, worktimeIntervalMin = 50, breaktimeIntervalMin = 7
    // - Expected Output: [0...7] = W, [8...14] = B, [15...17] = 0, [18...59] = W
    uint8_t u8TestCurrentMinute = 17;
    uint8_t u8TestWorktimeIntervalMin = 50;
    uint8_t u8TestBreaktimeIntervalMin = 7;
    uint8_t au8TestMinuteToColorArray[MINUTES_IN_HOUR] = {0};

    LightEffects_initMinuteToLedConfigArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    // Check the first 8 Minutes (Work Time)
    for (uint8_t u8Index = 0; u8Index < 7; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_RED_LOW, au8TestMinuteToColorArray[u8Index]);
    }

    // Check the next 7 Minutes (Break Time)
    for (uint8_t u8Index = 7; u8Index < 14; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_GREEN_LOW, au8TestMinuteToColorArray[u8Index]);
    }

    // Check the next 3 Minutes (Off Time)
    for (uint8_t u8Index = 14; u8Index < 17; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF, au8TestMinuteToColorArray[u8Index]);
    }

    // Check the last 42 Minutes (Work Time)
    for (uint8_t u8Index = 17; u8Index < MINUTES_IN_HOUR; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_RED_LOW, au8TestMinuteToColorArray[u8Index]);
    }
}

void test_LightEffects_removeColorsFromMinuteArray_should_RemoveColorsAtSpecificIndexFromArray(void)
{
    uint8_t u8TestCurrentMinute = 0;
    uint8_t u8TestWorktimeIntervalMin = 30;
    uint8_t u8TestBreaktimeIntervalMin = 20;
    uint8_t au8TestMinuteToColorArray[MINUTES_IN_HOUR] = {0};
    uint8_t au8TestLedToColorArray[TOTAL_LEDS] = {0};

    LightEffects_initMinuteToLedConfigArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    LightEffects_removeColorsFromMinuteArray(au8TestMinuteToColorArray, u8TestCurrentMinute);
    TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF, au8TestMinuteToColorArray[u8TestCurrentMinute]);

    // try another minute
    u8TestCurrentMinute = 12;
    LightEffects_removeColorsFromMinuteArray(au8TestMinuteToColorArray, u8TestCurrentMinute);
    TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF, au8TestMinuteToColorArray[u8TestCurrentMinute]);
}

void test_LightEffects_LightEffects_transformMinuteToLedConfigArrayToLedConfigArray_should_Transform()
{
    uint8_t u8TestCurrentMinute = 0;
    uint8_t u8TestWorktimeIntervalMin = 30;
    uint8_t u8TestBreaktimeIntervalMin = 20;
    uint8_t au8TestMinuteToColorArray[MINUTES_IN_HOUR] = {0};
    uint8_t au8TestLedToColorArray[TOTAL_LEDS] = {0};

    LightEffects_initMinuteToLedConfigArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    LightEffects_transformMinuteToLedConfigArrayToLedConfigArray(au8TestMinuteToColorArray, au8TestLedToColorArray);

    float u8LedsPerMinute = (float)TOTAL_LEDS_OUTER_RING / (float)MINUTES_IN_HOUR;

    for (float i = 0; i < MINUTES_IN_HOUR; i++)
    {
        uint8_t index = (uint8_t)(i * u8LedsPerMinute);
        TEST_ASSERT_EQUAL(au8TestMinuteToColorArray[(uint8_t)i], au8TestLedToColorArray[index]);
    }
}
