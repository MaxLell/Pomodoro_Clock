#include "unity.h"
#include "Rcc.h"

/**
 * RCC Testing abstract strategy:
 * - Set up the respecitve registers in a TDD Manner
 *   - Also enable the MCO (Clock output to a respective Pin for HW Verification)
 * - Flash the file to the Microcontroller
 * - Check the Clock Speed with the Logic Analyzer
 */

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Rcc_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement Rcc");
}
