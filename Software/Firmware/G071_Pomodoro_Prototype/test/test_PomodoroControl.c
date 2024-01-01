#include "PomodoroControl.h"
#include "unity.h"

#include "Common.h"
#include "FSM.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "PomodoroControl_Datatypes.h"
#include "PomodoroStateActions.h"
#include "mock_RgbLed.h"

extern FSM_Config_t sFsmConfig;
extern PomodoroControl_internalStatus_t sInternalState;

void setUp(void) {}

void tearDown(void) {}

// Write an E2E Test for one specific example:
// From the State Event to the State transition to the Final Compressed Arrays,
// which are to be displayed on the ring

void test_StateAction_OneShot_e2eTest(void) {
  // this should be representative of the one-shot state action executions

  // Functions like these are to be executed in the WorktimeInit, Breaktime Init
  // and the CancelSequenceInit State
}

void test_stateAction_MultipleTrigger_e2eTest(void) {
  // This is a sequence test, which tests the functions, which are triggered
  // multiple time in the State execution diagram (The run functions)
}