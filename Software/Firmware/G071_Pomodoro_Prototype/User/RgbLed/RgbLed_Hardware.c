#include "RgbLed_Hardware.h"
#include "main.h"
#include "tim.h"
#include "Common.h"

STATIC BOOL bPwmDataIsSent = FALSE;

void RgbLed_Hardware_init(void)
{
    bPwmDataIsSent = FALSE;
}

void RgbLed_SetLeds(uint16_t *au16PwmData, uint16_t u16PwmDataSize)
{
    bPwmDataIsSent = TRUE;
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)au16PwmData, u16PwmDataSize);

    while (bPwmDataIsSent)
    {
        // Do nothing
    }
}

void RgbLed_ISR(void)
{
    HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
}