/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "semphr.h"
#include "mpu6050.h"  //mpu6050
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "tftlcd.h"

//mpu6050
float pitch,roll,yaw; 		//欧拉角
short aacx,aacy,aacz;			//加速度传感器原始数据
float aacx1,aacy1,aacz1;			//加速度传感器原始数据
short gyrox,gyroy,gyroz;		//陀螺仪原始数据
float gyrox1,gyroy1,gyroz1;		//陀螺仪原始数据
short temp;						//温度
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
extern osSemaphoreId_t BinSem_StoreReadyHandle;  //在freertos.c里定义的二值信号量
extern osSemaphoreId_t BinSem_DataReadyHandle;  //在freertos.c里定义的二值信号量
extern osSemaphoreId_t myBinarySem03Handle;  //在freertos.c里定义的二值信号量
/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
     PC9   ------> RCC_MCO_2
     PA8   ------> RCC_MCO_1
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE2 PE4 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PF9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : PF10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}

/* USER CODE BEGIN 2 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_2) //PE2=KeyRight, 控制 LED2 闪烁
	   {
	   //HAL_Delay(5);
	   //HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);
	   //HAL_Delay(100);  //软件消除按键抖动的影响,观察优先级的作用
	   BaseType_t  normalTaskWoken=pdFALSE;
		  if (BinSem_DataReadyHandle!= NULL)
		  {

			  xSemaphoreGiveFromISR(BinSem_DataReadyHandle, &normalTaskWoken);

			  portYIELD_FROM_ISR(normalTaskWoken);   //申请进行一次任务调度
		}
	   }
   else if (GPIO_Pin == GPIO_PIN_4) //PE4=KeyLeft, 控制 LED1 闪烁   调度mpu6050
	   {
	   //HAL_Delay(5);
	   //HAL_GPIO_TogglePin(GPIOF ,GPIO_PIN_10);
	   //HAL_Delay(100);  //软件消除按键抖动的影响,观察优先级的作用
	   HAL_Delay(1000);
	   run_self_test();
	   MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
	   MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
	   HAL_Delay(100); //必须延时，否则 updateRTCTime()函数处理出错



/*		   LCD_ShowInt(80,320,(int)pitch);
		   LCD_ShowInt(80,340,(int)roll);
		   LCD_ShowInt(80,360,(int)yaw);
		   */
	   //欧拉角读取
/*    if (aacx<0)
    {
    aacx=-aacx;
    }*/
	//   LCD_ShowFloat(80,320,aacx*10,4);  //欧拉角表示
/*	   aacx1=aacx;
	   aacy1=aacy;
	   aacz1=aacz;
	   aacx1=aacx1/16384*9.8;
	   aacy1=aacy1/16384*9.8;
	   aacz1=aacz1/16384*9.8;
	   gyrox1=gyrox;
	   gyroy1=gyroy;
	   gyroz1=gyroz;
	   gyrox1=gyrox1/16.4;
	   gyroy1=gyroy1/16.4;
	   gyroz1=gyroz1/16.4;
	   /*
	   LCD_ShowInt(20,320,aacx);
	   LCD_ShowInt(20,340,aacy);
	   LCD_ShowInt(20,360,aacz);

	   LCD_ShowFloat(20,320,gyrox1,2);//显示浮点数
	   LCD_ShowFloat(20,340,gyroy1,2);//显示浮点数
	   LCD_ShowFloat(20,360,gyroz1,2);//显示浮点数
	   */

	   BaseType_t  normalTaskWoken=pdFALSE;
	   		  if (myBinarySem03Handle!= NULL)
	   		  {

	   			  xSemaphoreGiveFromISR(myBinarySem03Handle, &normalTaskWoken);

	   			  portYIELD_FROM_ISR(normalTaskWoken);   //申请进行一次任务调度
	   		}
	   }
}


/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
