#include "unity.h"
#include "mock_MessageBroker.h"
#include "RgbLed.h"
#include "Config.h"
#include "Common.h"
#include "LightEffects_Interface.h"

/**
 * Static external functions
 */
extern status_t RgbLed_callback(MessageBroker_message_t in_tMessage);
extern void RgbLed_DecodeColors(void);
extern void RgbLed_SetLed(
    uint8_t u8LedIndex,
    uint8_t u8Red,
    uint8_t u8Green,
    uint8_t u8Blue);

/**
 * Static external variables
 */
extern BOOL bNewEntry;
extern RgbLed_t saRgbLeds[TOTAL_LEDS];
extern uint8_t au8EncodedColors[TOTAL_LEDS];

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * Test cases
 */

void test_RgbLed_Init_ShallSubscribeToTopic(void)
{
    MessageBroker_subscribe_ExpectAndReturn(
        E_TOPIC_RING_LEDS_OUTPUT,
        RgbLed_callback,
        STATUS_OK);

    RgbLed_init();
}

void test_RgbLed_Init_ShallClearRgbLedArray(void)
{
    MessageBroker_subscribe_IgnoreAndReturn(STATUS_OK);

    // Fill the array with some values
    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        saRgbLeds[u8Index].u8Index = u8Index;
        saRgbLeds[u8Index].u8Red = u8Index;
        saRgbLeds[u8Index].u8Green = u8Index;
        saRgbLeds[u8Index].u8Blue = u8Index;
    }

    RgbLed_init();

    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        TEST_ASSERT_EQUAL_UINT8(0, saRgbLeds[u8Index].u8Index);
        TEST_ASSERT_EQUAL_UINT8(0, saRgbLeds[u8Index].u8Red);
        TEST_ASSERT_EQUAL_UINT8(0, saRgbLeds[u8Index].u8Green);
        TEST_ASSERT_EQUAL_UINT8(0, saRgbLeds[u8Index].u8Blue);
    }
}

void test_RgbLed_Init_ShallClearEncodedColorsArray(void)
{
    MessageBroker_subscribe_IgnoreAndReturn(STATUS_OK);

    // Fill the array with some values
    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        au8EncodedColors[u8Index] = u8Index;
    }

    RgbLed_init();

    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        TEST_ASSERT_EQUAL_UINT8(0, au8EncodedColors[u8Index]);
    }
}

void test_RgbLed_Init_ShallSetNewEntryFlagToFalse(void)
{
    MessageBroker_subscribe_IgnoreAndReturn(STATUS_OK);

    bNewEntry = TRUE;

    RgbLed_init();

    TEST_ASSERT_FALSE(bNewEntry);
}

void test_RgbLed_Callback_ShallCopyIncomingArrayIntoEncodedColorsArray(void)
{
    MessageBroker_message_t tMessage;
    tMessage.eMsgTopic = E_TOPIC_RING_LEDS_OUTPUT;
    tMessage.u16DataSize = TOTAL_LEDS;
    uint8_t au8DataBytes[TOTAL_LEDS] = {0};
    tMessage.au8DataBytes = au8DataBytes;

    // Fill the array with some values
    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        tMessage.au8DataBytes[u8Index] = u8Index;
    }

    RgbLed_callback(tMessage);

    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        TEST_ASSERT_EQUAL_UINT8(u8Index, au8EncodedColors[u8Index]);
    }
}

void test_RgbLed_Callback_ShallSetNewEntryFlagToTrue(void)
{
    MessageBroker_message_t tMessage;
    tMessage.eMsgTopic = E_TOPIC_RING_LEDS_OUTPUT;
    tMessage.u16DataSize = TOTAL_LEDS;
    uint8_t au8DataBytes[TOTAL_LEDS] = {0};
    tMessage.au8DataBytes = au8DataBytes;

    RgbLed_callback(tMessage);

    TEST_ASSERT_TRUE(bNewEntry);
}

void test_RgbLed_DecodeColors_ShallMapEncodedColorsToRgbColors(void)
{
    // Fill the array with some values
    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        au8EncodedColors[u8Index] = LIGHTEFFECTS_LED_GREEN_LOW;
    }

    RgbLed_DecodeColors();

    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        TEST_ASSERT_EQUAL_UINT8(LED_BRIGHTNESS_OFF, saRgbLeds[u8Index].u8Red);
        TEST_ASSERT_EQUAL_UINT8(LED_BRIGHTNESS_LOW, saRgbLeds[u8Index].u8Green);
        TEST_ASSERT_EQUAL_UINT8(LED_BRIGHTNESS_OFF, saRgbLeds[u8Index].u8Blue);
    }

    // Fill the array with High White values
    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        au8EncodedColors[u8Index] = LIGHTEFFECTS_LED_WHITE_HIGH;
    }

    RgbLed_DecodeColors();

    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        TEST_ASSERT_EQUAL_UINT8(LED_BRIGHTNESS_HIGH, saRgbLeds[u8Index].u8Red);
        TEST_ASSERT_EQUAL_UINT8(LED_BRIGHTNESS_HIGH, saRgbLeds[u8Index].u8Green);
        TEST_ASSERT_EQUAL_UINT8(LED_BRIGHTNESS_HIGH, saRgbLeds[u8Index].u8Blue);
    }
}

void test_RgbLed_SetLed_should_SetOneLed(void)
{
    // Reset the RgbLed Struct
    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        saRgbLeds[u8Index].u8Index = 0;
        saRgbLeds[u8Index].u8Red = 0;
        saRgbLeds[u8Index].u8Green = 0;
        saRgbLeds[u8Index].u8Blue = 0;
    }

    RgbLed_SetLed(0, 0, 0, 0);
    TEST_ASSERT_EQUAL_UINT8(0, saRgbLeds[0].u8Index);
    TEST_ASSERT_EQUAL_UINT8(0, saRgbLeds[0].u8Red);
    TEST_ASSERT_EQUAL_UINT8(0, saRgbLeds[0].u8Green);
    TEST_ASSERT_EQUAL_UINT8(0, saRgbLeds[0].u8Blue);

    RgbLed_SetLed(1, 20, 50, 100);
    TEST_ASSERT_EQUAL_UINT8(1, saRgbLeds[1].u8Index);
    TEST_ASSERT_EQUAL_UINT8(20, saRgbLeds[1].u8Red);
    TEST_ASSERT_EQUAL_UINT8(50, saRgbLeds[1].u8Green);
    TEST_ASSERT_EQUAL_UINT8(100, saRgbLeds[1].u8Blue);
}

// /*
// Translate the RgbLed Struct into the PWM Signal Array
// void WS2812_Send(void)
// {
//   uint32_t j = 0;
//   uint32_t color;

//   for (int i = 0; i < TOTAL_LEDS; i++)
//   {

// Translate the RGB Values into a 24 Bit Color Value
//     color = ((LED_Data[i][1] << 16) | // green
//             (LED_Data[i][2] << 8) |  // red
//             (LED_Data[i][3]));       // blue

//     for (int8_t i = 23; i >= 0; i--)
//     {
//       if (color & (1 << i))
//       {
//         pwmData[j] = WS2812_HIGH_BIT;
//       }
//       else
//       {
//         pwmData[j] = WS2812_LOW_BIT;
//       }
//       j++;
//     }
//   }

// // Insert 50 NULL Values in there - Sequence completed
// for (uint8_t i = 0; i < 50; i++)
// {
//     pwmData[j] = WS2812_OFF;
//     j++;
// }

// HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, j);

// while (!dataIsSent)
// {
//     // Do nothing
// }
// dataIsSent = 0;
// }
// */

void test_RgbLed_CreatePwmArray_should_CreatePwmArray(void)
{
}
