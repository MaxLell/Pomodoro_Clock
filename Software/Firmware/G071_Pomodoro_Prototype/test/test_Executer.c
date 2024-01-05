
#include "Executer.h"
#include "mock_Button.h"
#include "mock_MessageBroker.h"
#include "mock_OnBoardTest.h"
#include "mock_RealTimeClock.h"
#include "mock_StandbyControl.h"

void setUp(void) {}

void tearDown(void) {}

void test_Executer_init_ShouldInitializeAllModules(void) {
  Executer_init();
}

void test_Executer_execute_should_ExecuteAllModules(void) {
  Executer_execute();
}
