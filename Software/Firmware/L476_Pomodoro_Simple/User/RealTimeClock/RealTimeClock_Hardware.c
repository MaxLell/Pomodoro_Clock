#include "RealTimeClock_Hardware.h"
#include "main.h"

extern RTC_HandleTypeDef hrtc;

status_t RealTimeClockHW_getTimeAndDate(RealTimeClock_TimeAndDate_t *inout_pTimeAndDate)
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

    inout_pTimeAndDate->u8Hour = sTime.Hours;
    inout_pTimeAndDate->u8Minute = sTime.Minutes;
    inout_pTimeAndDate->u8Second = sTime.Seconds;
    inout_pTimeAndDate->u8Day = sDate.Date;
    inout_pTimeAndDate->u8Month = sDate.Month;
    inout_pTimeAndDate->u8Year = sDate.Year;

    return STATUS_OK;
}