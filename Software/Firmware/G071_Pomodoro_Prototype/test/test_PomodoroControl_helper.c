#include "PomodoroControl_helper.h"
#include "unity.h"
#include <stdio.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void helper_printArray(uint8_t *in_au8Array, uint8_t in_u8ArraySize)
{
    /**
     * This function prints the index of the array next to the value line by line
     * Example:
     * 0 - 0
     * 1 - 2
     * 2 - 2
     * 3 - 2
     * ...
     */
    for (uint8_t i = 0; i < in_u8ArraySize; i++)
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

void test_getMinuteArrayFromConfig(void)
{
    const uint8_t WORKTIME = 51;
    const uint8_t BREAKTIME = 17;

    PomodoroControl_helper sTestData;
    sTestData.u8Worktime = WORKTIME;
    sTestData.u8Breaktime = BREAKTIME;

    PomodoroControl_helper_getMinuteArrayFromConfig(&sTestData);

    helper_printArray((uint8_t *)&sTestData.au8MinuteArray, MAX_NOF_POMODORO_MINUTES);
}
