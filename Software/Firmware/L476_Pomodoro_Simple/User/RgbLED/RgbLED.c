#include "RgbLed.h"
#include "MessageBroker.h"
#include "Common.h"
#include "Config.h"
#include "LightEffects_Interface.h"

#define PWM_DATA_SIZE (24 * TOTAL_LEDS) + 50

/**
 * Static functions
 */
STATIC status_t RgbLed_callback(MessageBroker_message_t in_tMessage);
STATIC void RgbLed_DecodeColors(void);
STATIC void RgbLed_SetLed(
    uint8_t u8LedIndex,
    uint8_t u8Red,
    uint8_t u8Green,
    uint8_t u8Blue);

STATIC void RgbLed_CreatePwmArray(void);

/**
 * Static variables
 */

STATIC BOOL bNewEntry = FALSE;
STATIC RgbLed_t saRgbLeds[TOTAL_LEDS];
STATIC uint8_t au8EncodedColors[TOTAL_LEDS];
STATIC uint16_t au16PwmData[PWM_DATA_SIZE];

/**
 * Implementation
 */

STATIC void
RgbLed_SetLed(
    uint8_t u8LedIndex,
    uint8_t u8Red,
    uint8_t u8Green,
    uint8_t u8Blue)
{
    saRgbLeds[u8LedIndex].u8Index = u8LedIndex;
    saRgbLeds[u8LedIndex].u8Red = u8Red;
    saRgbLeds[u8LedIndex].u8Green = u8Green;
    saRgbLeds[u8LedIndex].u8Blue = u8Blue;
}

STATIC void RgbLed_CreatePwmArray(void)
{
    // Loop through all the entries of
}

STATIC void RgbLed_DecodeColors(void)
{
    // Decode the colors and map them to the RgbLed struct array
    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        saRgbLeds[u8Index].u8Index = u8Index;
        switch (au8EncodedColors[u8Index])
        {
        // Red
        case LIGHTEFFECTS_LED_RED_HIGH:
            RgbLed_SetLed(u8Index,
                          LED_BRIGHTNESS_HIGH,
                          LED_BRIGHTNESS_OFF,
                          LED_BRIGHTNESS_OFF);
            break;

        case LIGHTEFFECTS_LED_RED_MID:
            RgbLed_SetLed(u8Index,
                          LED_BRIGHTNESS_MEDIUM,
                          LED_BRIGHTNESS_OFF,
                          LED_BRIGHTNESS_OFF);
            break;

        case LIGHTEFFECTS_LED_RED_LOW:
            RgbLed_SetLed(u8Index,
                          LED_BRIGHTNESS_LOW,
                          LED_BRIGHTNESS_OFF,
                          LED_BRIGHTNESS_OFF);
            break;

        // Green
        case LIGHTEFFECTS_LED_GREEN_HIGH:
            RgbLed_SetLed(u8Index,
                          LED_BRIGHTNESS_OFF,
                          LED_BRIGHTNESS_HIGH,
                          LED_BRIGHTNESS_OFF);
            break;

        case LIGHTEFFECTS_LED_GREEN_MID:
            RgbLed_SetLed(u8Index,
                          LED_BRIGHTNESS_OFF,
                          LED_BRIGHTNESS_MEDIUM,
                          LED_BRIGHTNESS_OFF);
            break;

        case LIGHTEFFECTS_LED_GREEN_LOW:
            RgbLed_SetLed(u8Index,
                          LED_BRIGHTNESS_OFF,
                          LED_BRIGHTNESS_LOW,
                          LED_BRIGHTNESS_OFF);
            break;

        // Blue
        case LIGHTEFFECTS_LED_BLUE_HIGH:
            RgbLed_SetLed(u8Index,
                          LED_BRIGHTNESS_OFF,
                          LED_BRIGHTNESS_OFF,
                          LED_BRIGHTNESS_HIGH);
            break;

        case LIGHTEFFECTS_LED_BLUE_MID:
            RgbLed_SetLed(u8Index,
                          LED_BRIGHTNESS_OFF,
                          LED_BRIGHTNESS_OFF,
                          LED_BRIGHTNESS_MEDIUM);
            break;

        case LIGHTEFFECTS_LED_BLUE_LOW:
            RgbLed_SetLed(u8Index,
                          LED_BRIGHTNESS_OFF,
                          LED_BRIGHTNESS_OFF,
                          LED_BRIGHTNESS_LOW);
            break;

        // White
        case LIGHTEFFECTS_LED_WHITE_HIGH:
            RgbLed_SetLed(u8Index,
                          LED_BRIGHTNESS_HIGH,
                          LED_BRIGHTNESS_HIGH,
                          LED_BRIGHTNESS_HIGH);
            break;

        case LIGHTEFFECTS_LED_WHITE_MID:
            RgbLed_SetLed(u8Index,
                          LED_BRIGHTNESS_MEDIUM,
                          LED_BRIGHTNESS_MEDIUM,
                          LED_BRIGHTNESS_MEDIUM);
            break;

        case LIGHTEFFECTS_LED_WHITE_LOW:
            RgbLed_SetLed(u8Index,
                          LED_BRIGHTNESS_LOW,
                          LED_BRIGHTNESS_LOW,
                          LED_BRIGHTNESS_LOW);
            break;

        // Off
        case LIGHTEFFECTS_LED_OFF:
            RgbLed_SetLed(u8Index,
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
            au8EncodedColors[i] = in_tMessage.au8DataBytes[i];
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

    // Clear the RgbLed Array
    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        saRgbLeds[u8Index].u8Index = 0;
        saRgbLeds[u8Index].u8Red = 0;
        saRgbLeds[u8Index].u8Green = 0;
        saRgbLeds[u8Index].u8Blue = 0;
    }

    // Clear the encoded colors array
    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        au8EncodedColors[u8Index] = 0;
    }

    // Clear the new entry flag
    bNewEntry = FALSE;
}

void RgbLed_execute(void)
{
    // if a new entry arrives

    // Clear the flag

    // Take the array copy and replace the values with rgb values
}
