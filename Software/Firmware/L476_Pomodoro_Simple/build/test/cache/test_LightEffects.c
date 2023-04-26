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

    for (uint8_t i = 0;

         i < in_u8ArraySize;

         i++)

    {

        if (i < 10)

        {

            printf("%d ---> %d\n", i, in_au8Array[i]);

        }

        else if ((i < 100) && (i >= 10))

        {

            printf("%d --> %d\n", i, in_au8Array[i]);

        }

        else

        {

            printf("%d -> %d\n", i, in_au8Array[i]);

        }



        if (i == 59)

        {

            printf("##########\n");

        }

    }

}

void test_LightEffects_initMinuteToLedConfigArray_should_InitTwoRingsProperlyVariationOne(void)

{

    uint8_t u8TestCurrentMinute = 20;

    uint8_t u8TestWorktimeIntervalMin = 75;

    uint8_t u8TestBreaktimeIntervalMin = 30;



    uint8_t au8TestMinuteToColorArray[(60 * 2)] = {0};



    LightEffects_initMinuteToLedConfigArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);







    uint8_t u8RedLowCount = 0;

    uint8_t u8GreenLowCount = 0;

    uint8_t u8LedOffCount = 0;



    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_RED_LOW)

        {

            u8RedLowCount++;

        }

        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_GREEN_LOW)

        {

            u8GreenLowCount++;

        }

    }



    UnityAssertEqualNumber((UNITY_INT)((u8TestWorktimeIntervalMin)), (UNITY_INT)((u8RedLowCount)), (((void*)0)), (UNITY_UINT)(197), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((u8TestBreaktimeIntervalMin)), (UNITY_INT)((u8GreenLowCount)), (((void*)0)), (UNITY_UINT)(198), UNITY_DISPLAY_STYLE_INT);





    for (uint8_t u8Index = 0; u8Index < 60; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(203), UNITY_DISPLAY_STYLE_INT);

    }



    for (uint8_t u8Index = 60; u8Index < (60 * 2); u8Index++)

    {



        if (u8Index < 65)

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(211), UNITY_DISPLAY_STYLE_INT);

        }



        if ((u8Index >= 65) && (u8Index < 80))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(216), UNITY_DISPLAY_STYLE_INT);

        }





        if ((u8Index >= 80) && (u8Index < 95))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(222), UNITY_DISPLAY_STYLE_INT);

        }





        if ((u8Index >= 95) && (u8Index < 120))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(228), UNITY_DISPLAY_STYLE_INT);

        }

    }

}



void test_LightEffects_initMinuteToLedConfigArray_should_InitTwoRingsProperlyVariationTwo(void)

{

    uint8_t u8TestCurrentMinute = 50;

    uint8_t u8TestWorktimeIntervalMin = 50;

    uint8_t u8TestBreaktimeIntervalMin = 50;



    uint8_t au8TestMinuteToColorArray[(60 * 2)] = {0};



    LightEffects_initMinuteToLedConfigArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);







    uint8_t u8RedLowCount = 0;

    uint8_t u8GreenLowCount = 0;



    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_RED_LOW)

        {

            u8RedLowCount++;

        }

        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_GREEN_LOW)

        {

            u8GreenLowCount++;

        }

    }



    UnityAssertEqualNumber((UNITY_INT)((u8TestWorktimeIntervalMin)), (UNITY_INT)((u8RedLowCount)), (((void*)0)), (UNITY_UINT)(273), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((u8TestBreaktimeIntervalMin)), (UNITY_INT)((u8GreenLowCount)), (((void*)0)), (UNITY_UINT)(274), UNITY_DISPLAY_STYLE_INT);





    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if (u8Index < 40)

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(281), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 40) && (u8Index < 50))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(285), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 50) && (u8Index < 60))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(289), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 60) && (u8Index <= 90))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(293), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 90) && (u8Index <= 110))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(297), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 110) && (u8Index < 120))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(301), UNITY_DISPLAY_STYLE_INT);

        }

    }

}



void test_LightEffects_initMinuteToLedConfigArray_should_InitTwoRingsProperlyVariationThree(void)

{

    uint8_t u8TestCurrentMinute = 20;

    uint8_t u8TestWorktimeIntervalMin = 50;

    uint8_t u8TestBreaktimeIntervalMin = 10;



    uint8_t au8TestMinuteToColorArray[(60 * 2)] = {0};



    LightEffects_initMinuteToLedConfigArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);







    uint8_t u8RedLowCount = 0;

    uint8_t u8GreenLowCount = 0;



    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_RED_LOW)

        {

            u8RedLowCount++;

        }

        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_GREEN_LOW)

        {

            u8GreenLowCount++;

        }

    }



    UnityAssertEqualNumber((UNITY_INT)((u8TestWorktimeIntervalMin)), (UNITY_INT)((u8RedLowCount)), (((void*)0)), (UNITY_UINT)(346), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((u8TestBreaktimeIntervalMin)), (UNITY_INT)((u8GreenLowCount)), (((void*)0)), (UNITY_UINT)(347), UNITY_DISPLAY_STYLE_INT);





    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if ((u8Index >= 0) && (u8Index < 10))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(354), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 10) && (u8Index < 20))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(358), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 20) && (u8Index < 60))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(362), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 60) && (u8Index < 120))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(366), UNITY_DISPLAY_STYLE_INT);

        }

    }

}



void test_LightEffects_initMinuteToLedConfigArray_should_InitTwoRingsProperlyVariationFour(void)

{

    uint8_t u8TestCurrentMinute = 10;

    uint8_t u8TestWorktimeIntervalMin = 52;

    uint8_t u8TestBreaktimeIntervalMin = 18;



    uint8_t au8TestMinuteToColorArray[(60 * 2)] = {0};



    LightEffects_initMinuteToLedConfigArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);







    uint8_t u8RedLowCount = 0;

    uint8_t u8GreenLowCount = 0;



    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_RED_LOW)

        {

            u8RedLowCount++;

        }

        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_GREEN_LOW)

        {

            u8GreenLowCount++;

        }

    }



    UnityAssertEqualNumber((UNITY_INT)((u8TestWorktimeIntervalMin)), (UNITY_INT)((u8RedLowCount)), (((void*)0)), (UNITY_UINT)(411), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((u8TestBreaktimeIntervalMin)), (UNITY_INT)((u8GreenLowCount)), (((void*)0)), (UNITY_UINT)(412), UNITY_DISPLAY_STYLE_INT);



    helper_printArray(au8TestMinuteToColorArray, (60 * 2));





    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if ((u8Index >= 0) && (u8Index < 2))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(421), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 2) && (u8Index < 10))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(425), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 10) && (u8Index < 60))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(429), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 71) && (u8Index < 81))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(433), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 81) && (u8Index < 120))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(437), UNITY_DISPLAY_STYLE_INT);

        }

    }

}
