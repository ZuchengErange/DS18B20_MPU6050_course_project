/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "rtc.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include  "tftlcd.h"
#include "ds18b20.h"
#include "delay.h"
#include "sys.h"
#include "24cxx.h"
#include "mpu6050.h"  //mpu6050
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// ���õ����ַ�������
//Ҫд�뵽24c02���ַ�������
const u8 TEXT_Buffer[]={"hausaufgabe IIC TEST"};
//#define SIZE sizeof(TEXT_Buffer)

/*
//mpu6050���ñ���
 */
/*
float pitch,roll,yaw; 		//ŷ����

short aacx,aacy,aacz;			//���ٶȴ�����ԭʼ����
short gyrox,gyroy,gyroz;		//������ԭʼ����
short temp;						//�¶�
*/
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
  MX_FSMC_Init();
  MX_USART1_UART_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  delay_init(168);               	//��ʼ����ʱ����
  TFTLCD_Init(); //LCD ������ʼ��
  LCD_Clear(lcdColor_BLACK);  //��ɫ����
  lcdFRONT_COLOR=lcdColor_YELLOW; //ǰ��ɫ
  lcdBACK_COLOR=lcdColor_BLACK;  //����ɫ
  LCD_FS=16; //LCD �����С��ֻ���� 12,16,24
  MPU_Init();
  mpu_dmp_init();
  AT24CXX_Init();
 // eeprom ���Գ���
/*
	while(AT24CXX_Check())//��ⲻ��24c02
	{
		LCD_ShowString(30,150,"24C02 Check Failed!");
		delay_ms(500);
		LCD_ShowString(30,150,"Please Check!      ");
		delay_ms(500);
	}
	LCD_ShowString(30,150,"24C02 Ready!");
/*
	u8 datatemp[size_time];
	AT24CXX_Write(0,(u8*)timeStr,size_time);
	AT24CXX_Write(0,(u8*)timeStr,size_time);  //��дһ������
	AT24CXX_Read(0,datatemp,size_time);
	LCD_ShowString(30,170,"The Data Readed Is:  ");//��ʾ�������
	LCD_ShowString(30,190,datatemp);//��ʾ�������ַ���
*/
//mpu6050 ���Գ���

	while(mpu_dmp_init())
	{
		LCD_ShowString(30,130,"MPU6050 Error");
		delay_ms(200);
	}
	LCD_ShowString(120,80,"MPU6050 OK");

/*
	mpu_dmp_get_data(&pitch,&roll,&yaw);  //ŷ���Ƕ�ȡ
    temp=MPU_Get_Temperature();	//�õ��¶�ֵ
    MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
    MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
*/
  LCD_ShowString(10,10, (uint8_t *) "DS18B20 Temperature Detection");

  LCD_DrawLine_Color(0,300,240,300,lcdColor_YELLOW);//������
  LCD_DrawLine_Color(0,300,0,100,lcdColor_YELLOW);//���淶Χ (0,300)--(240,100)
  LCD_DrawLine_Color(0,100,10,110,lcdColor_YELLOW);//��ͷ
  LCD_DrawLine_Color(240,300,230,290,lcdColor_YELLOW);//��ͷ
  LCD_DrawLine_Color(240,300,230,310,lcdColor_YELLOW);//��ͷ

#ifdef	USE_HZ_LIB
  lcdFRONT_COLOR=lcdColor_RED;
  LCD_ShowHZ16(90, 120, "��");
  LCD_ShowHZ16(110, 120, "��");
  LCD_ShowHZ16(130, 120, "��");
  LCD_ShowHZ16(150, 120, "��");
  lcdFRONT_COLOR=lcdColor_YELLOW; //ǰ��ɫ

#endif

  uint8_t hello1[]="Hello,blocking\n         ";
  HAL_UART_Transmit(&huart1,hello1,sizeof(hello1),500);//����ģʽ
  HAL_Delay(100);    uint8_t hello2[]="Hello,none blocking\r       ";
  HAL_UART_Transmit_IT(&huart1,hello2,sizeof(hello2)); //�ж�ģʽ
  HAL_UART_Receive_IT(&huart1, rxBuffer,RX_CMD_LEN);//�ж�ģʽ����ָ��

  LCD_ShowString(20,320,"pitch:");
  LCD_ShowString(20,340,"roll:");
  LCD_ShowString(20,360,"yaw:");

  while(DS18B20_Init())	        //DS18B20��ʼ��
	  	{
	  		LCD_ShowString(10,210,"DS18B20 Error");
	  		delay_ms(200);
	  	}
	  	LCD_ShowString(120,100,"DS18B20 OK");
	  	LCD_ShowString(10,80,"Temp:      C");

/*	  	while(1)
	  	{
	  	while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0)
	  	{
	 	   LCD_ShowFloat(20,320,pitch,2);//��ʾ������
	 	   LCD_ShowFloat(20,340,roll,2);//��ʾ������
	 	   LCD_ShowFloat(20,360,yaw,2);//��ʾ������
	  	}
	  	}
	  	*/
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init(); 

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	    //temperature=DS18B20_Get_Temp();	  //�õ��¶���ʱ����
	  	//if(temperature<0)
	  	//{
	  	//	LCD_ShowChar(40,240,'-',0);			//��ʾ����
	  	//	temperature=-temperature;					//תΪ����
	  	//}else LCD_ShowChar(40,240,' ',0);			//ȥ������
	  	//LCD_ShowFloat(50,240,temperature/10,4);
	    //delay_ms(10);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);
  HAL_RCC_MCOConfig(RCC_MCO2, RCC_MCO2SOURCE_SYSCLK, RCC_MCODIV_1);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
