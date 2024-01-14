/************************************************************
 * Includes
 ************************************************************/
#include "OnBoardTest.h"

#include "FSM.h"
#include "MessageBroker.h"
#include "PomodoroControl.h"
#include "PomodoroControl_Datatypes.h"

#include "LightEffects.h"
#include "LightEffects_Pomodoro.h"

#include "RgbLed.h"
#include "RgbLed_Config.h"

#include "Delay.h"

/************************************************************
 * Private Data Types
 ************************************************************/

typedef enum
{
    // Basic Tests - Lighteffects
    E_TEST_DOT_AROUND_THE_CIRCLE,
    E_TEST_LIGHT_UP_ALL_LEDS,
    E_TEST_RGB_LED_RINGS_POMODORO_INITIAL,
    E_TEST_UPDATE_PER_MINUTE,

    // Button Tests
    E_TEST_BUTTON,

    // Pomodoro Test
    E_TEST_POMODORO_NOMINAL_SEQUENCE,
    E_TEST_POMODORO_WORK_TIME_STATE,
    E_TEST_POMODORO_SHORT_BREAK_INIT_STATE,
    E_TEST_POMODORO_SHORT_BREAK_STATE,
    E_TEST_POMODORO_WARNING_STATE,
    E_TEST_POMODORO_CANCEL_SEQUENCE_INIT_STATE,
    E_TEST_POMODORO_CANCEL_SEQUENCE_STATE,

    E_LAST_TEST
} OnBoardTest_Test_e;

typedef void (*test_function_ptr)(void);

/************************************************************
 * Private Defines
 ************************************************************/
#define TEST_TO_RUN E_TEST_POMODORO_NOMINAL_SEQUENCE

/************************************************************
 * Private Function Prototypes
 ************************************************************/

// LightEffects
void OnBoardTest_testInitialPomodoroConfigs(void);
void OnBoardTest_testLightUpAllLeds(void);
void OnBoardTest_testDotAroundTheCircle(void);
void OnBoardTest_testUpdatePerMinute(void);

// Button Tests
void OnBoardTest_testButtonBehaviours(void);

// Pomodoro State Function Tests
void OnBoardTest_testNominalPomodoroSequence(void);
void OnBoardTest_testCanceledPomodoroSequence(void);

/************************************************************
 * Private Variables
 ************************************************************/

STATIC test_function_ptr test_functions[E_LAST_TEST] = {
    // RGB LED Tests
    [E_TEST_LIGHT_UP_ALL_LEDS] = OnBoardTest_testLightUpAllLeds,
    [E_TEST_DOT_AROUND_THE_CIRCLE] = OnBoardTest_testDotAroundTheCircle,

    // Button Hardware Test
    [E_TEST_BUTTON] = OnBoardTest_testButtonBehaviours,

    // Pomodoro Tests
    [E_TEST_RGB_LED_RINGS_POMODORO_INITIAL] = OnBoardTest_testInitialPomodoroConfigs,
    [E_TEST_UPDATE_PER_MINUTE] = OnBoardTest_testUpdatePerMinute,
    [E_TEST_POMODORO_NOMINAL_SEQUENCE] = OnBoardTest_testNominalPomodoroSequence};

/************************************************************
 * External private variables
 ************************************************************/

extern FSM_Config_t sFsmConfig;

/************************************************************
 * Test function implementations
 ************************************************************/

void OnBoardTest_testDotAroundTheCircle(void)
{
    status_e eStatus;
    LightEffects_DotAroundTheCircle(&eStatus, 30);
}

void OnBoardTest_testLightUpAllLeds(void)
{
    for (uint8_t u8LedIndex = 0; u8LedIndex < TOTAL_LEDS; u8LedIndex++)
    {
        RgbLed_setPixelColor(u8LedIndex, 2, 0, 0);
    }
    RgbLed_show();
}

void OnBoardTest_testInitialPomodoroConfigs(void)
{
    // Load the initial LED Config
    uint8_t u8EffectArraySize = 0;
    LightEffects_PomodoroRingPhaseCfg_t asEffects[MAX_SETTINGS];
    uint8_t au8CompressedArrayMiddleRing[NOF_LEDS_MIDDLE_RING] = {0};
    uint8_t au8CompressedArrayOuterRing[NOF_LEDS_OUTER_RING] = {0};

    // LightEffect_PomodoroConfig_e ePomodoroConfig = E_EFFECT_51_17;
    // LightEffect_PomodoroConfig_e ePomodoroConfig = E_EFFECT_25_5;
    LightEffect_PomodoroConfig_e ePomodoroConfig = E_EFFECT_90_15;
    // LightEffect_PomodoroConfig_e ePomodoroConfig = E_EFFECT_50_10;

    LightEffects_getInitialPomodoroSetting(asEffects, &u8EffectArraySize, ePomodoroConfig);

    // current phase
    LightEffects_PomodoroPhase_e eCurrentPhase = E_PHASE_WARNING;

    // Convert the initial rendering to the rgb led array representation
    LightEffects_getCompressedArraysForCurrentPhase(asEffects, u8EffectArraySize, eCurrentPhase,
                                                    au8CompressedArrayMiddleRing, au8CompressedArrayOuterRing);

    // render it on the actual Leds
    LightEffects_RenderRings(au8CompressedArrayMiddleRing, NOF_LEDS_MIDDLE_RING, au8CompressedArrayOuterRing,
                             NOF_LEDS_OUTER_RING);

    RgbLed_show();

    Delay_ms(1000);
}

void OnBoardTest_testUpdatePerMinute(void)
{
    // Load the initial LED Config
    uint8_t u8EffectArraySize = 0;
    LightEffects_PomodoroRingPhaseCfg_t asEffects[MAX_SETTINGS];
    uint8_t au8CompressedArrayMiddleRing[NOF_LEDS_MIDDLE_RING] = {0};
    uint8_t au8CompressedArrayOuterRing[NOF_LEDS_OUTER_RING] = {0};

    // LightEffects_getInitialPomodoroSetting(asEffects, &u8EffectArraySize, E_EFFECT_25_5);
    LightEffects_getInitialPomodoroSetting(asEffects, &u8EffectArraySize, E_EFFECT_51_17);
    // LightEffects_getInitialPomodoroSetting(asEffects, &u8EffectArraySize, E_EFFECT_90_15);

    // current phase
    LightEffects_PomodoroPhase_e eCurrentPhase = E_PHASE_WORK_TIME;

    // update the current Minute 51 times
    for (uint8_t i = 0; i < 51; i++)
    {
        LightEffects_updateWorktimeCfgForCurrentMinute(asEffects, u8EffectArraySize, eCurrentPhase);

        // Convert the initial rendering to the rgb led array representation
        LightEffects_getCompressedArraysForCurrentPhase(asEffects, u8EffectArraySize, eCurrentPhase,
                                                        au8CompressedArrayMiddleRing, au8CompressedArrayOuterRing);

        // render it on the actual Leds
        LightEffects_RenderRings(au8CompressedArrayMiddleRing, NOF_LEDS_MIDDLE_RING, au8CompressedArrayOuterRing,
                                 NOF_LEDS_OUTER_RING);

        RgbLed_show();

        Delay_ms(30);
    }
}

void OnBoardTest_testNominalPomodoroSequence(void)
{
    // Keine Unit Tests hier schreiben!
    // Schreib einen Integration Test und iteriere.

    // Set initial State
    // IDLE -----(EVENT_POMODORO_SEQUENCE_START)------> WORKTIME INIT
    static BOOL bRanOnce = FALSE;
    if (!bRanOnce)
    {
        // Clear the Rings
        LightEffects_ClearAllRingLeds();

        // Delay to make a restart visible
        Delay_ms(100);

        // Initialize the Pomodoro Control
        PomodoroControl_init();

        // Set the different Pomodoro Configurations
        // LightEffect_PomodoroConfig_e ePomodoroConfig = E_EFFECT_51_17;
        // LightEffect_PomodoroConfig_e ePomodoroConfig = E_EFFECT_25_5;
        // LightEffect_PomodoroConfig_e ePomodoroConfig = E_EFFECT_90_15;
        LightEffect_PomodoroConfig_e ePomodoroConfig = E_EFFECT_50_10;

        // Publish the Pomodoro Config
        msg_t sMsg;
        sMsg.eMsgId = MSG_ID_0400;
        sMsg.au8DataBytes = (uint8_t *)&ePomodoroConfig;
        sMsg.u16DataSize = sizeof(LightEffect_PomodoroConfig_e);
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

status_e OnBoardTest_ButtonTestMsgCb(msg_t *in_psMsg)
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
        log_info("Trigger Btn Pressed");
    }
    break;

    case MSG_ID_0101: { // Trigger Btn Long Pressed
        log_info("Trigger Btn Long Pressed");
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

void OnBoardTest_testCanceledPomodoroSequence(void)
{
    // Set the system to the Break time State

    // Run and update through the entire state machine
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
