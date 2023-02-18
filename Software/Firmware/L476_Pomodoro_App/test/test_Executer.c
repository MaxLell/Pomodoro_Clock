#include "unity.h"

#include "mock_Rcc.h"
#include "mock_BlinkyLed.h"
#include "mock_SysTick.h"
#include "mock_Button.h"

#include "Executer.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Executer_init_shall_initializeAllTheModules(void)
{
    Rcc_init_Expect();
    SysTick_init_Expect();
    BlinkyLed_init_Expect();
    Button_init_Expect();

    Executer_init();
}
