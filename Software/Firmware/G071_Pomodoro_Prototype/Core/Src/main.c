/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdint.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TOTAL_LEDS 24
#define BIT_WIDTH_RGB_LED 24
#define NUMBER_OF_OFF_PULSES_BETWEEN_LED_PULSES 50
#define PWM_DATA_SIZE (BIT_WIDTH_RGB_LED * TOTAL_LEDS) + NUMBER_OF_OFF_PULSES_BETWEEN_LED_PULSES

#define WS2812B_HIGH_BIT 40
#define WS2812B_LOW_BIT 20
#define WS2812B_OFF 0

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t bDataIsSent = 0;
uint16_t au16PwmData[PWM_DATA_SIZE];
uint8_t u8LedData[TOTAL_LEDS][4]; // This stores the color data values of the LEDs

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void WS2812_show(void);
void WS2812B_setPixelColor(int ledIndex, int red, int green, int blue);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void WS2812B_setPixelColor(int ledIndex, int red, int green, int blue)
{
  u8LedData[ledIndex][0] = ledIndex;
  u8LedData[ledIndex][1] = green;
  u8LedData[ledIndex][2] = red;
  u8LedData[ledIndex][3] = blue;
}

void WS2812_show(void)
{
  uint32_t u32LedPulses = 0;
  uint32_t color;
  /**
   * PWM for LED Illumination
   */
  for (int k = 0; k < TOTAL_LEDS; k++)
  {
    color = ((u8LedData[k][1] << 16) | // green
             (u8LedData[k][2] << 8) |  // red
             (u8LedData[k][3]));       // blue

    /**
     * Parsing of the color Array and inserting the respective PWM Value
     * For PWM generation
     */
    for (int8_t i = BIT_WIDTH_RGB_LED - 1; i >= 0; i--)
    {
      if (color & (1 << i))
      {
        au16PwmData[u32LedPulses] = WS2812B_HIGH_BIT;
      }
      else
      {
        au16PwmData[u32LedPulses] = WS2812B_LOW_BIT;
      }
      u32LedPulses++;
    }
  }

  /**
   * Insert some 0 values as a reset value to be placed in
   * between sequences
   */
  for (uint8_t i = 0; i < NUMBER_OF_OFF_PULSES_BETWEEN_LED_PULSES; i++)
  {
    au16PwmData[u32LedPulses] = WS2812B_OFF;
    u32LedPulses++;
  }

  HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)au16PwmData, u32LedPulses);

  // while (!bDataIsSent)
  // {
  //   /* Do nothing an wait forever */
  // }
  // bDataIsSent = 0;
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_RTC_Init();
  MX_TIM1_Init();
  MX_TIM14_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t led_index = 0;

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    if (led_index % TOTAL_LEDS == 0)
    {
      led_index = 0;
    }

    uint8_t effect[TOTAL_LEDS] = {2, 5, 5, 5, 2};
    uint8_t effect_size = sizeof(effect);
    for (uint8_t i = 0; i <= TOTAL_LEDS; i++)
    {
      WS2812B_setPixelColor(i, 0, 0, 0);
    }
    for (uint8_t i = 0; i < effect_size; i++)
    {
      uint8_t tmp = (led_index + i) % TOTAL_LEDS;
      WS2812B_setPixelColor(tmp, effect[i], effect[i], effect[i]);
    }

    WS2812_show();
    led_index++;

    HAL_Delay(30);
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
   */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Configure LSE Drive Capability
   */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 9;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  /**
   * The DMA needs to be stopped, otherwise the signal
   * is repeated over and over again.
   * The problem remains, nonetheless: It takes the
   * ISR a couple of cycles to stop the TIM PWM
   * Therefore the TIM PWM continues to send out numbers
   */
  HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);

  bDataIsSent = 1;
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
