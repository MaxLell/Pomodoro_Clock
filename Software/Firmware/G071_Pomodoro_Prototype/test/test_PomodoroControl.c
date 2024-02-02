#include "Common.h"
#include "FSM.h"
#include "LightEffects.h"
#include "LightEffects_Pomodoro.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "PomodoroControl.h"
#include "PomodoroControl_Datatypes.h"
#include "mock_CountdownTimer.h"
#include "mock_Delay.h"
#include "mock_RgbLed.h"
#include "unity.h"

extern FSM_Config_t sFsmConfig;

extern uint8_t u8EffectArraySize;

extern uint8_t au8CompressedArrayRing1[NOF_LEDS_OUTER_RING];
extern uint8_t au8CompressedArrayRing2[NOF_LEDS_MIDDLE_RING];

extern void PomodoroControl_getMinuteArray(PCTRL_Progress_t *const inout_sSelf);
extern void PomodoroControl_updateSequence(PCTRL_Progress_t *const inout_sSelf);

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
        char stringToPrint[10] = {0};
        char caWorktime[] = "Worktime";
        char caBreaktime[] = "Breaktime";
        char caOff[] = "Off";
        switch (in_au8Array[i])
        {
        case E_CFG_WORKTIME:
            strncpy(stringToPrint, caWorktime, sizeof(caWorktime));
            break;

        case E_CFG_BREAKTIME:
            strncpy(stringToPrint, caBreaktime, sizeof(caBreaktime));
            break;

        case E_CFG_OFF:
            strncpy(stringToPrint, caOff, sizeof(caOff));
            break;

        default:
            break;
        }

        if (i < 10)
        {
            printf("%d ---> %s\n", i, stringToPrint);
        }
        else if ((i < 100) && (i >= 10))
        {
            printf("%d --> %s\n", i, stringToPrint);
        }
        else
        {
            printf("%d -> %s\n", i, stringToPrint);
        }

        if (i == 59)
        {
            printf("------------\n");
        }
    }
    printf("\n");
}

void helper_countEntriesInArray(uint8_t *const out_u8NofWorktimeEntries, uint8_t *const out_u8NofBreaktimeEntries,
                                uint8_t *const out_u8NofOffEntries, const uint8_t *const in_au8MinuteArray,
                                const uint8_t in_u8ArrSize)
{
    // reset all counter input variables
    *out_u8NofWorktimeEntries = 0;
    *out_u8NofBreaktimeEntries = 0;
    *out_u8NofOffEntries = 0;

    for (uint8_t i = 0; i < in_u8ArrSize; i++)
    {
        switch (in_au8MinuteArray[i])
        {
        case E_CFG_WORKTIME:
            (*out_u8NofWorktimeEntries)++;
            break;

        case E_CFG_BREAKTIME:
            (*out_u8NofBreaktimeEntries)++;
            break;

        case E_CFG_OFF:
            (*out_u8NofOffEntries)++;
            break;

        default:
            break;
        }
    }
}

void test_getMinuteArrayFromConfig(void)
{
    PCTRL_Progress_t sTestData;

    uint8_t WORKTIME = 51;
    uint8_t BREAKTIME = 17;
    uint8_t u8NofWorktimeEntries = 0;
    uint8_t u8NofBreaktimeEntries = 0;
    uint8_t u8NofOffEntries = 0;

    sTestData.u8Worktime = WORKTIME;
    sTestData.u8Breaktime = BREAKTIME;

    PomodoroControl_getMinuteArray(&sTestData);
    helper_countEntriesInArray(&u8NofWorktimeEntries, &u8NofBreaktimeEntries, &u8NofOffEntries,
                               (uint8_t *)&sTestData.au8MinuteArray, TOTAL_MINUTES);

    TEST_ASSERT_EQUAL(WORKTIME, u8NofWorktimeEntries);
    TEST_ASSERT_EQUAL(BREAKTIME, u8NofBreaktimeEntries);
    TEST_ASSERT_EQUAL((TOTAL_MINUTES - (WORKTIME + BREAKTIME)), u8NofOffEntries);

    WORKTIME = 1;
    BREAKTIME = 1;
    sTestData.u8Worktime = WORKTIME;
    sTestData.u8Breaktime = BREAKTIME;
    PomodoroControl_getMinuteArray(&sTestData);

    helper_countEntriesInArray(&u8NofWorktimeEntries, &u8NofBreaktimeEntries, &u8NofOffEntries,
                               (uint8_t *)&sTestData.au8MinuteArray, TOTAL_MINUTES);

    TEST_ASSERT_EQUAL(WORKTIME, u8NofWorktimeEntries);
    TEST_ASSERT_EQUAL(BREAKTIME, u8NofBreaktimeEntries);
    TEST_ASSERT_EQUAL((TOTAL_MINUTES - (WORKTIME + BREAKTIME)), u8NofOffEntries);

    WORKTIME = 25;
    BREAKTIME = 5;
    sTestData.u8Worktime = WORKTIME;
    sTestData.u8Breaktime = BREAKTIME;

    PomodoroControl_getMinuteArray(&sTestData);
    helper_countEntriesInArray(&u8NofWorktimeEntries, &u8NofBreaktimeEntries, &u8NofOffEntries,
                               (uint8_t *)&sTestData.au8MinuteArray, TOTAL_MINUTES);

    TEST_ASSERT_EQUAL(WORKTIME, u8NofWorktimeEntries);
    TEST_ASSERT_EQUAL(BREAKTIME, u8NofBreaktimeEntries);
    TEST_ASSERT_EQUAL((TOTAL_MINUTES - (WORKTIME + BREAKTIME)), u8NofOffEntries);

    WORKTIME = 90;
    BREAKTIME = 15;

    sTestData.u8Worktime = WORKTIME;
    sTestData.u8Breaktime = BREAKTIME;
    PomodoroControl_getMinuteArray(&sTestData);
    helper_countEntriesInArray(&u8NofWorktimeEntries, &u8NofBreaktimeEntries, &u8NofOffEntries,
                               (uint8_t *)&sTestData.au8MinuteArray, TOTAL_MINUTES);

    TEST_ASSERT_EQUAL(WORKTIME, u8NofWorktimeEntries);
    TEST_ASSERT_EQUAL(BREAKTIME, u8NofBreaktimeEntries);
    TEST_ASSERT_EQUAL((TOTAL_MINUTES - (WORKTIME + BREAKTIME)), u8NofOffEntries);

    WORKTIME = 90;
    BREAKTIME = 35;

    sTestData.u8Worktime = WORKTIME;
    sTestData.u8Breaktime = BREAKTIME;
    PomodoroControl_getMinuteArray(&sTestData);
    helper_countEntriesInArray(&u8NofWorktimeEntries, &u8NofBreaktimeEntries, &u8NofOffEntries,
                               (uint8_t *)&sTestData.au8MinuteArray, TOTAL_MINUTES);

    TEST_ASSERT_EQUAL(WORKTIME, u8NofWorktimeEntries);
    TEST_ASSERT_EQUAL(0, u8NofBreaktimeEntries);
    TEST_ASSERT_EQUAL((TOTAL_MINUTES - (WORKTIME)), u8NofOffEntries);

    WORKTIME = 120;
    BREAKTIME = 15;
    sTestData.u8Worktime = WORKTIME;
    sTestData.u8Breaktime = BREAKTIME;

    PomodoroControl_getMinuteArray(&sTestData);
    helper_countEntriesInArray(&u8NofWorktimeEntries, &u8NofBreaktimeEntries, &u8NofOffEntries,
                               (uint8_t *)&sTestData.au8MinuteArray, TOTAL_MINUTES);

    TEST_ASSERT_EQUAL(WORKTIME, u8NofWorktimeEntries);
    TEST_ASSERT_EQUAL(0, u8NofBreaktimeEntries);
    TEST_ASSERT_EQUAL((TOTAL_MINUTES - (WORKTIME)), u8NofOffEntries);

    // Make sure that the Worktime and Breaktime configs have not been changed
    TEST_ASSERT_EQUAL(WORKTIME, sTestData.u8Worktime);
    TEST_ASSERT_EQUAL(BREAKTIME, sTestData.u8Breaktime);
}

void test_updateArray(void)
{
    uint8_t WORKTIME = 3;
    uint8_t BREAKTIME = 2;
    uint8_t u8NofWorktimeEntries = 0;
    uint8_t u8NofBreaktimeEntries = 0;
    uint8_t u8NofOffEntries = 0;

    PCTRL_Progress_t sTestData;
    sTestData.u8Worktime = WORKTIME;
    sTestData.u8Breaktime = BREAKTIME;

    PomodoroControl_getMinuteArray(&sTestData);
    helper_countEntriesInArray(&u8NofWorktimeEntries, &u8NofBreaktimeEntries, &u8NofOffEntries,
                               (uint8_t *)&sTestData.au8MinuteArray, TOTAL_MINUTES);

    TEST_ASSERT_EQUAL(WORKTIME, u8NofWorktimeEntries);
    TEST_ASSERT_EQUAL(BREAKTIME, u8NofBreaktimeEntries);
    TEST_ASSERT_EQUAL((TOTAL_MINUTES - (WORKTIME + BREAKTIME)), u8NofOffEntries);

    PomodoroControl_updateSequence(&sTestData);
    helper_countEntriesInArray(&u8NofWorktimeEntries, &u8NofBreaktimeEntries, &u8NofOffEntries,
                               (uint8_t *)&sTestData.au8MinuteArray, TOTAL_MINUTES);

    TEST_ASSERT_EQUAL(WORKTIME - 1, u8NofWorktimeEntries);
    TEST_ASSERT_EQUAL(BREAKTIME, u8NofBreaktimeEntries);

    WORKTIME = 25;
    BREAKTIME = 5;
    sTestData.u8Worktime = WORKTIME;
    sTestData.u8Breaktime = BREAKTIME;

    PomodoroControl_getMinuteArray(&sTestData);
    for (uint8_t i = 0; i < 10; i++)
    {
        PomodoroControl_updateSequence(&sTestData);
    }

    helper_printArray((uint8_t *)&sTestData.au8MinuteArray, TOTAL_MINUTES);
}
