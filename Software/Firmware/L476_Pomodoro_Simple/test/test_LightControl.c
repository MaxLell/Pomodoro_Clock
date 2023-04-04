#include "unity.h"
#include "Common.h"
#include "LightControl.h"
#include "mock_RgbLed.h"

uint8_t au8MinuteToColorArray[60] = {0};
void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * LightControl_fillMinuteToColorArray Tests
 *
 * 1. Happy Day Tests:
 * Test 1:
 * - Input: currentMinute = 0, worktimeIntervalMin = 0, breaktimeIntervalMin = 0
 * - Expected Output: [0...59] = 0
 *
 * Test 2:
 * - Input: currentMinute = 0, worktimeIntervalMin = 1, breaktimeIntervalMin = 0
 * - Expected Output: [0,1] = W, [2...59] = 0
 *
 * Test 3:
 * - Input: currentMinute = 0, worktimeIntervalMin = 1, breaktimeIntervalMin = 1
 * - Expected Output: [0,1] = W, [2,3] = B, [4...59] = 0
 *
 * Test 4:
 * - Input: currentMinute = 17, worktimeIntervalMin = 50, breaktimeIntervalMin = 7
 * - Expected Output: [0...7] = W, [8...14] = B, [15...17] = 0, [18...59] = W
 *
 * Test 5:
 * - Input: currentMinute = 60, worktimeIntervalMin = 0, breaktimeIntervalMin = 0
 * - Expected Output: [0...59] = 0
 *
 * 2. Bad Day Tests:
 * Test 6:
 * - Input: currentMinute = 61, worktimeIntervalMin = 0, breaktimeIntervalMin = 0
 * - Expected Output: [0...59] = 0; returns a Status Error Code
 *
 * Test 7:
 * - Input: currentMinute = 0, worktimeIntervalMin = 61, breaktimeIntervalMin = 0
 * - Expected Output: [0...59] = 0; returns a Status Error Code
 *
 * Test 8:
 * - Input: currentMinute = 0, worktimeIntervalMin = 10, breaktimeIntervalMin = 60
 * - Expected Output: [0...59] = 0; returns a Status Error Code
 *
 * Test 9:
 * - Input: currentMinute = 0, worktimeIntervalMin = 67, breaktimeIntervalMin = 10
 * - Expected Output: [0...59] = 0; returns a Status Error Code
 *
 * 3. Random Day Tests:
 * Test 10:
 * - Input: currentMinute = 20, worktimeIntervalMin = 10, breaktimeIntervalMin = 10
 * - Expected Output: [0...20] = 0, [21...30] = W, [31...40] = B, [41...59] = 0
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

void test_LightControl_fillMinuteToColorArray_Test1()
{
    // Test 1:
    // - Input: currentMinute = 0, worktimeIntervalMin = 0, breaktimeIntervalMin = 0
    // - Expected Output: [0...59] = 0
    uint8_t u8CurrentMinute = 0;
    uint8_t u8WorktimeIntervalMin = 0;
    uint8_t u8BreaktimeIntervalMin = 0;
    uint8_t au8MinuteToColorArray[60] = {0};

    LightControl_fillMinuteToColorArray(
        u8CurrentMinute,
        u8WorktimeIntervalMin,
        u8BreaktimeIntervalMin,
        au8MinuteToColorArray);

    // Check the first 60 Minutes (Off Time)
    for (uint8_t u8Index = 0; u8Index < MINUTES_IN_HOUR; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8MinuteToColorArray[u8Index]);
    }
}
void test_LightControl_fillMinuteToColorArray_Test2()
{
    // Test 2:
    // - Input: currentMinute = 0, worktimeIntervalMin = 1, breaktimeIntervalMin = 0
    // - Expected Output: [0,1] = W, [2...59] = 0
    uint8_t u8CurrentMinute = 0;
    uint8_t u8WorktimeIntervalMin = 1;
    uint8_t u8BreaktimeIntervalMin = 0;
    uint8_t au8MinuteToColorArray[60] = {0};

    LightControl_fillMinuteToColorArray(
        u8CurrentMinute,
        u8WorktimeIntervalMin,
        u8BreaktimeIntervalMin,
        au8MinuteToColorArray);

    // Check the first 2 Minutes (Work Time)
    for (uint8_t u8Index = 0; u8Index < 1; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_RED, au8MinuteToColorArray[u8Index]);
    }

    // Check the next 58 Minutes (Off Time)
    for (uint8_t u8Index = 2; u8Index < MINUTES_IN_HOUR; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8MinuteToColorArray[u8Index]);
    }
}

void test_LightControl_fillMinuteToColorArray_Test3()
{
    // Test 3:
    // - Input: currentMinute = 0, worktimeIntervalMin = 1, breaktimeIntervalMin = 1
    // - Expected Output: [0,1] = W, [2,3] = B, [4...59] = 0
    uint8_t u8CurrentMinute = 0;
    uint8_t u8WorktimeIntervalMin = 1;
    uint8_t u8BreaktimeIntervalMin = 1;
    uint8_t au8MinuteToColorArray[60] = {0};

    LightControl_fillMinuteToColorArray(
        u8CurrentMinute,
        u8WorktimeIntervalMin,
        u8BreaktimeIntervalMin,
        au8MinuteToColorArray);

    // Check the first 2 Minutes (Work Time)
    for (uint8_t u8Index = 0; u8Index < 1; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_RED, au8MinuteToColorArray[u8Index]);
    }

    // Check the next 2 Minutes (Break Time)
    for (uint8_t u8Index = 1; u8Index < 2; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_GREEN, au8MinuteToColorArray[u8Index]);
    }

    // Check the next 56 Minutes (Off Time)
    for (uint8_t u8Index = 2; u8Index < MINUTES_IN_HOUR; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8MinuteToColorArray[u8Index]);
    }
}

void test_LightControl_fillMinuteToColorArray_Test4()
{
    // Test 4:
    // - Input: currentMinute = 17, worktimeIntervalMin = 50, breaktimeIntervalMin = 7
    // - Expected Output: [0...7] = W, [8...14] = B, [15...17] = 0, [18...59] = W
    uint8_t u8CurrentMinute = 17;
    uint8_t u8WorktimeIntervalMin = 50;
    uint8_t u8BreaktimeIntervalMin = 7;
    uint8_t au8MinuteToColorArray[60] = {0};

    LightControl_fillMinuteToColorArray(
        u8CurrentMinute,
        u8WorktimeIntervalMin,
        u8BreaktimeIntervalMin,
        au8MinuteToColorArray);

    // Check the first 8 Minutes (Work Time)
    for (uint8_t u8Index = 0; u8Index < 7; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_RED, au8MinuteToColorArray[u8Index]);
    }

    // Check the next 7 Minutes (Break Time)
    for (uint8_t u8Index = 7; u8Index < 14; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_GREEN, au8MinuteToColorArray[u8Index]);
    }

    // Check the next 3 Minutes (Off Time)
    for (uint8_t u8Index = 14; u8Index < 17; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8MinuteToColorArray[u8Index]);
    }

    // Check the last 42 Minutes (Work Time)
    for (uint8_t u8Index = 17; u8Index < MINUTES_IN_HOUR; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_RED, au8MinuteToColorArray[u8Index]);
    }
}

void test_LightControl_fillMinuteToColorArray_Test5()
{
    // - Input: currentMinute = 59, worktimeIntervalMin = 10, breaktimeIntervalMin = 0
    // - Expected Output: [0...59] = 0
    uint8_t u8CurrentMinute = 59;
    uint8_t u8WorktimeIntervalMin = 10;
    uint8_t u8BreaktimeIntervalMin = 0;
    uint8_t au8MinuteToColorArray[60] = {0};

    LightControl_fillMinuteToColorArray(
        u8CurrentMinute,
        u8WorktimeIntervalMin,
        u8BreaktimeIntervalMin,
        au8MinuteToColorArray);

    // Check the first 10 Minutes (Work Time)
    for (uint8_t u8Index = 0; u8Index < 9; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_RED, au8MinuteToColorArray[u8Index]);
    }

    // Check the next 50 Minutes (Off Time)
    for (uint8_t u8Index = 9; u8Index < u8CurrentMinute; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8MinuteToColorArray[u8Index]);
    }
}
/*
 * Test 6:
 * - Input: currentMinute = 61, worktimeIntervalMin = 0, breaktimeIntervalMin = 0
 * - Expected Output: [0...59] = 0; returns a Status Error Code
 */
void test_LightControl_fillMinuteToColorArray_Test6()
{
    uint8_t u8CurrentMinute = 61;
    uint8_t u8WorktimeIntervalMin = 0;
    uint8_t u8BreaktimeIntervalMin = 0;
    uint8_t au8MinuteToColorArray[60] = {0};

    uint8_t u8Status = LightControl_fillMinuteToColorArray(
        u8CurrentMinute,
        u8WorktimeIntervalMin,
        u8BreaktimeIntervalMin,
        au8MinuteToColorArray);

    TEST_ASSERT_EQUAL(STATUS_INVALID_ARG, u8Status);
}

/*
 * Test 7:
 * - Input: currentMinute = 0, worktimeIntervalMin = 61, breaktimeIntervalMin = 0
 * - Expected Output: [0...59] = 0; returns a Status Invalid Argument
 */
void test_LightControl_fillMinuteToColorArray_Test7()
{
    uint8_t u8CurrentMinute = 0;
    uint8_t u8WorktimeIntervalMin = 61;
    uint8_t u8BreaktimeIntervalMin = 0;
    uint8_t au8MinuteToColorArray[60] = {0};

    uint8_t u8Status = LightControl_fillMinuteToColorArray(
        u8CurrentMinute,
        u8WorktimeIntervalMin,
        u8BreaktimeIntervalMin,
        au8MinuteToColorArray);

    TEST_ASSERT_EQUAL(STATUS_INVALID_ARG, u8Status);
}

/*
 * Test 8:
 * - Input: currentMinute = 0, worktimeIntervalMin = 10, breaktimeIntervalMin = 60
 * - Expected Output: [0...59] = 0; returns a Status Error Code
 */
void test_LightControl_fillMinuteToColorArray_Test8()
{
    uint8_t u8CurrentMinute = 0;
    uint8_t u8WorktimeIntervalMin = 10;
    uint8_t u8BreaktimeIntervalMin = 60;
    uint8_t au8MinuteToColorArray[60] = {0};

    uint8_t u8Status = LightControl_fillMinuteToColorArray(
        u8CurrentMinute,
        u8WorktimeIntervalMin,
        u8BreaktimeIntervalMin,
        au8MinuteToColorArray);

    TEST_ASSERT_EQUAL(STATUS_INVALID_ARG, u8Status);
}

/*
 * Test 9:
 * - Input: currentMinute = 0, worktimeIntervalMin = 67, breaktimeIntervalMin = 10
 * - Expected Output: [0...59] = 0; returns a Status Error Code
 */
void test_LightControl_fillMinuteToColorArray_Test9()
{
    uint8_t u8CurrentMinute = 0;
    uint8_t u8WorktimeIntervalMin = 67;
    uint8_t u8BreaktimeIntervalMin = 10;
    uint8_t au8MinuteToColorArray[60] = {0};

    uint8_t u8Status = LightControl_fillMinuteToColorArray(
        u8CurrentMinute,
        u8WorktimeIntervalMin,
        u8BreaktimeIntervalMin,
        au8MinuteToColorArray);

    TEST_ASSERT_EQUAL(STATUS_INVALID_ARG, u8Status);
}
/*
 * Test 10:
 * - Input: currentMinute = 20, worktimeIntervalMin = 10, breaktimeIntervalMin = 10
 * - Expected Output: [0...20] = 0, [21...30] = W, [31...40] = B, [41...59] = 0
 */
void test_LightControl_fillMinuteToColorArray_Test10()
{
    uint8_t u8CurrentMinute = 20;
    uint8_t u8WorktimeIntervalMin = 10;
    uint8_t u8BreaktimeIntervalMin = 10;
    uint8_t au8MinuteToColorArray[60] = {0};

    LightControl_fillMinuteToColorArray(
        u8CurrentMinute,
        u8WorktimeIntervalMin,
        u8BreaktimeIntervalMin,
        au8MinuteToColorArray);

    // Check the first 20 Minutes (Off Time)
    for (uint8_t u8Index = 0; u8Index < u8CurrentMinute; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8MinuteToColorArray[u8Index]);
    }

    // Check the next 10 Minutes (Work Time)
    for (uint8_t u8Index = u8CurrentMinute; u8Index < u8CurrentMinute + u8WorktimeIntervalMin; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_RED, au8MinuteToColorArray[u8Index]);
    }

    // Check the next 10 Minutes (Break Time)
    for (uint8_t u8Index = u8CurrentMinute + u8WorktimeIntervalMin; u8Index < u8CurrentMinute + u8WorktimeIntervalMin + u8BreaktimeIntervalMin; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_GREEN, au8MinuteToColorArray[u8Index]);
    }

    // Check the last 30 Minutes (Off Time)
    for (uint8_t u8Index = u8CurrentMinute + u8WorktimeIntervalMin + u8BreaktimeIntervalMin; u8Index < MINUTES_IN_HOUR; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8MinuteToColorArray[u8Index]);
    }
}

/**
 * Tests for LightControl_fillLedToColorArray():
 * Test 11:
 * - Input [0...30] = W, [30...50] = B, [50...59] = 0
 * - Output [0...11] = W, [12...20] = B, [21...23] = 0
 */
void test_LightControl_fillLedToColorArray_Test11()
{
    uint8_t u8CurrentMinute = 0;
    uint8_t u8WorktimeIntervalMin = 30;
    uint8_t u8BreaktimeIntervalMin = 20;
    uint8_t au8MinuteToColorArray[MINUTES_IN_HOUR] = {0};
    uint8_t au8LedToColorArray[TOTAL_LEDS] = {0};

    LightControl_fillMinuteToColorArray(
        u8CurrentMinute,
        u8WorktimeIntervalMin,
        u8BreaktimeIntervalMin,
        au8MinuteToColorArray);

    LightControl_fillLedToColorArray(au8MinuteToColorArray, au8LedToColorArray);

    float u8LedsPerMinute = (float)TOTAL_LEDS / (float)MINUTES_IN_HOUR;

    for (float i = 0; i < MINUTES_IN_HOUR; i++)
    {
        uint8_t index = (uint8_t)(i * u8LedsPerMinute);
        TEST_ASSERT_EQUAL(au8MinuteToColorArray[(uint8_t)i], au8LedToColorArray[index]);
    }
}
