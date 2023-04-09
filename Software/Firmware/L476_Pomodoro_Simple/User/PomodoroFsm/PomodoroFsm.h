#ifndef POMODOROFSM_H
#define POMODOROFSM_H

#include "Common.h"

typedef enum
{
    E_PFSM_STATE_IDLE = 0U,
    E_PFSM_STATE_WORKTIME,
    E_PFSM_STATE_BREAKTIME,
    E_PFSM_STATE_SEEKING_ATTENTION,
} PomodoroFsm_state_e;

typedef struct
{
    BOOL bButtonPressed;
    uint8_t u8CurrentMinute;
    uint8_t u8LightControlState;
} PomodoroFsm_inputs_t;

void PomodoroFsm_init(void);

void PomodoroFsm_execute(void);

#endif // POMODOROFSM_H
