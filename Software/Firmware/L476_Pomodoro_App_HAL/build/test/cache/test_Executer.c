#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
#include "build/test/mocks/mock_MessageBroker.h"
#include "build/test/mocks/mock_Button_Conductor.h"
#include "build/test/mocks/mock_BlinkyLed.h"
#include "App/Executer/Executer.h"




void setUp(void) {}



void tearDown(void) {}



void test_Executer_init_shall_initializeAllTheModules(void) {

  BlinkyLed_init_CMockExpect(12);

  Button_Conductor_init_CMockExpect(13);

  MessageBroker_init_CMockExpectAndReturn(14, (0));



  Executer_init();

}
