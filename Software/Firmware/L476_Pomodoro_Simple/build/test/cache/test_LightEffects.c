#include "User/Common/Config.h"
#include "User/LightEffects/LightEffects_Interface.h"
#include "build/test/mocks/mock_MessageBroker.h"
#include "User/LightEffects/LightEffects.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}



extern void LightEffects_initMinuteToLedConfigArray(uint8_t in_u8CurrentMinute,

                                                    uint8_t in_u8WorktimeIntervalMin,

                                                    uint8_t in_u8BreaktimeIntervalMin,

                                                    uint8_t *inout_au8ColorArray);



extern void LightEffects_removeColorsFromMinuteArray(uint8_t *inout_au8MinuteToColorArray,

                                                     uint8_t in_u8CurrentMinute);



extern void LightEffects_transformMinuteToLedConfigArrayToLedConfigArray(uint8_t *in_au8MinuteToColorArray,

                                                                         uint8_t *inout_au8LedToColorArray);



extern void LightEffects_setLedsToColor(uint8_t *in_au8LedToColorArray);











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



void test_LightEffects_LightEffects_initMinuteToLedConfigArray_should_SetInitialWorkBreakAndOffConditions(void)

{





    uint8_t u8TestCurrentMinute = 17;

    uint8_t u8TestWorktimeIntervalMin = 50;

    uint8_t u8TestBreaktimeIntervalMin = 7;

    uint8_t au8TestMinuteToColorArray[60] = {0};



    LightEffects_initMinuteToLedConfigArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);





    for (uint8_t u8Index = 0; u8Index < 7; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 7; u8Index < 14; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(78), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 14; u8Index < 17; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(84), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 17; u8Index < 60; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_INT);

    }

}



void test_LightEffects_removeColorsFromMinuteArray_should_RemoveColorsAtSpecificIndexFromArray(void)

{

    uint8_t u8TestCurrentMinute = 0;

    uint8_t u8TestWorktimeIntervalMin = 30;

    uint8_t u8TestBreaktimeIntervalMin = 20;

    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t au8TestLedToColorArray[24] = {0};



    LightEffects_initMinuteToLedConfigArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    LightEffects_removeColorsFromMinuteArray(au8TestMinuteToColorArray, u8TestCurrentMinute);

    UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8TestCurrentMinute])), (((void*)0)), (UNITY_UINT)(109), UNITY_DISPLAY_STYLE_INT);





    u8TestCurrentMinute = 12;

    LightEffects_removeColorsFromMinuteArray(au8TestMinuteToColorArray, u8TestCurrentMinute);

    UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8TestCurrentMinute])), (((void*)0)), (UNITY_UINT)(114), UNITY_DISPLAY_STYLE_INT);

}



void test_LightEffects_fillLedToColorArray_Test11()

{

    uint8_t u8TestCurrentMinute = 0;

    uint8_t u8TestWorktimeIntervalMin = 30;

    uint8_t u8TestBreaktimeIntervalMin = 20;

    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t au8TestLedToColorArray[24] = {0};



    LightEffects_initMinuteToLedConfigArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    LightEffects_transformMinuteToLedConfigArrayToLedConfigArray(au8TestMinuteToColorArray, au8TestLedToColorArray);



    float u8LedsPerMinute = (float)24 / (float)60;



    for (float i = 0; i < 60; i++)

    {

        uint8_t index = (uint8_t)(i * u8LedsPerMinute);

        UnityAssertEqualNumber((UNITY_INT)((au8TestMinuteToColorArray[(uint8_t)i])), (UNITY_INT)((au8TestLedToColorArray[index])), (((void*)0)), (UNITY_UINT)(138), UNITY_DISPLAY_STYLE_INT);

    }

}
