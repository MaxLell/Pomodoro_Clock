#include "App/Executer/Executer.h"
#include "build/test/mocks/mock_Button.h"
#include "build/test/mocks/mock_SysTick.h"
#include "build/test/mocks/mock_BlinkyLed.h"
#include "build/test/mocks/mock_Rcc.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"






void setUp(void)

{

}



void tearDown(void)

{

}



void test_Executer_init_shall_initializeAllTheModules(void)

{

    Rcc_init_CMockExpect(20);

    SysTick_init_CMockExpect(21);

    BlinkyLed_init_CMockExpect(22);

    Button_init_CMockExpect(23);



    Executer_init();

}
