/************************************************************
 * Includes
 ************************************************************/
#include "OnBoardTest_TestDecleration.h"
#include "OnBoardTest.h"

// Module specific test includes
#include "OnBoardTest_RgbLed.h"

/************************************************************
 * private variables
 ************************************************************/

static OnBoardTest_Test_e eCurrentTest = E_TEST_LIGHT_UP_ALL_LEDS;

/**
 * Init Function Array
 */
static const test_function_ptr initLookUpTable[E_LAST_TEST] = {
    [E_TEST_LIGHT_UP_ALL_LEDS] = OnBoardTest_RgbLed_init,
};

/**
 * Execute Function Array
 */
static const test_function_ptr executeLookUpTable[E_LAST_TEST] = {
    [E_TEST_LIGHT_UP_ALL_LEDS] = OnBoardTest_RgbLed_execute,
};

/************************************************************
 * Implementation
 ************************************************************/

void OnBoardTest_init(void)
{
    { // Input Check
        ASSERT_MSG(eCurrentTest < E_LAST_TEST, "Invalid Test - Test is out of bounds");
    }

    initLookUpTable[eCurrentTest]();
}

void OnBoardTest_execute(void)
{
    { // Input Check
        ASSERT_MSG(eCurrentTest < E_LAST_TEST, "Invalid Test - Test is out of bounds");
    }
    executeLookUpTable[eCurrentTest]();
}
