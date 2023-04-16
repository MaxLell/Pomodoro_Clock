#include "unity.h"
#include "Common.h"
#include "Config.h"
#include "LightControl.h"
#include "mock_RgbLed.h"

void setUp(void)
{
}

void tearDown(void)
{
}

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

void test_LightControl_fillMinuteToColorArray_Test4()
{
    // Test 4:
    // - Input: currentMinute = 17, worktimeIntervalMin = 50, breaktimeIntervalMin = 7
    // - Expected Output: [0...7] = W, [8...14] = B, [15...17] = 0, [18...59] = W
    uint8_t u8TestCurrentMinute = 17;
    uint8_t u8TestWorktimeIntervalMin = 50;
    uint8_t u8TestBreaktimeIntervalMin = 7;
    uint8_t au8TestMinuteToColorArray[60] = {0};

    LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    // Check the first 8 Minutes (Work Time)
    for (uint8_t u8Index = 0; u8Index < 7; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_RED, au8TestMinuteToColorArray[u8Index]);
    }

    // Check the next 7 Minutes (Break Time)
    for (uint8_t u8Index = 7; u8Index < 14; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_GREEN, au8TestMinuteToColorArray[u8Index]);
    }

    // Check the next 3 Minutes (Off Time)
    for (uint8_t u8Index = 14; u8Index < 17; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8TestMinuteToColorArray[u8Index]);
    }

    // Check the last 42 Minutes (Work Time)
    for (uint8_t u8Index = 17; u8Index < MINUTES_IN_HOUR; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_RED, au8TestMinuteToColorArray[u8Index]);
    }
}

/*
 * Test 6:
 * - Input: currentMinute = 61, worktimeIntervalMin = 0, breaktimeIntervalMin = 0
 * - Expected Output: [0...59] = 0; returns a Status Error Code
 */
void test_LightControl_fillMinuteToColorArray_Test6()
{
    uint8_t u8TestCurrentMinute = 61;
    uint8_t u8TestWorktimeIntervalMin = 0;
    uint8_t u8TestBreaktimeIntervalMin = 0;
    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t u8Status = LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    TEST_ASSERT_EQUAL(STATUS_INVALID_ARG, u8Status);
}

/*
 * Test 7:
 * - Input: currentMinute = 0, worktimeIntervalMin = 61, breaktimeIntervalMin = 0
 * - Expected Output: [0...59] = 0; returns a Status Invalid Argument
 */
void test_LightControl_fillMinuteToColorArray_Test7()
{
    uint8_t u8TestCurrentMinute = 0;
    uint8_t u8TestWorktimeIntervalMin = 61;
    uint8_t u8TestBreaktimeIntervalMin = 0;
    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t u8Status = LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    TEST_ASSERT_EQUAL(STATUS_INVALID_ARG, u8Status);
}

/*
 * Test 8:
 * - Input: currentMinute = 0, worktimeIntervalMin = 10, breaktimeIntervalMin = 60
 * - Expected Output: [0...59] = 0; returns a Status Error Code
 */
void test_LightControl_fillMinuteToColorArray_Test8()
{
    uint8_t u8TestCurrentMinute = 0;
    uint8_t u8TestWorktimeIntervalMin = 10;
    uint8_t u8TestBreaktimeIntervalMin = 60;
    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t u8Status = LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    TEST_ASSERT_EQUAL(STATUS_INVALID_ARG, u8Status);
}

/*
 * Test 9:
 * - Input: currentMinute = 0, worktimeIntervalMin = 67, breaktimeIntervalMin = 10
 * - Expected Output: [0...59] = 0; returns a Status Error Code
 */
void test_LightControl_fillMinuteToColorArray_Test9()
{
    uint8_t u8TestCurrentMinute = 0;
    uint8_t u8TestWorktimeIntervalMin = 67;
    uint8_t u8TestBreaktimeIntervalMin = 10;
    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t u8Status = LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    TEST_ASSERT_EQUAL(STATUS_INVALID_ARG, u8Status);
}
/**
 * Tests for LightControl_fillLedToColorArray():
 * Test 11:
 * - Input [0...30] = W, [30...50] = B, [50...59] = 0
 * - Output [0...11] = W, [12...20] = B, [21...23] = 0
 */
void test_LightControl_fillLedToColorArray_Test11()
{
    uint8_t u8TestCurrentMinute = 0;
    uint8_t u8TestWorktimeIntervalMin = 30;
    uint8_t u8TestBreaktimeIntervalMin = 20;
    uint8_t au8TestMinuteToColorArray[MINUTES_IN_HOUR] = {0};
    uint8_t au8TestLedToColorArray[TOTAL_LEDS] = {0};

    LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    LightControl_fillLedToColorArray(au8TestMinuteToColorArray, au8TestLedToColorArray);

    float u8LedsPerMinute = (float)TOTAL_LEDS / (float)MINUTES_IN_HOUR;

    for (float i = 0; i < MINUTES_IN_HOUR; i++)
    {
        uint8_t index = (uint8_t)(i * u8LedsPerMinute);
        TEST_ASSERT_EQUAL(au8TestMinuteToColorArray[(uint8_t)i], au8TestLedToColorArray[index]);
    }
}

/**
 * Tests for LightControl_removeColorsFromMinuteArray():
 * Test 12:
 * The input is a default time array with the spec as it is shown below
 * The remove function shall take out the current minute from the array
 */
void test_LightControl_removeColorsFromMinuteArray_Test12()
{
    uint8_t u8TestCurrentMinute = 0;
    uint8_t u8TestWorktimeIntervalMin = 30;
    uint8_t u8TestBreaktimeIntervalMin = 20;
    uint8_t au8TestMinuteToColorArray[MINUTES_IN_HOUR] = {0};
    uint8_t au8TestLedToColorArray[TOTAL_LEDS] = {0};

    LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    LightControl_removeColorsFromMinuteArray(au8TestMinuteToColorArray, u8TestCurrentMinute);
    TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8TestMinuteToColorArray[u8TestCurrentMinute]);

    // try another minute
    u8TestCurrentMinute = 12;
    LightControl_removeColorsFromMinuteArray(au8TestMinuteToColorArray, u8TestCurrentMinute);
    TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8TestMinuteToColorArray[u8TestCurrentMinute]);
}

/**
 * Tests for LightControl_removeColorsFromMinuteArray():
 * Test 13:
 * Remove all colors from the array
 */

void test_LightControl_removeColorsFromMinuteArray_Test13()
{
    uint8_t u8TestCurrentMinute = 25;
    uint8_t u8TestWorktimeIntervalMin = 30;
    uint8_t u8TestBreaktimeIntervalMin = 20;
    uint8_t au8TestMinuteToColorArray[MINUTES_IN_HOUR] = {0};
    uint8_t au8TestLedToColorArray[TOTAL_LEDS] = {0};

    LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    for (uint8_t i = 0; i < MINUTES_IN_HOUR; i++)
    {
        LightControl_removeColorsFromMinuteArray(au8TestMinuteToColorArray, i);
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8TestMinuteToColorArray[i]);
    }
}

/**
 * Tests for LightControl_init()
 * - It shall subscribe to the current time topic
 * - It shall subscribe to the PFSM State Change topic
 */