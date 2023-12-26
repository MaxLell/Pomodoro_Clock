#ifndef FSM_H
#define FSM_H

#include "Common.h"

typedef status_e (*FSM_Statecb)(const uint16_t* const in_u16FsmState,
                                uint8_t* const inout_pData);

typedef void (*FSM_getEventCb)(uint16_t* out_u16Event);

typedef struct {
  FSM_Statecb pfnEntry;
  FSM_Statecb pfnRun;
  FSM_Statecb pfnExit;
} FSM_StateCbs_t;

typedef struct {
  const uint16_t NUMBER_OF_STATES;
  const uint16_t NUMBER_OF_EVENTS;
  const int16_t* psaTransitionMatrix;
  const FSM_StateCbs_t* psStateCbs;
  const FSM_getEventCb pfnGetEvent;
  int16_t i16CurrentState;
} FSM_Config_t;

void FSM_getNextState(const FSM_Config_t* const in_psFsmConfig,
                      int16_t* const inout_i16State,
                      const uint16_t in_u16Event);

status_e FSM_runStateCbs(const FSM_StateCbs_t* const in_psFsmCallbacks,
                         uint16_t* const inout_u16State,
                         uint8_t* const inout_pData);

#endif  // FSM_H
