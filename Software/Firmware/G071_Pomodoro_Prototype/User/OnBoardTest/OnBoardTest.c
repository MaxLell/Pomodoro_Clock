/************************************************************
 * Includes
 ************************************************************/
#include "OnBoardTest.h"

// Module Includes
#include "PomodoroControl.h"
#include "PomodoroControl_Datatypes.h"
#include "LightEffects.h"
#include "LightEffects_Pomodoro.h"
#include "RgbLed.h"
#include "RgbLed_Config.h"
#include "Score.h"
#include "Encoder.h"
#include "Button.h"
#include "SeekingAttention.h"
#include "ContextManagement.h"

// Utility includes
#include "FSM.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "CountdownTimer.h"
#include "Delay.h"
#include "inttypes.h"

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

    // Context Mgmt Test
    E_TEST_CONTEXT_MGMT,

    // Score
    E_TEST_SCORE,

    // Encoder
    E_TEST_BASIC_ENCODER,

    // Seeking Attention
    E_TEST_SEEKING_ATTENTION,

    E_LAST_TEST
} OnBoardTest_Test_e;

typedef void (*test_function_ptr)(void);

/************************************************************
 * Private Defines
 ************************************************************/
#define TEST_TO_RUN E_TEST_SCORE

/************************************************************
 * Private Function Prototypes
 ************************************************************/

// LightEffects

void OnBoardTest_testLightUpAllLeds(void);

// Button Tests
void OnBoardTest_testButtonBehaviours(void);

// Pomodoro State Function Tests
void OnBoardTest_testNominalPomodoroSequence(void);

// Context Mgmt Test
void OnBoardTest_testContextMgmt(void);

// Score
void OnBoardTest_testScore(void);

// Encoder
void OnBoardTest_testBasicEncoder(void);

// Seeking Attention
void OnBoardTest_testSeekingAttention(void);

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

    // Context Mgmt Test
    [E_TEST_CONTEXT_MGMT] = OnBoardTest_testContextMgmt,

    // Score System
    [E_TEST_SCORE] = OnBoardTest_testScore,

    // Encoder
    [E_TEST_BASIC_ENCODER] = OnBoardTest_testBasicEncoder,

    // Seeking Attention
    [E_TEST_SEEKING_ATTENTION] = OnBoardTest_testSeekingAttention

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

        const uint8_t WORKTIME = 50;
        const uint8_t BREAKTIME = 10;

        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0003;
        PomodoroTimingCfg_s sTimingCfg = {0};
        sTimingCfg.sPomodoroPeriodConfiguration.u8MinutesWorktimePeriod = WORKTIME;
        sTimingCfg.sPomodoroPeriodConfiguration.u8MinutesBreaktimePeriod = BREAKTIME;

        // Comment out the following section if you do not want to speed up the sequence
        sTimingCfg.u16TimeOutPeriodMin = 100;
        sTimingCfg.u16TimerPeriodCancelSeqMs = 30;
        sTimingCfg.u16TimerPeriodSnoozeMs = 50;
        sTimingCfg.u16TimerPeriodWarningMs = 30;
        sTimingCfg.u16TimerPeriodSec = 30;
        sTimingCfg.u16TimerPeriodMin = 60;

        sMsg.au8DataBytes = (uint8_t *)&sTimingCfg;
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");

        // Publish the Pomodoro Sequence Start: Triggers the transition from IDLE to WORKTIME_INIT
        sMsg.eMsgId = MSG_0200;
        eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");

        // Clear the Flag
        bRanOnce = TRUE;

        // Initialize the Button
        Button_init();

        unused(eStatus);
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

    case MSG_0103:
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

    return STATUS_OK;
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
        MessageBroker_subscribe(MSG_0103, OnBoardTest_ButtonTestMsgCb);

        Button_init();
    }

    Button_execute();
}

status_e OnBoardTest_ScoreTestMsgCb(const msg_t *const in_psMsg)
{
    { // Input Checks
        ASSERT_MSG(in_psMsg != NULL, "in_psMsg is NULL");
    }

    return STATUS_OK;
}

timer_t sScoreTimer;

void OnBoardTest_testScore(void)
{
    static BOOL bRunOnce = FALSE;
    if (bRunOnce == FALSE)
    {
        printf("%s", "************************************************************\n");
        printf("%s\n", "                 OnBoardTest_testScore");
        printf("%s", "************************************************************\n");

        // Clear the flag
        bRunOnce = TRUE;

        // Run the score init function
        Score_init();

        const uint32_t FIFTY_MSEC = 50;
        const uint32_t ONE_MINUTE = 60000;
        const uint32_t TWENTY_SECONDS = 20000;
        const uint32_t THIRTY_SECONDS = 30000;
        const uint32_t TEN_SECONDS = 10000;

        // Send out the Test Message
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0003;
        ScoreTimeStamps_s sScoreTimeStamps = {0};
        sScoreTimeStamps.u32MinutePeriod = FIFTY_MSEC;
        sScoreTimeStamps.u32TimeoutPeriod = TWENTY_SECONDS;
        sScoreTimeStamps.u32WatchdogPeriod = THIRTY_SECONDS;
        sMsg.au8DataBytes = (uint8_t *)&sScoreTimeStamps;
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
        log_info("Test Config Message Sent");

        // Send in the Pomodoro Start Message
        sMsg.eMsgId = MSG_0200;
        eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
        log_info("Pomodoro Start Message Sent");

        // Start a timer that runs for 10 seconds
        Countdown_initTimerMs(&sScoreTimer, TWENTY_SECONDS, E_OPERATIONAL_MODE_ONE_SHOT);
        Countdown_resetAndStartTimer(&sScoreTimer);

        unused(eStatus);
    }

    Score_execute();

    // if the timer has expired - sent out the Pomodoro Complete Message
    if (E_COUNTDOWN_TIMER_EXPIRED == Countdown_getTimerStatus(&sScoreTimer))
    {
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0204;
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
        unused(eStatus);
        log_info("Pomodoro Complete Message Sent");
    }
}

status_e OnboardTest_EncoderTestMsgCb(const msg_t *const in_psMsg)
{
    // Input Checks
    ASSERT_MSG(in_psMsg != NULL, "in_psMsg is NULL");

    switch (in_psMsg->eMsgId)
    {
    case MSG_0601:
    {
        // Print the score
        int32_t s32EncoderValue = in_psMsg->au8DataBytes[0] << 0 | in_psMsg->au8DataBytes[1] << 8 |
                                  in_psMsg->au8DataBytes[2] << 16 | in_psMsg->au8DataBytes[3] << 24;

        // Print out the unsigned value of the score // Print an unsigned value
        log_info("Encoder Value: %" PRIu32, s32EncoderValue);
    }
    break;

    case MSG_0103:
    {
        ButtonMessage_s *psButtonMessage = (ButtonMessage_s *)in_psMsg->au8DataBytes;
        if (psButtonMessage->eButton == E_BUTTON_ENCODER)
        {
            // Publish the reset message
            msg_t sMsg = {0};
            sMsg.eMsgId = MSG_0600;
            status_e eStatus = MessageBroker_publish(&sMsg);
            ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
            unused(eStatus); // Suppress the unused variable warning
        }
    }
    break;
    default:
        ASSERT_MSG(NULL, "Unknown Message ID: %d", in_psMsg->eMsgId);
        break;
    }
    return STATUS_OK;
}

void OnBoardTest_testBasicEncoder(void)
{
    static BOOL bRanOnce = FALSE;
    if (bRanOnce == FALSE)
    {
        printf("%s", "************************************************************\n");
        printf("%s\n", "                 OnBoardTest_testBasicEncoder");
        printf("%s", "************************************************************\n");

        // Clear the flag
        bRanOnce = TRUE;

        // Subscribe to the Reset Encoder Value message
        MessageBroker_subscribe(MSG_0601, &OnboardTest_EncoderTestMsgCb);

        // Subscribe to the Trigger Button Message
        MessageBroker_subscribe(MSG_0103, &OnboardTest_EncoderTestMsgCb);

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

status_e OnBoardTest_testSeekingAttentionMsgCb(const msg_t *const in_psMsg)
{
    // Input Checks
    ASSERT_MSG(in_psMsg != NULL, "in_psMsg is NULL");

    switch (in_psMsg->eMsgId)
    {
    case MSG_0103:
    {
        status_e eStatus;
        ButtonMessage_s *psButtonMessage = (ButtonMessage_s *)in_psMsg->au8DataBytes;

        if (E_BUTTON_TRIGGER == psButtonMessage->eButton)
        {
            if (E_BTN_EVENT_RELEASED == psButtonMessage->eEvent)
            {
                // Publish the Seeking Attention Start Message
                msg_t sMsg = {0};
                sMsg.eMsgId = MSG_0900;
                eStatus = MessageBroker_publish(&sMsg);
                ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
                unused(eStatus); // Suppress the unused variable warning

                log_info("Seeking Attention Command: Start");
            }
        }
        if (E_BUTTON_ENCODER == psButtonMessage->eButton)
        {
            if (E_BTN_EVENT_RELEASED == psButtonMessage->eEvent)
            {
                // Publish the Seeking Attention Stop Message
                msg_t sMsg = {0};
                sMsg.eMsgId = MSG_0901;
                eStatus = MessageBroker_publish(&sMsg);
                ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
                unused(eStatus); // Suppress the unused variable warning

                log_info("Seeking Attention Command: Stop");
            }
        }
    }
    break;

    case MSG_0902:
    {
        log_info("Seeking Attention is now finished");
    }
    break;

    default:
        ASSERT_MSG(NULL, "Unknown Message ID: %d", in_psMsg->eMsgId);
        break;
    }

    return STATUS_OK;
}

void OnBoardTest_testSeekingAttention(void)
{
    static BOOL bRanOnce = FALSE;
    if (bRanOnce == FALSE)
    {
        printf("%s", "************************************************************\n");
        printf("%s\n", "                 OnBoardTest_testSeekingAttention");
        printf("%s", "************************************************************\n");

        // Clear the flag
        bRanOnce = TRUE;

        // Initialize the Button
        Button_init();

        // Subscribe to the Button Events
        status_e eStatus = MessageBroker_subscribe(MSG_0103, &OnBoardTest_testSeekingAttentionMsgCb);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe failed");

        // Subscribe to the Seeking Attention Finished Message
        eStatus = MessageBroker_subscribe(MSG_0902, &OnBoardTest_testSeekingAttentionMsgCb);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe failed");

        unused(eStatus); // Suppress the unused variable warning

        // Initialize the Seeking Attention Sequence
        SeekingAttention_init();

        // Publish the Test Message (Needs to be after the Seeking Attention Init function!!!)
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0003;
        eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
    }

    // Run the Button execute function
    Button_execute();

    // Run the Seeking Attention execute function
    SeekingAttention_execute();
}

status_e OnBoardTest_testContextMgmtMsgCb(const msg_t *const in_psMsg)
{
    // Input Checks
    ASSERT_MSG(in_psMsg != NULL, "in_psMsg is NULL");

    // Pomodoro Messages
    switch (in_psMsg->eMsgId)
    {
    case MSG_0103:
    {
        // if the Trigger Button is pressed for long -> Send out the Pomodoro Complete Message
        ButtonMessage_s *psButtonMessage = (ButtonMessage_s *)in_psMsg->au8DataBytes;

        if (psButtonMessage->eButton == E_BUTTON_TRIGGER)
        {
            if (psButtonMessage->eEvent == E_BTN_EVENT_LONG_PRESSED)
            {
                msg_t sMsg = {0};
                status_e eStatus;

                // Publish the Setting Complete Message
                sMsg.eMsgId = MSG_0701;
                eStatus = MessageBroker_publish(&sMsg);
                ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");

                log_info("Setting Complete Message sent");

                unused(eStatus); // Suppress the unused variable warning
            }
        }
    }
    break;

    case MSG_0200:
    {
        log_info("Pomodoro Sequence Start Command");
    }
    break;

    case MSG_0204:
    {
        log_info("Pomodoro Complete Message received");
    }
    break;

    // Seeking Attention Messages
    case MSG_0900:
    {
        log_info("Seeking Attention Start Command");
    }
    break;

    case MSG_0901:
    {
        log_info("Seeking Attention Stop Command");
    }
    break;

    case MSG_0902:
    {
        log_info("Seeking Attention is now finished");
    }
    break;

    // Setting Messages
    case MSG_0700:
    {
        log_info("Setting Start Commands");
    }
    break;

    case MSG_0701:
    {
        log_info("Setting Complete Msg received");
    }
    break;

    default:
    {
        ASSERT_MSG(NULL, "Unknown Message ID: %d", in_psMsg->eMsgId);
    }
    }
    return STATUS_OK;
}

void OnBoardTest_testContextMgmt(void)
{
    static BOOL bRanOnce = FALSE;
    if (bRanOnce == FALSE)
    {
        printf("%s", "************************************************************\n");
        printf("%s\n", "                 OnBoardTest_testContextMgmt");
        printf("%s", "************************************************************\n");

        // Clear the flag
        bRanOnce = TRUE;

        // Initialize the Button
        Button_init();

        // Subscribe the messages
        status_e eStatus;
        eStatus = MessageBroker_subscribe(MSG_0103, &OnBoardTest_testContextMgmtMsgCb);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe failed");

        eStatus = MessageBroker_subscribe(MSG_0200, &OnBoardTest_testContextMgmtMsgCb);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe failed");

        eStatus = MessageBroker_subscribe(MSG_0204, &OnBoardTest_testContextMgmtMsgCb);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe failed");

        eStatus = MessageBroker_subscribe(MSG_0900, &OnBoardTest_testContextMgmtMsgCb);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe failed");

        eStatus = MessageBroker_subscribe(MSG_0901, &OnBoardTest_testContextMgmtMsgCb);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe failed");

        eStatus = MessageBroker_subscribe(MSG_0902, &OnBoardTest_testContextMgmtMsgCb);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe failed");

        eStatus = MessageBroker_subscribe(MSG_0700, &OnBoardTest_testContextMgmtMsgCb);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe failed");

        eStatus = MessageBroker_subscribe(MSG_0701, &OnBoardTest_testContextMgmtMsgCb);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_subscribe failed");

        unused(eStatus); // Suppress the unused variable warning

        // Initialize the Context Management
        ContextManagement_init();

        // Initialize the Seeking Attention
        SeekingAttention_init();

        // Initialize the POmodoro Control
        PomodoroControl_init();

        // Publish the Test Message (Needs to be after the Seeking Attention Init function!!!)
        // So that the Seeking Attention is visible
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0003;
        PomodoroTimingCfg_s sTimingCfg = {0};
        sTimingCfg.sPomodoroPeriodConfiguration.u8MinutesWorktimePeriod = 50;
        sTimingCfg.sPomodoroPeriodConfiguration.u8MinutesBreaktimePeriod = 10;
        sTimingCfg.u16TimeOutPeriodMin = 100;
        sTimingCfg.u16TimerPeriodCancelSeqMs = 30;
        sTimingCfg.u16TimerPeriodSnoozeMs = 50;
        sTimingCfg.u16TimerPeriodWarningMs = 30;
        sTimingCfg.u16TimerPeriodSec = 30;
        sTimingCfg.u16TimerPeriodMin = 60;

        sMsg.au8DataBytes = (uint8_t *)&sTimingCfg;
        eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
    }

    // Run the Button execute function
    Button_execute();

    // Run the Context Management execute function
    ContextManagement_execute();

    // Run the Seeking Attention execute function
    SeekingAttention_execute();

    // Run the Pomodoro Control execute function
    PomodoroControl_execute();
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