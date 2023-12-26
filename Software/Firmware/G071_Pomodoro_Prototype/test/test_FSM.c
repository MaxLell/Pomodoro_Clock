#include "Common.h"
#include "FSM.h"
#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

/*********************************************
 * Setup
 *********************************************/

/*********************************************
 * State Definitions
 *********************************************/

typedef enum {
  FSM_STATE_A = 0U,
  FSM_STATE_B,
  FSM_STATE_C,
  FSM_STATE_LAST
} FSM_state_e;

/*********************************************
 * State Actions
 *********************************************/
uint8_t u8TestCounter = 0;
void ActionStateA() {
  u8TestCounter = 1;
}

void ActionStateB() {}

void ActionStateC() {}

static const FSM_StateActionCb saStateActions[] = {
    [FSM_STATE_A] = ActionStateA,
    [FSM_STATE_B] = ActionStateB,
    [FSM_STATE_C] = ActionStateC};

/*********************************************
 * State Transition Events
 *********************************************/

typedef enum {
  FSM_EVENT_1 = 0U,
  FSM_EVENT_2,
  FSM_EVENT_3,
  FSM_EVENT_LAST
} FSM_event_e;

static const uint16_t FSM_transitionMatrix[FSM_STATE_LAST][FSM_EVENT_LAST] = {
    /*
           ┌─────1─────┐
           │           │
        ┌──┴┐        ┌─▼─┐
        │ A ◄────2───┤ B │
        └─▲─┘        └─┬─┘
          │            │
          1            3
          │    ┌───┐   │
          └────┤ C ◄───┘
               └───┘
        https://asciiflow.com/#/
    */
    // Current State
    [FSM_STATE_A] =
        {
            // Event -----> Next State
            [FSM_EVENT_1] = FSM_STATE_B,
            [FSM_EVENT_2] = FSM_STATE_A,
            [FSM_EVENT_3] = FSM_STATE_A,
        },
    // Current State
    [FSM_STATE_B] =
        {
            // Event -----> Next State
            [FSM_EVENT_1] = FSM_STATE_B,
            [FSM_EVENT_2] = FSM_STATE_A,
            [FSM_EVENT_3] = FSM_STATE_C,
        },
    // Current State
    [FSM_STATE_C] =
        {
            // Event -----> Next State
            [FSM_EVENT_1] = FSM_STATE_A,
            [FSM_EVENT_2] = FSM_STATE_C,
            [FSM_EVENT_3] = FSM_STATE_C,
        },
};

/*
#########################
          Tests
#########################
 */

void test_getNextState_shouldReturnNextState(void) {
  FSM_Config_t sFsmConfig = {
      .NUMBER_OF_EVENTS = FSM_EVENT_LAST,
      .NUMBER_OF_STATES = FSM_STATE_LAST,
      .au16TransitionMatrix = (uint16_t*)&FSM_transitionMatrix,
      .asStateActions = saStateActions};
  /**
   * State A
   */
  // Event 1 -> State B
  sFsmConfig.u16CurrentState = FSM_STATE_A;
  FSM_setTriggerEvent(&sFsmConfig, FSM_EVENT_1);
  FSM_getNextState(&sFsmConfig);
  TEST_ASSERT_EQUAL(FSM_STATE_B, sFsmConfig.u16CurrentState);

  // Event 2 -> State A
  sFsmConfig.u16CurrentState = FSM_STATE_A;
  FSM_setTriggerEvent(&sFsmConfig, FSM_EVENT_2);
  FSM_getNextState(&sFsmConfig);
  TEST_ASSERT_EQUAL(FSM_STATE_A, sFsmConfig.u16CurrentState);

  // Event 3 -> State A
  sFsmConfig.u16CurrentState = FSM_STATE_A;
  FSM_setTriggerEvent(&sFsmConfig, FSM_EVENT_3);
  FSM_getNextState(&sFsmConfig);
  TEST_ASSERT_EQUAL(FSM_STATE_A, sFsmConfig.u16CurrentState);

  /**
   * State B
   */
  // Event 1 -> State B
  sFsmConfig.u16CurrentState = FSM_STATE_B;
  FSM_setTriggerEvent(&sFsmConfig, FSM_EVENT_1);
  FSM_getNextState(&sFsmConfig);
  TEST_ASSERT_EQUAL(FSM_STATE_B, sFsmConfig.u16CurrentState);

  // Event 2 -> State A
  sFsmConfig.u16CurrentState = FSM_STATE_B;
  FSM_setTriggerEvent(&sFsmConfig, FSM_EVENT_2);
  FSM_getNextState(&sFsmConfig);
  TEST_ASSERT_EQUAL(FSM_STATE_A, sFsmConfig.u16CurrentState);

  // Event 3 -> State C
  sFsmConfig.u16CurrentState = FSM_STATE_B;
  FSM_setTriggerEvent(&sFsmConfig, FSM_EVENT_3);
  FSM_getNextState(&sFsmConfig);
  TEST_ASSERT_EQUAL(FSM_STATE_C, sFsmConfig.u16CurrentState);

  /**
   * State C
   */
  // Event 1 -> State A
  sFsmConfig.u16CurrentState = FSM_STATE_C;
  FSM_setTriggerEvent(&sFsmConfig, FSM_EVENT_1);
  FSM_getNextState(&sFsmConfig);
  TEST_ASSERT_EQUAL(FSM_STATE_A, sFsmConfig.u16CurrentState);

  // Event 2 -> State C
  sFsmConfig.u16CurrentState = FSM_STATE_C;
  FSM_setTriggerEvent(&sFsmConfig, FSM_EVENT_2);
  FSM_getNextState(&sFsmConfig);
  TEST_ASSERT_EQUAL(FSM_STATE_C, sFsmConfig.u16CurrentState);

  // Event 3 -> State C
  sFsmConfig.u16CurrentState = FSM_STATE_C;
  FSM_setTriggerEvent(&sFsmConfig, FSM_EVENT_3);
  FSM_getNextState(&sFsmConfig);
  TEST_ASSERT_EQUAL(FSM_STATE_C, sFsmConfig.u16CurrentState);
}

void test_runStateAction_runsTheStateFunction(void) {
  FSM_Config_t sFsmConfig = {
      .NUMBER_OF_EVENTS = FSM_EVENT_LAST,
      .NUMBER_OF_STATES = FSM_STATE_LAST,
      .au16TransitionMatrix = (uint16_t*)&FSM_transitionMatrix,
      .asStateActions = saStateActions};

  sFsmConfig.u16CurrentState = FSM_STATE_A;
  FSM_runStateAction(&sFsmConfig);
  TEST_ASSERT_EQUAL(1, u8TestCounter);
}

void test_execute_shouldRunStateAction(void) {
  FSM_Config_t sFsmConfig = {
      .NUMBER_OF_EVENTS = FSM_EVENT_LAST,
      .NUMBER_OF_STATES = FSM_STATE_LAST,
      .au16TransitionMatrix = (uint16_t*)&FSM_transitionMatrix,
      .asStateActions = saStateActions,
      .u16CurrentState = FSM_STATE_A,
  };
  FSM_setTriggerEvent(&sFsmConfig, FSM_EVENT_1);
  FSM_execute(&sFsmConfig);
  TEST_ASSERT_EQUAL(1, u8TestCounter);
  TEST_ASSERT_EQUAL(FSM_STATE_B, sFsmConfig.u16CurrentState);
}