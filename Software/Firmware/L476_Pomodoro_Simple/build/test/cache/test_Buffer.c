#include "User/Common/Common.h"
#include "User/LightControl/Buffer.h"
#include "User/Common/Status.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"

static uint8_t test_data[(1000) + 1];

static BUFFER_T test_buffer;

void setUp(void)

{

    UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((Buffer_Init(&test_buffer, test_data, (1000) + 1))), (((void *)0)), (UNITY_UINT)(14), UNITY_DISPLAY_STYLE_INT);
}

void test_Buffer_Put_and_Get_should_WorkTogetherToInsertAndExtractAValue(void)

{

    const uint8_t data[] = {0, 1, 0x5A, 0x7F, 0xFF};

    uint8_t fetched;

    int i;

    for (i = 0; i < sizeof(data); i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((Buffer_enqueue(&test_buffer, data[i]))), (((void *)0)), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_INT);

        UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((Buffer_dequeue(&test_buffer, &fetched))), (((void *)0)), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_INT);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8)((data[i])), (UNITY_INT)(UNITY_INT8)((fetched)), (((void *)0)), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_HEX8);
    }
}

void test_Buffer_Get_should_ReturnErrorIfCalledWhenEmpty(void)

{

    uint8_t fetched;

    do
    {
        if ((((0)) != (Buffer_dequeue(&test_buffer, &fetched))))
        {
        }
        else
        {
            UnityFail(((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(35)));
        }
    } while (0);
}

void test_Buffer_Put_should_ReturnErrorIfCalledWhenFull(void)

{

    int i;

    for (i = 0; i < (1000); i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((Buffer_enqueue(&test_buffer, i))), (((void *)0)), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_INT);
    }

    do
    {
        if ((((0)) != (Buffer_enqueue(&test_buffer, 1))))
        {
        }
        else
        {
            UnityFail(((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(47)));
        }
    } while (0);
}

void test_Buffer_Get_should_ProperlyGrabEveryItemFromFullToEmpty(void)

{

    int i;

    uint8_t fetched;

    for (i = 0; i < (1000); i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((Buffer_enqueue(&test_buffer, i))), (((void *)0)), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_INT);
    }

    do
    {
        if ((((0)) != (Buffer_enqueue(&test_buffer, 1))))
        {
        }
        else
        {
            UnityFail(((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(60)));
        }
    } while (0);

    for (i = 0; i < (1000); i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((Buffer_dequeue(&test_buffer, &fetched))), (((void *)0)), (UNITY_UINT)(64), UNITY_DISPLAY_STYLE_INT);

        UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8)((i)), (UNITY_INT)(UNITY_INT8)((fetched)), (((void *)0)), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_HEX8);
    }

    do
    {
        if ((((0)) != (Buffer_dequeue(&test_buffer, &fetched))))
        {
        }
        else
        {
            UnityFail(((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(68)));
        }
    } while (0);
}

void test_Buffer_IsFull_should_ReturnTrueWhenFullOtherwiseFalse(void)

{

    int i;

    for (i = 0; i < (1000); i++)

    {

        do
        {
            if (!(Buffer_isFull(&test_buffer)))
            {
            }
            else
            {
                UnityFail(((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(77)));
            }
        } while (0);

        UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((Buffer_enqueue(&test_buffer, i))), (((void *)0)), (UNITY_UINT)(78), UNITY_DISPLAY_STYLE_INT);
    }

    do
    {
        if ((Buffer_isFull(&test_buffer)))
        {
        }
        else
        {
            UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(81)));
        }
    } while (0);

    do
    {
        if ((((0)) != (Buffer_enqueue(&test_buffer, 1))))
        {
        }
        else
        {
            UnityFail(((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(82)));
        }
    } while (0);
}

void test_Buffer_IsEmpty_should_ReturnTrueWhenEmptyOtherwiseFalse(void)

{

    int i;

    uint8_t fetched;

    do
    {
        if ((Buffer_isEmpty(&test_buffer)))
        {
        }
        else
        {
            UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(90)));
        }
    } while (0);

    for (i = 0; i < (1000); i++)

    {

        UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((Buffer_enqueue(&test_buffer, i))), (((void *)0)), (UNITY_UINT)(94), UNITY_DISPLAY_STYLE_INT);

        do
        {
            if (!(Buffer_isEmpty(&test_buffer)))
            {
            }
            else
            {
                UnityFail(((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(95)));
            }
        } while (0);
    }

    for (i = 0; i < (1000); i++)

    {

        do
        {
            if (!(Buffer_isEmpty(&test_buffer)))
            {
            }
            else
            {
                UnityFail(((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(100)));
            }
        } while (0);

        UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((Buffer_dequeue(&test_buffer, &fetched))), (((void *)0)), (UNITY_UINT)(101), UNITY_DISPLAY_STYLE_INT);
    }

    do
    {
        if ((Buffer_isEmpty(&test_buffer)))
        {
        }
        else
        {
            UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(104)));
        }
    } while (0);
}

void test_Buffer_Clear_should_ClearItIfCleared(void)

{

    do
    {
        if ((Buffer_isEmpty(&test_buffer)))
        {
        }
        else
        {
            UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(109)));
        }
    } while (0);

    Buffer_Clear(&test_buffer);

    do
    {
        if ((Buffer_isEmpty(&test_buffer)))
        {
        }
        else
        {
            UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(111)));
        }
    } while (0);
}

void test_Buffer_Clear_should_ClearItIfSomeElementsInIt(void)

{

    int i;

    do
    {
        if ((Buffer_isEmpty(&test_buffer)))
        {
        }
        else
        {
            UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(118)));
        }
    } while (0);

    Buffer_Clear(&test_buffer);

    do
    {
        if ((Buffer_isEmpty(&test_buffer)))
        {
        }
        else
        {
            UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(120)));
        }
    } while (0);

    for (i = 0; i < 3; i++)

        UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((Buffer_enqueue(&test_buffer, i))), (((void *)0)), (UNITY_UINT)(123), UNITY_DISPLAY_STYLE_INT);

    do
    {
        if (!(Buffer_isEmpty(&test_buffer)))
        {
        }
        else
        {
            UnityFail(((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(124)));
        }
    } while (0);

    Buffer_Clear(&test_buffer);

    do
    {
        if ((Buffer_isEmpty(&test_buffer)))
        {
        }
        else
        {
            UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(127)));
        }
    } while (0);
}

void test_Buffer_Clear_should_ClearItIfFull(void)

{

    int i;

    do
    {
        if ((Buffer_isEmpty(&test_buffer)))
        {
        }
        else
        {
            UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(134)));
        }
    } while (0);

    Buffer_Clear(&test_buffer);

    do
    {
        if ((Buffer_isEmpty(&test_buffer)))
        {
        }
        else
        {
            UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(136)));
        }
    } while (0);

    for (i = 0; i < (1000); i++)

        UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((Buffer_enqueue(&test_buffer, i))), (((void *)0)), (UNITY_UINT)(139), UNITY_DISPLAY_STYLE_INT);

    do
    {
        if (!(Buffer_isEmpty(&test_buffer)))
        {
        }
        else
        {
            UnityFail(((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(140)));
        }
    } while (0);

    Buffer_Clear(&test_buffer);

    do
    {
        if ((Buffer_isEmpty(&test_buffer)))
        {
        }
        else
        {
            UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(143)));
        }
    } while (0);
}
