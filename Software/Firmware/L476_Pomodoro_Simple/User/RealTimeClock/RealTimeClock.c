#include "RealTimeClock.h"
#include "main.h"

extern RTC_HandleTypeDef hrtc;

RealTimeClock_Time RealTimeClock_getTime(void)
{
    RealTimeClock_Time currentTime = {0};
    RTC_TimeTypeDef rtcTime = {0};
    HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN);
    currentTime.hour = rtcTime.Hours;
    currentTime.minute = rtcTime.Minutes;
    currentTime.second = rtcTime.Seconds;
    return currentTime;
}
