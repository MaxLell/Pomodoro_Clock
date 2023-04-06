#include "RealTimeClock.h"
#include "main.h"

extern RTC_HandleTypeDef hrtc;

/**
 * @brief  Get the current time from the RTC. This is only a wrapper
 *        function for the HAL_RTC_GetTime() function.
 * @retval RealTimeClock_Time
 */
RealTimeClock_Time RealTimeClock_getTime(void)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    RealTimeClock_Time currentTime = {0};
    currentTime.hour = sTime.Hours;
    currentTime.minute = sTime.Minutes;
    currentTime.second = sTime.Seconds;
    return currentTime;
}

status_t RealTimeClock_getCurrentMinute(uint8_t *u8Minute)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};
    HAL_StatusTypeDef tStatus;
    tStatus = HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    if (tStatus != HAL_OK)
    {
        log_error("HAL_RTC_GetTime() failed with error code: %d", tStatus);
        return STATUS_UNKNOWN_ERR;
    }

    tStatus = HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
    if (tStatus != HAL_OK)
    {
        log_error("HAL_RTC_GetDate() failed with error code: %d", tStatus);
        return STATUS_UNKNOWN_ERR;
    }

    *u8Minute = sTime.Minutes;
    return STATUS_OK;
}
