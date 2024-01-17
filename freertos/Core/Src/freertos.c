/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stdio.h"
#include "ds18b20.h"
#include "TM1637.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"
#include "UartRingbuffer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
  uint8_t temperature ;
  uint8_t logString[] = "to lam duoc";
  uint8_t displayData[4] = {0};
  uint8_t messageLength = 0;
  extern char receivedMessage[6];
  uint8_t receivedData;
  int i = 0;
  int condition = 1;
  char string[64];
  char message[6] = "ledddd";
  char message2[] = "stop";
  uint8_t uartRxBuffer[50];
  char logMessage[] = "start?\n"; 
  extern Ds18b20Sensor_t ds18b20[_DS18B20_MAX_SENSORS];
  char receivedString[4];
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
/* Definitions for task1 */
osThreadId_t task1Handle;
const osThreadAttr_t task1_attributes = {
  .name = "task1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for task2 */
osThreadId_t task2Handle;
const osThreadAttr_t task2_attributes = {
  .name = "task2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for task3 */
osThreadId_t task3Handle;
const osThreadAttr_t task3_attributes = {
  .name = "task3",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void task1function(void *argument);
void task2function(void *argument);
void StartTask03(void *argument);

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
  /* creation of task1 */
  task1Handle = osThreadNew(task1function, NULL, &task1_attributes);

  /* creation of task2 */
  task2Handle = osThreadNew(task2function, NULL, &task2_attributes);

  /* creation of task3 */
  task3Handle = osThreadNew(StartTask03, NULL, &task3_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_task1function */
/**
  * @brief  Function implementing the task1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_task1function */
void task1function(void *argument)
{
  /* USER CODE BEGIN task1function */

  /* Infinite loop */
 for (;;) {
    HAL_UART_Transmit(&huart1, (uint8_t *)"okelahhh\r\n", 8 , 100);
    
    if(receivedMessage[0] == 'l'){
      HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
        osDelay(1000);
    }
    osDelay(1000);

    // So sánh chuỗi và phát Semaphore nếu chuỗi bằng với một giá trị mong muốn
//    if ( Wait_for(message)) {
        //osSemaphoreRelease(SemaHandle);;
//    }
}
      osDelay(1000);
}


  /* USER CODE END task1function */


/* USER CODE BEGIN Header_task2function */
/**
* @brief Function implementing the task2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_task2function */
void task2function(void *argument)
{
  /* USER CODE BEGIN task2function */
  /* Infinite loop */
	//HAL_UART_Transmit(&huart1, (uint8_t *)logMessage, 8 , 100);
//  extern UART_HandleTypeDef huart1;
  for(;;)
  {
      DS18B20_ReadAll();
      DS18B20_StartAll();

  }
  osDelay(100);
  /* USER CODE END task2function */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the task3 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
	//HAL_UART_Transmit(&huart1, (uint8_t *)logMessage, 8 , 100);
  /* Infinite loop */
   for(;;)
  {
      temperature = ds18b20[0].Temperature;
      sprintf(string, "%d C\n",temperature);
      HAL_UART_Transmit(&huart1, (uint8_t *)string, sizeof(string), 100);
      tm1637_DisplayInteger(temperature);
      osDelay(1000);
   }
   osDelay(1000);
}
  /* USER CODE END StartTask03 */


/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

