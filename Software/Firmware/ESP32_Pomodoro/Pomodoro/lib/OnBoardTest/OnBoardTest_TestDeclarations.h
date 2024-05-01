#ifndef ONBOARDTEST_TESTDECLERATION_H
#define ONBOARDTEST_TESTDECLERATION_H

typedef enum
{
    // RgbLed Test
    E_TEST_RGBLED = 0,

    // Button Test
    E_TEST_BUTTON,

    E_LAST_TEST
} OnBoardTest_Test_e;

typedef void (*test_function_ptr)(void);

#endif // ONBOARDTEST_TESTDECLERATION_H