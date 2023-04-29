#include "User/Config/Config.h"
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



extern void LightEffects_createAndPublishLedArray(

    uint8_t in_u8DailyPomodoroScore,

    uint8_t *in_au8MinuteToLedConfig);



extern void LightEffects_updateMinuteToLedArray(

    uint8_t in_u8CurrentMinute,

    uint8_t *inout_au8MinuteToLedConfigArray);



extern void LightEffects_WorktimeEntryFunction();



extern void LightEffects_BreaktimeEntryFunction();



extern uint8_t au8TestPublishedLedArray[(24 + 16 + 8)];

extern uint8_t au8MinuteToLedConfigArray[(60 * 2)];

extern uint8_t u8CurrentMinute;



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

    printf("\n");

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



    UnityAssertEqualNumber((UNITY_INT)((u8TestWorktimeIntervalMin)), (UNITY_INT)((u8RedLowCount)), (((void*)0)), (UNITY_UINT)(131), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((u8TestBreaktimeIntervalMin)), (UNITY_INT)((u8GreenLowCount)), (((void*)0)), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_INT);





    for (uint8_t u8Index = 0; u8Index < 60; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(137), UNITY_DISPLAY_STYLE_INT);

    }



    for (uint8_t u8Index = 60; u8Index < (60 * 2); u8Index++)

    {



        if (u8Index < 65)

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(145), UNITY_DISPLAY_STYLE_INT);

        }



        if ((u8Index >= 65) && (u8Index < 80))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(150), UNITY_DISPLAY_STYLE_INT);

        }





        if ((u8Index >= 80) && (u8Index < 95))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(156), UNITY_DISPLAY_STYLE_INT);

        }





        if ((u8Index >= 95) && (u8Index < 120))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(162), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((UNITY_INT)((u8TestWorktimeIntervalMin)), (UNITY_INT)((u8RedLowCount)), (((void*)0)), (UNITY_UINT)(207), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((u8TestBreaktimeIntervalMin)), (UNITY_INT)((u8GreenLowCount)), (((void*)0)), (UNITY_UINT)(208), UNITY_DISPLAY_STYLE_INT);





    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if (u8Index < 40)

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(215), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 40) && (u8Index < 50))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(219), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 50) && (u8Index < 60))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(223), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 60) && (u8Index <= 90))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(227), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 90) && (u8Index <= 110))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(231), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 110) && (u8Index < 120))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(235), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((UNITY_INT)((u8TestWorktimeIntervalMin)), (UNITY_INT)((u8RedLowCount)), (((void*)0)), (UNITY_UINT)(280), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((u8TestBreaktimeIntervalMin)), (UNITY_INT)((u8GreenLowCount)), (((void*)0)), (UNITY_UINT)(281), UNITY_DISPLAY_STYLE_INT);





    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if ((u8Index >= 0) && (u8Index < 10))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(288), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 10) && (u8Index < 20))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(292), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 20) && (u8Index < 60))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(296), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 60) && (u8Index < 120))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(300), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((UNITY_INT)((u8TestWorktimeIntervalMin)), (UNITY_INT)((u8RedLowCount)), (((void*)0)), (UNITY_UINT)(345), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((u8TestBreaktimeIntervalMin)), (UNITY_INT)((u8GreenLowCount)), (((void*)0)), (UNITY_UINT)(346), UNITY_DISPLAY_STYLE_INT);





    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if ((u8Index >= 0) && (u8Index < 2))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(353), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 2) && (u8Index < 10))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(357), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 10) && (u8Index < 60))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(361), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 71) && (u8Index < 81))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(365), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 81) && (u8Index < 120))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(369), UNITY_DISPLAY_STYLE_INT);

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

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestScaledOuterRing[u8Index])), (((void*)0)), (UNITY_UINT)(402), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 15) && (u8Index < 20))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestScaledOuterRing[u8Index])), (((void*)0)), (UNITY_UINT)(406), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 20) && (u8Index < 24))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestScaledOuterRing[u8Index])), (((void*)0)), (UNITY_UINT)(410), UNITY_DISPLAY_STYLE_INT);

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

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestScaledMiddleRing[u8Index])), (((void*)0)), (UNITY_UINT)(428), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 8) && (u8Index < 14))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestScaledMiddleRing[u8Index])), (((void*)0)), (UNITY_UINT)(432), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 14) && (u8Index < 16))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestScaledMiddleRing[u8Index])), (((void*)0)), (UNITY_UINT)(436), UNITY_DISPLAY_STYLE_INT);

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

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(494), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 15) && (u8Index < 20))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(498), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 20) && (u8Index < 24))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(502), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 24) && (u8Index < 32))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(506), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 32) && (u8Index < 38))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(510), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 38) && (u8Index < 40))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(514), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 40) && (u8Index < 45))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_WHITE_LOW)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(518), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 45) && (u8Index < 48))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestAssembledLEDArray[u8Index])), (((void*)0)), (UNITY_UINT)(522), UNITY_DISPLAY_STYLE_INT);

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



    MessageBroker_publish_CMockIgnoreAndReturn(542, (0));



    LightEffects_createAndPublishLedArray(

        u8TestDailyPomodoroScore,

        au8TestMinuteToColorArray);





    for (uint8_t u8Index = 0; u8Index < (24 + 16 + 8); u8Index++)

    {

        if ((u8Index >= 0) && (u8Index <= 15))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(553), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 15) && (u8Index < 20))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(557), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 20) && (u8Index < 24))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_RED_LOW)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(561), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 24) && (u8Index < 32))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(565), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index > 32) && (u8Index < 38))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(569), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 38) && (u8Index < 40))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_GREEN_LOW)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(573), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 40) && (u8Index < 45))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_WHITE_LOW)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(577), UNITY_DISPLAY_STYLE_INT);

        }

        if ((u8Index >= 45) && (u8Index < 48))

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestPublishedLedArray[u8Index])), (((void*)0)), (UNITY_UINT)(581), UNITY_DISPLAY_STYLE_INT);

        }

    }

}



void test_LightEffects_updateMinuteToLedArray_should_SwitchTheCurrentMinutesLedToOffOne(void)

{



    uint8_t u8TestCurrentMinute = 50;

    uint8_t u8TestWorktimeIntervalMin = 50;

    uint8_t u8TestBreaktimeIntervalMin = 50;

    uint8_t u8TestDailyPomodoroScore = 5;

    uint8_t au8TestMinuteToColorArray[(60 * 2)] = {0};

    uint8_t au8BeforeMinuteToLedArray[(60 * 2)] = {0};

    uint8_t au8AfterMinuteToLedArray[(60 * 2)] = {0};



    LightEffects_initMinuteToLedConfigArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    __builtin___memcpy_chk (au8BeforeMinuteToLedArray, au8TestMinuteToColorArray, (60 * 2), __builtin_object_size (au8BeforeMinuteToLedArray, 0));



    uint8_t u8TestCurrentMinuteUpdate = 0;

    LightEffects_updateMinuteToLedArray(

        u8TestCurrentMinuteUpdate,

        au8TestMinuteToColorArray);



    __builtin___memcpy_chk (au8AfterMinuteToLedArray, au8TestMinuteToColorArray, (60 * 2), __builtin_object_size (au8AfterMinuteToLedArray, 0));





    BOOL bArraysAreEqual = 1;

    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if (au8BeforeMinuteToLedArray[u8Index] != au8AfterMinuteToLedArray[u8Index])

        {

            bArraysAreEqual = 0;

        }

    }

    do {if (!(bArraysAreEqual)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(621)));}} while(0);

}



void test_LightEffects_updateMinuteToLedArray_should_SwitchTheCurrentMinutesLedToOffTwo(void)

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



    for (uint8_t u8Index = 0; u8Index < 60; u8Index++)

    {

        LightEffects_updateMinuteToLedArray(

            u8Index,

            au8TestMinuteToColorArray);

    }





    for (uint8_t u8Index = 0; u8Index < 60; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(653), UNITY_DISPLAY_STYLE_INT);

    }

}



void test_LightEffects_updateMinuteToLedArray_should_SwitchTheCurrentMinutesLedToOffThree(void)

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





    for (uint8_t u8Index = 0; u8Index < 60; u8Index++)

    {

        LightEffects_updateMinuteToLedArray(

            u8Index,

            au8TestMinuteToColorArray);

    }

    for (uint8_t u8Index = 0; u8Index < 10; u8Index++)

    {

        LightEffects_updateMinuteToLedArray(

            u8Index,

            au8TestMinuteToColorArray);

    }





    uint8_t u8RedLedCount = 0;

    uint8_t u8GreenLedCount = 0;



    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_RED_LOW)

        {

            u8RedLedCount++;

        }

        if (au8TestMinuteToColorArray[u8Index] == LIGHTEFFECTS_LED_GREEN_LOW)

        {

            u8GreenLedCount++;

        }

    }



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((u8RedLedCount)), (((void*)0)), (UNITY_UINT)(708), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((30)), (UNITY_INT)((u8GreenLedCount)), (((void*)0)), (UNITY_UINT)(709), UNITY_DISPLAY_STYLE_INT);

}



void test_LightEffects_updateMinuteToLedArray_should_SwitchTheCurrentMinutesLedToOffFour(void)

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









    for (uint8_t u8CurrentMinuteIndex = 35;

         u8CurrentMinuteIndex < 45;

         u8CurrentMinuteIndex++)

    {

        LightEffects_updateMinuteToLedArray(

            u8CurrentMinuteIndex,

            au8TestMinuteToColorArray);

    }



    for (uint8_t u8Index = 35; u8Index < 45; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(763), UNITY_DISPLAY_STYLE_INT);

    }









    for (uint8_t u8CurrentMinuteIndex = 0;

         u8CurrentMinuteIndex < 60;

         u8CurrentMinuteIndex++)

    {

        LightEffects_updateMinuteToLedArray(

            u8CurrentMinuteIndex,

            au8TestMinuteToColorArray);

    }



    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if (u8Index < 60)

        {

            UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(782), UNITY_DISPLAY_STYLE_INT);

        }

    }













    for (uint8_t u8CurrentMinuteIndex = 45;

         u8CurrentMinuteIndex < 55;

         u8CurrentMinuteIndex++)

    {

        LightEffects_updateMinuteToLedArray(

            u8CurrentMinuteIndex,

            au8TestMinuteToColorArray);

    }





    for (uint8_t u8Index = 105; u8Index < 115; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTEFFECTS_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(803), UNITY_DISPLAY_STYLE_INT);

    }

}



void test_LightEffects_worktimeEntryFunction_should_initializeTheMinuteArray(void)

{

    uint8_t u8TestCurrentMinute = 50;

    uint8_t u8TestWorktimeIntervalMin = 0;

    uint8_t u8TestBreaktimeIntervalMin = 0;



    Config_getWorktime(&u8TestWorktimeIntervalMin);

    Config_getBreaktime(&u8TestBreaktimeIntervalMin);



    UnityAssertEqualNumber((UNITY_INT)((50)), (UNITY_INT)((u8TestWorktimeIntervalMin)), (((void*)0)), (UNITY_UINT)(816), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((10)), (UNITY_INT)((u8TestBreaktimeIntervalMin)), (((void*)0)), (UNITY_UINT)(817), UNITY_DISPLAY_STYLE_INT);



    uint8_t au8TestMinuteToColorArrayManual[(60 * 2)] = {0};



    LightEffects_initMinuteToLedConfigArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArrayManual);





    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        au8MinuteToLedConfigArray[u8Index] = 0;

    }



    u8CurrentMinute = 50;

    LightEffects_WorktimeEntryFunction();





    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        UnityAssertEqualIntArray(( const void*)((au8TestMinuteToColorArrayManual)), ( const void*)((au8MinuteToLedConfigArray)), (UNITY_UINT32)(((60 * 2))), (((void*)0)), (UNITY_UINT)(842), UNITY_DISPLAY_STYLE_CHAR, UNITY_ARRAY_TO_ARRAY);







    }

}



void test_LightEffects_breaktimeEntryFunction_should_replaceAllGreenLowLedsWithGreenHighLedsAndSwitchOffAllRedLeds(void)

{

    uint8_t u8TestCurrentMinute = 50;

    uint8_t u8TestWorktimeIntervalMin = 0;

    uint8_t u8TestBreaktimeIntervalMin = 0;



    Config_getWorktime(&u8TestWorktimeIntervalMin);

    Config_getBreaktime(&u8TestBreaktimeIntervalMin);



    UnityAssertEqualNumber((UNITY_INT)((50)), (UNITY_INT)((u8TestWorktimeIntervalMin)), (((void*)0)), (UNITY_UINT)(855), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((10)), (UNITY_INT)((u8TestBreaktimeIntervalMin)), (((void*)0)), (UNITY_UINT)(856), UNITY_DISPLAY_STYLE_INT);



    LightEffects_initMinuteToLedConfigArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8MinuteToLedConfigArray);





    LightEffects_BreaktimeEntryFunction();











    uint8_t u8GreenLowLedCounter = 0;

    uint8_t u8RedLowLedCounter = 0;

    uint8_t u8GreenHighLedCounter = 0;



    for (uint8_t u8Index = 0; u8Index < (60 * 2); u8Index++)

    {

        if (au8MinuteToLedConfigArray[u8Index] == LIGHTEFFECTS_LED_GREEN_LOW)

        {

            u8GreenLowLedCounter++;

        }

        else if (au8MinuteToLedConfigArray[u8Index] == LIGHTEFFECTS_LED_RED_LOW)

        {

            u8RedLowLedCounter++;

        }

        else if (au8MinuteToLedConfigArray[u8Index] == LIGHTEFFECTS_LED_GREEN_HIGH)

        {

            u8GreenHighLedCounter++;

        }

    }



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((u8GreenLowLedCounter)), (((void*)0)), (UNITY_UINT)(891), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((u8RedLowLedCounter)), (((void*)0)), (UNITY_UINT)(892), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((10)), (UNITY_INT)((u8GreenHighLedCounter)), (((void*)0)), (UNITY_UINT)(893), UNITY_DISPLAY_STYLE_INT);

}
