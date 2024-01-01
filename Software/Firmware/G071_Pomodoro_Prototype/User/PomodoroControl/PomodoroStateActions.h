#ifndef POMODORO_STATE_ACTIONS_H
#define POMODORO_STATE_ACTIONS_H

void StateActionIdle(void);
void StateActionWorktimeInit(void);
void StateActionWorktime(void);
void StateActionWarning(void);
void StateActionBreaktimeInit(void);
void StateActionBreaktime(void);
void StateActionCancelSequenceRunning(void);
void StateActionCancelSequenceHalted(void);

#endif  // POMODORO_STATE_ACTIONS_H
