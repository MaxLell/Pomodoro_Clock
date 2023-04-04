#include "build/test/mocks/mock_RgbLed.h"
#include "User/LightControl/LightControl.h"
#include "User/Common/Common.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


uint8_t au8MinuteToColorArray[60] = {0};

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



void test_LightControl_fillMinuteToColorArray_Test1()

{







    uint8_t u8CurrentMinute = 0;

    uint8_t u8WorktimeIntervalMin = 0;

    uint8_t u8BreaktimeIntervalMin = 0;

    uint8_t au8MinuteToColorArray[60] = {0};



    LightControl_fillMinuteToColorArray(

        u8CurrentMinute,

        u8WorktimeIntervalMin,

        u8BreaktimeIntervalMin,

        au8MinuteToColorArray);





    for (uint8_t u8Index = 0; u8Index < 60; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(102), UNITY_DISPLAY_STYLE_INT);

    }

}

void test_LightControl_fillMinuteToColorArray_Test2()

{







    uint8_t u8CurrentMinute = 0;

    uint8_t u8WorktimeIntervalMin = 1;

    uint8_t u8BreaktimeIntervalMin = 0;

    uint8_t au8MinuteToColorArray[60] = {0};



    LightControl_fillMinuteToColorArray(

        u8CurrentMinute,

        u8WorktimeIntervalMin,

        u8BreaktimeIntervalMin,

        au8MinuteToColorArray);





    for (uint8_t u8Index = 0; u8Index < 1; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_RED)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(124), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 2; u8Index < 60; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(130), UNITY_DISPLAY_STYLE_INT);

    }

}



void test_LightControl_fillMinuteToColorArray_Test3()

{







    uint8_t u8CurrentMinute = 0;

    uint8_t u8WorktimeIntervalMin = 1;

    uint8_t u8BreaktimeIntervalMin = 1;

    uint8_t au8MinuteToColorArray[60] = {0};



    LightControl_fillMinuteToColorArray(

        u8CurrentMinute,

        u8WorktimeIntervalMin,

        u8BreaktimeIntervalMin,

        au8MinuteToColorArray);





    for (uint8_t u8Index = 0; u8Index < 1; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_RED)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(153), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 1; u8Index < 2; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_GREEN)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(159), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 2; u8Index < 60; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(165), UNITY_DISPLAY_STYLE_INT);

    }

}



void test_LightControl_fillMinuteToColorArray_Test4()

{







    uint8_t u8CurrentMinute = 17;

    uint8_t u8WorktimeIntervalMin = 50;

    uint8_t u8BreaktimeIntervalMin = 7;

    uint8_t au8MinuteToColorArray[60] = {0};



    LightControl_fillMinuteToColorArray(

        u8CurrentMinute,

        u8WorktimeIntervalMin,

        u8BreaktimeIntervalMin,

        au8MinuteToColorArray);





    for (uint8_t u8Index = 0; u8Index < 7; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_RED)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(188), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 7; u8Index < 14; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_GREEN)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(194), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 14; u8Index < 17; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(200), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 17; u8Index < 60; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_RED)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(206), UNITY_DISPLAY_STYLE_INT);

    }

}



void test_LightControl_fillMinuteToColorArray_Test5()

{





    uint8_t u8CurrentMinute = 59;

    uint8_t u8WorktimeIntervalMin = 10;

    uint8_t u8BreaktimeIntervalMin = 0;

    uint8_t au8MinuteToColorArray[60] = {0};



    LightControl_fillMinuteToColorArray(

        u8CurrentMinute,

        u8WorktimeIntervalMin,

        u8BreaktimeIntervalMin,

        au8MinuteToColorArray);





    for (uint8_t u8Index = 0; u8Index < 9; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_RED)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(228), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = 9; u8Index < u8CurrentMinute; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(234), UNITY_DISPLAY_STYLE_INT);

    }

}











void test_LightControl_fillMinuteToColorArray_Test6()

{

    uint8_t u8CurrentMinute = 61;

    uint8_t u8WorktimeIntervalMin = 0;

    uint8_t u8BreaktimeIntervalMin = 0;

    uint8_t au8MinuteToColorArray[60] = {0};



    uint8_t u8Status = LightControl_fillMinuteToColorArray(

        u8CurrentMinute,

        u8WorktimeIntervalMin,

        u8BreaktimeIntervalMin,

        au8MinuteToColorArray);



    UnityAssertEqualNumber((UNITY_INT)(((4))), (UNITY_INT)((u8Status)), (((void*)0)), (UNITY_UINT)(255), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_fillMinuteToColorArray_Test7()

{

    uint8_t u8CurrentMinute = 0;

    uint8_t u8WorktimeIntervalMin = 61;

    uint8_t u8BreaktimeIntervalMin = 0;

    uint8_t au8MinuteToColorArray[60] = {0};



    uint8_t u8Status = LightControl_fillMinuteToColorArray(

        u8CurrentMinute,

        u8WorktimeIntervalMin,

        u8BreaktimeIntervalMin,

        au8MinuteToColorArray);



    UnityAssertEqualNumber((UNITY_INT)(((4))), (UNITY_INT)((u8Status)), (((void*)0)), (UNITY_UINT)(276), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_fillMinuteToColorArray_Test8()

{

    uint8_t u8CurrentMinute = 0;

    uint8_t u8WorktimeIntervalMin = 10;

    uint8_t u8BreaktimeIntervalMin = 60;

    uint8_t au8MinuteToColorArray[60] = {0};



    uint8_t u8Status = LightControl_fillMinuteToColorArray(

        u8CurrentMinute,

        u8WorktimeIntervalMin,

        u8BreaktimeIntervalMin,

        au8MinuteToColorArray);



    UnityAssertEqualNumber((UNITY_INT)(((4))), (UNITY_INT)((u8Status)), (((void*)0)), (UNITY_UINT)(297), UNITY_DISPLAY_STYLE_INT);

}













void test_LightControl_fillMinuteToColorArray_Test9()

{

    uint8_t u8CurrentMinute = 0;

    uint8_t u8WorktimeIntervalMin = 67;

    uint8_t u8BreaktimeIntervalMin = 10;

    uint8_t au8MinuteToColorArray[60] = {0};



    uint8_t u8Status = LightControl_fillMinuteToColorArray(

        u8CurrentMinute,

        u8WorktimeIntervalMin,

        u8BreaktimeIntervalMin,

        au8MinuteToColorArray);



    UnityAssertEqualNumber((UNITY_INT)(((4))), (UNITY_INT)((u8Status)), (((void*)0)), (UNITY_UINT)(318), UNITY_DISPLAY_STYLE_INT);

}











void test_LightControl_fillMinuteToColorArray_Test10()

{

    uint8_t u8CurrentMinute = 20;

    uint8_t u8WorktimeIntervalMin = 10;

    uint8_t u8BreaktimeIntervalMin = 10;

    uint8_t au8MinuteToColorArray[60] = {0};



    LightControl_fillMinuteToColorArray(

        u8CurrentMinute,

        u8WorktimeIntervalMin,

        u8BreaktimeIntervalMin,

        au8MinuteToColorArray);





    for (uint8_t u8Index = 0; u8Index < u8CurrentMinute; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(341), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = u8CurrentMinute; u8Index < u8CurrentMinute + u8WorktimeIntervalMin; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_RED)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(347), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = u8CurrentMinute + u8WorktimeIntervalMin; u8Index < u8CurrentMinute + u8WorktimeIntervalMin + u8BreaktimeIntervalMin; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_GREEN)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(353), UNITY_DISPLAY_STYLE_INT);

    }





    for (uint8_t u8Index = u8CurrentMinute + u8WorktimeIntervalMin + u8BreaktimeIntervalMin; u8Index < 60; u8Index++)

    {

        UnityAssertEqualNumber((UNITY_INT)((LIGHTCONTROL_LED_OFF)), (UNITY_INT)((au8MinuteToColorArray[u8Index])), (((void*)0)), (UNITY_UINT)(359), UNITY_DISPLAY_STYLE_INT);

    }

}















void test_LightControl_fillLedToColorArray_Test11()

{

    uint8_t u8CurrentMinute = 0;

    uint8_t u8WorktimeIntervalMin = 30;

    uint8_t u8BreaktimeIntervalMin = 20;

    uint8_t au8MinuteToColorArray[60] = {0};

    uint8_t au8LedToColorArray[24] = {0};



    LightControl_fillMinuteToColorArray(

        u8CurrentMinute,

        u8WorktimeIntervalMin,

        u8BreaktimeIntervalMin,

        au8MinuteToColorArray);



    LightControl_fillLedToColorArray(au8MinuteToColorArray, au8LedToColorArray);



    float u8LedsPerMinute = (float)24 / (float)60;



    for (float i = 0; i < 60; i++)

    {

        uint8_t index = (uint8_t)(i * u8LedsPerMinute);

        UnityAssertEqualNumber((UNITY_INT)((au8MinuteToColorArray[(uint8_t)i])), (UNITY_INT)((au8LedToColorArray[index])), (((void*)0)), (UNITY_UINT)(390), UNITY_DISPLAY_STYLE_INT);

    }

}















void test_LightControl_setLedsToColor_Test12()

{







    uint8_t u8CurrentMinute = 0;

    uint8_t u8WorktimeIntervalMin = 30;

    uint8_t u8BreaktimeIntervalMin = 20;

    uint8_t au8MinuteToColorArray[60] = {0};

    uint8_t au8LedToColorArray[24] = {0};



    LightControl_fillMinuteToColorArray(

        u8CurrentMinute,

        u8WorktimeIntervalMin,

        u8BreaktimeIntervalMin,

        au8MinuteToColorArray);



    LightControl_fillLedToColorArray(au8MinuteToColorArray, au8LedToColorArray);









    RgbLed_SetLedToColor_CMockIgnore();









    LightControl_setLedsToColor(au8LedToColorArray);

}
