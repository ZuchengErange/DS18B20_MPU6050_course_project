/**
  ******************************************************************************
  * File Name          : RTC.c
  * Description        : This file provides code for the configuration
  *                      of the RTC instances.
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
#include "rtc.h"

/* USER CODE BEGIN 0 */
#include "tftlcd.h"
#include "ds18b20.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "semphr.h"


uint8_t counter=0;//计数
uint32_t Point_old,Point_new;//保存坐标
float temperature;    //定义温度临时变量

//所用到的字符串变量
uint8_t timeStr[]="15:32:06 \r\n";  //时间字符串
uint8_t tempStr[]="18.5 C\r\n";  //温度字符串
uint16_t size_time=0;
uint16_t size_temp=0;
extern osSemaphoreId_t BinSem_DataReadyHandle;  //在freertos.c里定义的二值信号量
extern osSemaphoreId_t BinSem_StoreReadyHandle;  //在freertos.c里定义的二值信号量
/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /** Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
    
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date 
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable the WakeUp 
  */
  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0, RTC_WAKEUPCLOCK_CK_SPRE_16BITS) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */
    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();

    /* RTC interrupt Init */
    HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();

    /* RTC interrupt Deinit */
    HAL_NVIC_DisableIRQ(RTC_WKUP_IRQn);
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
//显示时间
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;
	const uint8_t  charW=8;  //一个字符的宽度
	if (HAL_RTC_GetTime(hrtc, &sTime, RTC_FORMAT_BIN) == HAL_OK)
	{
	HAL_RTC_GetDate(hrtc, &sDate, RTC_FORMAT_BIN);
	/* 调用 HAL_RTC_GetTime()之后必须调用 HAL_RTC_GetDate()以解锁数据，才能连续更新日期和时间 */
	uint16_t  yPos=50;
	uint16_t  xPos=30;

	uint8_t hour=sTime.Hours;
	uint8_t tmp10,tmp1;
	tmp10=hour/10+0x30; //ASCII 码,十位数
	tmp1=hour%10+0x30; //ASCII 码，个位数
	timeStr[0]=tmp10;
	timeStr[1]=tmp1;
	uint8_t min=sTime.Minutes;
	tmp10=min/10+0x30; //ASCII 码,十位数
	tmp1=min%10+0x30;  //ASCII 码，个位数
	timeStr[3]=tmp10;
	timeStr[4]=tmp1;
	uint8_t sec=sTime.Seconds;
	tmp10=sec/10+0x30; //ASCII 码,十位数
	tmp1=sec%10+0x30;  //ASCII 码，个位数
	timeStr[6]=tmp10;
	timeStr[7]=tmp1;

	size_time=sizeof(timeStr);

	LCD_ShowString(10,yPos, "Time:");//位置要改
	LCD_ShowString(xPos+30,yPos, timeStr);//位置要改
	if (isUploadTime) //变量 isUploadTime 在文件 usart.c 中定义
	HAL_UART_Transmit(&huart1,timeStr,sizeof(timeStr),200);
	}

	// HAL_Delay(1000);  //在后面的测试代码中用到时取消注释
//温度采集


	 uint8_t tmp10,tmp1;
	 uint8_t temper = 0;
	 temperature=DS18B20_Get_Temp();	  //得到温度临时变量
	 temperature=temperature/10-10;


/*	 if(temperature<0)
		{
		  LCD_ShowChar(50,80,'-',0);			//显示负号
		  temperature=-temperature;					//转为正数
		}else LCD_ShowChar(50,80,' ',0);			//去掉负号
	  LCD_ShowFloat(60,80,temperature,1);
*/
/*	  if(counter<240)
	  {
	  Point_new=300-(int)(temperature*200/30);//温度范围 0--30度
	  counter++;
	  if(counter>2)//滤除刚开始的异常数据
	  LCD_DrawLine_Color(counter-1,Point_old,counter,Point_new,lcdColor_RED);
	  Point_old=Point_new;
	  }
*/
	  temper=temperature;
	  tmp10=temper/10+0x30; //ASCII 码,十位数
	  tmp1=temper%10+0x30; //ASCII 码，个位数
	  tempStr[0]=tmp10;
	  tempStr[1]=tmp1;
	  temper=(temperature-(int)(temperature))*10;//取小数部分
	  tempStr[3]=temper+0x30;

	  size_temp=sizeof(tempStr);

	  if (isUploadTime) //变量 isUploadTime 在文件 usart.c 中定义
	  HAL_UART_Transmit(&huart1,tempStr,sizeof(tempStr),200);

	  BaseType_t  highTaskWoken=pdFALSE;
	  if (BinSem_StoreReadyHandle != NULL)
	  {
		  xSemaphoreGiveFromISR(BinSem_StoreReadyHandle, &highTaskWoken);

		  portYIELD_FROM_ISR(highTaskWoken);   //申请进行一次任务调度
	  }

}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
