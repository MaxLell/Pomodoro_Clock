#ifndef ONBOARDTEST_TESTDECLERATION_H
#define ONBOARDTEST_TESTDECLERATION_H

typedef enum
{
    // RgbLed Test
    E_TEST_RGBLED = 0,

    // Button Test
    E_TEST_BUTTON,

    // Input Sampling Thread Test
    E_TEST_INPUTSAMPLING,

    // Pomodoro Test
    E_TEST_POMODORO,

    // Countdown Timer and BlinkyLed Test
    E_TEST_COUNTDOWN_TIMER_AND_BLINKY_LED,

    E_LAST_TEST
} OnBoardTest_Test_e;

typedef void (*test_function_ptr)(void);

#endif // ONBOARDTEST_TESTDECLERATION_H