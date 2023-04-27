#include "User/Common/Config.h"
#include "User/LightEffects/LightEffects_Interface.h"
#include "build/test/mocks/mock_MessageBroker.h"
#include "User/LightEffects/LightEffects.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




extern void LightEffects_initMinuteToLedConfigArray(uint8_t in_u8CurrentMinute,

                                                    uint8_t in_u8WorktimeIntervalMin,

                                                    uint8_t in_u8BreaktimeIntervalMin,

                                                    uint8_t *inout_au8ColorArray);



extern void LightEffects_removeColorsFromMinuteArray(uint8_t *inout_au8MinuteToColorArray,

                                                     uint8_t in_u8CurrentMinute);



extern void LightEffects_setLedsToColor(uint8_t *in_au8LedToColorArray);



extern void LightEffects_scaleArray(

    uint8_t *in_au8SourceArray, uint8_t in_u8SourceArraySize,

    uint8_t *inout_au8TargetArray, uint8_t in_u8TargetArraySize);



extern void LightEffects_assembleLEDArray(

    uint8_t *in_au8OuterRingArray, uint8_t in_u8OuterRingArraySize,

    uint8_t *in_au8MiddleRingArray, uint8_t in_u8MiddleRingArraySize,

    uint8_t *in_au8InnerRingArray, uint8_t in_u8InnerRingArraySize,

    uint8_t *inout_au8AssembledLEDArray, uint8_t in_u8AssembledLEDArraySize);



extern void LightEffects_setScoreToArray(

    uint8_t in_u8Score,

    uint8_t *inout_au8ScoreArray,

    uint8_t in_u8ScoreArraySize);



extern void LightEffect_createAndPublishLedArray(

    uint8_t in_u8DailyPomodoroScore,

    uint8_t *in_au8MinuteToLedConfig);



extern uint8_t au8TestPublishedLedArray[(24 + 16 + 8)];



void setUp(void)

{

}



void tearDown(void)

{

}











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



    UnityAssertEqualNumber((UNITY_INT)((u8TestWorktimeIntervalMin)), (UNITY_INT)((u8RedLowCount)), (((void*)0)), (UNITY_UINT)(122), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((u8TestBreaktimeIntervalMin)), (UNITY_INT)((u8GreenLowCount)), (((void*)0)), (UNITY_UINT)(123), UNITY_DISPLAY_STYLE_INT);





    for (uint8_t u8Index = 0; u8Index < 60; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(128), UNITY_DISPLAY_STYLE_INT);

    }



    for (uint8_t u8Index = 60; u8Index < (60 * 2); u8Index++)

    {



        if (u8Index < 65)

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(136), UNITY_DISPLAY_STYLE_INT);

        }



        if ((u8Index >= 65) && (u8Index < 80))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(141), UNITY_DISPLAY_STYLE_INT);

        }





        if ((u8Index >= 80) && (u8Index < 95))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(147), UNITY_DISPLAY_STYLE_INT);

        }





        if ((u8Index >= 95) && (u8Index < 120))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(153), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((UNITY_INT)((u8TestWorktimeIntervalMin)), (UNITY_INT)((u8RedLowCount)), (((void*)0)), (UNITY_UINT)(198), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((u8TestBreaktimeIntervalMin)), (UNITY_INT)((u8GreenLowCount)), (((void*)0)), (UNITY_UINT)(199), UNITY_DISPLAY_STYLE_INT);





    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if (u8Index < 40)

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(206), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 40) && (u8Index < 50))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(210), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 50) && (u8Index < 60))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(214), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 60) && (u8Index <= 90))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(218), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 90) && (u8Index <= 110))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(222), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 110) && (u8Index < 120))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(226), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((UNITY_INT)((u8TestWorktimeIntervalMin)), (UNITY_INT)((u8RedLowCount)), (((void*)0)), (UNITY_UINT)(271), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((u8TestBreaktimeIntervalMin)), (UNITY_INT)((u8GreenLowCount)), (((void*)0)), (UNITY_UINT)(272), UNITY_DISPLAY_STYLE_INT);





    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if ((u8Index >= 0) && (u8Index < 10))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(279), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 10) && (u8Index < 20))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(283), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 20) && (u8Index < 60))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(287), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 60) && (u8Index < 120))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(291), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((UNITY_INT)((u8TestWorktimeIntervalMin)), (UNITY_INT)((u8RedLowCount)), (((void*)0)), (UNITY_UINT)(336), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((u8TestBreaktimeIntervalMin)), (UNITY_INT)((u8GreenLowCount)), (((void*)0)), (UNITY_UINT)(337), UNITY_DISPLAY_STYLE_INT);





    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if ((u8Index >= 0) && (u8Index < 2))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(344), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 2) && (u8Index < 10))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(348), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 10) && (u8Index < 60))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(352), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 71) && (u8Index < 81))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(356), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 81) && (u8Index < 120))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(360), UNITY_DISPLAY_STYLE_INT);

        }

    }

}



void test_LightEffects_scaleArray_should_scaleMinuteToColorArray(void)

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



    uint8_t au8TestOuterRing[60] = {0};



    __builtin___memcpy_chk (au8TestOuterRing, au8TestMinuteToColorArray, 60, __builtin_object_size (au8TestOuterRing, 0));



    uint8_t au8TestScaledOuterRing[24] = {0};

    LightEffects_scaleArray(

        au8TestOuterRing, 60,

        au8TestScaledOuterRing, 24);





    for (uint8_t u8Index = 0; u8Index < 24; u8Index++)

    {

        if ((u8Index >= 0) && (u8Index <= 15))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestScaledOuterRing[u8Index])), (((void*)0)), (UNITY_UINT)(393), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 15) && (u8Index < 20))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestScaledOuterRing[u8Index])), (((void*)0)), (UNITY_UINT)(397), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 20) && (u8Index < 24))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestScaledOuterRing[u8Index])), (((void*)0)), (UNITY_UINT)(401), UNITY_DISPLAY_STYLE_INT);

        }

    }



    uint8_t au8TestMiddleRing[60] = {0};



    __builtin___memcpy_chk (au8TestMiddleRing, &au8TestMinuteToColorArray[60], 60, __builtin_object_size (au8TestMiddleRing, 0));



    uint8_t au8TestScaledMiddleRing[16] = {0};

    LightEffects_scaleArray(

        au8TestMiddleRing, 60,

        au8TestScaledMiddleRing, 16);





    for (uint8_t u8Index = 0; u8Index < 16; u8Index++)

    {

        if ((u8Index >= 0) && (u8Index <= 8))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestScaledMiddleRing[u8Index])), (((void*)0)), (UNITY_UINT)(419), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 8) && (u8Index < 14))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestScaledMiddleRing[u8Index])), (((void*)0)), (UNITY_UINT)(423), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 14) && (u8Index < 16))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestScaledMiddleRing[u8Index])), (((void*)0)), (UNITY_UINT)(427), UNITY_DISPLAY_STYLE_INT);

        }

    }

}



void test_LightEffects_assembleLEDArray_should_GenerateOneArrayForAllLedRings(void)

{



    uint8_t u8TestCurrentMinute = 50;

    uint8_t u8TestWorktimeIntervalMin = 50;

    uint8_t u8TestBreaktimeIntervalMin = 50;

    uint8_t u8TestDailyPomodoroScore = 5;



    uint8_t au8TestOuterRing[60] = {0};

    uint8_t au8TestScaledOuterRing[24] = {0};

    uint8_t au8TestMiddleRing[60] = {0};

    uint8_t au8TestScaledMiddleRing[16] = {0};

    uint8_t au8TestInnerRing[8] = {0};

    uint8_t au8TestAssembledLEDArray[(24 + 16 + 8)] = {0};



    uint8_t au8TestMinuteToColorArray[(60 * 2)] = {0};





    LightEffects_initMinuteToLedConfigArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);





    __builtin___memcpy_chk (au8TestOuterRing, au8TestMinuteToColorArray, 60, __builtin_object_size (au8TestOuterRing, 0));

    LightEffects_scaleArray(

        au8TestOuterRing, 60,

        au8TestScaledOuterRing, 24);





    __builtin___memcpy_chk (au8TestMiddleRing, &au8TestMinuteToColorArray[60], 60, __builtin_object_size (au8TestMiddleRing, 0));

    LightEffects_scaleArray(

        au8TestMiddleRing, 60,

        au8TestScaledMiddleRing, 16);





    LightEffects_setScoreToArray(

        u8TestDailyPomodoroScore,

        au8TestInnerRing,

        8);



    LightEffects_assembleLEDArray(

        au8TestScaledOuterRing, 24,

        au8TestScaledMiddleRing, 16,

        au8TestInnerRing, 8,

        au8TestAssembledLEDArray, (24 + 16 + 8));





    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        if ((u8Index >= 0) && (u8Index <= 15))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(485), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 15) && (u8Index < 20))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(489), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 20) && (u8Index < 24))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(493), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 24) && (u8Index < 32))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(497), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 32) && (u8Index < 38))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(501), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 38) && (u8Index < 40))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(505), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 40) && (u8Index < 45))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_WHITE_LOW)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(509), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 45) && (u8Index < 48))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(513), UNITY_DISPLAY_STYLE_INT);

        }

    }

}



void test_LightEffects_createAndPublishOutputLedArray_should_TakeInAllSubArraysAndCreateOneOutputArrayAndPublishIt(void)

{



    uint8_t u8TestCurrentMinute = 50;

    uint8_t u8TestWorktimeIntervalMin = 50;

    uint8_t u8TestBreaktimeIntervalMin = 50;

    uint8_t u8TestDailyPomodoroScore = 5;

    uint8_t au8TestMinuteToColorArray[(60 * 2)] = {0};



    LightEffects_initMinuteToLedConfigArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    MessageBroker_publish_CMockIgnoreAndReturn(533, (0));



    LightEffect_createAndPublishLedArray(

        u8TestDailyPomodoroScore,

        au8TestMinuteToColorArray);





    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        if ((u8Index >= 0) && (u8Index <= 15))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(544), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 15) && (u8Index < 20))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(548), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 20) && (u8Index < 24))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(552), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 24) && (u8Index < 32))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(556), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 32) && (u8Index < 38))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(560), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 38) && (u8Index < 40))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(564), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 40) && (u8Index < 45))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_WHITE_LOW)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(568), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 45) && (u8Index < 48))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(572), UNITY_DISPLAY_STYLE_INT);

        }

    }

}
