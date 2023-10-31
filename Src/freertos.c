/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "rtc.h"
#include "tftlcd.h"
#include "semphr.h"
#include "ds18b20.h"
#include "delay.h"
#include "sys.h"
#include "24cxx.h"
#include "mpu6050.h"  //mpu6050
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

extern   uint8_t counter;//计数
extern uint32_t Point_old,Point_new;//保存坐标
extern float temperature;    //定义温度临时变量
/*
//mpu6050 所用变量
extern float pitch,roll,yaw; 		//欧拉角
extern short aacx,aacy,aacz;			//加速度传感器原始数据
extern short gyrox,gyroy,gyroz;		//陀螺仪原始数据
extern short temp;						//温度
*/
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
uint8_t tempStr_group[1800];  //温度字符串
/* USER CODE END Variables */
osThreadId_t AppTask_DrawHandle;
osThreadId_t AppTask_StoreHandle;
osThreadId_t AppTask_PlotHandle;
osSemaphoreId_t BinSem_DataReadyHandle;
osSemaphoreId_t BinSem_StoreReadyHandle;
osSemaphoreId_t myBinarySem03Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void Task_Draw(void *argument);
void Task_Store(void *argument);
void Task_Plot(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */
osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of BinSem_DataReady */
  const osSemaphoreAttr_t BinSem_DataReady_attributes = {
    .name = "BinSem_DataReady"
  };
  BinSem_DataReadyHandle = osSemaphoreNew(1, 1, &BinSem_DataReady_attributes);

  /* definition and creation of BinSem_StoreReady */
  const osSemaphoreAttr_t BinSem_StoreReady_attributes = {
    .name = "BinSem_StoreReady"
  };
  BinSem_StoreReadyHandle = osSemaphoreNew(1, 1, &BinSem_StoreReady_attributes);

  /* definition and creation of myBinarySem03 */
  const osSemaphoreAttr_t myBinarySem03_attributes = {
    .name = "myBinarySem03"
  };
  myBinarySem03Handle = osSemaphoreNew(1, 1, &myBinarySem03_attributes);

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
  /* definition and creation of AppTask_Draw */
  const osThreadAttr_t AppTask_Draw_attributes = {
    .name = "AppTask_Draw",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 1024
  };
  AppTask_DrawHandle = osThreadNew(Task_Draw, NULL, &AppTask_Draw_attributes);

  /* definition and creation of AppTask_Store */
  const osThreadAttr_t AppTask_Store_attributes = {
    .name = "AppTask_Store",
    .priority = (osPriority_t) osPriorityHigh,
    .stack_size = 1024
  };
  AppTask_StoreHandle = osThreadNew(Task_Store, NULL, &AppTask_Store_attributes);

  /* definition and creation of AppTask_Plot */
  const osThreadAttr_t AppTask_Plot_attributes = {
    .name = "AppTask_Plot",
    .priority = (osPriority_t) osPriorityHigh,
    .stack_size = 1024
  };
  AppTask_PlotHandle = osThreadNew(Task_Plot, NULL, &AppTask_Plot_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Task_Draw */
/**
  * @brief  Function implementing the AppTask_Draw thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_Task_Draw */
void Task_Draw(void *argument)
{
  /* USER CODE BEGIN Task_Draw */
  /* Infinite loop */
	  LCD_DrawLine_Color(0,300,240,300,lcdColor_YELLOW);//坐标轴
	  LCD_DrawLine_Color(0,300,0,100,lcdColor_YELLOW);//画面范围 (0,300)--(240,100)
	  LCD_DrawLine_Color(0,100,10,110,lcdColor_YELLOW);//箭头

	  LCD_DrawLine_Color(240,300,230,290,lcdColor_YELLOW);//箭头
	  LCD_DrawLine_Color(240,300,230,310,lcdColor_YELLOW);//箭头
	  for(;;)
	  {
		  if (xSemaphoreTake(BinSem_StoreReadyHandle, portMAX_DELAY)==pdTRUE)
		  {
			  	 if(temperature<0)
			  		{
			  		  LCD_ShowChar(50,80,'-',0);			//显示负号
			  		  temperature=-temperature;					//转为正数
			  		}else LCD_ShowChar(50,80,' ',0);			//去掉负号
			  	  LCD_ShowFloat(60,80,temperature,1);

			  	  if(counter<240)
			  	  {
			  	  Point_new=300-(int)(temperature*200/30);//温度范围 0--30度
			  	  counter++;
			  	  if(counter>2)//滤除刚开始的异常数据
			  	  LCD_DrawLine_Color(counter-1,Point_old,counter,Point_new,lcdColor_RED);
			  	  Point_old=Point_new;

			  	  strcat (tempStr_group,tempStr);//字符串合并
			  	  }
		  }
	  }

  /* USER CODE END Task_Draw */
}

/* USER CODE BEGIN Header_Task_Store */
/**
* @brief Function implementing the AppTask_Store thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_Store */
void Task_Store(void *argument)
{
  /* USER CODE BEGIN Task_Store */
  /* Infinite loop */
	 //LCD_ShowString(10,350, (uint8_t *) "task_store");
  for(;;)
  {
	  //HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
	  if (xSemaphoreTake(BinSem_DataReadyHandle, portMAX_DELAY)==pdTRUE)
	  {
		  HAL_Delay(100);
		  HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
		  HAL_Delay(100);  //软件消除按键抖动的影响,观察优先级的作用
		   while(AT24CXX_Check())//检测不到24c02
		   	{
		   		LCD_ShowString(30,150,"24C02 Check Failed!");
		   		delay_ms(500);
		   		LCD_ShowString(30,150,"Please Check!      ");
		   		delay_ms(500);
		   	}
		   	//LCD_ShowString(30,150,"24C02 Ready!");

		   	u8 datatemp[size_temp*counter];
		   	AT24CXX_Write(0,(u8*)tempStr_group,size_temp*counter);
		   	AT24CXX_Write(0,(u8*)tempStr_group,size_temp*counter);  //再写一次试试
		   	AT24CXX_Read(0,datatemp,size_temp*counter);
		   	//LCD_ShowString(0,305,"The Data Readed Is:  ");//提示传送完成
		   	LCD_ShowString(0,200,datatemp);//显示读到的字符串

	  }
  }
  /* USER CODE END Task_Store */
}

/* USER CODE BEGIN Header_Task_Plot */
/**
* @brief Function implementing the AppTask_Plot thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_Plot */
void Task_Plot(void *argument)
{
  /* USER CODE BEGIN Task_Plot */
  /* Infinite loop */
  for(;;)
  {
	  if (xSemaphoreTake(myBinarySem03Handle, portMAX_DELAY)==pdTRUE)
		  {
		     HAL_Delay(100);
		  	 HAL_GPIO_TogglePin(GPIOF ,GPIO_PIN_10);

		  	// HAL_Delay(1000);  //软件消除按键抖动的影响,观察优先级的作用

 /*
*/
		  	float pitch,roll,yaw; 		//欧拉角
		  	  while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0) {}
			   LCD_ShowFloat(80,320,pitch,0);//显示浮点数
			   LCD_ShowFloat(80,340,roll,0);//显示浮点数
			   LCD_ShowFloat(80,360,yaw,0);//显示浮点数
		  }
  }
  /* USER CODE END Task_Plot */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
