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
 * Tests for LightControl_init():
 * check whether the worktime and breaktime interval are set correctly
 */
extern uint8_t u8WorktimeIntervalMin;
extern uint8_t u8BreaktimeIntervalMin;
void test_LightControl_init_should_SetWorktimeAndBreaktimeInterval()
{
    uint8_t u8CurrentTime = 10;

    LightControl_init(u8CurrentTime);

    TEST_ASSERT_EQUAL(50, u8WorktimeIntervalMin);
    TEST_ASSERT_EQUAL(10, u8BreaktimeIntervalMin);
}

/**
 * Tests for LightControl_init():
 * check whether the minute to color array is filled correctly
 */
extern uint8_t au8MinuteToColorArray[MINUTES_IN_HOUR];
void test_LightControl_init_should_FillMinuteToColorArray()
{
    uint8_t u8CurrentTime = 15;

    /**
     * Reset the array to 0
     */
    for (uint8_t i = 0; i < MINUTES_IN_HOUR; i++)
    {
        au8MinuteToColorArray[i] = 0;
    }

    LightControl_init(u8CurrentTime);

    // Check that every element from the array is different from 0
    for (uint8_t i = 0; i < MINUTES_IN_HOUR; i++)
    {
        TEST_ASSERT_NOT_EQUAL(0, au8MinuteToColorArray[i]);
    }
}

/**
 * Tests for LightControl_init():
 * check whether the sequence couter is set correctly
 */
extern uint8_t u8SequenceCounter;
void test_LightControl_init_should_SetSequenceCounter()
{
    uint8_t u8CurrentTime = 15;

    LightControl_init(u8CurrentTime);

    uint8_t u8Breaktime;
    uint8_t u8Worktime;
    Config_getBreaktime(&u8Breaktime);
    Config_getWorktime(&u8Worktime);

    TEST_ASSERT_EQUAL(u8SequenceCounter, u8Breaktime + u8Worktime);
}

/**
 * Tests for LightControl_init():
 * check whether the sequence initialized flag is set to true
 */
extern BOOL bSequenceWasInitialized;
void test_LightControl_init_should_SetSequenceInitializedFlagToTrue()
{
    uint8_t u8CurrentTime = 15;
    bSequenceWasInitialized = FALSE;

    LightControl_init(u8CurrentTime);

    TEST_ASSERT_TRUE(bSequenceWasInitialized);
}

/**
 * Tests for LightControl_endSequence():
 * checks whether all leds are turned off afterwards
 */
extern uint8_t au8LedToColorArray[TOTAL_LEDS];
void test_LightControl_endSequence_should_TurnOffAllLeds()
{
    for (uint8_t i = 0; i < TOTAL_LEDS; i++)
    {
        au8LedToColorArray[i] = LIGHTCONTROL_LED_GREEN;
    }

    RgbLed_SetLedToColor_Ignore();

    LightControl_endSequence();

    for (uint8_t i = 0; i < TOTAL_LEDS; i++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8LedToColorArray[i]);
    }
}

/**
 * Tests for LightControl_endSequence():
 * checks whether the sequence initialized flag is set to false
 */
void test_LightControl_endSequence_should_SetSequenceInitializedFlagToFalse()
{
    bSequenceWasInitialized = TRUE;

    RgbLed_SetLedToColor_Ignore();

    LightControl_endSequence();

    TEST_ASSERT_FALSE(bSequenceWasInitialized);
}

/**
 * Tests for LightControl_endSequence():
 * checks whether the sequence counter is set to 0
 */

void test_LightControl_endSequence_should_SetSequenceCounterToZero()
{
    u8SequenceCounter = 10;
    RgbLed_SetLedToColor_Ignore();
    LightControl_endSequence();
    TEST_ASSERT_EQUAL(0, u8SequenceCounter);
}
