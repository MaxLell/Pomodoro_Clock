#ifndef FSM_H
#define FSM_H

#include "Common.h"

typedef void (*FSM_StateActionCb)(void);

typedef struct {
  const uint16_t NUMBER_OF_STATES;
  const uint16_t NUMBER_OF_EVENTS;
  const uint16_t* au16TransitionMatrix;
  const FSM_StateActionCb* asStateActions;
  uint16_t u16CurrentState;
  uint16_t u16CurrentEvent;
} FSM_Config_t;

void FSM_setTriggerEvent(FSM_Config_t* const inout_psFsmConfig,
                         uint16_t in_u16Event);

void FSM_getNextState(FSM_Config_t* const inout_psFsmConfig);

void FSM_runStateAction(const FSM_Config_t* const in_psFsmConfig);

void FSM_execute(FSM_Config_t* const in_psFsmConfig);

void FSM_checkConfig(const FSM_Config_t* const in_psFsmConfig);

#endif  // FSM_H
