#include "PomodoroControl_helper.h"
#include "LightEffects_Pomodoro.h"

void PomodoroControl_helper_getMinuteArray(PomodoroControl_helper *const inout_sSelf)
{
    { // Input checks
      // Check against NULL Pointers
        ASSERT_MSG(!(NULL == inout_sSelf), "NULL Pointer");

        // Make sure that the Worktime is smaller then 121
        ASSERT_MSG(!(inout_sSelf->u8Worktime > MAX_NOF_POMODORO_MINUTES), "Worktime is bigger then 120");

        // Make sure that the Worktime is not 0
        ASSERT_MSG(!(inout_sSelf->u8Worktime == 0), "Worktime is 0");

        // Make sure that the Breaktime is smaller then 61
        ASSERT_MSG(!(inout_sSelf->u8Breaktime > MINUTES_IN_HOUR), "Breaktime is bigger then 60");

        // Make sure that the Breaktime is not 0
        ASSERT_MSG(!(inout_sSelf->u8Breaktime == 0), "Breaktime is 0");
    }

    int8_t i8CurrentWorktime = (int8_t)inout_sSelf->u8Worktime;
    int8_t i8CurrentBreaktime = (int8_t)inout_sSelf->u8Breaktime;

    uint8_t u8Sum = i8CurrentWorktime + i8CurrentBreaktime;
    BOOL bRunOnce = FALSE;

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

        if ((u8CurrentIdx >= MINUTES_IN_HOUR) && (FALSE == bRunOnce))
        {
            bRunOnce = TRUE;
            u8CurrentIdx += MINUTES_IN_HOUR + 1;
        }
        if (u8CurrentIdx >= MAX_NOF_POMODORO_MINUTES)
        {
            break;
        }
    }

    if ((u8CurrentIdx >= MINUTES_IN_HOUR) || (u8Sum >= MINUTES_IN_HOUR))
    {
        u8CurrentIdx += MINUTES_IN_HOUR;
    }

    while ((i8CurrentBreaktime > 0) && (u8CurrentIdx < MAX_NOF_POMODORO_MINUTES))
    {
        i8CurrentBreaktime--;
        inout_sSelf->au8MinuteArray[u8CurrentIdx] = E_PHASE_BREAK_TIME;
        u8CurrentIdx++;

        if (u8CurrentIdx >= MAX_NOF_POMODORO_MINUTES)
        {
            u8CurrentIdx = MINUTES_IN_HOUR;
        }
    }
}