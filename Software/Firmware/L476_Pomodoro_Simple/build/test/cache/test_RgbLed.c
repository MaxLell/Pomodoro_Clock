#include "build/test/mocks/mock_RgbLed_Hardware.h"
#include "User/LightEffects/LightEffects_Interface.h"
#include "User/Common/Common.h"
#include "User/Config/Config.h"
#include "User/RgbLed/RgbLed.h"
#include "build/test/mocks/mock_MessageBroker.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"










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









extern BOOL bNewEntry;

extern uint8_t au8ColorArray[(24 + 16 + 8)];



void setUp(void)

{

}



void tearDown(void)

{

}











void test_RgbLed_Init_ShallSubscribeToTopic(void)

{

    MessageBroker_subscribe_CMockExpectAndReturn(71, E_TOPIC_RING_LEDS_OUTPUT, RgbLed_callback, (0));









    RgbLed_init();

}



void test_RgbLed_Init_ShallClearEncodedColorsArray(void)

{

    MessageBroker_subscribe_CMockIgnoreAndReturn(78, (0));





    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        au8ColorArray[u8Index] = u8Index;

    }



    RgbLed_init();



    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((au8ColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_UINT8);

    }

}



void test_RgbLed_Init_ShallSetNewEntryFlagToFalse(void)

{

    MessageBroker_subscribe_CMockIgnoreAndReturn(96, (0));



    bNewEntry = 1;



    RgbLed_init();



    do {if (!(bNewEntry)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(102)));}} while(0);

}



void test_RgbLed_Callback_ShallCopyIncomingArrayIntoEncodedColorsArray(void)

{

    MessageBroker_message_t tMessage;

    tMessage.eMsgTopic = E_TOPIC_RING_LEDS_OUTPUT;

    tMessage.u16DataSize = (24 + 16 + 8);

    uint8_t au8DataBytes[(24 + 16 + 8)] = {0};

    tMessage.au8DataBytes = au8DataBytes;





    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        tMessage.au8DataBytes[u8Index] = u8Index;

    }



    RgbLed_callback(tMessage);



    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((u8Index)), (UNITY_INT)(UNITY_UINT8 )((au8ColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(123), UNITY_DISPLAY_STYLE_UINT8);

    }

}



void test_RgbLed_Callback_ShallSetNewEntryFlagToTrue(void)

{

    MessageBroker_message_t tMessage;

    tMessage.eMsgTopic = E_TOPIC_RING_LEDS_OUTPUT;

    tMessage.u16DataSize = (24 + 16 + 8);

    uint8_t au8DataBytes[(24 + 16 + 8)] = {0};

    tMessage.au8DataBytes = au8DataBytes;



    RgbLed_callback(tMessage);



    do {if ((bNewEntry)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(137)));}} while(0);

}



void test_RgbLed_SetLed_should_SetOneLed(void)

{

    RgbLed_t tRgbLed = {0};



    RgbLed_SetLedRgbValues(&tRgbLed, 1, 2, 3, 4);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((tRgbLed.u8Index)), (((void*)0)), (UNITY_UINT)(146), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2)), (UNITY_INT)(UNITY_UINT8 )((tRgbLed.u8Red)), (((void*)0)), (UNITY_UINT)(147), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((3)), (UNITY_INT)(UNITY_UINT8 )((tRgbLed.u8Green)), (((void*)0)), (UNITY_UINT)(148), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((4)), (UNITY_INT)(UNITY_UINT8 )((tRgbLed.u8Blue)), (((void*)0)), (UNITY_UINT)(149), UNITY_DISPLAY_STYLE_UINT8);

}



void test_RgbLed_DecodeColorsToRgbValues_should_DecodeOneLed(void)

{

    uint8_t au8ColorArray[2] = {LIGHTEFFECTS_LED_BLUE_HIGH, LIGHTEFFECTS_LED_GREEN_LOW};

    RgbLed_t saRgbLeds[2] = {0};



    RgbLed_DecodeColorsToRgbValues(au8ColorArray, saRgbLeds, 2);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[0].u8Index)), (((void*)0)), (UNITY_UINT)(159), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[0].u8Red)), (((void*)0)), (UNITY_UINT)(160), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[0].u8Green)), (((void*)0)), (UNITY_UINT)(161), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[0].u8Blue)), (((void*)0)), (UNITY_UINT)(162), UNITY_DISPLAY_STYLE_UINT8);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[1].u8Index)), (((void*)0)), (UNITY_UINT)(164), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[1].u8Red)), (((void*)0)), (UNITY_UINT)(165), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((10)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[1].u8Green)), (((void*)0)), (UNITY_UINT)(166), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[1].u8Blue)), (((void*)0)), (UNITY_UINT)(167), UNITY_DISPLAY_STYLE_UINT8);

}



void test_RgbLed_EncodeRgbValuesToColors_should_EncodeOneLed(void)

{

    RgbLed_t saRgbLeds[2] = {0};

    saRgbLeds[0].u8Index = 0;

    saRgbLeds[0].u8Red = 0;

    saRgbLeds[0].u8Green = 0;

    saRgbLeds[0].u8Blue = 255;



    saRgbLeds[1].u8Index = 1;

    saRgbLeds[1].u8Red = 255;

    saRgbLeds[1].u8Green = 0;

    saRgbLeds[1].u8Blue = 0;



    uint32_t au32BitArray[2] = {0};



    RgbLed_EncodeRgbValuesTo24Bit(saRgbLeds, au32BitArray, 2);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((0x000000FF)), (UNITY_INT)(UNITY_INT32)((au32BitArray[0])), (((void*)0)), (UNITY_UINT)(187), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((0x00FF0000)), (UNITY_INT)(UNITY_INT32)((au32BitArray[1])), (((void*)0)), (UNITY_UINT)(188), UNITY_DISPLAY_STYLE_HEX32);

}



void test_RgbLed_PlaceRgbLed24BitDataInPwmDataArray_should_Transform2Leds(void)

{

    uint32_t au32BitArray[1] = {0x000000FF};



    uint16_t au16PwmData[24] = {0};



    RgbLed_PlaceRgbLed24BitDataInPwmDataArray(au32BitArray, au16PwmData, 1, 24);





    for (uint8_t u8Index = 0; u8Index < 24; u8Index++)

    {

        if (u8Index < 8)

        {

            UnityAssertEqualNumber((UNITY_INT)((60)), (UNITY_INT)((au16PwmData[u8Index])), (((void*)0)), (UNITY_UINT)(204), UNITY_DISPLAY_STYLE_INT);

        }

        else

        {

            UnityAssertEqualNumber((UNITY_INT)((30)), (UNITY_INT)((au16PwmData[u8Index])), (((void*)0)), (UNITY_UINT)(208), UNITY_DISPLAY_STYLE_INT);

        }

    }

}



void test_RgbLed_PlaceEndOfFrameInPwmDataArray_should_PlaceEndOfFrame(void)

{



    uint32_t au32BitArray[1] = {0x00FFFFFF};

    uint16_t au16PwmData[74] = {0};

    au16PwmData[60] = 11;

    RgbLed_PlaceRgbLed24BitDataInPwmDataArray(au32BitArray, au16PwmData, 1, 74);





    RgbLed_PlaceEndOfSequenceInPwmDataArray(au16PwmData, 74);





    for (uint8_t u8Index = 24; u8Index < 74; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0)), (UNITY_INT)(UNITY_UINT16)((au16PwmData[u8Index])), (((void*)0)), (UNITY_UINT)(227), UNITY_DISPLAY_STYLE_UINT16);

    }

}



void test_RgbLed_BuildRgbLedSequence_should_BuildASequence(void)

{

    uint8_t au8ColorArray[1] = {LIGHTEFFECTS_LED_BLUE_HIGH};

    uint16_t au16PwmData[74] = {0};



    RgbLed_BuildRgbLedSequence(au8ColorArray, 1, au16PwmData, 74);





    for (uint8_t i = 0; i < 74; i++)

    {

        if (i < 8)

        {

            UnityAssertEqualNumber((UNITY_INT)((60)), (UNITY_INT)((au16PwmData[i])), (((void*)0)), (UNITY_UINT)(243), UNITY_DISPLAY_STYLE_INT);

        }

        else if (i < 24)

        {

            UnityAssertEqualNumber((UNITY_INT)((30)), (UNITY_INT)((au16PwmData[i])), (((void*)0)), (UNITY_UINT)(247), UNITY_DISPLAY_STYLE_INT);

        }

        else if (i < 60)

        {

            UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((au16PwmData[i])), (((void*)0)), (UNITY_UINT)(251), UNITY_DISPLAY_STYLE_INT);

        }

    }

}
