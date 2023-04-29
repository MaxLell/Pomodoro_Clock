#include "User/LightEffects/LightEffects_Interface.h"
#include "User/Common/Common.h"
#include "User/Config/Config.h"
#include "User/RgbLed/RgbLed.h"
#include "build/test/mocks/mock_MessageBroker.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"










extern status_t RgbLed_callback(MessageBroker_message_t in_tMessage);

extern void RgbLed_DecodeColors(void);

extern void RgbLed_SetLed(

    uint8_t u8LedIndex,

    uint8_t u8Red,

    uint8_t u8Green,

    uint8_t u8Blue);









extern BOOL bNewEntry;

extern RgbLed_t saRgbLeds[(24 + 16 + 8)];

extern uint8_t au8EncodedColors[(24 + 16 + 8)];



void setUp(void)

{

}



void tearDown(void)

{

}











void test_RgbLed_Init_ShallSubscribeToTopic(void)

{

    MessageBroker_subscribe_CMockExpectAndReturn(43, E_TOPIC_RING_LEDS_OUTPUT, RgbLed_callback, (0));









    RgbLed_init();

}



void test_RgbLed_Init_ShallClearRgbLedArray(void)

{

    MessageBroker_subscribe_CMockIgnoreAndReturn(50, (0));





    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        saRgbLeds[u8Index].u8Index = u8Index;

        saRgbLeds[u8Index].u8Red = u8Index;

        saRgbLeds[u8Index].u8Green = u8Index;

        saRgbLeds[u8Index].u8Blue = u8Index;

    }



    RgbLed_init();



    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[u8Index].u8Index)), (((void*)0)), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_UINT8);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[u8Index].u8Red)), (((void*)0)), (UNITY_UINT)(66), UNITY_DISPLAY_STYLE_UINT8);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[u8Index].u8Green)), (((void*)0)), (UNITY_UINT)(67), UNITY_DISPLAY_STYLE_UINT8);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[u8Index].u8Blue)), (((void*)0)), (UNITY_UINT)(68), UNITY_DISPLAY_STYLE_UINT8);

    }

}



void test_RgbLed_Init_ShallClearEncodedColorsArray(void)

{

    MessageBroker_subscribe_CMockIgnoreAndReturn(74, (0));





    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        au8EncodedColors[u8Index] = u8Index;

    }



    RgbLed_init();



    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((au8EncodedColors[u8Index])), (((void*)0)), (UNITY_UINT)(86), UNITY_DISPLAY_STYLE_UINT8);

    }

}



void test_RgbLed_Init_ShallSetNewEntryFlagToFalse(void)

{

    MessageBroker_subscribe_CMockIgnoreAndReturn(92, (0));



    bNewEntry = 1;



    RgbLed_init();



    do {if (!(bNewEntry)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(98)));}} while(0);

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

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((u8Index)), (UNITY_INT)(UNITY_UINT8 )((au8EncodedColors[u8Index])), (((void*)0)), (UNITY_UINT)(119), UNITY_DISPLAY_STYLE_UINT8);

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



    do {if ((bNewEntry)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(133)));}} while(0);

}



void test_RgbLed_DecodeColors_ShallMapEncodedColorsToRgbColors(void)

{



    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        au8EncodedColors[u8Index] = LIGHTEFFECTS_LED_GREEN_LOW;

    }



    RgbLed_DecodeColors();



    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[u8Index].u8Red)), (((void*)0)), (UNITY_UINT)(148), UNITY_DISPLAY_STYLE_UINT8);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((10)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[u8Index].u8Green)), (((void*)0)), (UNITY_UINT)(149), UNITY_DISPLAY_STYLE_UINT8);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[u8Index].u8Blue)), (((void*)0)), (UNITY_UINT)(150), UNITY_DISPLAY_STYLE_UINT8);

    }





    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        au8EncodedColors[u8Index] = LIGHTEFFECTS_LED_WHITE_HIGH;

    }



    RgbLed_DecodeColors();



    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[u8Index].u8Red)), (((void*)0)), (UNITY_UINT)(163), UNITY_DISPLAY_STYLE_UINT8);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[u8Index].u8Green)), (((void*)0)), (UNITY_UINT)(164), UNITY_DISPLAY_STYLE_UINT8);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[u8Index].u8Blue)), (((void*)0)), (UNITY_UINT)(165), UNITY_DISPLAY_STYLE_UINT8);

    }

}



void test_RgbLed_SetLed_should_SetOneLed(void)

{



    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        saRgbLeds[u8Index].u8Index = 0;

        saRgbLeds[u8Index].u8Red = 0;

        saRgbLeds[u8Index].u8Green = 0;

        saRgbLeds[u8Index].u8Blue = 0;

    }



    RgbLed_SetLed(0, 0, 0, 0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[0].u8Index)), (((void*)0)), (UNITY_UINT)(181), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[0].u8Red)), (((void*)0)), (UNITY_UINT)(182), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[0].u8Green)), (((void*)0)), (UNITY_UINT)(183), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[0].u8Blue)), (((void*)0)), (UNITY_UINT)(184), UNITY_DISPLAY_STYLE_UINT8);



    RgbLed_SetLed(1, 20, 50, 100);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[1].u8Index)), (((void*)0)), (UNITY_UINT)(187), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((20)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[1].u8Red)), (((void*)0)), (UNITY_UINT)(188), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((50)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[1].u8Green)), (((void*)0)), (UNITY_UINT)(189), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((100)), (UNITY_INT)(UNITY_UINT8 )((saRgbLeds[1].u8Blue)), (((void*)0)), (UNITY_UINT)(190), UNITY_DISPLAY_STYLE_UINT8);

}

void test_RgbLed_CreatePwmArray_should_CreatePwmArray(void)

{

}
