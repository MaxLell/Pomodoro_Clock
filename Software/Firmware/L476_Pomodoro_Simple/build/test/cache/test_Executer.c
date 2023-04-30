#include "build/test/mocks/mock_Score.h"
#include "build/test/mocks/mock_RgbLed.h"
#include "build/test/mocks/mock_PomodoroFsm.h"
#include "build/test/mocks/mock_LightEffects.h"
#include "build/test/mocks/mock_Buzzer.h"
#include "build/test/mocks/mock_MessageBroker.h"
#include "build/test/mocks/mock_RealTimeClock.h"
#include "build/test/mocks/mock_Button.h"
#include "build/test/mocks/mock_StopWatch.h"
#include "build/test/mocks/mock_BlinkyLed.h"
#include "User/Executer/Executer.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}



void test_Executer_init_ShouldInitializeAllModules(void)

{

    MessageBroker_init_CMockExpectAndReturn(25, (0));

    StopWatch_init_CMockExpect(26);

    RealTimeClock_init_CMockExpect(27);

    Buzzer_Init_CMockExpect(28);

    LightEffects_init_CMockExpect(29);

    PomodoroFsm_init_CMockExpect(30);

    RgbLed_init_CMockExpect(31);

    Score_init_CMockExpect(32);



    Executer_init();

}



void test_Executer_execute_should_ExecuteAllModules(void)

{

    StopWatch_execute_CMockExpect(39);

    RealTimeClock_execute_CMockExpectAndReturn(40, (0));

    Button_execute_CMockExpect(41);

    Buzzer_execute_CMockExpect(42);

    LightEffects_execute_CMockExpectAndReturn(43, (0));

    PomodoroFsm_execute_CMockExpect(44);

    RgbLed_execute_CMockExpect(45);

    Score_execute_CMockExpect(46);



    Executer_execute();

}
