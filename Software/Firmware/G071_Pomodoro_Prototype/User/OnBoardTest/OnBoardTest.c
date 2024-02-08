/************************************************************
 * Includes
 ************************************************************/
#include "OnBoardTest.h"

#include "FSM.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "PomodoroControl.h"
#include "PomodoroControl_Datatypes.h"

#include "LightEffects.h"
#include "LightEffects_Pomodoro.h"

#include "RgbLed.h"
#include "RgbLed_Config.h"

#include "Score.h"

#include "CountdownTimer.h"
#include "Delay.h"

/************************************************************
 * Private Data Types
 ************************************************************/

typedef enum
{
    // Basic Tests - Lighteffects
    E_TEST_LIGHT_UP_ALL_LEDS,
    E_TEST_RGB_LED_RINGS_POMODORO_INITIAL,

    // Button Tests
    E_TEST_BUTTON,

    // Pomodoro Test
    E_TEST_POMODORO_SEQUENCE,

    // Score
    E_TEST_SCORE,

    E_LAST_TEST
} OnBoardTest_Test_e;

typedef void (*test_function_ptr)(void);

/************************************************************
 * Private Defines
 ************************************************************/
#define TEST_TO_RUN E_TEST_POMODORO_SEQUENCE

/************************************************************
 * Private Function Prototypes
 ************************************************************/

// LightEffects

void OnBoardTest_testLightUpAllLeds(void);

// Button Tests
void OnBoardTest_testButtonBehaviours(void);

// Pomodoro State Function Tests
void OnBoardTest_testNominalPomodoroSequence(void);

// Score
void OnBoardTest_testScore(void);

/************************************************************
 * Private Variables
 ************************************************************/

STATIC test_function_ptr test_functions[E_LAST_TEST] = {
    // RGB LED Tests
    [E_TEST_LIGHT_UP_ALL_LEDS] = OnBoardTest_testLightUpAllLeds,

    // Button Hardware Test
    [E_TEST_BUTTON] = OnBoardTest_testButtonBehaviours,

    // Pomodoro Tests
    [E_TEST_POMODORO_SEQUENCE] = OnBoardTest_testNominalPomodoroSequence,

    // Score System
    [E_TEST_SCORE] = OnBoardTest_testScore};

/************************************************************
 * External private variables
 ************************************************************/

extern FSM_Config_t sFsmConfig;

/************************************************************
 * Test function implementations
 ************************************************************/

void OnBoardTest_testLightUpAllLeds(void)
{
    for (uint8_t u8LedIndex = 0; u8LedIndex < TOTAL_LEDS; u8LedIndex++)
    {
        RgbLed_setPixelColor(u8LedIndex, 2, 0, 0);
    }
    RgbLed_show();
}

void OnBoardTest_testNominalPomodoroSequence(void)
{
    static BOOL bRanOnce = FALSE;
    if (!bRanOnce)
    {
        printf("%s", "************************************************************\n");
        printf("%s", "                 OnBoardTest_testNominalPomodoroSequence\n");
        printf("%s", "************************************************************\n");

        // Clear the Rings
        LightEffects_ClearAllRingLeds();

        // Delay to make a restart visible
        Delay_ms(100);

        // Initialize the Pomodoro Control
        PomodoroControl_init();

        const uint8_t WORKTIME = 51;
        const uint8_t BREAKTIME = 17;

        PomodoroPeriodConfiguration_t sPomodoroPeriodConfig = {0};
        sPomodoroPeriodConfig.u8MinutesWorktimePeriod = WORKTIME;
        sPomodoroPeriodConfig.u8MinutesBreaktimePeriod = BREAKTIME;

        // Publish the Pomodoro Config
        msg_t sMsg;
        sMsg.eMsgId = MSG_ID_0400;

        sMsg.au8DataBytes = (uint8_t *)&sPomodoroPeriodConfig;
        sMsg.u16DataSize = sizeof(PomodoroPeriodConfiguration_t);
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");

        // Publish the Pomodoro Sequence Start: Triggers the transition from IDLE to WORKTIME_INIT
        sMsg.eMsgId = MSG_ID_0200;
        eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");

        // Clear the Flag
        bRanOnce = TRUE;
    }

    // Run the CUT
    PomodoroControl_execute();
}

status_e OnBoardTest_ButtonTestMsgCb(const msg_t *const in_psMsg)
{
    { // Input Checks
        ASSERT_MSG(in_psMsg != NULL, "in_psMsg is NULL");

        // Message ID check
        ASSERT_MSG(
            !(in_psMsg->eMsgId != MSG_ID_0100 && in_psMsg->eMsgId != MSG_ID_0101 && in_psMsg->eMsgId != MSG_ID_0102),
            "Unknown Message ID: %d", in_psMsg->eMsgId);
    }

    switch (in_psMsg->eMsgId)
    {

    case MSG_ID_0100: { // Trigger Btn Pressed
        log_info("Trigger Btn was short pressed");
    }
    break;

    case MSG_ID_0101: { // Trigger Btn Long Pressed
        log_info("Trigger Btn was looooooooong Pressed");
    }
    break;

    case MSG_ID_0102: { // Trigger Btn Released
        log_info("Trigger Btn Released");
    }
    break;

    default:
        ASSERT_MSG(NULL, "Unknown Message ID: %d", in_psMsg->eMsgId);
        break;
    }

    return STATUS_SUCCESS;
}

void OnBoardTest_testButtonBehaviours(void)
{
    static BOOL bRanOnce = FALSE;
    if (bRanOnce == FALSE)
    {
        printf("%s", "************************************************************\n");
        printf("%s", "                 OnBoardTest_testButtonBehaviours\n");
        printf("%s", "************************************************************\n");

        // Clear the flag
        bRanOnce = TRUE;

        // Subsribe to the Trigger Btn pressed Message
        MessageBroker_subscribe(MSG_ID_0100, OnBoardTest_ButtonTestMsgCb);

        // Subscribe to the Trigger Btn Long press Message
        MessageBroker_subscribe(MSG_ID_0101, OnBoardTest_ButtonTestMsgCb);

        // Subscribe to the Trigger Btn Released Message
        MessageBroker_subscribe(MSG_ID_0102, OnBoardTest_ButtonTestMsgCb);
    }
}

status_e OnBoardTest_ScoreTestMsgCb(const msg_t *const in_psMsg)
{
    { // Input Checks
        ASSERT_MSG(in_psMsg != NULL, "in_psMsg is NULL");

        // Message ID check
        ASSERT_MSG(in_psMsg->eMsgId == MSG_ID_0500, "Unknown Message ID: %d", in_psMsg->eMsgId);
    }

    // Print the score
    uint32_t u32ScoreSec = in_psMsg->au8DataBytes[0] << 24 | in_psMsg->au8DataBytes[1] << 16 |
                           in_psMsg->au8DataBytes[2] << 8 | in_psMsg->au8DataBytes[3] << 0;

    // Print out the unsigned value of the score // Print an unsigned value
    log_info("Score in Seconds: %u", u32ScoreSec);

    return STATUS_SUCCESS;
}

timer_t sScoreTimer;

void OnBoardTest_testScore(void)
{
    static BOOL bRunOnce = FALSE;
    if (bRunOnce == FALSE)
    {
        printf("%s", "************************************************************\n");
        printf("%s", "                 OnBoardTest_testScore\n");
        printf("%s", "************************************************************\n");

        // Clear the flag
        bRunOnce = TRUE;

        // Set the timer
        Countdown_initTimerMs(&sScoreTimer, 5000, E_OPERATIONAL_MODE_CONTIUNOUS);
        Countdown_startTimer(&sScoreTimer);

        // Subscribe to the Score Updated Message
        MessageBroker_subscribe(MSG_ID_0500, OnBoardTest_ScoreTestMsgCb);

        // Run the score init function
        Score_init();
    }

    static uint8_t u8ProgramCounter = 0U;
    if (E_COUNTDOWN_TIMER_EXPIRED == Countdown_getTimerStatus(&sScoreTimer))
    {
        switch (u8ProgramCounter)
        {
        case 0U: {
            log_info("%s", "Pomodoro Sequence Start");

            msg_t sMsg = {0};
            sMsg.eMsgId = MSG_ID_0200;
            status_e eStatus = MessageBroker_publish(&sMsg);
            ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
            unused(eStatus);

            u8ProgramCounter++;
        }
        break;

        case 1: {
            log_info("%s", "Work Time Sequence Complete");

            msg_t sMsg = {0};
            sMsg.eMsgId = MSG_ID_0201;
            status_e eStatus = MessageBroker_publish(&sMsg);
            ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
            unused(eStatus);

            u8ProgramCounter++;
        }
        break;
        case 2: {
            log_info("%s", "Break Time Sequence Complete");

            msg_t sMsg = {0};
            sMsg.eMsgId = MSG_ID_0202;
            status_e eStatus = MessageBroker_publish(&sMsg);
            ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
            unused(eStatus);

            u8ProgramCounter = 0;
        }
        break;
        default: {
        }
        }
    }

    Score_execute();

    unused(eStatus);
}

/************************************************************
 * Implementation
 ************************************************************/

void OnBoardTest_init(void)
{
}

void OnBoardTest_execute(void)
{
    // run the "Test to run"
    test_functions[TEST_TO_RUN]();
}
