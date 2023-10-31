/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
 uint8_t  proBuffer[10]="#S45;";  //用于处理的数据
 uint8_t  rxBuffer[10]="#H12;";  //接收数据缓冲区
 uint8_t rxCompleted=RESET; //HAL_UART_Receive_IT()接收是否完成
 uint8_t  rxBufPos=0;   //缓冲区存储位置
 uint8_t feedback[10]="OK!"; //反馈，表示命令接受
 uint8_t  isUploadTime=1; //控制 RTC 周期唤醒中断里是否上传时间数据
/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 57600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		rxCompleted=SET; //接收完成
		for(uint16_t i=0; i<RX_CMD_LEN; i++)
			proBuffer[i]=rxBuffer[i];
			__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE); //开启 IDLE 中断
	}
}
void on_UART_IDLE(UART_HandleTypeDef *huart)
{
	if(__HAL_UART_GET_IT_SOURCE(huart,UART_IT_IDLE) == RESET)
		return;   __HAL_UART_CLEAR_IDLEFLAG(huart);  //清除 IDLE 标志
	__HAL_UART_DISABLE_IT(huart, UART_IT_IDLE);  //禁止 IDLE 中断
     if (rxCompleted) //接收到了一个字节
    	 {
    	  uint8_t  ch=rxBuffer[0];   //接收到的一个字节
    	  if (ch=='#') //起始符
    		  rxBufPos=0;  //存储位置复位
    	  proBuffer[rxBufPos]=ch;  //存储到缓冲区
    	  rxBufPos++;  //存储位置移动
    	  if (ch==';')   //结束符
    		  {
    		  proBuffer[0]='#';
    		  HAL_UART_Transmit(huart,proBuffer,rxBufPos,200); //上传
    		  HAL_Delay(100); //必须延时，否则 updateRTCTime()函数处理出错
    		  updateRTCTime(); //处理指令
    		  }
    	 rxCompleted=RESET;
    	 HAL_UART_Receive_IT(huart, rxBuffer,RX_CMD_LEN);//再次启动输入
    	 }
}
void updateRTCTime() //根据串口接收的数据进行处理  (暂时作出如下处理，为以后命令读入和功能拓展做准备)
{
	if (proBuffer[0] != '#') //非有效指令
		return;
	 HAL_UART_Transmit(&huart1,feedback,sizeof(feedback),200);  //反馈，表示命令收到
	uint8_t timeSection=proBuffer[1]; //类型字符
	uint8_t timeSection1=proBuffer[2]; //类型字符
	uint8_t timeSection2=proBuffer[3]; //类型字符
	uint8_t tmp10=proBuffer[2]-0x30; //十位数
	uint8_t tmp1 =proBuffer[3]-0x30; //个位数
	uint8_t val=10*tmp10+tmp1;
	uint8_t temp1[40]="#S45 "; //发送变量存储
	if ((timeSection=='R')&&(timeSection1=='T')&&(timeSection2=='C')) //是否上传  时间温度
	{
		isUploadTime=!isUploadTime;
		return;
	}
	if ((timeSection=='M')&&(timeSection1=='P')&&(timeSection2=='U'))   //MPU功能检测
	{
			if(mpu_dmp_init())
			{
				uint8_t	temp1[]="MPU6050 Error!\n";
				HAL_UART_Transmit(&huart1,temp1,sizeof(temp1),200);
				delay_ms(100);
			}
			else
			{
				uint8_t temp1[]="MPU6050 OK!\n         ";
				HAL_UART_Transmit(&huart1,temp1,sizeof(temp1),200);
				delay_ms(100);
			}
		return;
	}
	if ((timeSection=='D')&&(timeSection1=='S')&&(timeSection2=='B')) //温度传感器检测
	{
		if(DS18B20_Init())
		{
			uint8_t	temp1[]="DS18B20 Error!\n";
			HAL_UART_Transmit(&huart1,temp1,sizeof(temp1),200);
			delay_ms(100);
		}
		else
		{
			uint8_t temp1[]="DS18B20 OK!\n         ";
			HAL_UART_Transmit(&huart1,temp1,sizeof(temp1),200);
			delay_ms(100);
		}
	return;
	}
	if ((timeSection=='R')&&(timeSection1=='O')&&(timeSection2=='M')) //eeprom检测
	{
		if(AT24CXX_Check())
		{
			uint8_t	temp1[]="24C02 Check Failed!\n";
			HAL_UART_Transmit(&huart1,temp1,sizeof(temp1),200);
			delay_ms(100);
		}
		else
		{
			uint8_t temp1[]="24C02 Ready!\n         ";
			HAL_UART_Transmit(&huart1,temp1,sizeof(temp1),200);
			delay_ms(100);
		}
	return;
	}
	if ((timeSection=='R')&&(timeSection1=='S')&&(timeSection2=='T')) //软件复位
	{
			uint8_t temp1[]="Restart!\n         ";
			HAL_UART_Transmit(&huart1,temp1,sizeof(temp1),200);
			delay_ms(100);
		    __set_FAULTMASK(1);
		    NVIC_SystemReset();  //软件复位
	        return;
	}
	else
	{
		uint8_t	temp1[]="Error Command!\n";
		HAL_UART_Transmit(&huart1,temp1,sizeof(temp1),200);
		delay_ms(100);
	}
	if (timeSection=='R')
	{
		val=1;
	}
	else if (timeSection=='m')   //月（和分钟区分开）
			val=1;
	else if (timeSection=='D')   //日
			val=1;
	else if (timeSection=='W')   //星期
			val=1;
	 uint8_t  proBuffer[10]="#S45;";  //用于处理的数据
	 uint8_t  rxBuffer[10]="#H12;";  //接收数据缓冲区

}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
