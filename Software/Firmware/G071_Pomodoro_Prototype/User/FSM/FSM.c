#include "FSM.h"

void FSM_checkConfig(const FSM_Config_t* const in_psFsmConfig) {
  // Check the config inputs
  // Null Pointer Checks for all entries
  ASSERT_MSG(!(in_psFsmConfig == NULL), "Config is NULL");
  ASSERT_MSG(!(in_psFsmConfig->au16TransitionMatrix == NULL),
             "Transition Matrix is NULL");
  ASSERT_MSG(!(in_psFsmConfig->asStateActions == NULL),
             "State Actions Array is NULL");

  // out of bounds checks for the Elements
  ASSERT_MSG(!(in_psFsmConfig->NUMBER_OF_STATES == 0), "Number of States is 0");
  ASSERT_MSG(!(in_psFsmConfig->NUMBER_OF_EVENTS == 0), "Number of Events is 0");
  ASSERT_MSG(
      !(in_psFsmConfig->u16CurrentState >= in_psFsmConfig->NUMBER_OF_STATES),
      "Current State is out of bounds");
  ASSERT_MSG(
      !(in_psFsmConfig->u16CurrentEvent >= in_psFsmConfig->NUMBER_OF_EVENTS),
      "Current Event is out of bounds");
}

void FSM_setTriggerEvent(FSM_Config_t* const inout_psFsmConfig,
                         uint16_t in_u16Event) {
  {  // Input Checks
    FSM_checkConfig(inout_psFsmConfig);
    ASSERT_MSG(!(in_u16Event >= inout_psFsmConfig->NUMBER_OF_EVENTS),
               "Event is not valid");
  }
  inout_psFsmConfig->u16CurrentEvent = in_u16Event;
}

void FSM_getNextState(FSM_Config_t* const inout_psFsmConfig) {
  {  // Input Checks
    FSM_checkConfig(inout_psFsmConfig);
  }

  // Approach taken from https://stackoverflow.com/a/54103595
  const uint16_t* au16Matrix = inout_psFsmConfig->au16TransitionMatrix;
  uint16_t u16NofEvents = inout_psFsmConfig->NUMBER_OF_EVENTS;
  uint16_t u16Event = inout_psFsmConfig->u16CurrentEvent;
  uint16_t u16State = inout_psFsmConfig->u16CurrentState;

  inout_psFsmConfig->u16CurrentState =
      *(au16Matrix + (u16State * u16NofEvents) + u16Event);

  ASSERT_MSG(!(inout_psFsmConfig->u16CurrentState >=
               inout_psFsmConfig->NUMBER_OF_STATES),
             "Next State is out of bounds");
}

void FSM_runStateAction(const FSM_Config_t* const in_psFsmConfig) {
  {  // Input Checks
    FSM_checkConfig(in_psFsmConfig);
  }
  uint16_t u16State = in_psFsmConfig->u16CurrentState;
  FSM_StateActionCb runStateAction = in_psFsmConfig->asStateActions[u16State];
  ASSERT_MSG(!(runStateAction == NULL), "State Callback is NULL");
  runStateAction();
}

void FSM_execute(FSM_Config_t* const inout_psFsmConfig) {
  {  // Input Checks
    FSM_checkConfig(inout_psFsmConfig);
  }
  FSM_getNextState(inout_psFsmConfig);
  FSM_runStateAction(inout_psFsmConfig);
}