#include "unity.h"
#include "Executer.h"
#include "mock_BlinkyLed.h"
#include "mock_StopWatch.h"
#include "mock_Button.h"
#include "mock_RealTimeClock.h"
#include "mock_StopWatch.h"
#include "mock_MessageBroker.h"
#include "mock_Buzzer.h"
#include "mock_LightEffects.h"
#include "mock_PomodoroFsm.h"
#include "mock_RgbLed.h"
#include "mock_Score.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Executer_init_ShouldInitializeAllModules(void)
{
    MessageBroker_init_ExpectAndReturn(STATUS_OK);
    StopWatch_init_Expect();
    RealTimeClock_init_Expect();
    Buzzer_Init_Expect();
    LightEffects_init_Expect();
    PomodoroFsm_init_Expect();
    RgbLed_init_Expect();
    Score_init_Expect();

    Executer_init();
}

void test_Executer_execute_should_ExecuteAllModules(void)
{
    StopWatch_execute_Expect();
    RealTimeClock_execute_ExpectAndReturn(STATUS_OK);
    Button_execute_Expect();
    Buzzer_execute_Expect();
    LightEffects_execute_ExpectAndReturn(STATUS_OK);
    PomodoroFsm_execute_Expect();
    RgbLed_execute_Expect();
    Score_execute_Expect();

    Executer_execute();
}
