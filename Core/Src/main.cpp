/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "stm32f4xx_hal_i2c.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "adc.h"
#include "dma.h"
#include "gpio.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "system_clock.h"
#include "gpio.hpp"
#include "motor_driver.h"
#include "i2c1.h"


void StartDefaultTask(void *argument);
void IR_sensor_task(void *argument);
void BLE_telemetry_task(void *arguement);
void IMU_task(void *arguement);

struct IR_readings{
    uint16_t right_IR_sensor;
    uint16_t left_IR_sensor;
    uint16_t front_IR_sensor;
};

QueueHandle_t irQueue;

int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_SPI2_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM11_Init();

  /* Create the thread(s) */
  /* creation of defaultTask */
    BaseType_t result = xTaskCreate(
      StartDefaultTask,
      "defaultTask",
      512,
      NULL,
      2,
      NULL
  );

  if (result != pdPASS) {
    Error_Handler();
  }

  BaseType_t result2 = xTaskCreate(
      IR_sensor_task,
      "IR_sensors",
      128,
      NULL,
      4,
      NULL
  );

  if (result2 != pdPASS) {
    Error_Handler();
  }

  BaseType_t result3 = xTaskCreate(
      BLE_telemetry_task,
      "Bluetooth telemetry",
      128,
      NULL,
      1,
      NULL
  );

  if (result3 != pdPASS) {
    Error_Handler();
  }

  BaseType_t result4 = xTaskCreate(
      IMU_task,
      "IMU",
      128,
      NULL,
      3,
      NULL
  );

  if (result4 != pdPASS) {
    Error_Handler();
  }

  irQueue = xQueueCreate(1, sizeof(IR_readings));

  if (irQueue == NULL) {
    Error_Handler();
  }

  /* Init scheduler */
  vTaskStartScheduler();

  /* We should never get here as control is now taken by the scheduler */
  Error_Handler();
  /* Infinite loop */
  while (1)
  {
    
  }
}


/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* Infinite loop */
  GPIO LED(GPIOA,GPIO_PIN_5);
  motor_init();
  while(1)
  {
    motor_brake();
    LED.toggle();
    vTaskDelay(50);
  }
}

void IR_sensor_task(void *argument)
{
  /* USER CODE BEGIN 5 */
  IR_readings readings;

  /* Infinite loop */
  while(1)
  {
    readings.right_IR_sensor = 100;
    readings.left_IR_sensor = 200;
    readings.front_IR_sensor = 300;

    xQueueOverwrite(irQueue, &readings);

    vTaskDelay(10);
  }
  /* USER CODE END 5 */
}

void BLE_telemetry_task(void *argument)
{
  /* USER CODE BEGIN 5 */
  
  /* Infinite loop */
  while(1)
  {
    vTaskDelay(10);
  }
  /* USER CODE END 5 */
}

void IMU_task(void *argument)
{
  /* USER CODE BEGIN 5 */
  
  /* Infinite loop */
  while(1)
  {
    vTaskDelay(10);
  }
  /* USER CODE END 5 */
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM10)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
