/************************************************************
 * Includes
 ************************************************************/
#include "OnBoardTest.h"

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
    E_TEST_DOT_AROUND_THE_CIRCLE,
    E_TEST_LIGHT_UP_ALL_LEDS,
    E_TEST_RGB_LED_RINGS_POMODORO_INITIAL,
    E_TEST_UPDATE_PER_MINUTE,
    E_LAST_TEST
} OnBoardTest_Test_e;

typedef void (*test_function_ptr)(void);

/************************************************************
 * Private Defines
 ************************************************************/

#define TEST_TO_RUN E_TEST_UPDATE_PER_MINUTE

/************************************************************
 * Private Function Prototypes
 ************************************************************/

void OnBoardTest_testPomodoroSequenceRgbLedRingsInitialConfig(void);
void OnBoardTest_testLightUpAllLeds(void);
void OnBoardTest_testDotAroundTheCircle(void);
void OnBoardTest_TestUpdatePerMinute(void);

/************************************************************
 * Private Variables
 ************************************************************/

STATIC test_function_ptr test_functions[E_LAST_TEST] = {
    [E_TEST_LIGHT_UP_ALL_LEDS] = OnBoardTest_testLightUpAllLeds,
    [E_TEST_DOT_AROUND_THE_CIRCLE] = OnBoardTest_testDotAroundTheCircle,
    [E_TEST_RGB_LED_RINGS_POMODORO_INITIAL] = OnBoardTest_testPomodoroSequenceRgbLedRingsInitialConfig,
    [E_TEST_UPDATE_PER_MINUTE] = OnBoardTest_TestUpdatePerMinute,
};

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

void OnBoardTest_testPomodoroSequenceRgbLedRingsInitialConfig(void)
{
    // Load the initial LED Config
    uint8_t u8EffectArraySize = 0;
    LightEffects_PomodoroRingPhaseCfg_t asEffects[MAX_SETTINGS];
    uint8_t au8CompressedArrayMiddleRing[NOF_LEDS_MIDDLE_RING] = {0};
    uint8_t au8CompressedArrayOuterRing[NOF_LEDS_OUTER_RING] = {0};

    LightEffects_getInitialPomodoroSetting(asEffects, &u8EffectArraySize, E_EFFECT_51_17);

    // current phase
    LightEffects_PomodoroPhase_e eCurrentPhase = E_PHASE_WORK_TIME;

    // Convert the initial rendering to the rgb led array representation
    LightEffects_getCompressedArraysForCurrentPhase(asEffects, u8EffectArraySize, eCurrentPhase,
                                                    au8CompressedArrayMiddleRing, au8CompressedArrayOuterRing);

    // render it on the actual Leds
    LightEffects_RenderRings(au8CompressedArrayMiddleRing, NOF_LEDS_MIDDLE_RING, au8CompressedArrayOuterRing,
                             NOF_LEDS_OUTER_RING);

    RgbLed_show();

    Delay_ms(1000);
}

void OnBoardTest_TestUpdatePerMinute(void)
{
    // Load the initial LED Config
    uint8_t u8EffectArraySize = 0;
    LightEffects_PomodoroRingPhaseCfg_t asEffects[MAX_SETTINGS];
    uint8_t au8CompressedArrayMiddleRing[NOF_LEDS_MIDDLE_RING] = {0};
    uint8_t au8CompressedArrayOuterRing[NOF_LEDS_OUTER_RING] = {0};

    LightEffects_getInitialPomodoroSetting(asEffects, &u8EffectArraySize, E_EFFECT_51_17);

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