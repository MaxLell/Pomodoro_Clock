#include "unity.h"

#include "mock_Rcc.h"
#include "mock_BlinkyLed.h"
#include "mock_SysTick.h"
#include "mock_Button_Conductor.h"
#include "mock_MessageBroker.h"

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
    Button_Conductor_init_Expect();
    MessageBroker_init_ExpectAndReturn(STATUS_OK);

    Executer_init();
}
