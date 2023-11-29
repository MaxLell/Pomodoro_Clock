#include "RgbLed.h"
#include "MessageBroker.h"
#include "Common.h"
#include "Config.h"
#include "LightEffects_Interface.h"
#include "RgbLed_Hardware.h"

/**
 * Static functions
 */
STATIC status_t RgbLed_callback(MessageBroker_message_t in_tMessage);
STATIC void RgbLed_DecodeColorsToRgbValues(
    uint8_t *in_au8ColorArray,
    RgbLed_t *out_saRgbLeds,
    uint8_t in_u8ArraySizes);

STATIC void RgbLed_SetLedRgbValues(
    RgbLed_t *inout_tRgbLed,
    uint8_t in_u8LedIndex,
    uint8_t in_u8Red,
    uint8_t in_u8Green,
    uint8_t in_u8Blue);

STATIC void RgbLed_EncodeRgbValuesTo24Bit(
    RgbLed_t *in_tRgbLed,
    uint32_t *inout_u32RgbLed24Bit,
    uint8_t in_u8ArraySizes);

STATIC void RgbLed_PlaceRgbLed24BitDataInPwmDataArray(
    uint32_t *in_u32RgbLed24Bit,
    uint16_t *inout_au16PwmData,
    uint8_t in_u8RgbLedArraySize,
    uint32_t in_u32PwmDataArraySize);

STATIC void RgbLed_PlaceEndOfSequenceInPwmDataArray(
    uint16_t *inout_au16PwmData,
    uint32_t in_u32PwmDataArraySize);

STATIC void RgbLed_BuildRgbLedSequence(
    uint8_t *in_au8ColorArray,
    uint8_t in_u8ColorArraySize,
    uint16_t *inout_au16PwmData,
    uint32_t in_u32PwmDataArraySize);

/**
 * Static variables
 */

STATIC BOOL bNewEntry = FALSE;
STATIC uint8_t au8ColorArray[TOTAL_LEDS];
STATIC uint16_t au16PwmData[PWM_DATA_SIZE];

/**
 * Implementation
 */

STATIC void RgbLed_BuildRgbLedSequence(
    uint8_t *in_au8ColorArray,
    uint8_t in_u8ColorArraySize,
    uint16_t *inout_au16PwmData,
    uint32_t in_u32PwmDataArraySize)
{
    assert_true(in_au8ColorArray != NULL);
    assert_true(in_u8ColorArraySize > 0);
    assert_true(inout_au16PwmData != NULL);
    assert_true(in_u32PwmDataArraySize > 0);

    RgbLed_t saRgbLeds[TOTAL_LEDS];
    uint32_t u32RgbLed24Bit[TOTAL_LEDS];

    // Decode the color array to RGB values
    RgbLed_DecodeColorsToRgbValues(
        in_au8ColorArray,
        saRgbLeds,
        in_u8ColorArraySize);

    // Encode the RGB values to 24 bit values
    RgbLed_EncodeRgbValuesTo24Bit(
        saRgbLeds,
        u32RgbLed24Bit,
        in_u8ColorArraySize);

    // Place the 24 bit values in the PWM data array
    RgbLed_PlaceRgbLed24BitDataInPwmDataArray(
        u32RgbLed24Bit,
        inout_au16PwmData,
        in_u8ColorArraySize,
        in_u32PwmDataArraySize);

    // Place the end of sequence in the PWM data array
    RgbLed_PlaceEndOfSequenceInPwmDataArray(
        inout_au16PwmData,
        in_u32PwmDataArraySize);
}

STATIC void RgbLed_PlaceEndOfSequenceInPwmDataArray(
    uint16_t *inout_au16PwmData,
    uint32_t in_u32PwmDataArraySize)
{
    assert_true(inout_au16PwmData != NULL);
    assert_true(in_u32PwmDataArraySize > 0);

    // Make sure that the last 50 elements of the array are set to 0
    for (uint32_t i = in_u32PwmDataArraySize - 50; i < in_u32PwmDataArraySize; i++)
    {
        if (inout_au16PwmData[i] != 0)
        {
            log_error("PWM Array is not set to 0 at index %d", i);
            inout_au16PwmData[i] = WS2812_OFF;
        }
    }
}

STATIC void RgbLed_PlaceRgbLed24BitDataInPwmDataArray(
    uint32_t *in_u32RgbLed24Bit,
    uint16_t *inout_au16PwmData,
    uint8_t in_u8RgbLedArraySize,
    uint32_t in_u32PwmDataArraySize)
{
    assert_true(in_u32RgbLed24Bit != NULL);
    assert_true(inout_au16PwmData != NULL);
    assert_true((in_u8RgbLedArraySize * 24) <= in_u32PwmDataArraySize);

    // Process each LED
    for (uint32_t i = 0; i < in_u8RgbLedArraySize; i++)
    {
        uint32_t u32Color = in_u32RgbLed24Bit[i];

        // Map each bit to the PWM data array
        // LSB is mapped to the first element of the array
        for (int8_t j = 23; j >= 0; j--)
        {
            if (u32Color & (1 << j))
            {
                inout_au16PwmData[j] = WS2812_HIGH_BIT;
            }
            else
            {
                inout_au16PwmData[j] = WS2812_LOW_BIT;
            }
        }
    }
}

STATIC void RgbLed_EncodeRgbValuesTo24Bit(
    RgbLed_t *in_tRgbLed,
    uint32_t *inout_u32RgbLed24Bit,
    uint8_t in_u8ArraySizes)
{
    // Check if the pointer is valid
    assert_true(in_tRgbLed != NULL);
    assert_true(inout_u32RgbLed24Bit != NULL);

    for (uint8_t u8Index = 0; u8Index < in_u8ArraySizes; u8Index++)
    {
        inout_u32RgbLed24Bit[u8Index] = (in_tRgbLed[u8Index].u8Red << 16) |
                                        (in_tRgbLed[u8Index].u8Green << 8) |
                                        (in_tRgbLed[u8Index].u8Blue);
    }
}

STATIC void RgbLed_SetLedRgbValues(
    RgbLed_t *inout_tRgbLed,
    uint8_t in_u8LedIndex,
    uint8_t in_u8Red,
    uint8_t in_u8Green,
    uint8_t in_u8Blue)
{
    // Check if the pointer is valid
    assert_true(inout_tRgbLed != NULL);

    inout_tRgbLed->u8Index = in_u8LedIndex;
    inout_tRgbLed->u8Red = in_u8Red;
    inout_tRgbLed->u8Green = in_u8Green;
    inout_tRgbLed->u8Blue = in_u8Blue;
}

STATIC void RgbLed_DecodeColorsToRgbValues(
    uint8_t *in_au8ColorArray,
    RgbLed_t *inout_saRgbLeds,
    uint8_t in_u8ArraySizes)
{
    // Check if the pointer is valid
    assert_true(in_au8ColorArray != NULL);
    assert_true(inout_saRgbLeds != NULL);

    // Translate the color array to RGB values
    for (uint8_t u8Index = 0; u8Index < in_u8ArraySizes; u8Index++)
    {
        inout_saRgbLeds[u8Index].u8Index = u8Index;
        switch (in_au8ColorArray[u8Index])
        {
        // Red
        case LIGHTEFFECTS_LED_RED_HIGH:
            RgbLed_SetLedRgbValues(&inout_saRgbLeds[u8Index],
                                   u8Index,
                                   LED_BRIGHTNESS_HIGH,
                                   LED_BRIGHTNESS_OFF,
                                   LED_BRIGHTNESS_OFF);
            break;

        case LIGHTEFFECTS_LED_RED_MID:
            RgbLed_SetLedRgbValues(&inout_saRgbLeds[u8Index],
                                   u8Index,
                                   LED_BRIGHTNESS_MEDIUM,
                                   LED_BRIGHTNESS_OFF,
                                   LED_BRIGHTNESS_OFF);
            break;

        case LIGHTEFFECTS_LED_RED_LOW:
            RgbLed_SetLedRgbValues(&inout_saRgbLeds[u8Index],
                                   u8Index,
                                   LED_BRIGHTNESS_LOW,
                                   LED_BRIGHTNESS_OFF,
                                   LED_BRIGHTNESS_OFF);
            break;

        // Green
        case LIGHTEFFECTS_LED_GREEN_HIGH:
            RgbLed_SetLedRgbValues(&inout_saRgbLeds[u8Index],
                                   u8Index,
                                   LED_BRIGHTNESS_OFF,
                                   LED_BRIGHTNESS_HIGH,
                                   LED_BRIGHTNESS_OFF);
            break;

        case LIGHTEFFECTS_LED_GREEN_MID:
            RgbLed_SetLedRgbValues(&inout_saRgbLeds[u8Index],
                                   u8Index,
                                   LED_BRIGHTNESS_OFF,
                                   LED_BRIGHTNESS_MEDIUM,
                                   LED_BRIGHTNESS_OFF);
            break;

        case LIGHTEFFECTS_LED_GREEN_LOW:
            RgbLed_SetLedRgbValues(&inout_saRgbLeds[u8Index],
                                   u8Index,
                                   LED_BRIGHTNESS_OFF,
                                   LED_BRIGHTNESS_LOW,
                                   LED_BRIGHTNESS_OFF);
            break;

        // Blue
        case LIGHTEFFECTS_LED_BLUE_HIGH:
            RgbLed_SetLedRgbValues(&inout_saRgbLeds[u8Index],
                                   u8Index,
                                   LED_BRIGHTNESS_OFF,
                                   LED_BRIGHTNESS_OFF,
                                   LED_BRIGHTNESS_HIGH);
            break;

        case LIGHTEFFECTS_LED_BLUE_MID:
            RgbLed_SetLedRgbValues(&inout_saRgbLeds[u8Index],
                                   u8Index,
                                   LED_BRIGHTNESS_OFF,
                                   LED_BRIGHTNESS_OFF,
                                   LED_BRIGHTNESS_MEDIUM);

            break;

        case LIGHTEFFECTS_LED_BLUE_LOW:
            RgbLed_SetLedRgbValues(&inout_saRgbLeds[u8Index],
                                   u8Index,
                                   LED_BRIGHTNESS_OFF,
                                   LED_BRIGHTNESS_OFF,
                                   LED_BRIGHTNESS_LOW);
            break;

        // White
        case LIGHTEFFECTS_LED_WHITE_HIGH:
            RgbLed_SetLedRgbValues(&inout_saRgbLeds[u8Index],
                                   u8Index,
                                   LED_BRIGHTNESS_HIGH,
                                   LED_BRIGHTNESS_HIGH,
                                   LED_BRIGHTNESS_HIGH);
            break;

        case LIGHTEFFECTS_LED_WHITE_MID:
            RgbLed_SetLedRgbValues(&inout_saRgbLeds[u8Index],
                                   u8Index,
                                   LED_BRIGHTNESS_MEDIUM,
                                   LED_BRIGHTNESS_MEDIUM,
                                   LED_BRIGHTNESS_MEDIUM);
            break;

        case LIGHTEFFECTS_LED_WHITE_LOW:
            RgbLed_SetLedRgbValues(&inout_saRgbLeds[u8Index],
                                   u8Index,
                                   LED_BRIGHTNESS_LOW,
                                   LED_BRIGHTNESS_LOW,
                                   LED_BRIGHTNESS_LOW);
            break;

        // Off
        case LIGHTEFFECTS_LED_OFF:
            RgbLed_SetLedRgbValues(&inout_saRgbLeds[u8Index],
                                   u8Index,
                                   LED_BRIGHTNESS_OFF,
                                   LED_BRIGHTNESS_OFF,
                                   LED_BRIGHTNESS_OFF);
            break;

        default:
            log_error("Invalid color received");
            break;
        }
    }
}

STATIC status_t RgbLed_callback(MessageBroker_message_t in_tMessage)
{
    switch (in_tMessage.eMsgTopic)
    {
    case E_TOPIC_RING_LEDS_OUTPUT:
    {
        // Copy the array into the encoded colors array
        for (uint8_t i = 0; i < in_tMessage.u16DataSize; i++)
        {
            au8ColorArray[i] = in_tMessage.au8DataBytes[i];
        }

        // Set the new entry flag
        bNewEntry = TRUE;
    }
    break;

    default:
    {
        log_error("Invalid topic received");
        return STATUS_INVALID_ARG;
    }
    break;
    }
    return STATUS_OK;
}

void RgbLed_init(void)
{
    // Subscribe to the RgbLed topic
    MessageBroker_subscribe(
        E_TOPIC_RING_LEDS_OUTPUT,
        RgbLed_callback);

    // Clear the encoded colors array
    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        au8ColorArray[u8Index] = 0;
    }

    // Clear the new entry flag
    bNewEntry = FALSE;
}

void RgbLed_execute(void)
{
    if (bNewEntry)
    {
        // Clear the new entry flag
        bNewEntry = FALSE;

        // Build the PWM data
        RgbLed_BuildRgbLedSequence(
            au8ColorArray,
            TOTAL_LEDS,
            au16PwmData,
            PWM_DATA_SIZE);

        // Send the PWM data to Hardware
        RgbLed_SetLeds(au16PwmData, PWM_DATA_SIZE);
    }
}
