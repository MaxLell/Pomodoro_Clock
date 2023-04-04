#include "LightControl.h"
#include "RgbLed.h"
#include "Common.h"
#include "Config.h"

STATIC uint8_t u8WorktimeIntervalMin = 0;
STATIC uint8_t u8BreaktimeIntervalMin = 0;
STATIC uint8_t au8MinuteToColorArray[MINUTES_IN_HOUR] = {0};
STATIC uint8_t au8LedToColorArray[TOTAL_LEDS] = {0};

STATIC uint8_t u8PreviousMinute = MINUTES_IN_HOUR + 10; // Gives it an impossible value

uint8_t LightControl_fillMinuteToColorArray(uint8_t in_u8CurrentMinute,
                                            uint8_t in_u8WorktimeIntervalMin,
                                            uint8_t in_u8BreaktimeIntervalMin,
                                            uint8_t *inout_au8ColorArray)
{
    // Input Checks
    assert_true(inout_au8ColorArray != NULL);

    if (inout_au8ColorArray == NULL)
    {
        log_error("inout_au8ColorArray is NULL");
        return STATUS_NULL_POINTER;
    }

    if (in_u8WorktimeIntervalMin >= MINUTES_IN_HOUR)
    {
        log_error("in_u8WorktimeIntervalMin is >= 60");
        return STATUS_INVALID_ARG;
    }

    uint8_t currentMinuteCounter = in_u8CurrentMinute;

    // Write the Entries for the Work Time (with the respective offset)
    for (uint8_t i = 0; i < in_u8WorktimeIntervalMin; i++)
    {
        inout_au8ColorArray[currentMinuteCounter] = LIGHTCONTROL_LED_RED;
        currentMinuteCounter++;
        if (currentMinuteCounter >= MINUTES_IN_HOUR)
        {
            currentMinuteCounter = 0;
        }
    }

    // Write the Entries for the Break Time
    for (uint8_t i = 0; i < in_u8BreaktimeIntervalMin; i++)
    {
        inout_au8ColorArray[currentMinuteCounter] = LIGHTCONTROL_LED_GREEN;
        currentMinuteCounter++;
        if (currentMinuteCounter >= MINUTES_IN_HOUR)
        {
            currentMinuteCounter = 0;
        }
    }

    // Write the Entries for the Off Time
    for (uint8_t i = 0; i < (MINUTES_IN_HOUR - in_u8WorktimeIntervalMin - in_u8BreaktimeIntervalMin); i++)
    {
        inout_au8ColorArray[currentMinuteCounter] = LIGHTCONTROL_LED_OFF;
        currentMinuteCounter++;
        if (currentMinuteCounter >= MINUTES_IN_HOUR)
        {
            currentMinuteCounter = 0;
        }
    }

    return STATUS_OK;
}

uint8_t LightControl_fillLedToColorArray(uint8_t *in_au8MinuteToColorArray,
                                         uint8_t *inout_au8LedToColorArray)
{
    // Input Checks
    assert_true(in_au8MinuteToColorArray != NULL);
    assert_true(inout_au8LedToColorArray != NULL);

    if (in_au8MinuteToColorArray == NULL)
    {
        log_error("in_au8MinuteToColorArray is NULL");
        return STATUS_NULL_POINTER;
    }

    if (inout_au8LedToColorArray == NULL)
    {
        log_error("inout_au8LedToColorArray is NULL");
        return STATUS_NULL_POINTER;
    }

    // Calculate the number of LEDs per Minute
    float u8LedsPerMinute = (float)TOTAL_LEDS / (float)MINUTES_IN_HOUR;
    // printf("Leds per Minute: %f", u8LedsPerMinute);

    // Fill the LED Array
    for (float i = 0; i < MINUTES_IN_HOUR; i++)
    {
        uint8_t index = (uint8_t)(i * u8LedsPerMinute);
        inout_au8LedToColorArray[(uint8_t)(i * u8LedsPerMinute)] = in_au8MinuteToColorArray[(uint8_t)i];
    }
    return STATUS_OK;
}

uint8_t LightControl_setLedsToColor(uint8_t *in_au8LedToColorArray)
{
    // Input Checks
    assert_true(in_au8LedToColorArray != NULL);
    if (in_au8LedToColorArray == NULL)
    {
        log_error("in_au8LedToColorArray is NULL");
        return STATUS_NULL_POINTER;
    }

    // Set the LEDs to the respective color
    for (uint8_t i = 0; i < TOTAL_LEDS; i++)
    {
        switch (in_au8LedToColorArray[i])
        {
        case LIGHTCONTROL_LED_OFF:
            RgbLed_SetLedToColor(i, 0, 0, 0);
            break;
        case LIGHTCONTROL_LED_RED:
            RgbLed_SetLedToColor(i, 255, 0, 0);
            break;
        case LIGHTCONTROL_LED_GREEN:
            RgbLed_SetLedToColor(i, 0, 255, 0);
            break;
        case LIGHTCONTROL_LED_BLUE:
            RgbLed_SetLedToColor(i, 0, 0, 255);
            break;
        default:
            RgbLed_SetLedToColor(i, 0, 0, 0);
            return STATUS_OVERFLOW;
            log_error("Default case in LightControl_fillLedToRgbArray");
            break;
        }
    }
    return STATUS_OK;
}

uint8_t LightControl_execute(uint8_t in_u8CurrentMinute)
{
    // Input Checks
    assert_true(in_u8CurrentMinute < MINUTES_IN_HOUR);

    if (in_u8CurrentMinute >= MINUTES_IN_HOUR)
    {
        log_error("in_u8CurrentMinute is >= 60");
        return STATUS_INVALID_ARG;
    }

    /**
     * This code needs to be executed every minute
     */

    if (u8PreviousMinute == in_u8CurrentMinute)
    {
        // The minute has not changed, so we do not need to execute the code
        return STATUS_OK;
    }
    else
    {
        // The minute has changed, so we need to execute the code
        u8PreviousMinute = in_u8CurrentMinute;
        // Fill the Minute to Color Array
        LightControl_fillMinuteToColorArray(in_u8CurrentMinute, u8WorktimeIntervalMin, u8BreaktimeIntervalMin, au8MinuteToColorArray);
        // Fill the LED to Color Array
        LightControl_fillLedToColorArray(au8MinuteToColorArray, au8LedToColorArray);
        // Set the LEDs to the respective color
        LightControl_setLedsToColor(au8LedToColorArray);

        return STATUS_OK;
    }
}

uint8_t LightControl_init(void)
{
    // Get the Worktime Interval from the Config
    Config_getWorktime(&u8WorktimeIntervalMin);

    // Get the Breaktime Interval from the Config
    Config_getBreaktime(&u8BreaktimeIntervalMin);

    return STATUS_OK;
}