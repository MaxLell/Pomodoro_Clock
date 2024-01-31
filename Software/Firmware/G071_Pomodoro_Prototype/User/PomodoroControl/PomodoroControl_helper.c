#include "PomodoroControl_helper.h"
#include "LightEffects_Pomodoro.h"
#include "PomodoroControl_Datatypes.h"

#define LEDS_PER_RING 60

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

    uint8_t u8LocalCopyWortime = inout_sSelf->u8Worktime;
    uint8_t u8LocalCopyBreaktime = inout_sSelf->u8Breaktime;

    int8_t i8CurrentWorktime = (int8_t)inout_sSelf->u8Worktime;
    int8_t i8CurrentBreaktime = (int8_t)inout_sSelf->u8Breaktime;

    uint8_t u8Sum = i8CurrentWorktime + i8CurrentBreaktime;
    BOOL bRunOnce = FALSE;

    uint8_t u8CurrentIdx = 0;

    // Fill the entire Minute Array with NONE Phase Entries
    for (uint8_t i = 0; i < MAX_NOF_POMODORO_MINUTES; i++)
    {
        inout_sSelf->au8MinuteArray[i] = E_CFG_OFF;
    }

    // Fill in the Worktime
    while (i8CurrentWorktime > 0)
    {
        i8CurrentWorktime--;
        inout_sSelf->au8MinuteArray[u8CurrentIdx] = E_CFG_WORKTIME;
        u8CurrentIdx++;

        ASSERT_MSG(!(u8CurrentIdx > MAX_NOF_POMODORO_MINUTES), "u8CurrentIdx >= MAX_NOF_POMODORO_MINUTES");
    }

    if (u8Sum >= LEDS_PER_RING)
    {
        // Breaktime and Worktime are not fitting into on Ring
        if (u8CurrentIdx < LEDS_PER_RING)
        {
            // Add an offset of 60 to the current index
            // So that the Breaktime is rendered on teh second ring
            u8CurrentIdx += MINUTES_IN_HOUR;
        }
    }

    if (u8Sum >= 120)
    {
        // Do Nuthin
        // Do not add in the Breaktime entries - as they would exceed the second ring
    }
    else
    {
        // Fill in the Breaktime entries
        while ((i8CurrentBreaktime > 0) && (u8CurrentIdx < MAX_NOF_POMODORO_MINUTES))
        {
            i8CurrentBreaktime--;
            inout_sSelf->au8MinuteArray[u8CurrentIdx] = E_CFG_BREAKTIME;
            u8CurrentIdx++;

            if (u8CurrentIdx >= MAX_NOF_POMODORO_MINUTES)
            {
                u8CurrentIdx = MINUTES_IN_HOUR;
            }

            ASSERT_MSG(!(u8CurrentIdx >= MAX_NOF_POMODORO_MINUTES), "u8CurrentIdx >= MAX_NOF_POMODORO_MINUTES");
        }
    }

    // Make sure that the original config is not changed
    ASSERT_MSG(!(u8LocalCopyWortime != inout_sSelf->u8Worktime), "Worktime has changed");
    ASSERT_MSG(!(u8LocalCopyBreaktime != inout_sSelf->u8Breaktime), "Breaktime has changed");
    unused(u8LocalCopyWortime);   // Avoid compiler warning
    unused(u8LocalCopyBreaktime); // Avoid compiler warning
}