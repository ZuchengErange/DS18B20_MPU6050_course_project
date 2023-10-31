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
 uint8_t  proBuffer[10]="#S45;";  //���ڴ��������
 uint8_t  rxBuffer[10]="#H12;";  //�������ݻ�����
 uint8_t rxCompleted=RESET; //HAL_UART_Receive_IT()�����Ƿ����
 uint8_t  rxBufPos=0;   //�������洢λ��
 uint8_t feedback[10]="OK!"; //��������ʾ�������
 uint8_t  isUploadTime=1; //���� RTC ���ڻ����ж����Ƿ��ϴ�ʱ������
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
		rxCompleted=SET; //�������
		for(uint16_t i=0; i<RX_CMD_LEN; i++)
			proBuffer[i]=rxBuffer[i];
			__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE); //���� IDLE �ж�
	}
}
void on_UART_IDLE(UART_HandleTypeDef *huart)
{
	if(__HAL_UART_GET_IT_SOURCE(huart,UART_IT_IDLE) == RESET)
		return;   __HAL_UART_CLEAR_IDLEFLAG(huart);  //��� IDLE ��־
	__HAL_UART_DISABLE_IT(huart, UART_IT_IDLE);  //��ֹ IDLE �ж�
     if (rxCompleted) //���յ���һ���ֽ�
    	 {
    	  uint8_t  ch=rxBuffer[0];   //���յ���һ���ֽ�
    	  if (ch=='#') //��ʼ��
    		  rxBufPos=0;  //�洢λ�ø�λ
    	  proBuffer[rxBufPos]=ch;  //�洢��������
    	  rxBufPos++;  //�洢λ���ƶ�
    	  if (ch==';')   //������
    		  {
    		  proBuffer[0]='#';
    		  HAL_UART_Transmit(huart,proBuffer,rxBufPos,200); //�ϴ�
    		  HAL_Delay(100); //������ʱ������ updateRTCTime()�����������
    		  updateRTCTime(); //����ָ��
    		  }
    	 rxCompleted=RESET;
    	 HAL_UART_Receive_IT(huart, rxBuffer,RX_CMD_LEN);//�ٴ���������
    	 }
}
void updateRTCTime() //���ݴ��ڽ��յ����ݽ��д���  (��ʱ�������´���Ϊ�Ժ��������͹�����չ��׼��)
{
	if (proBuffer[0] != '#') //����Чָ��
		return;
	 HAL_UART_Transmit(&huart1,feedback,sizeof(feedback),200);  //��������ʾ�����յ�
	uint8_t timeSection=proBuffer[1]; //�����ַ�
	uint8_t timeSection1=proBuffer[2]; //�����ַ�
	uint8_t timeSection2=proBuffer[3]; //�����ַ�
	uint8_t tmp10=proBuffer[2]-0x30; //ʮλ��
	uint8_t tmp1 =proBuffer[3]-0x30; //��λ��
	uint8_t val=10*tmp10+tmp1;
	uint8_t temp1[40]="#S45 "; //���ͱ����洢
	if ((timeSection=='R')&&(timeSection1=='T')&&(timeSection2=='C')) //�Ƿ��ϴ�  ʱ���¶�
	{
		isUploadTime=!isUploadTime;
		return;
	}
	if ((timeSection=='M')&&(timeSection1=='P')&&(timeSection2=='U'))   //MPU���ܼ��
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
	if ((timeSection=='D')&&(timeSection1=='S')&&(timeSection2=='B')) //�¶ȴ��������
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
	if ((timeSection=='R')&&(timeSection1=='O')&&(timeSection2=='M')) //eeprom���
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
	if ((timeSection=='R')&&(timeSection1=='S')&&(timeSection2=='T')) //�����λ
	{
			uint8_t temp1[]="Restart!\n         ";
			HAL_UART_Transmit(&huart1,temp1,sizeof(temp1),200);
			delay_ms(100);
		    __set_FAULTMASK(1);
		    NVIC_SystemReset();  //�����λ
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
	else if (timeSection=='m')   //�£��ͷ������ֿ���
			val=1;
	else if (timeSection=='D')   //��
			val=1;
	else if (timeSection=='W')   //����
			val=1;
	 uint8_t  proBuffer[10]="#S45;";  //���ڴ��������
	 uint8_t  rxBuffer[10]="#H12;";  //�������ݻ�����

}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
