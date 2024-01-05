#include "Common.h"
#include "FSM.h"
#include "LightEffects.h"
#include "LightEffects_Pomodoro.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "PomodoroControl.h"
#include "PomodoroControl_Datatypes.h"
#include "mock_CountdownTimer.h"
#include "mock_Delay.h"
#include "mock_RgbLed.h"
#include "unity.h"

extern FSM_Config_t sFsmConfig;

extern PomodoroControl_internalStatus_t sInternalState;
extern LightEffects_PomodoroRingPhaseCfg_t asEffects[MAX_SETTINGS];

extern uint8_t u8EffectArraySize;

extern uint8_t au8CompressedArrayRing1[NOF_LEDS_OUTER_RING];
extern uint8_t au8CompressedArrayRing2[NOF_LEDS_MIDDLE_RING];

extern void StateActionIdle(void);
extern void StateActionWorktimeInit(void);
extern void StateActionWorktime(void);
extern void StateActionWarning(void);
extern void StateActionBreaktimeInit(void);
extern void StateActionBreaktime(void);
extern void StateActionCancelSequenceRunning(void);
extern void StateActionCancelSequenceHalted(void);

void setUp(void) {
  sFsmConfig.u16CurrentState = STATE_IDLE;
  sFsmConfig.u16CurrentEvent = EVENT_SEQUENCE_PENDING;
  sInternalState.u8CurrentPhase = E_PHASE_NONE;

  // Reset the Effect Array
  u8EffectArraySize = 0;

  // Reset the Compressed Arrays
  memset(au8CompressedArrayRing1, 0, NOF_LEDS_OUTER_RING);
  memset(au8CompressedArrayRing2, 0, NOF_LEDS_INNER_RING);
}

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

void test_WorktimeInit(void) {
  // Start: Idle State
  TEST_ASSERT_EQUAL(STATE_IDLE, sFsmConfig.u16CurrentState);

  // SetEvent: Pomodoro Start
  FSM_setTriggerEvent(&sFsmConfig, EVENT_POMODORO_SEQUENCE_START);

  // Set the phase to breaktime (just to observe the change)
  sInternalState.u8CurrentPhase = E_PHASE_NONE;

  // Set the mock expectation
  Countdown_initTimer_Ignore();
  Countdown_startTimer_Ignore();

  FSM_execute(&sFsmConfig);  // WT Init

  // Make sure that the Effect Config is no longer Empty
  TEST_ASSERT_EQUAL(4, u8EffectArraySize);

  // Make sure that the Phase is set to Worktime
  TEST_ASSERT_EQUAL(E_PHASE_WORK_TIME, sInternalState.u8CurrentPhase);

  // Expect State to be Worktime Init
  TEST_ASSERT_EQUAL(STATE_WORKTIME_INIT, sFsmConfig.u16CurrentState);
}