#include "Common.h"
#include "FSM.h"
#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

/*********************************************
 * Setup
 *********************************************/

typedef enum {
  FSM_NO_STATE_TRANSITION = -1,
  FSM_STATE_A = 0U,
  FSM_STATE_B,
  FSM_STATE_C,
  FSM_STATE_LAST
} FSM_state_e;

status_e StateFnA(const uint16_t* const in_u16State,
                  uint8_t* const inout_pData) {
  return STATUS_SUCCESS;
}

status_e StateFnB(const uint16_t* const in_u16State,
                  uint8_t* const inout_pData) {
  return STATUS_SUCCESS;
}

status_e StateFnC(const uint16_t* const in_u16State,
                  uint8_t* const inout_pData) {
  return STATUS_SUCCESS;
}

// Create new States
static const FSM_StateCbs_t saStateCb[] = {
    [FSM_STATE_A] = {.pfnEntry = NULL, .pfnRun = StateFnA, .pfnExit = NULL},

    [FSM_STATE_B] = {.pfnEntry = NULL, .pfnRun = StateFnB, .pfnExit = NULL},

    [FSM_STATE_C] = {.pfnEntry = NULL, .pfnRun = StateFnC, .pfnExit = NULL}};

const FSM_StateCbs_t* const psStateCb = saStateCb;

// Events
typedef enum {
  FSM_EVENT_1 = 0U,
  FSM_EVENT_2,
  FSM_EVENT_3,
  FSM_EVENT_LAST
} FSM_event_e;

static const int16_t FSM_transitionMatrix[FSM_STATE_LAST][FSM_EVENT_LAST] = {
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
            [FSM_EVENT_2] = FSM_NO_STATE_TRANSITION,
            [FSM_EVENT_3] = FSM_NO_STATE_TRANSITION,
        },
    // Current State
    [FSM_STATE_B] =
        {
            // Event -----> Next State
            [FSM_EVENT_1] = FSM_NO_STATE_TRANSITION,
            [FSM_EVENT_2] = FSM_STATE_A,
            [FSM_EVENT_3] = FSM_STATE_C,
        },
    // Current State
    [FSM_STATE_C] =
        {
            // Event -----> Next State
            [FSM_EVENT_1] = FSM_STATE_A,
            [FSM_EVENT_2] = FSM_NO_STATE_TRANSITION,
            [FSM_EVENT_3] = FSM_NO_STATE_TRANSITION,
        },
};

void runState(FSM_Config_t* psFsmContext, uint8_t* inout_au8Data) {
  {  // input Checks

    ASSERT_MSG(!(psFsmContext->psaTransitionMatrix == NULL),
               "Transition Matrix is NULL");
    ASSERT_MSG(!(psFsmContext->psStateCbs == NULL), "State Callbacks are NULL");
    ASSERT_MSG(!(inout_au8Data == NULL), "inout_au8Data is NULL");
    ASSERT_MSG(!(psFsmContext == NULL), "psFsmContext is NULL");
  }

  status_e eStatus = STATUS_SUCCESS;

  uint16_t u16Event;
  (psFsmContext->pfnGetEvent)(&u16Event);

  FSM_getNextState(psFsmContext, &psFsmContext->i16CurrentState, u16Event);

  log_info("%d next state", psFsmContext->i16CurrentState);

  //   When the defined State is not NULL->Well then execute it
  if (FSM_NO_STATE_TRANSITION != psFsmContext->i16CurrentState) {
    // Run the State functions
    eStatus = FSM_runStateAction(psFsmContext->psStateCbs,
                              (uint16_t*)&psFsmContext->i16CurrentState,
                              inout_au8Data);
    ASSERT_MSG(!(eStatus == STATUS_ERROR), "Run Function returned error");
  }
  return;
}

void test_probeTheTransitionMatrix(void) {
  // Copy the transition matrix reference and then access the matrix
  // by using the reference - print then all values
  FSM_Config_t sFsmConfig;
  sFsmConfig.psaTransitionMatrix = (int16_t*)&FSM_transitionMatrix;

  const int16_t* configRowPtr = &sFsmConfig.psaTransitionMatrix[FSM_STATE_A];
  const int16_t* configElementPtr = &configRowPtr[FSM_EVENT_1];
  int16_t configValue = *configElementPtr;
  TEST_ASSERT_EQUAL(FSM_STATE_B, configValue);

  //   int16_t configValue2 = fsmConfig.psaTransitionMatrix[0][0]; // <-
  //   Produces an Error. C does not properly support 2D Arrays. Instead one can
  //   work with 1D Arrays pointing to 1D Arrays. This is what is done in the
  //   FSM_Config_t struct.
}

void test_getNextState_shouldReturnNextState(void) {
  FSM_Config_t sFsmConfig = {
      .NUMBER_OF_EVENTS = FSM_EVENT_LAST,
      .NUMBER_OF_STATES = FSM_STATE_LAST,
      .psaTransitionMatrix = (int16_t*)&FSM_transitionMatrix,
      .psStateCbs = saStateCb};

  /**
   * State A
   */
  // Event 1 -> State B
  int16_t i16CurrentState = FSM_STATE_A;
  FSM_getNextState(&sFsmConfig, &i16CurrentState, FSM_EVENT_1);
  TEST_ASSERT_EQUAL(FSM_STATE_B, i16CurrentState);

  // Event 2 -> No State Transition
  i16CurrentState = FSM_STATE_A;
  FSM_getNextState(&sFsmConfig, &i16CurrentState, FSM_EVENT_2);
  TEST_ASSERT_EQUAL(FSM_NO_STATE_TRANSITION, i16CurrentState);

  // Event 3 -> No State Transition
  i16CurrentState = FSM_STATE_A;
  FSM_getNextState(&sFsmConfig, &i16CurrentState, FSM_EVENT_3);
  TEST_ASSERT_EQUAL(FSM_NO_STATE_TRANSITION, i16CurrentState);

  /**
   * State B
   */
  // Event 1 -> No State Transition
  i16CurrentState = FSM_STATE_B;
  FSM_getNextState(&sFsmConfig, &i16CurrentState, FSM_EVENT_1);
  TEST_ASSERT_EQUAL(FSM_NO_STATE_TRANSITION, i16CurrentState);

  // Event 2 -> State A
  i16CurrentState = FSM_STATE_B;
  FSM_getNextState(&sFsmConfig, &i16CurrentState, FSM_EVENT_2);
  TEST_ASSERT_EQUAL(FSM_STATE_A, i16CurrentState);

  // Event 3 -> State C
  i16CurrentState = FSM_STATE_B;
  FSM_getNextState(&sFsmConfig, &i16CurrentState, FSM_EVENT_3);
  TEST_ASSERT_EQUAL(FSM_STATE_C, i16CurrentState);

  /**
   * State C
   */
  // Event 1 -> State A
  i16CurrentState = FSM_STATE_C;
  FSM_getNextState(&sFsmConfig, &i16CurrentState, FSM_EVENT_1);
  TEST_ASSERT_EQUAL(FSM_STATE_A, i16CurrentState);

  // Event 2 -> No State Transition
  i16CurrentState = FSM_STATE_C;
  FSM_getNextState(&sFsmConfig, &i16CurrentState, FSM_EVENT_2);
  TEST_ASSERT_EQUAL(FSM_NO_STATE_TRANSITION, i16CurrentState);

  // Event 3 -> No State transition
  i16CurrentState = FSM_STATE_C;
  FSM_getNextState(&sFsmConfig, &i16CurrentState, FSM_EVENT_3);
  TEST_ASSERT_EQUAL(FSM_NO_STATE_TRANSITION, i16CurrentState);
}

void Module_getEvent(uint16_t* out_u16Event) {
  static int count = 0;
  switch (count) {
    // Event 1
    case 0:
      *out_u16Event = FSM_EVENT_1;
      count++;
      break;

      // Event 3
    case 1:
      *out_u16Event = FSM_EVENT_3;
      count++;
      break;

      // Event 1
    case 2:
      *out_u16Event = FSM_EVENT_1;
      count++;
      break;

      // Event 1
    case 3:
      *out_u16Event = FSM_EVENT_1;
      count++;
      break;

      // Event 2
    case 4:
      *out_u16Event = FSM_EVENT_2;
      count++;
      break;

    default:
      log_info("huhu");
      break;
  }
}

void test_RunThroughEntireStatemachine(void) {
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
  uint16_t u16Event;
  status_e eStatus = STATUS_ERROR;
  uint8_t u8Data = 0U;

  // Set up the object
  FSM_Config_t sFsmConfig = {
      .NUMBER_OF_EVENTS = FSM_EVENT_LAST,
      .NUMBER_OF_STATES = FSM_STATE_LAST,
      .psaTransitionMatrix = (int16_t*)&FSM_transitionMatrix,
      .psStateCbs = saStateCb,
      .pfnGetEvent = Module_getEvent,
      .i16CurrentState = FSM_STATE_A  // Set initial State to A
  };

  // Introduce an EVENT_1 as a trigger to move from A to B
  (sFsmConfig.pfnGetEvent)(&u16Event);
  TEST_ASSERT_EQUAL(FSM_EVENT_1, u16Event);
  runState(&sFsmConfig, &u8Data);

  // Verify that the current State is B
  TEST_ASSERT_EQUAL(FSM_STATE_B, sFsmConfig.i16CurrentState);

  // // Introduce an EVENT_3 as a trigger to move from B to C
  // (sFsmConfig.pfnGetEvent)(&u16Event);
  // TEST_ASSERT_EQUAL(FSM_STATE_B, u16CurrentState);
  // TEST_ASSERT_EQUAL(FSM_EVENT_3, u16Event);
  // eStatus = runState(&sFsmConfig, &u16CurrentState, u16Event, &u8Data);
  // TEST_ASSERT_EQUAL(STATUS_SUCCESS, eStatus);

  // // Verify that the current State is C
  // TEST_ASSERT_EQUAL(FSM_STATE_C, u16CurrentState);

  // // Introduce an EVENT_1 as a trigger to move from C to A
  // (sFsmConfig.pfnGetEvent)(&u16Event);
  // TEST_ASSERT_EQUAL(FSM_STATE_C, u16CurrentState);
  // TEST_ASSERT_EQUAL(FSM_EVENT_1, u16Event);
  // eStatus = runState(&sFsmConfig, &u16CurrentState, u16Event, &u8Data);
  // TEST_ASSERT_EQUAL(STATUS_SUCCESS, eStatus);

  // // Verify that the current State is A
  // TEST_ASSERT_EQUAL(FSM_STATE_A, u16CurrentState);

  // // Introduce an EVENT_1 as a trigger to move from A to B
  // (sFsmConfig.pfnGetEvent)(&u16Event);
  // TEST_ASSERT_EQUAL(FSM_STATE_A, u16CurrentState);
  // TEST_ASSERT_EQUAL(FSM_EVENT_1, u16Event);
  // eStatus = runState(&sFsmConfig, &u16CurrentState, u16Event, &u8Data);
  // TEST_ASSERT_EQUAL(STATUS_SUCCESS, eStatus);

  // // Verify that the current State is B
  // TEST_ASSERT_EQUAL(FSM_STATE_B, u16CurrentState);

  // // Introduce an EVENT_2 as a trigger to move from B to A
  // (sFsmConfig.pfnGetEvent)(&u16Event);
  // TEST_ASSERT_EQUAL(FSM_STATE_B, u16CurrentState);
  // TEST_ASSERT_EQUAL(FSM_EVENT_2, u16Event);
  // eStatus = runState(&sFsmConfig, &u16CurrentState, u16Event, &u8Data);
  // TEST_ASSERT_EQUAL(STATUS_SUCCESS, eStatus);

  // // Verify that the current state is A
  // TEST_ASSERT_EQUAL(FSM_STATE_A, u16CurrentState);
}

// Wenn in einem der States ein Event zu triggern ist, wie bekomm ich diese
// Informationen heraus?

// Ich brauch eine Funktion, die "getEvent" heißt und von
//  überall her die Events zusammensammelt
//  - Vom Message Broker
//  - von der internen State Machine
//  Diese Funktion führt dann ein Mapping durch - also die Events auf die
//  inputs für die getState function

/**
 * Was sind die Schritte, die eine Statemachine durchgehen muss?
 * - Collect all Events - determine whether there are any
 * - Determine which State (Action) is to be executed
 * - Execute the respective State
 */
