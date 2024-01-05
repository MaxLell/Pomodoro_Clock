/************************************************************
 * Includes
 ************************************************************/
#include "OnBoardTest.h"

#include "LightEffects.h"
#include "RgbLed.h"
#include "RgbLed_Config.h"

/************************************************************
 * Private Function Prototypes
 ************************************************************/

void OnBoardTest_testPomodoroSequenceRgbLedRings(void);
void OnBoardTest_testLightUpAllLeds(void);
void OnBoardTest_testRenderRing(void);

/************************************************************
 * Private Data Types
 ************************************************************/

typedef enum {
  E_TEST_RGB_LED_RING_AROUND_THE_ROSY,
  E_TEST_LIGHT_UP_ALL_LEDS,
  E_TEST_RGB_LED_RINGS_POMODORO,
  E_LAST_TEST
} OnBoardTest_Test_e;

typedef void (*test_function_ptr)(void);

/************************************************************
 * Private Defines
 ************************************************************/

#define TEST_TO_RUN E_TEST_RGB_LED_RING_AROUND_THE_ROSY

/************************************************************
 * Private Variables
 ************************************************************/

STATIC test_function_ptr test_functions[E_LAST_TEST] = {
    [E_TEST_RGB_LED_RINGS_POMODORO] =
        OnBoardTest_testPomodoroSequenceRgbLedRings,
    [E_TEST_RGB_LED_RING_AROUND_THE_ROSY] = OnBoardTest_testRenderRing,
    [E_TEST_LIGHT_UP_ALL_LEDS] = OnBoardTest_testLightUpAllLeds};

/************************************************************
 * Implementation
 ************************************************************/

void OnBoardTest_testRenderRing(void) {
  status_e eStatus;
  LightEffects_DotAroundTheCircle(&eStatus, 30);
}

void OnBoardTest_testLightUpAllLeds(void) {
  for (uint8_t u8LedIndex = 0; u8LedIndex < TOTAL_LEDS; u8LedIndex++) {
    RgbLed_setPixelColor(u8LedIndex, 2, 0, 0);
  }
  RgbLed_show();
}

void OnBoardTest_testPomodoroSequenceRgbLedRings(void) {
  // Load the initial LED Config

  // Convert the initial rendering to the rgb led array representation

  // render it on the actual Leds
}

void OnBoardTest_init(void) {}

void OnBoardTest_execute(void) {
  // run the "Test to run"
  test_functions[TEST_TO_RUN]();
}