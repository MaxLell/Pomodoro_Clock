#include "build/test/mocks/mock_RgbLed.h"
#include "User/LightControl/LightControl.h"
#include "User/Common/Config.h"
#include "User/Common/Common.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


void setUp(void)

{

}



void tearDown(void)

{

}



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



void test_LightControl_fillMinuteToColorArray_Test4()

{







    uint8_t u8TestCurrentMinute = 17;

    uint8_t u8TestWorktimeIntervalMin = 50;

    uint8_t u8TestBreaktimeIntervalMin = 7;

    uint8_t au8TestMinuteToColorArray[60] = {0};



    LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);





    for (uint8_t u8Index = 0; u8Index < 7; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_RED)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 7; u8Index < 14; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_GREEN)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 14; u8Index < 17; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(67), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 17; u8Index < 60; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_RED)), (UNITY_INT)((au8TestMinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_INT);

    }

}













void test_LightControl_fillMinuteToColorArray_Test6()

{

    uint8_t u8TestCurrentMinute = 61;

    uint8_t u8TestWorktimeIntervalMin = 0;

    uint8_t u8TestBreaktimeIntervalMin = 0;

    uint8_t au8TestMinuteToColorArray[60] = {0};



    uint8_t u8Status = LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    UnityAssertEqualNumber((UNITY_INT)(((4))), (UNITY_INT)((u8Status)), (((void*)0)), (UNITY_UINT)(95), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_fillMinuteToColorArray_Test7()

{

    uint8_t u8TestCurrentMinute = 0;

    uint8_t u8TestWorktimeIntervalMin = 61;

    uint8_t u8TestBreaktimeIntervalMin = 0;

    uint8_t au8TestMinuteToColorArray[60] = {0};



    uint8_t u8Status = LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    UnityAssertEqualNumber((UNITY_INT)(((4))), (UNITY_INT)((u8Status)), (((void*)0)), (UNITY_UINT)(116), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_fillMinuteToColorArray_Test8()

{

    uint8_t u8TestCurrentMinute = 0;

    uint8_t u8TestWorktimeIntervalMin = 10;

    uint8_t u8TestBreaktimeIntervalMin = 60;

    uint8_t au8TestMinuteToColorArray[60] = {0};



    uint8_t u8Status = LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    UnityAssertEqualNumber((UNITY_INT)(((4))), (UNITY_INT)((u8Status)), (((void*)0)), (UNITY_UINT)(137), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_fillMinuteToColorArray_Test9()

{

    uint8_t u8TestCurrentMinute = 0;

    uint8_t u8TestWorktimeIntervalMin = 67;

    uint8_t u8TestBreaktimeIntervalMin = 10;

    uint8_t au8TestMinuteToColorArray[60] = {0};



    uint8_t u8Status = LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    UnityAssertEqualNumber((UNITY_INT)(((4))), (UNITY_INT)((u8Status)), (((void*)0)), (UNITY_UINT)(158), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_fillLedToColorArray_Test11()

{

    uint8_t u8TestCurrentMinute = 0;

    uint8_t u8TestWorktimeIntervalMin = 30;

    uint8_t u8TestBreaktimeIntervalMin = 20;

    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t au8TestLedToColorArray[24] = {0};



    LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    LightControl_fillLedToColorArray(au8TestMinuteToColorArray, au8TestLedToColorArray);



    float u8LedsPerMinute = (float)24 / (float)60;



    for (float i = 0; i < 60; i++)

    {

        uint8_t index = (uint8_t)(i * u8LedsPerMinute);

        UnityAssertEqualNumber((UNITY_INT)((au8TestMinuteToColorArray[(uint8_t)i])), (UNITY_INT)((au8TestLedToColorArray[index])), (((void*)0)), (UNITY_UINT)(187), UNITY_DISPLAY_STYLE_INT);

    }

}















void test_LightControl_removeColorsFromMinuteArray_Test12()

{

    uint8_t u8TestCurrentMinute = 0;

    uint8_t u8TestWorktimeIntervalMin = 30;

    uint8_t u8TestBreaktimeIntervalMin = 20;

    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t au8TestLedToColorArray[24] = {0};



    LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    LightControl_removeColorsFromMinuteArray(au8TestMinuteToColorArray, u8TestCurrentMinute);

    UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8TestCurrentMinute])), (((void*)0)), (UNITY_UINT)(212), UNITY_DISPLAY_STYLE_INT);





    u8TestCurrentMinute = 12;

    LightControl_removeColorsFromMinuteArray(au8TestMinuteToColorArray, u8TestCurrentMinute);

    UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[u8TestCurrentMinute])), (((void*)0)), (UNITY_UINT)(217), UNITY_DISPLAY_STYLE_INT);

}















void test_LightControl_removeColorsFromMinuteArray_Test13()

{

    uint8_t u8TestCurrentMinute = 25;

    uint8_t u8TestWorktimeIntervalMin = 30;

    uint8_t u8TestBreaktimeIntervalMin = 20;

    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t au8TestLedToColorArray[24] = {0};



    LightControl_fillMinuteToColorArray(

        u8TestCurrentMinute,

        u8TestWorktimeIntervalMin,

        u8TestBreaktimeIntervalMin,

        au8TestMinuteToColorArray);



    for (uint8_t i = 0; i < 60; i++)

    {

        LightControl_removeColorsFromMinuteArray(au8TestMinuteToColorArray, i);

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8TestMinuteToColorArray[i])), (((void*)0)), (UNITY_UINT)(243), UNITY_DISPLAY_STYLE_INT);

    }

}











extern uint8_t u8WorktimeIntervalMin;

extern uint8_t u8BreaktimeIntervalMin;

void test_LightControl_init_should_SetWorktimeAndBreaktimeInterval()

{

    uint8_t u8CurrentTime = 10;



    LightControl_init(u8CurrentTime);



    UnityAssertEqualNumber((UNITY_INT)((50)), (UNITY_INT)((u8WorktimeIntervalMin)), (((void*)0)), (UNITY_UINT)(259), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((10)), (UNITY_INT)((u8BreaktimeIntervalMin)), (((void*)0)), (UNITY_UINT)(260), UNITY_DISPLAY_STYLE_INT);

}











extern uint8_t au8MinuteToColorArray[60];

void test_LightControl_init_should_FillMinuteToColorArray()

{

    uint8_t u8CurrentTime = 15;









    for (uint8_t i = 0; i < 60; i++)

    {

        au8MinuteToColorArray[i] = 0;

    }



    LightControl_init(u8CurrentTime);





    for (uint8_t i = 0; i < 60; i++)

    {

        do {if (((0) != (au8MinuteToColorArray[i]))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(285)));}} while(0);

    }

}











extern uint8_t u8SequenceCounter;

void test_LightControl_init_should_SetSequenceCounter()

{

    uint8_t u8CurrentTime = 15;



    LightControl_init(u8CurrentTime);



    uint8_t u8Breaktime;

    uint8_t u8Worktime;

    Config_getBreaktime(&u8Breaktime);

    Config_getWorktime(&u8Worktime);



    UnityAssertEqualNumber((UNITY_INT)((u8SequenceCounter)), (UNITY_INT)((u8Breaktime + u8Worktime)), (((void*)0)), (UNITY_UINT)(305), UNITY_DISPLAY_STYLE_INT);

}











extern BOOL bSequenceWasInitialized;

void test_LightControl_init_should_SetSequenceInitializedFlagToTrue()

{

    uint8_t u8CurrentTime = 15;

    bSequenceWasInitialized = 0;



    LightControl_init(u8CurrentTime);



    do {if ((bSequenceWasInitialized)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(320)));}} while(0);

}











extern uint8_t au8LedToColorArray[24];

void test_LightControl_endSequence_should_TurnOffAllLeds()

{

    for (uint8_t i = 0; i < 24; i++)

    {

        au8LedToColorArray[i] = LIGHTCONTROL_LED_GREEN;

    }



    RgbLed_SetLedToColor_CMockIgnore();



    LightControl_endSequence();



    for (uint8_t i = 0; i < 24; i++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8LedToColorArray[i])), (((void*)0)), (UNITY_UINT)(341), UNITY_DISPLAY_STYLE_INT);

    }

}











void test_LightControl_endSequence_should_SetSequenceInitializedFlagToFalse()

{

    bSequenceWasInitialized = 1;



    RgbLed_SetLedToColor_CMockIgnore();



    LightControl_endSequence();



    do {if (!(bSequenceWasInitialized)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(357)));}} while(0);

}













void test_LightControl_endSequence_should_SetSequenceCounterToZero()

{

    u8SequenceCounter = 10;

    RgbLed_SetLedToColor_CMockIgnore();

    LightControl_endSequence();

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((u8SequenceCounter)), (((void*)0)), (UNITY_UINT)(370), UNITY_DISPLAY_STYLE_INT);

}
