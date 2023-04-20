#ifndef POMODOROFSM_H
#define POMODOROFSM_H

#include "Common.h"
#include "PomodoroFsm_Interface.h"

typedef struct
{
    BOOL bButtonPressed;
    uint8_t u8CurrentMinute;
    uint8_t u8WorktimeEndMin;
    uint8_t u8BreaktimeEndMin;
} PomodoroFsm_inputs_t;

void PomodoroFsm_init(void);

void PomodoroFsm_execute(void);

#endif // POMODOROFSM_H
