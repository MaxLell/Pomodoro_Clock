/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for executerTask */
osThreadId_t executerTaskHandle;
const osThreadAttr_t executerTask_attributes = {
  .name = "executerTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for msgBrokerTask */
osThreadId_t msgBrokerTaskHandle;
const osThreadAttr_t msgBrokerTask_attributes = {
  .name = "msgBrokerTask",
  .priority = (osPriority_t) osPriorityAboveNormal,
  .stack_size = 128 * 4
};
/* Definitions for absTimeTask */
osThreadId_t absTimeTaskHandle;
const osThreadAttr_t absTimeTask_attributes = {
  .name = "absTimeTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for ringMgmtTask */
osThreadId_t ringMgmtTaskHandle;
const osThreadAttr_t ringMgmtTask_attributes = {
  .name = "ringMgmtTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for buttonTask */
osThreadId_t buttonTaskHandle;
const osThreadAttr_t buttonTask_attributes = {
  .name = "buttonTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void startExecuterTask(void *argument);
void startMessageBrokerTask(void *argument);
void startAbsTimeTask(void *argument);
void startRingMgmtTask(void *argument);
void startButtonTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of executerTask */
  executerTaskHandle = osThreadNew(startExecuterTask, NULL, &executerTask_attributes);

  /* creation of msgBrokerTask */
  msgBrokerTaskHandle = osThreadNew(startMessageBrokerTask, NULL, &msgBrokerTask_attributes);

  /* creation of absTimeTask */
  absTimeTaskHandle = osThreadNew(startAbsTimeTask, NULL, &absTimeTask_attributes);

  /* creation of ringMgmtTask */
  ringMgmtTaskHandle = osThreadNew(startRingMgmtTask, NULL, &ringMgmtTask_attributes);

  /* creation of buttonTask */
  buttonTaskHandle = osThreadNew(startButtonTask, NULL, &buttonTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_startExecuterTask */
/**
  * @brief  Function implementing the executerTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_startExecuterTask */
void startExecuterTask(void *argument)
{
  /* USER CODE BEGIN startExecuterTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END startExecuterTask */
}

/* USER CODE BEGIN Header_startMessageBrokerTask */
/**
* @brief Function implementing the msgBrokerTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startMessageBrokerTask */
void startMessageBrokerTask(void *argument)
{
  /* USER CODE BEGIN startMessageBrokerTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END startMessageBrokerTask */
}

/* USER CODE BEGIN Header_startAbsTimeTask */
/**
* @brief Function implementing the absTimeTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startAbsTimeTask */
void startAbsTimeTask(void *argument)
{
  /* USER CODE BEGIN startAbsTimeTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END startAbsTimeTask */
}

/* USER CODE BEGIN Header_startRingMgmtTask */
/**
* @brief Function implementing the ringMgmtTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startRingMgmtTask */
void startRingMgmtTask(void *argument)
{
  /* USER CODE BEGIN startRingMgmtTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END startRingMgmtTask */
}

/* USER CODE BEGIN Header_startButtonTask */
/**
* @brief Function implementing the buttonTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startButtonTask */
void startButtonTask(void *argument)
{
  /* USER CODE BEGIN startButtonTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END startButtonTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

