#include "Executer.h"
#include "mock_BlinkyLed.h"
#include "mock_Button_Conductor.h"
#include "mock_MessageBroker.h"
#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

void test_Executer_init_shall_initializeAllTheModules(void) {
  BlinkyLed_init_Expect();
  Button_Conductor_init_Expect();
  MessageBroker_init_ExpectAndReturn(STATUS_OK);

  Executer_init();
}
