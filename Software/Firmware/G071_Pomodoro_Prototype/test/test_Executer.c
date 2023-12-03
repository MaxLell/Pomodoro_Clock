#include "Executer.h"
#include "mock_MessageBroker.h"
#include "mock_StandbyControl.h"
#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

void test_Executer_init_ShouldInitializeAllModules(void) {
  MessageBroker_init_Expect();
  StandbyControl_init_Expect();
  Executer_init();
}

void test_Executer_execute_should_ExecuteAllModules(void) {
  //   StandbyControl_execute();
}
