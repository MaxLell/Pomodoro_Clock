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
    /**
     * This function prints the index of the array next to the value line by line
     * Example:
     * 0 - 0
     * 1 - 2
     * 2 - 2
     * 3 - 2
     * ...
     */
    for (uint8_t i = 0;
         i < in_u8ArraySize;
         i++)
    {
        if (i < 10)
        {
            printf("%d ---> %d\n", i, in_au8Array[i]);
        }
        else if ((i < 100) && (i >= 10))
        {
            printf("%d --> %d\n", i, in_au8Array[i]);
        }
        else
        {
            printf("%d -> %d\n", i, in_au8Array[i]);
        }
    }
}

void test_LightEffects_initMinuteToLedConfigArray_should_InitTwoRingsProperlyVariationOne(void)
{
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
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    // Count the number of occurences of each color in the array
    // These need to match the intial values
    uint8_t u8RedLowCount = 0;
    uint8_t u8GreenLowCount = 0;
    uint8_t u8LedOffCount = 0;

    for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++)
    {
        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_RED_LOW)
        {
            u8RedLowCount++;
        }
        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_GREEN_LOW)
        {
            u8GreenLowCount++;
        }
    }

    TEST_ASSERT_EQUAL(u8TestWorktimeIntervalMin, u8RedLowCount);
    TEST_ASSERT_EQUAL(u8TestBreaktimeIntervalMin, u8GreenLowCount);

    // Check the first Ring - All entries need to be set to RED_LOW
    for (uint8_t u8Index = 0; u8Index < MINUTES_IN_HOUR; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_RED_LOW, au8TestMinuteToColorArray[u8Index]);
    }

    for (uint8_t u8Index = MINUTES_IN_HOUR; u8Index < TOTAL_MINUTES; u8Index++)
    {
        // Green Low
        if (u8Index < 65)
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_GREEN_LOW, au8TestMinuteToColorArray[u8Index]);
        }
        // LED Off
        if ((u8Index >= 65) && (u8Index < 80))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF, au8TestMinuteToColorArray[u8Index]);
        }

        // Red Low
        if ((u8Index >= 80) && (u8Index < 95))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_RED_LOW, au8TestMinuteToColorArray[u8Index]);
        }

        // Green Low
        if ((u8Index >= 95) && (u8Index < 120))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_GREEN_LOW, au8TestMinuteToColorArray[u8Index]);
        }
    }
}

void test_LightEffects_initMinuteToLedConfigArray_should_InitTwoRingsProperlyVariationTwo(void)
{
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
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    // Count the number of occurences of each color in the array
    // These need to match the intial values
    uint8_t u8RedLowCount = 0;
    uint8_t u8GreenLowCount = 0;

    for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++)
    {
        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_RED_LOW)
        {
            u8RedLowCount++;
        }
        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_GREEN_LOW)
        {
            u8GreenLowCount++;
        }
    }

    TEST_ASSERT_EQUAL(u8TestWorktimeIntervalMin, u8RedLowCount);
    TEST_ASSERT_EQUAL(u8TestBreaktimeIntervalMin, u8GreenLowCount);

    // Check the positions of the entries
    for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++)
    {
        if (u8Index < 40)
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_RED_LOW, au8TestMinuteToColorArray[u8Index]);
        }
        if ((u8Index >= 40) && (u8Index < 50))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_GREEN_LOW, au8TestMinuteToColorArray[u8Index]);
        }
        if ((u8Index >= 50) && (u8Index < 60))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_RED_LOW, au8TestMinuteToColorArray[u8Index]);
        }
        if ((u8Index >= 60) && (u8Index <= 90))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_GREEN_LOW, au8TestMinuteToColorArray[u8Index]);
        }
        if ((u8Index > 90) && (u8Index <= 110))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF, au8TestMinuteToColorArray[u8Index]);
        }
        if ((u8Index > 110) && (u8Index < 120))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_GREEN_LOW, au8TestMinuteToColorArray[u8Index]);
        }
    }
}

void test_LightEffects_initMinuteToLedConfigArray_should_InitTwoRingsProperlyVariationThree(void)
{
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
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    // Count the number of occurences of each color in the array
    // These need to match the intial values
    uint8_t u8RedLowCount = 0;
    uint8_t u8GreenLowCount = 0;

    for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++)
    {
        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_RED_LOW)
        {
            u8RedLowCount++;
        }
        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_GREEN_LOW)
        {
            u8GreenLowCount++;
        }
    }

    TEST_ASSERT_EQUAL(u8TestWorktimeIntervalMin, u8RedLowCount);
    TEST_ASSERT_EQUAL(u8TestBreaktimeIntervalMin, u8GreenLowCount);

    // Check the positions of the entries
    for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++)
    {
        if ((u8Index >= 0) && (u8Index < 10))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_RED_LOW, au8TestMinuteToColorArray[u8Index]);
        }
        if ((u8Index >= 10) && (u8Index < 20))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_GREEN_LOW, au8TestMinuteToColorArray[u8Index]);
        }
        if ((u8Index >= 20) && (u8Index < 60))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_RED_LOW, au8TestMinuteToColorArray[u8Index]);
        }
        if ((u8Index >= 60) && (u8Index < 120))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF, au8TestMinuteToColorArray[u8Index]);
        }
    }
}

void test_LightEffects_initMinuteToLedConfigArray_should_InitTwoRingsProperlyVariationFour(void)
{
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
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    // Count the number of occurences of each color in the array
    // These need to match the intial values
    uint8_t u8RedLowCount = 0;
    uint8_t u8GreenLowCount = 0;

    for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++)
    {
        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_RED_LOW)
        {
            u8RedLowCount++;
        }
        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_GREEN_LOW)
        {
            u8GreenLowCount++;
        }
    }

    TEST_ASSERT_EQUAL(u8TestWorktimeIntervalMin, u8RedLowCount);
    TEST_ASSERT_EQUAL(u8TestBreaktimeIntervalMin, u8GreenLowCount);

    // Check the positions of the entries
    for (uint8_t u8Index = 0; u8Index < TOTAL_MINUTES; u8Index++)
    {
        if ((u8Index >= 0) && (u8Index < 2))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_RED_LOW, au8TestMinuteToColorArray[u8Index]);
        }
        if ((u8Index >= 2) && (u8Index < 10))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_GREEN_LOW, au8TestMinuteToColorArray[u8Index]);
        }
        if ((u8Index >= 10) && (u8Index < 60))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_RED_LOW, au8TestMinuteToColorArray[u8Index]);
        }
        if ((u8Index >= 71) && (u8Index < 81))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_GREEN_LOW, au8TestMinuteToColorArray[u8Index]);
        }
        if ((u8Index >= 81) && (u8Index < 120))
        {
            TEST_ASSERT_EQUAL(LIGHTEFFECTS_LED_OFF, au8TestMinuteToColorArray[u8Index]);
        }
    }
}
