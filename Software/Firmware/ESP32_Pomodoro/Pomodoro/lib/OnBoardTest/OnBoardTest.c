/************************************************************
 * Includes
 ************************************************************/
#include "OnBoardTest_TestDecleration.h"
#include "OnBoardTest.h"

// Module specific test includes
#include "OnBoardTest_RgbLed.h"
#include "OnBoardTest_Button.h"

// Utilities
#include "MessageBroker.h"
#include "RgbLed.h"

/************************************************************
 * private variables
 ************************************************************/

static OnBoardTest_Test_e eCurrentTest = E_TEST_BUTTON;

/**
 * Init Function Array
 */
static const test_function_ptr initLookUpTable[E_LAST_TEST] = {
    [E_TEST_RGBLED] = OnBoardTest_RgbLed_init,
    [E_TEST_BUTTON] = OnBoardTest_Button_init,
};

/**
 * Execute Function Array
 */
static const test_function_ptr executeLookUpTable[E_LAST_TEST] = {
    [E_TEST_RGBLED] = OnBoardTest_RgbLed_execute,
    [E_TEST_BUTTON] = OnBoardTest_Button_execute,
};

/************************************************************
 * Implementation
 ************************************************************/

void OnBoardTest_init(void)
{
    { // Input Check
        ASSERT_MSG(eCurrentTest < E_LAST_TEST, "Invalid Test - Test is out of bounds");
    }

    // Init the Message Broker
    MessageBroker_init();

    // Clear all LEDs
    RgbLed_clear();

    // Run the Init function of the current test
    initLookUpTable[eCurrentTest]();
}

void OnBoardTest_execute(void)
{
    { // Input Check
        ASSERT_MSG(eCurrentTest < E_LAST_TEST, "Invalid Test - Test is out of bounds");
    }
    executeLookUpTable[eCurrentTest]();
}
