#include "unity.h"
#include "mock_MessageBroker.h"
#include "RgbLed.h"
#include "Config.h"
#include "Common.h"
#include "LightEffects_Interface.h"
#include "mock_RgbLed_Hardware.h"

/**
 * Static external functions
 */
extern status_t RgbLed_callback(
    MessageBroker_message_t in_tMessage);

extern void RgbLed_SetLedRgbValues(
    RgbLed_t *inout_tRgbLed,
    uint8_t in_u8LedIndex,
    uint8_t in_u8Red,
    uint8_t in_u8Green,
    uint8_t in_u8Blue);

extern void RgbLed_DecodeColorsToRgbValues(
    uint8_t *in_au8ColorArray,
    RgbLed_t *out_saRgbLeds,
    uint8_t in_u8ArraySizes);

extern void RgbLed_EncodeRgbValuesTo24Bit(
    RgbLed_t *in_tRgbLed,
    uint32_t *inout_u32RgbLed24Bit,
    uint8_t in_u8ArraySizes);

extern void RgbLed_PlaceRgbLed24BitDataInPwmDataArray(
    uint32_t *in_u32RgbLed24Bit,
    uint16_t *inout_au16PwmData,
    uint8_t in_u8RgbLedArraySize,
    uint32_t in_u32PwmDataArraySize);

extern void RgbLed_PlaceEndOfSequenceInPwmDataArray(
    uint16_t *inout_au16PwmData,
    uint32_t in_u32PwmDataArraySize);

extern void RgbLed_BuildRgbLedSequence(
    uint8_t *in_au8ColorArray,
    uint8_t in_u8ColorArraySize,
    uint16_t *inout_au16PwmData,
    uint32_t in_u32PwmDataArraySize);

/**
 * Static external variables
 */
extern BOOL bNewEntry;
extern uint8_t au8ColorArray[TOTAL_LEDS];

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

void test_RgbLed_Init_ShallClearEncodedColorsArray(void)
{
    MessageBroker_subscribe_IgnoreAndReturn(STATUS_OK);

    // Fill the array with some values
    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        au8ColorArray[u8Index] = u8Index;
    }

    RgbLed_init();

    for (uint8_t u8Index = 0; u8Index < TOTAL_LEDS; u8Index++)
    {
        TEST_ASSERT_EQUAL_UINT8(0, au8ColorArray[u8Index]);
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
        TEST_ASSERT_EQUAL_UINT8(u8Index, au8ColorArray[u8Index]);
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

void test_RgbLed_SetLed_should_SetOneLed(void)
{
    RgbLed_t tRgbLed = {0};

    RgbLed_SetLedRgbValues(&tRgbLed, 1, 2, 3, 4);

    TEST_ASSERT_EQUAL_UINT8(1, tRgbLed.u8Index);
    TEST_ASSERT_EQUAL_UINT8(2, tRgbLed.u8Red);
    TEST_ASSERT_EQUAL_UINT8(3, tRgbLed.u8Green);
    TEST_ASSERT_EQUAL_UINT8(4, tRgbLed.u8Blue);
}

void test_RgbLed_DecodeColorsToRgbValues_should_DecodeOneLed(void)
{
    uint8_t au8ColorArray[2] = {LIGHTEFFECTS_LED_BLUE_HIGH, LIGHTEFFECTS_LED_GREEN_LOW};
    RgbLed_t saRgbLeds[2] = {0};

    RgbLed_DecodeColorsToRgbValues(au8ColorArray, saRgbLeds, 2);

    TEST_ASSERT_EQUAL_UINT8(LED_BRIGHTNESS_OFF, saRgbLeds[0].u8Index);
    TEST_ASSERT_EQUAL_UINT8(LED_BRIGHTNESS_OFF, saRgbLeds[0].u8Red);
    TEST_ASSERT_EQUAL_UINT8(LED_BRIGHTNESS_OFF, saRgbLeds[0].u8Green);
    TEST_ASSERT_EQUAL_UINT8(LED_BRIGHTNESS_HIGH, saRgbLeds[0].u8Blue);

    TEST_ASSERT_EQUAL_UINT8(1, saRgbLeds[1].u8Index);
    TEST_ASSERT_EQUAL_UINT8(LED_BRIGHTNESS_OFF, saRgbLeds[1].u8Red);
    TEST_ASSERT_EQUAL_UINT8(LED_BRIGHTNESS_LOW, saRgbLeds[1].u8Green);
    TEST_ASSERT_EQUAL_UINT8(LED_BRIGHTNESS_OFF, saRgbLeds[1].u8Blue);
}

void test_RgbLed_EncodeRgbValuesToColors_should_EncodeOneLed(void)
{
    RgbLed_t saRgbLeds[2] = {0};
    saRgbLeds[0].u8Index = 0;
    saRgbLeds[0].u8Red = LED_BRIGHTNESS_OFF;
    saRgbLeds[0].u8Green = LED_BRIGHTNESS_OFF;
    saRgbLeds[0].u8Blue = LED_BRIGHTNESS_HIGH;

    saRgbLeds[1].u8Index = 1;
    saRgbLeds[1].u8Red = LED_BRIGHTNESS_HIGH;
    saRgbLeds[1].u8Green = LED_BRIGHTNESS_OFF;
    saRgbLeds[1].u8Blue = LED_BRIGHTNESS_OFF;

    uint32_t au32BitArray[2] = {0};

    RgbLed_EncodeRgbValuesTo24Bit(saRgbLeds, au32BitArray, 2);

    TEST_ASSERT_EQUAL_HEX32(0x000000FF, au32BitArray[0]);
    TEST_ASSERT_EQUAL_HEX32(0x00FF0000, au32BitArray[1]);
}

void test_RgbLed_PlaceRgbLed24BitDataInPwmDataArray_should_Transform2Leds(void)
{
    uint32_t au32BitArray[1] = {0x000000FF};

    uint16_t au16PwmData[24] = {0};

    RgbLed_PlaceRgbLed24BitDataInPwmDataArray(au32BitArray, au16PwmData, 1, 24);

    // Print the pwm data array
    for (uint8_t u8Index = 0; u8Index < 24; u8Index++)
    {
        if (u8Index < 8)
        {
            TEST_ASSERT_EQUAL(WS2812_HIGH_BIT, au16PwmData[u8Index]);
        }
        else
        {
            TEST_ASSERT_EQUAL(WS2812_LOW_BIT, au16PwmData[u8Index]);
        }
    }
}

void test_RgbLed_PlaceEndOfFrameInPwmDataArray_should_PlaceEndOfFrame(void)
{
    // Prepare the data
    uint32_t au32BitArray[1] = {0x00FFFFFF};
    uint16_t au16PwmData[74] = {0};
    au16PwmData[60] = 11;
    RgbLed_PlaceRgbLed24BitDataInPwmDataArray(au32BitArray, au16PwmData, 1, 74);

    // Place the end of frame
    RgbLed_PlaceEndOfSequenceInPwmDataArray(au16PwmData, 74);

    // Test that the last 50 entries are set to 0
    for (uint8_t u8Index = 24; u8Index < 74; u8Index++)
    {
        TEST_ASSERT_EQUAL_UINT16(WS2812_OFF, au16PwmData[u8Index]);
    }
}

void test_RgbLed_BuildRgbLedSequence_should_BuildASequence(void)
{
    uint8_t au8ColorArray[1] = {LIGHTEFFECTS_LED_BLUE_HIGH};
    uint16_t au16PwmData[74] = {0};

    RgbLed_BuildRgbLedSequence(au8ColorArray, 1, au16PwmData, 74);

    // Print the pwm data array
    for (uint8_t i = 0; i < 74; i++)
    {
        if (i < 8)
        {
            TEST_ASSERT_EQUAL(WS2812_HIGH_BIT, au16PwmData[i]);
        }
        else if (i < 24)
        {
            TEST_ASSERT_EQUAL(WS2812_LOW_BIT, au16PwmData[i]);
        }
        else if (i < 60)
        {
            TEST_ASSERT_EQUAL(WS2812_OFF, au16PwmData[i]);
        }
    }
}