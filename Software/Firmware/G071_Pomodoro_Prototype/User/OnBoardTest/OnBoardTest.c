/************************************************************
 * Includes
 ************************************************************/
#include "OnBoardTest.h"

#include "LightEffects.h"

/************************************************************
 * Private Function Prototypes
 ************************************************************/

void OnBoardTest_testPomodoroSequenceRgbLedRings(void);
void OnBoardTest_testRenderRing(void);

/************************************************************
 * Private Data Types
 ************************************************************/

typedef enum {
  E_TEST_RGB_LED_RING_AROUND_THE_ROSY,
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
    [E_TEST_RGB_LED_RING_AROUND_THE_ROSY] = OnBoardTest_testRenderRing};

/************************************************************
 * Implementation
 ************************************************************/

void OnBoardTest_testRenderRing(void) {
  status_e eStatus;
  LightEffects_DotAroundTheCircle(&eStatus, 100);
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