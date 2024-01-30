#include "PomodoroControl_helper.h"
#include "LightEffects_Pomodoro.h"

void PomodoroControl_helper_getMinuteArrayFromConfig(PomodoroControl_helper *const inout_sSelf)
{
    { // Input checks
      // TBD

        // Make sure that the Worktime is smaller then 121

        // Make sure that the Breaktime is smaller then 61
    }

    int8_t i8CurrentWorktime = (int8_t)inout_sSelf->u8Worktime;
    int8_t i8CurrentBreaktime = (int8_t)inout_sSelf->u8Breaktime;

    uint8_t u8Sum = i8CurrentWorktime + i8CurrentBreaktime;
    BOOL bOneRingComplete = FALSE;

    uint8_t u8CurrentIdx = 0;

    // Fill the entire Minute Array with NONE Phase Entries
    for (uint8_t i = 0; i < MAX_NOF_POMODORO_MINUTES; i++)
    {
        inout_sSelf->au8MinuteArray[i] = E_PHASE_NONE;
    }

    // Fill in the Worktime
    while (i8CurrentWorktime > 0)
    {
        i8CurrentWorktime--;
        inout_sSelf->au8MinuteArray[u8CurrentIdx] = E_PHASE_WORK_TIME;
        u8CurrentIdx++;

        if (u8CurrentIdx >= MINUTES_IN_HOUR)
        {
            bOneRingComplete = TRUE;
            u8CurrentIdx += MINUTES_IN_HOUR + 1;
        }
        if (u8CurrentIdx >= (MINUTES_IN_HOUR * 2))
        {
            break;
        }
    }

    if ((u8CurrentIdx >= MINUTES_IN_HOUR) || (u8Sum >= MINUTES_IN_HOUR))
    {
        bOneRingComplete = TRUE;
        u8CurrentIdx += MINUTES_IN_HOUR;
    }

    while (i8CurrentBreaktime > 0)
    {
        log_info("%s", "huhu");
        i8CurrentBreaktime--;
        inout_sSelf->au8MinuteArray[u8CurrentIdx] = E_PHASE_BREAK_TIME;
        u8CurrentIdx++;

        if (u8CurrentIdx >= (MINUTES_IN_HOUR * 2))
        {
            u8CurrentIdx = MINUTES_IN_HOUR;
        }
    }
}