#ifndef ONBOARDTEST_TESTDECLERATION_H
#define ONBOARDTEST_TESTDECLERATION_H

typedef enum
{
    // Basic Tests - Lighteffects
    E_TEST_LIGHT_UP_ALL_LEDS = 0,

    E_LAST_TEST
} OnBoardTest_Test_e;

typedef void (*test_function_ptr)(void);

#endif // ONBOARDTEST_TESTDECLERATION_H