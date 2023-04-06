#include "LightControl.h"
#include "RgbLed.h"
#include "Common.h"
#include "Config.h"

STATIC uint8_t u8WorktimeIntervalMin = 0;
STATIC uint8_t u8BreaktimeIntervalMin = 0;
STATIC uint8_t au8MinuteToColorArray[MINUTES_IN_HOUR] = {0};
STATIC uint8_t au8LedToColorArray[TOTAL_LEDS] = {0};
STATIC BOOL bSequenceWasInitialized = FALSE;
STATIC uint8_t u8SequenceCounter = 0;
STATIC BOOL bSequenceIsCompleted = TRUE;

STATIC uint8_t u8PreviousMinute = MINUTES_IN_HOUR + 10; // Gives it an impossible value

status_t LightControl_fillMinuteToColorArray(uint8_t in_u8CurrentMinute,
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

    if (in_u8BreaktimeIntervalMin >= MINUTES_IN_HOUR)
    {
        log_error("in_u8BreaktimeIntervalMin is >= 60");
        return STATUS_INVALID_ARG;
    }

    if (in_u8CurrentMinute >= MINUTES_IN_HOUR)
    {
        log_error("in_u8CurrentMinute is >= 60");
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

status_t LightControl_fillLedToColorArray(uint8_t *in_au8MinuteToColorArray,
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

status_t LightControl_setLedsToColor(uint8_t *in_au8LedToColorArray)
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

status_t LightControl_removeColorsFromMinuteArray(uint8_t *inout_au8MinuteToColorArray,
                                                  uint8_t in_u8CurrentMinute)
{
    // Input Checks
    assert_true(inout_au8MinuteToColorArray != NULL);
    assert_true(in_u8CurrentMinute < MINUTES_IN_HOUR);

    if (inout_au8MinuteToColorArray == NULL)
    {
        log_error("inout_au8MinuteToColorArray is NULL");
        return STATUS_NULL_POINTER;
    }

    if (in_u8CurrentMinute >= MINUTES_IN_HOUR)
    {
        log_error("in_u8CurrentMinute is >= 60");
        return STATUS_INVALID_ARG;
    }

    // Remove the Colors from the Minute Array
    inout_au8MinuteToColorArray[in_u8CurrentMinute] = LIGHTCONTROL_LED_OFF;

    return STATUS_OK;
}

status_t LightControl_execute(uint8_t in_u8CurrentMinute)
{
    /**
     * This function shall be executed once every minute
     */

    // Input Checks
    assert_true(in_u8CurrentMinute < MINUTES_IN_HOUR);
    if (in_u8CurrentMinute >= MINUTES_IN_HOUR)
    {
        log_error("in_u8CurrentMinute is >= 60");
        return STATUS_INVALID_ARG;
    }

    // Check if the minute has changed
    if (u8PreviousMinute == in_u8CurrentMinute)
    {
        // The minute has not changed, so we do not need to execute the code
        return STATUS_OK;
    }
    else
    {
        // The minute has changed

        // Check if the color array has already been initialized
        if (bSequenceWasInitialized == FALSE)
        {
            LightControl_init(in_u8CurrentMinute);
        }
        else
        {
            // If the sequence counter is 0, then the sequence is completed
            if (u8SequenceCounter == 0)
            {
                LightControl_endSequence();
            }
            else
            {
                LightControl_runSequence(in_u8CurrentMinute);
            }
        }
        return STATUS_OK;
    }
}

status_t LightControl_init(uint8_t in_u8CurrentMinute)
{
    status_t tStatus = STATUS_OK;

    // Get the Worktime Interval from the Config
    tStatus = Config_getWorktime(&u8WorktimeIntervalMin);
    if (tStatus != STATUS_OK)
    {
        log_error("Config_getWorktime returned an error");
        return tStatus;
    }

    // Get the Breaktime Interval from the Config
    tStatus = Config_getBreaktime(&u8BreaktimeIntervalMin);
    if (tStatus != STATUS_OK)
    {
        log_error("Config_getBreaktime returned an error");
        return tStatus;
    }

    // Fill the Minute to Color Array)
    tStatus = LightControl_fillMinuteToColorArray(in_u8CurrentMinute, u8WorktimeIntervalMin, u8BreaktimeIntervalMin, au8MinuteToColorArray);
    if (tStatus != STATUS_OK)
    {
        log_error("LightControl_fillMinuteToColorArray returned an error");
        return tStatus;
    }
    // Sequence was initialized
    bSequenceWasInitialized = TRUE;

    // Set the sequence counter to u8WorktimeIntervalMin + u8BreaktimeIntervalMin
    u8SequenceCounter = u8WorktimeIntervalMin + u8BreaktimeIntervalMin;

    // Set the sequence is completed flag to false
    bSequenceIsCompleted = FALSE;

    return STATUS_OK;
}

status_t LightControl_endSequence(void)
{
    // Set the all LEDs in the au8LedToColorArray to LED_OFF
    for (uint8_t i = 0; i < TOTAL_LEDS; i++)
    {
        au8LedToColorArray[i] = LIGHTCONTROL_LED_OFF;
    }
    status_t tStatus = LightControl_setLedsToColor(au8LedToColorArray);
    if (tStatus != STATUS_OK)
    {
        log_error("LightControl_setLedsToColor returned an error");
        return tStatus;
    }

    // Set the sequence counter to 0
    u8SequenceCounter = 0;

    // Set the sequence was initialized flag to false
    bSequenceWasInitialized = FALSE;

    // Set the sequence is completed flag to true
    bSequenceIsCompleted = TRUE;

    return STATUS_OK;
}

status_t LightControl_runSequence(uint8_t in_u8CurrentMinute)
{
    // Remove the color from the minute array
    status_t tStatus = LightControl_removeColorsFromMinuteArray(au8MinuteToColorArray, u8PreviousMinute);
    if (tStatus != STATUS_OK)
    {
        log_error("LightControl_removeColorsFromMinuteArray returned an error");
        return tStatus;
    }

    // Fill the LED Array
    tStatus = LightControl_fillLedToColorArray(au8MinuteToColorArray, au8LedToColorArray);
    if (tStatus != STATUS_OK)
    {
        log_error("LightControl_fillLedToRgbArray returned an error");
        return tStatus;
    }

    // Set the LEDs to the respective color
    tStatus = LightControl_setLedsToColor(au8LedToColorArray);
    if (tStatus != STATUS_OK)
    {
        log_error("LightControl_setLedsToColor returned an error");
        return tStatus;
    }

    // Update the previous minute
    u8PreviousMinute = in_u8CurrentMinute;

    // Decrement the sequence counter
    u8SequenceCounter--;

    return STATUS_OK;
}

status_t LightControl_sequenceIsCompleted(BOOL *out_bSequenceIsCompleted)
{
    // Input Checks
    assert_true(out_bSequenceIsCompleted != NULL);
    if (out_bSequenceIsCompleted == NULL)
    {
        log_error("out_bSequenceIsCompleted is NULL");
        return STATUS_NULL_POINTER;
    }

    // Set the out_bSequenceIsCompleted to the bSequenceIsCompleted flag
    *out_bSequenceIsCompleted = bSequenceIsCompleted;

    return STATUS_OK;
}