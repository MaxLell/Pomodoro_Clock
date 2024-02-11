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

#include "Encoder.h"

#include "Button.h"

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

    // Encoder
    E_TEST_BASIC_ENCODER,

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

// Encoder
void OnBoardTest_testBasicEncoder(void);

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
    [E_TEST_SCORE] = OnBoardTest_testScore,

    // Encoder
    [E_TEST_BASIC_ENCODER] = OnBoardTest_testBasicEncoder

};

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

        const uint8_t WORKTIME = 25;
        const uint8_t BREAKTIME = 35;

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

        // Initialize the Button
        Button_init();
    }

    // Run the CUT
    PomodoroControl_execute();

    Button_execute();
}

status_e OnBoardTest_ButtonTestMsgCb(const msg_t *const in_psMsg)
{
    { // Input Checks
        ASSERT_MSG(in_psMsg != NULL, "in_psMsg is NULL");
    }

    switch (in_psMsg->eMsgId)
    {

    case MSG_ID_0103:
    {
        // Print the score
        ButtonMessage_s *psButtonMessage = (ButtonMessage_s *)in_psMsg->au8DataBytes;

        // Print out the unsigned value of the score // Print an unsigned value
        // log_info("Button: %d, Event: %d", psButtonMessage->eButton, psButtonMessage->eEvent);

        // Map the correct button to the button number
        char *pcButtonNames[] = {"Invalid", "Trigger Btn", "Encoder Btn", "Shoulder Btn 1", "Shoulder Btn 2"};

        // Map the correct event to the event number
        char *pcEventNames[] = {"Invalid", "Pressed", "Released", "Long Pressed"};

        log_info("Button: %s, Event: %s", pcButtonNames[psButtonMessage->eButton], pcEventNames[psButtonMessage->eEvent]);
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

        // Subscribe to the Trigger Btn Released Message
        MessageBroker_subscribe(MSG_ID_0103, OnBoardTest_ButtonTestMsgCb);

        Button_init();
    }

    Button_execute();
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
        case 0U:
        {
            log_info("%s", "Pomodoro Sequence Start");

            msg_t sMsg = {0};
            sMsg.eMsgId = MSG_ID_0200;
            status_e eStatus = MessageBroker_publish(&sMsg);
            ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
            unused(eStatus);

            u8ProgramCounter++;
        }
        break;

        case 1:
        {
            log_info("%s", "Work Time Sequence Complete");

            msg_t sMsg = {0};
            sMsg.eMsgId = MSG_ID_0201;
            status_e eStatus = MessageBroker_publish(&sMsg);
            ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
            unused(eStatus);

            u8ProgramCounter++;
        }
        break;
        case 2:
        {
            log_info("%s", "Break Time Sequence Complete");

            msg_t sMsg = {0};
            sMsg.eMsgId = MSG_ID_0202;
            status_e eStatus = MessageBroker_publish(&sMsg);
            ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
            unused(eStatus);

            u8ProgramCounter = 0;
        }
        break;
        default:
        {
        }
        }
    }

    Score_execute();

    unused(eStatus);
}

status_e OnboardTest_EncoderTestMsgCb(const msg_t *const in_psMsg)
{
    // Input Checks
    ASSERT_MSG(in_psMsg != NULL, "in_psMsg is NULL");

    switch (in_psMsg->eMsgId)
    {
    case MSG_ID_0601:
    {
        // Print the score
        int32_t s32EncoderValue = in_psMsg->au8DataBytes[0] << 0 | in_psMsg->au8DataBytes[1] << 8 |
                                  in_psMsg->au8DataBytes[2] << 16 | in_psMsg->au8DataBytes[3] << 24;

        // Print out the unsigned value of the score // Print an unsigned value
        log_info("Encoder Value: %d", s32EncoderValue);
    }
    break;

    case MSG_ID_0100:
    {
        // Publish the reset message
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_ID_0600;
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
        unused(eStatus); // Suppress the unused variable warning
    }
    break;
    default:
        ASSERT_MSG(NULL, "Unknown Message ID: %d", in_psMsg->eMsgId);
        break;
        return STATUS_SUCCESS;
    }
}

void OnBoardTest_testBasicEncoder(void)
{
    static BOOL bRanOnce = FALSE;
    if (bRanOnce == FALSE)
    {
        printf("%s", "************************************************************\n");
        printf("%s", "                 OnBoardTest_testBasicEncoder\n");
        printf("%s", "************************************************************\n");

        // Clear the flag
        bRanOnce = TRUE;

        // Subscribe to the Reset Encoder Value message
        MessageBroker_subscribe(MSG_ID_0601, &OnboardTest_EncoderTestMsgCb);

        // Subscribe to the Trigger Button Message
        MessageBroker_subscribe(MSG_ID_0100, &OnboardTest_EncoderTestMsgCb);

        // Run the Encoder init function
        Encoder_init();
    }

    // Run the Encoder execute function
    Encoder_execute();

    // Run the Button execute function
    Button_execute();

    // Wait for 100 msec
    Delay_ms(100);
}

/************************************************************
 * Implementation
 ************************************************************/

void OnBoardTest_init(void)
{
    MessageBroker_init();
}

void OnBoardTest_execute(void)
{
    // run the "Test to run"
    test_functions[TEST_TO_RUN]();
}

BOOL OnBoardTest_isRunning(void)
{
#ifdef RUN_ON_BOARD_TEST
    return TRUE;
#else
    return FALSE;
#endif
}