#include "tftlcd.h"
//#include "SysTick.h"
//#include "usart.h"
#include "font.h"

#include	<stdio.h>
#include	<math.h>
#include	<string.h>

#ifdef USE_HZ_LIB
	#include "HzLib.h"
#endif


//LCD�Ļ�����ɫ�ͱ���ɫ	   
uint16_t 	lcdFRONT_COLOR=lcdColor_WHITE;	//������ɫ
uint16_t 	lcdBACK_COLOR=lcdColor_BLACK;  //����ɫ

TFTLCD_ParaDef lcdPara;

uint16_t LCD_W;		//LCD ���,����LCD_Display_Dir()�������ʼ��
uint16_t LCD_H;		//LCD �߶�

uint16_t LCD_CurPosX=0;	//��ǰλ��X
uint16_t LCD_CurPosY=0;	//��ǰλ��Y

uint8_t	LCD_FS=16;	//fontsize


void TFTLCD_GPIO_Init(void)
{//����ʹ�ñ�׼��ʱ��LCD �ӿ����ŵĳ�ʼ����������
//	GPIO_InitTypeDef  GPIO_InitStructure;
//
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|
//							RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��PD,PE,PF,PGʱ��
//
//
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);  //FSMC_D0-FSMC_D15
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);
//
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);  //FSMC_NOE
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC);  //FSMC_NWE
//	GPIO_PinAFConfig(GPIOF,GPIO_PinSource12,GPIO_AF_FSMC);//FSMC_A6
//	GPIO_PinAFConfig(GPIOG,GPIO_PinSource12,GPIO_AF_FSMC);//FSMC_NE4
//
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4
//	                              | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9
//								  | GPIO_Pin_10 | GPIO_Pin_14| GPIO_Pin_15;//PD0,1,4,5,8,9,10,14,15
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�������
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
//	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9
//	                              | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12
//								  | GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15;//PE7~15
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�������
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
//	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//PF12,FSMC_A6
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�������
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
//	GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//PG12,FSMC_NE4
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�������
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
//	GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��
	
}


//void TFTLCD_FSMC_Init(void)
//{
//	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
//	FSMC_NORSRAMTimingInitTypeDef  FSMC_ReadNORSRAMTiming;
//	FSMC_NORSRAMTimingInitTypeDef  FSMC_WriteNORSRAMTiming;
//
//	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);//ʹ��FSMCʱ��
//
//
//	FSMC_ReadNORSRAMTiming.FSMC_AddressSetupTime = 0X01;	 //��ַ����ʱ�䣨ADDSET��Ϊ2��HCLK 1/168M=6ns*2=12ns
//	FSMC_ReadNORSRAMTiming.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�
//	FSMC_ReadNORSRAMTiming.FSMC_DataSetupTime = 0x0f;			//���ݱ���ʱ��Ϊ16��HCLK	��ΪҺ������IC�Ķ����ݵ�ʱ���ٶȲ���̫��
//	FSMC_ReadNORSRAMTiming.FSMC_BusTurnAroundDuration = 0x00;
//	FSMC_ReadNORSRAMTiming.FSMC_CLKDivision = 0x00;
//	FSMC_ReadNORSRAMTiming.FSMC_DataLatency = 0x00;
//	FSMC_ReadNORSRAMTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA
//
//#ifdef defined(TFTLCD_NT35510)|| defined(TFTLCD_ILI9488)
//	FSMC_WriteNORSRAMTiming.FSMC_AddressSetupTime =0x03;	      //��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK
//	FSMC_WriteNORSRAMTiming.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨A
//	FSMC_WriteNORSRAMTiming.FSMC_DataSetupTime = 0x02;		 //���ݱ���ʱ��Ϊ6ns*9��HCLK=54ns
//	FSMC_WriteNORSRAMTiming.FSMC_BusTurnAroundDuration = 0x00;
//	FSMC_WriteNORSRAMTiming.FSMC_CLKDivision = 0x00;
//	FSMC_WriteNORSRAMTiming.FSMC_DataLatency = 0x00;
//	FSMC_WriteNORSRAMTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA
//#endif
//
//#if	defined(TFTLCD_HX8357D)||defined(TFTLCD_HX8352C)||defined(TFTLCD_ST7793)||
//	defined(TFTLCD_ILI9327)||defined(TFTLCD_ILI9486)
//
//	FSMC_WriteNORSRAMTiming.FSMC_AddressSetupTime =0x10;	      //��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK
//	FSMC_WriteNORSRAMTiming.FSMC_AddressHoldTime = 0x10;	 //��ַ����ʱ�䣨A
//	FSMC_WriteNORSRAMTiming.FSMC_DataSetupTime = 0x18;		 //���ݱ���ʱ��Ϊ6ns*9��HCLK=54ns
//	FSMC_WriteNORSRAMTiming.FSMC_BusTurnAroundDuration = 0x00;
//	FSMC_WriteNORSRAMTiming.FSMC_CLKDivision = 0x00;
//	FSMC_WriteNORSRAMTiming.FSMC_DataLatency = 0x00;
//	FSMC_WriteNORSRAMTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA
//#endif
//
//	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  ��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7]��
//	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ���������ݵ�ַ
//	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM
//	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�洢�����ݿ��Ϊ16bit
//	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable;
//	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
//	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
//	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
//	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
//	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  �洢��дʹ��
//	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
//	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // ��дʹ�ò�ͬ��ʱ��
//	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
//	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_ReadNORSRAMTiming; //��дʱ��
//	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_WriteNORSRAMTiming;  //дʱ��
//
//	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC����
//
//	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // ʹ��BANK1
//
//}

//д�Ĵ�������
//cmd:�Ĵ���ֵ
void LCD_WriteCmd(uint16_t cmd)
{
#ifdef TFTLCD_HX8357D	
	TFTLCD->LCD_CMD=cmd;//д��Ҫд�ļĴ������
#endif

#ifdef TFTLCD_HX8352C
	TFTLCD->LCD_CMD=cmd<<8;
#endif

#ifdef TFTLCD_ILI9488
	TFTLCD->LCD_CMD=cmd;
#endif

#ifdef TFTLCD_ILI9327
	TFTLCD->LCD_CMD=cmd;
#endif
	
#ifdef TFTLCD_ST7793		
	TFTLCD->LCD_CMD=cmd>>8;
	TFTLCD->LCD_CMD=cmd&0xff;
#endif
	
#ifdef TFTLCD_NT35510		
	TFTLCD->LCD_CMD=cmd;	
#endif

#ifdef TFTLCD_ILI9486
	TFTLCD->LCD_CMD=cmd;
#endif	
}

//д����
//data:Ҫд���ֵ
void LCD_WriteData(uint16_t data)
{
#ifdef TFTLCD_HX8357D	
	TFTLCD->LCD_DATA=data;//д��Ҫд�ļĴ������
#endif
	
#ifdef TFTLCD_HX8352C
	TFTLCD->LCD_DATA=data<<8;
#endif

#ifdef TFTLCD_ILI9488
	TFTLCD->LCD_DATA=data;
#endif
	
#ifdef TFTLCD_ILI9327
	TFTLCD->LCD_DATA=data;
#endif
	
#ifdef TFTLCD_ST7793	
	TFTLCD->LCD_DATA=data>>8;	
	TFTLCD->LCD_DATA=data&0xff;	
#endif
	
#ifdef TFTLCD_NT35510		
	TFTLCD->LCD_DATA=data;	
#endif

#ifdef TFTLCD_ILI9486
	TFTLCD->LCD_DATA=data;
#endif
}

void LCD_WriteCmdData(uint16_t cmd,uint16_t data)
{
	LCD_WriteCmd(cmd);
	LCD_WriteData(data);
}


void LCD_WriteData_Color(uint16_t color)
{
#ifdef TFTLCD_HX8357D
	TFTLCD->LCD_DATA=color;
#endif

#ifdef TFTLCD_HX8352C
	TFTLCD->LCD_DATA=color&0xff00;
	TFTLCD->LCD_DATA=color<<8;
#endif	

#ifdef TFTLCD_ILI9488
	TFTLCD->LCD_DATA=color;
#endif
	
#ifdef TFTLCD_ILI9327
	TFTLCD->LCD_DATA=color>>8;
	TFTLCD->LCD_DATA=color&0xff;
#endif
	
#ifdef TFTLCD_ST7793
	TFTLCD->LCD_DATA=color>>8;
	TFTLCD->LCD_DATA=color&0xff;
#endif
	
#ifdef TFTLCD_NT35510
	TFTLCD->LCD_DATA=color;	
#endif

#ifdef TFTLCD_ILI9486
	TFTLCD->LCD_DATA=color;
#endif
}

//������
//����ֵ:������ֵ
uint16_t LCD_ReadData(void)
{
#ifdef TFTLCD_HX8357D
	return TFTLCD->LCD_DATA;
#endif
	
#ifdef TFTLCD_HX8352C
	return ((TFTLCD->LCD_DATA<<8)|(TFTLCD->LCD_DATA));
#endif

#ifdef TFTLCD_ILI9488
	return TFTLCD->LCD_DATA;
#endif
	
#ifdef TFTLCD_ILI9327		
	uint16_t ram;
	ram=TFTLCD->LCD_DATA;
	ram=ram<<8;
	ram|=TFTLCD->LCD_DATA;	
	return ram;		
#endif
	
#ifdef TFTLCD_ST7793		
	uint16_t ram;
	ram=TFTLCD->LCD_DATA;
	ram=ram<<8;
	ram|=TFTLCD->LCD_DATA;	
	return ram;		
#endif
	
#ifdef TFTLCD_NT35510		
	return TFTLCD->LCD_DATA;
#endif

#ifdef TFTLCD_ILI9486
	return TFTLCD->LCD_DATA;
#endif
}


//����LCD��ʾ����
//dir:0,������1,����
void LCD_Display_Dir(uint8_t dir)
{
	if(dir==0)  //Ĭ����������
	{		
#ifdef TFTLCD_HX8357D		
		LCD_WriteCmd(0x36);   //���ò�����ʾ����ļĴ���
		LCD_WriteData(0x4c);
		lcdPara.height=480;
		lcdPara.width=320;
#endif

#ifdef TFTLCD_HX8352C
		LCD_WriteCmd(0x36);   //���ò�����ʾ����ļĴ���
		LCD_WriteData(0x03);  //03:U-D,L-R; 06:D-U,R-L;
		lcdPara.height=400;
		lcdPara.width=240;			
#endif

#ifdef TFTLCD_ILI9488
		LCD_WriteCmd(0x36);   //���ò�����ʾ����ļĴ���
		LCD_WriteData(0x48);  
		lcdPara.height=480;
		lcdPara.width=320;
					
#endif

#ifdef TFTLCD_ILI9327
		LCD_WriteCmd(0x36);   //���ò�����ʾ����ļĴ���
		LCD_WriteData(0x48);  
		lcdPara.height=400;
		lcdPara.width=240;			
#endif
		
#ifdef TFTLCD_ST7793
		LCD_WriteCmd(0x0001);   
		LCD_WriteData(0x0100);
		LCD_WriteCmd(0x0003);
		LCD_WriteData(0x1030);
		lcdPara.height=400;
		lcdPara.width=240;			
#endif
		
#ifdef TFTLCD_NT35510	
		LCD_WriteCmd(0x3600);   
		LCD_WriteData(0x0000);
		lcdPara.height=800;
		lcdPara.width=480;
#endif

#ifdef TFTLCD_ILI9486
		LCD_WriteCmd(0x36);   //���ò�����ʾ����ļĴ���
		LCD_WriteData(0x00);  
		lcdPara.height=480;
		lcdPara.width=320;			
#endif
		lcdPara.dir=0;
	}
	else
	{	
#ifdef TFTLCD_HX8357D
		LCD_WriteCmd(0x36);   
		LCD_WriteData(0x2c);
		lcdPara.height=320;
		lcdPara.width=480;
#endif
		
#ifdef TFTLCD_HX8352C
		LCD_WriteCmd(0x16);   //���ò�����ʾ����ļĴ���
		LCD_WriteData(0x60);  //60������  
		lcdPara.height=240;
		lcdPara.width=400;			
#endif

#ifdef TFTLCD_ILI9488
		LCD_WriteCmd(0x36);   //���ò�����ʾ����ļĴ���
		LCD_WriteData(0x38);  
		lcdPara.height=320;
		lcdPara.width=480;			
#endif
		
#ifdef TFTLCD_ILI9327
		LCD_WriteCmd(0x36);   //���ò�����ʾ����ļĴ���
		LCD_WriteData(0x28);  
		lcdPara.height=240;
		lcdPara.width=400;			
#endif

#ifdef TFTLCD_ST7793
		LCD_WriteCmd(0x0001);   
		LCD_WriteData(0x0000);
		LCD_WriteCmd(0x0003);
		LCD_WriteData(0x1038);
		lcdPara.height=240;
		lcdPara.width=400;			
#endif

#ifdef TFTLCD_NT35510	
		LCD_WriteCmd(0x3600);   
		LCD_WriteData(0x0060);
		lcdPara.height=480;
		lcdPara.width=800;
#endif

#ifdef TFTLCD_ILI9486
		LCD_WriteCmd(0x36);   //���ò�����ʾ����ļĴ���
		LCD_WriteData(0x60);  
		lcdPara.height=320;
		lcdPara.width=480;			
#endif
		lcdPara.dir=1;
	}	

//ʹ��ȫ�ֱ���
	LCD_W=lcdPara.width;		//LCD ���
	LCD_H=lcdPara.height;		//LCD �߶�
}

// TFT LCD�����ʼ��
void TFTLCD_Init(void)
{
	HAL_Delay(50);
	
#ifdef TFTLCD_HX8357D	
	LCD_WriteCmd(0Xd0);				   
	lcdPara.id=LCD_ReadData();	//dummy read 	
	lcdPara.id=LCD_ReadData();    
#endif 

#ifdef TFTLCD_HX8352C
	LCD_WriteCmd(0X00);	
	lcdPara.id=TFTLCD->LCD_DATA>>8; 
#endif
	
#ifdef TFTLCD_ILI9488
	LCD_WriteCmd(0Xd3);	
	lcdPara.id=TFTLCD->LCD_DATA;	//dummy read 
	lcdPara.id=TFTLCD->LCD_DATA;  //00
	lcdPara.id=TFTLCD->LCD_DATA;  //94
	lcdPara.id<<=8;
	lcdPara.id|=TFTLCD->LCD_DATA;  //88
#endif

#ifdef TFTLCD_ILI9327
	LCD_WriteCmd(0XEF);	
	lcdPara.id=TFTLCD->LCD_DATA;	//dummy read 
	lcdPara.id=TFTLCD->LCD_DATA;  //02
	lcdPara.id=TFTLCD->LCD_DATA;  //04
	lcdPara.id=TFTLCD->LCD_DATA;  //93
	lcdPara.id=(lcdPara.id<<8)|TFTLCD->LCD_DATA;  //27
#endif

#ifdef TFTLCD_ST7793	
	LCD_WriteCmd(0X0000);				   	
	lcdPara.id=LCD_ReadData();	
#endif 
	
#ifdef TFTLCD_NT35510	
	LCD_WriteCmd(0XDA00);	
	lcdPara.id=LCD_ReadData();		//����0X00	 
	LCD_WriteCmd(0XDB00);	
	lcdPara.id=LCD_ReadData();		//����0X80
	lcdPara.id<<=8;	
	LCD_WriteCmd(0XDC00);	
	lcdPara.id|=LCD_ReadData();		//����0X00
#endif	

#ifdef TFTLCD_ILI9486
	LCD_WriteCmd(0Xd3);	
	lcdPara.id=TFTLCD->LCD_DATA;	//dummy read 
	lcdPara.id=TFTLCD->LCD_DATA;  //00
	lcdPara.id=TFTLCD->LCD_DATA;  //94
	lcdPara.id<<=8;
	lcdPara.id|=TFTLCD->LCD_DATA;  //86
#endif
	
// 	printf(" LCD ID:%x\r\n",tftlcd_data.id); //��ӡLCD ID
	
#ifdef TFTLCD_HX8357D	
	LCD_WriteCmd(0xE9); 
	LCD_WriteData(0x20); 
	
	LCD_WriteCmd(0x11); //Exit Sleep 
	for(i=500; i>0; i--);
	
	LCD_WriteCmd(0x3A);
	LCD_WriteData(0x55);  //16Bit colors
	
	LCD_WriteCmd(0xD1); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x65); //���Դ�ֵ����ˮ��
	LCD_WriteData(0x1F); 
	
	LCD_WriteCmd(0xD0); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x80); 
	
	LCD_WriteCmd(0x36); 	 //Set_address_mode
	LCD_WriteData(0x4c);   	//4c
	
	LCD_WriteCmd(0xC1); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x02); 
	LCD_WriteData(0x02); 
	
	LCD_WriteCmd(0xC0); //Set Default Gamma 
	LCD_WriteData(0x00);  
	LCD_WriteData(0x35); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x02); 

	LCD_WriteCmd(0xC4);			
	LCD_WriteData(0x03);

	LCD_WriteCmd(0xC5); //Set frame rate 
	LCD_WriteData(0x01); 
	
	LCD_WriteCmd(0xD2); //power setting 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x22); 

	LCD_WriteCmd(0xE7);			
	LCD_WriteData(0x38);
	
	LCD_WriteCmd(0xF3);			
    LCD_WriteData(0x08); 
	LCD_WriteData(0x12);
	LCD_WriteData(0x12);
	LCD_WriteData(0x08);

	LCD_WriteCmd(0xC8); //Set Gamma 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x52); 
	LCD_WriteData(0x37); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x0d); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x04); 
	LCD_WriteData(0x51); 
	LCD_WriteData(0x77); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x0d); 
	LCD_WriteData(0x08); 
	LCD_WriteData(0x80); 
	LCD_WriteData(0x00);

    LCD_WriteCmd(0x29);
#endif

#ifdef TFTLCD_HX8352C

	//************* Start Initial Sequence **********//	
	//##################################################################
	//Power Voltage Setting
	LCD_WriteCmdData(0x1A,0x02); //BT  0x02
	LCD_WriteCmdData(0x1B,0x88); //VRH  0x88
	LCD_WriteCmdData(0x1C,0x06); //AP[0:2]  //�Լ����
	
	//****VCOM offset**///
	LCD_WriteCmdData(0x23,0x00); //SEL_VCM   00
	LCD_WriteCmdData(0x24,0x5f); //VCM    5f
	LCD_WriteCmdData(0x25,0x15); //VDV   0x15
	LCD_WriteCmdData(0x2D,0x03); //NOW[2:0]=011
	//Power on Setting
	LCD_WriteCmdData(0x18,0x04); //Frame rate 72Hz
	LCD_WriteCmdData(0x19,0x01); //OSC_EN='1', start Osc
	LCD_WriteCmdData(0x01,0x00); //DP_STB='0', out deep sleep
	LCD_WriteCmdData(0x1F,0x88); //STB=0
	HAL_Delay(5);
	LCD_WriteCmdData(0x1F,0x80); //DK=0
	HAL_Delay(5);
	LCD_WriteCmdData(0x1F,0x90); //PON=1
	HAL_Delay(5);
	LCD_WriteCmdData(0x1F,0xD0); //VCOMG=1
	HAL_Delay(5);
	//262k/65k color selection
	LCD_WriteCmdData(0x17,0x05); //default 0x06 262k color // 0x05 65k color
	//SET PANEL
	LCD_WriteCmdData(0x36,0x13); //REV_P, SM_P, GS_P, BGR_P, SS_P   0x03
	LCD_WriteCmdData(0x29,0x31); //400 lines
	LCD_WriteCmdData(0x71,0x1A); //RTN
	//Gamma 2.2 Setting
	LCD_WriteCmdData(0x40,0x00);
	LCD_WriteCmdData(0x41,0x45);
	LCD_WriteCmdData(0x42,0x45);
	LCD_WriteCmdData(0x43,0x04);
	LCD_WriteCmdData(0x44,0x00);
	LCD_WriteCmdData(0x45,0x08);
	LCD_WriteCmdData(0x46,0x23);
	LCD_WriteCmdData(0x47,0x23);
	LCD_WriteCmdData(0x48,0x77);
	LCD_WriteCmdData(0x49,0x40);
	LCD_WriteCmdData(0x4A,0x04);
	LCD_WriteCmdData(0x4B,0x00);
	LCD_WriteCmdData(0x4C,0x88);
	LCD_WriteCmdData(0x4D,0x88);
	LCD_WriteCmdData(0x4E,0x88);
	//Set GRAM Area
	LCD_WriteCmdData(0x02,0x00);
	LCD_WriteCmdData(0x03,0x00); //Column Start
	LCD_WriteCmdData(0x04,0x00);
	LCD_WriteCmdData(0x05,0xEF); //Column End
	LCD_WriteCmdData(0x06,0x00);
	LCD_WriteCmdData(0x07,0x00); //Row Start
	LCD_WriteCmdData(0x08,0x01);
	LCD_WriteCmdData(0x09,0x8F); //Row End  //AF
	//Display ON Setting
	LCD_WriteCmdData(0x28,0x38); //GON=1, DTE=1, D=10
	HAL_Delay(40);
	LCD_WriteCmdData(0x28,0x3F); //GON=1, DTE=1, D=11  0x3C
	LCD_WriteCmd(0x22);
	 //Start GRAM write
	//##################################################################
	// Power Off Setting
	LCD_WriteCmdData(0x28,0x38); //GON=��1�� DTE=��1�� D[1:0]=��10��
	HAL_Delay(40);
	LCD_WriteCmdData(0x1F,0x89); // GAS=1, VOMG=0, PON=0, DK=1, XDK=0, DVDH_TRI=0, STB=1
	HAL_Delay(40);
	LCD_WriteCmdData(0x28,0x20); //GON=��1�� DTE=��0�� D[1:0]=��00��
	HAL_Delay(40);
	LCD_WriteCmdData(0x19,0x00); //OSC_EN=��0��
	HAL_Delay(40);
	//M51_WR_REG(U05_LCD_POWER_ON, 0x00); //VCI & IOVCC OFF
	//##################################################################
	// ENTER IDLE mode Setting
	LCD_WriteCmdData(0x18,0x07); //Frame Rate 60Hz
	LCD_WriteCmdData(0x01,0x04); //IDLE='1' , enter IDLE mode
	// EXIT IDLE mode Setting
	LCD_WriteCmdData(0x18,0x04); //Frame rate 72Hz
	LCD_WriteCmdData(0x01,0x00); //IDLE='0', EXIT IDLE mode
	//##################################################################
	// ENTER Partial mode Setting 32line
	LCD_WriteCmdData(0x18,0x04); //Frame rate 72Hz
	LCD_WriteCmdData(0x01,0x01); //PTL='1', Enter Partial mode
	LCD_WriteCmdData(0x0A,0x00); //PSL[15:8]=0x00
	LCD_WriteCmdData(0x0B,0x20); //PSL[7:0]=0x20
	LCD_WriteCmdData(0x0C,0x00); //PEL[15:8]=0x00
	LCD_WriteCmdData(0x0D,0x3F); //PEL[7:0]=0x3F
	// EXIT Partial mode Setting
	LCD_WriteCmdData(0x18,0x04); //Frame rate 72Hz
	LCD_WriteCmdData(0x01,0x00); //PTL='0', EXIT Partial mode
	//##################################################################
	// ENTER Partial + IDLE mode Setting 32line
	LCD_WriteCmdData(0x18,0x07); //Frame Rate 60Hz
	LCD_WriteCmdData(0x01,0x05); // PTL='1' IDLE=��1��, Enter Partial + IDLE mode
	LCD_WriteCmdData(0x0A,0x00); //PSL[15:8]=0x00
	LCD_WriteCmdData(0x0B,0x20); //PSL[7:0]=0x20
	LCD_WriteCmdData(0x0C,0x00); //PEL[15:8]=0x00
	LCD_WriteCmdData(0x0D,0x3F); //PEL[7:0]=0x3F
	// EXIT Partial + IDLE mode Setting
	LCD_WriteCmdData(0x18,0x04); //Frame rate 72Hz
	LCD_WriteCmdData(0x01,0x00); // PTL='0' IDLE=��0��, EXIT Partial + IDLE mode
	//##################################################################
	// Enter Sleep mode Setting
	LCD_WriteCmdData(0x28,0x38); //GON=��1�� DTE=��1�� D[1:0]=��10��
	HAL_Delay(40);
	LCD_WriteCmdData(0x1F,0x89); // GAS=1, VOMG=0, PON=0, DK=1, XDK=0, DVDH_TRI=0, STB=1
	HAL_Delay(40);
	LCD_WriteCmdData(0x28,0x20); //GON=��1�� DTE=��0�� D[1:0]=��00��
	HAL_Delay(40);
	LCD_WriteCmdData(0x19,0x00); //OSC_EN=��0��
	HAL_Delay(5);
	// Exit Sleep mode Setting
	LCD_WriteCmdData(0x19,0x01); //OSC_EN='1', start Osc
	LCD_WriteCmdData(0x1F,0x88); //STB=0
	HAL_Delay(5);
	LCD_WriteCmdData(0x1F,0x80); //DK=0
	HAL_Delay(5);
	LCD_WriteCmdData(0x1F,0x90); //PON=1
	HAL_Delay(5);
	LCD_WriteCmdData(0x1F,0xD0); //VCOMG=1
	HAL_Delay(5);
	LCD_WriteCmdData(0x28,0x38); //GON=1, DTE=1, D=10
	HAL_Delay(40);
	LCD_WriteCmdData(0x28,0x3F); //GON=1, DTE=1, D=11
	//##################################################################
	// Enter Deep Sleep mode Setting
	LCD_WriteCmdData(0x28,0x38); //GON=��1�� DTE=��1�� D[1:0]=��10��
	HAL_Delay(40);
	LCD_WriteCmdData(0x1F,0x89); // GAS=1, VOMG=0, PON=0, DK=1, XDK=0, DVDH_TRI=0, STB=1
	HAL_Delay(40);
	LCD_WriteCmdData(0x28,0x20); //GON=��1�� DTE=��0�� D[1:0]=��00��
	HAL_Delay(40);
	LCD_WriteCmdData(0x19,0x00); //OSC_EN=��0��
	HAL_Delay(5);
	LCD_WriteCmdData(0x01,0x80); //DP_STB=��1��
	// Exit Deep Sleep mode Setting
	LCD_WriteCmdData(0x01,0x00); //DP_STB='0', out deep sleep
	HAL_Delay(10);
	LCD_WriteCmdData(0x19,0x01); //OSC_EN='1', start Osc
	LCD_WriteCmdData(0x1F,0x88); //STB=0
	HAL_Delay(5);
	LCD_WriteCmdData(0x1F,0x80); //DK=0
	HAL_Delay(5);
	LCD_WriteCmdData(0x1F,0x90); //PON=1
	HAL_Delay(5);
	LCD_WriteCmdData(0x1F,0xD0); //VCOMG=1
	HAL_Delay(5);
	LCD_WriteCmdData(0x28,0x38); //GON=1, DTE=1, D=10
	HAL_Delay(40);
	LCD_WriteCmdData(0x28,0x3C); //GON=1, DTE=1, D=11

	LCD_WriteCmd(0x22);

#endif

#ifdef TFTLCD_ILI9488

//ILI9488+CTC3.5
//************* Start Initial Sequence **********//
	LCD_WriteCmd(0xE0); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x0f); 
	LCD_WriteData(0x0D); 
	LCD_WriteData(0x1B); 
	LCD_WriteData(0x0A); 
	LCD_WriteData(0x3c); 
	LCD_WriteData(0x78); 
	LCD_WriteData(0x4A); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x0E); 
	LCD_WriteData(0x09); 
	LCD_WriteData(0x1B); 
	LCD_WriteData(0x1e); 
	LCD_WriteData(0x0f);  
	
	LCD_WriteCmd(0xE1); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x22); 
	LCD_WriteData(0x24); 
	LCD_WriteData(0x06); 
	LCD_WriteData(0x12); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x36); 
	LCD_WriteData(0x47); 
	LCD_WriteData(0x47); 
	LCD_WriteData(0x06); 
	LCD_WriteData(0x0a); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x30); 
	LCD_WriteData(0x37); 
	LCD_WriteData(0x0f); 
	
	LCD_WriteCmd(0xC0); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x10); 
	
	LCD_WriteCmd(0xC1); 
	LCD_WriteData(0x41); 
	
	LCD_WriteCmd(0xC5); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x22); 
	LCD_WriteData(0x80); 
	
	LCD_WriteCmd(0x36); 
	LCD_WriteData(0x00); 
	
	LCD_WriteCmd(0x3A); //Interface Mode Control
	LCD_WriteData(0x55);
		
	LCD_WriteCmd(0XB0);  //Interface Mode Control  
	LCD_WriteData(0x00); 
	LCD_WriteCmd(0xB1);   //Frame rate 70HZ  
	LCD_WriteData(0xB0); 
	LCD_WriteData(0x11); 
	LCD_WriteCmd(0xB4); 
	LCD_WriteData(0x02);   
	LCD_WriteCmd(0xB6); //RGB/MCU Interface Control
	LCD_WriteData(0x02); 
	LCD_WriteData(0x02); 
	
	LCD_WriteCmd(0xB7); 
	LCD_WriteData(0xC6); 
	
	//LCD_WriteCmd(0XBE);
	//LCD_WriteData(0x00);
	//LCD_WriteData(0x04);
	
	LCD_WriteCmd(0xE9); 
	LCD_WriteData(0x00);
	
	LCD_WriteCmd(0XF7);    
	LCD_WriteData(0xA9); 
	LCD_WriteData(0x51); 
	LCD_WriteData(0x2C); 
	LCD_WriteData(0x82);
	
	LCD_WriteCmd(0x11); 
	HAL_Delay(120);
	LCD_WriteCmd(0x29); 
	
#endif

#ifdef TFTLCD_ILI9327
	//************* Start Initial Sequence **********// 

	LCD_WriteCmd(0xE9); 
	LCD_WriteData(0x20); 
	
	LCD_WriteCmd(0x11); //Exit Sleep 
	HAL_Delay(100);
	
	LCD_WriteCmd(0x3A);
	LCD_WriteData(0x55);
	
	LCD_WriteCmd(0xD1); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x65); //���Դ�ֵ����ˮ��
	LCD_WriteData(0x1F); 
	
	LCD_WriteCmd(0xD0); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x07); 
	LCD_WriteData(0x80); 
	
	LCD_WriteCmd(0x36); 
	LCD_WriteData(0x48); 
	
	LCD_WriteCmd(0xC1); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x02); 
	LCD_WriteData(0x02); 
	
	LCD_WriteCmd(0xC0); //Set Default Gamma 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x35); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x00); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x02); 
	
	LCD_WriteCmd(0xC5); //Set frame rate 
	LCD_WriteData(0x01); 
	
	LCD_WriteCmd(0xD2); //power setting 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x22); 
	
	LCD_WriteCmd(0xC8); //Set Gamma 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x52); 
	LCD_WriteData(0x37); 
	LCD_WriteData(0x10); 
	LCD_WriteData(0x0d); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x04); 
	LCD_WriteData(0x51); 
	LCD_WriteData(0x77); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x01); 
	LCD_WriteData(0x0d); 
	LCD_WriteData(0x08); 
	LCD_WriteData(0x80); 
	LCD_WriteData(0x00); 
	
	LCD_WriteCmd(0x29); //display on

#endif

#ifdef TFTLCD_ST7793	
	for(i=500; i>0; i--);
	LCD_WriteCmd(0x0001);
	LCD_WriteData(0x0100);
	LCD_WriteCmd(0x0003);
	LCD_WriteData(0x1030); //16bit 565 
	
	LCD_WriteCmd(0x0008);
	LCD_WriteData(0x0808);
	LCD_WriteCmd(0x0090);
	LCD_WriteData(0x8000);
	LCD_WriteCmd(0x0400);
	LCD_WriteData(0x6200);
	LCD_WriteCmd(0x0401);
	LCD_WriteData(0x0001);

	LCD_WriteCmd(0x00ff);
	LCD_WriteData(0x0001);
	LCD_WriteCmd(0x0102);
	LCD_WriteData(0x01b0);
	LCD_WriteCmd(0x0710);
	LCD_WriteData(0x0016);
	LCD_WriteCmd(0x0712);
	LCD_WriteData(0x000f);
	LCD_WriteCmd(0x0752);
	LCD_WriteData(0x002f);
	LCD_WriteCmd(0x0724);
	LCD_WriteData(0x001a);
	LCD_WriteCmd(0x0754);	
	LCD_WriteData(0x0018);
	for(i=500; i>0; i--);
    
    /* Gamma */
	LCD_WriteCmd(0x0380);
	LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0381);
	LCD_WriteData(0x5F10);//5f10
	LCD_WriteCmd(0x0382);
	LCD_WriteData(0x0B02);//0b02
	LCD_WriteCmd(0x0383);
	LCD_WriteData(0x0614);
	LCD_WriteCmd(0x0384);
	LCD_WriteData(0x0111);
	LCD_WriteCmd(0x0385);
	LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0386);
	LCD_WriteData(0xA90B);//a90b
	LCD_WriteCmd(0x0387);
	LCD_WriteData(0x0606);//0606
	LCD_WriteCmd(0x0388);
	LCD_WriteData(0x0612);
	LCD_WriteCmd(0x0389);
	LCD_WriteData(0x0111);	  


    /* Gamma Setting */
    /* Setting */
	LCD_WriteCmd(0x0702);
	LCD_WriteData(0x003b);//003b
	LCD_WriteCmd(0x00ff);
	LCD_WriteData(0x0000);


    /* Vcom Setting */
	LCD_WriteCmd(0x0007);
	LCD_WriteData(0x0100);
	for(i=500; i>0; i--); 
	LCD_WriteCmd(0x0200);
	LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0201);                  
	LCD_WriteData(0x0000);	
#endif

#ifdef TFTLCD_NT35510

	//************* Start Initial Sequence **********//
	//**********LV2 Page 1 enable***********//
	LCD_WriteCmd(0xF000);	LCD_WriteData(0x0055);
	LCD_WriteCmd(0xF001);	LCD_WriteData(0x00AA);
	LCD_WriteCmd(0xF002);	LCD_WriteData(0x0052);
	LCD_WriteCmd(0xF003);	LCD_WriteData(0x0008);
	LCD_WriteCmd(0xF004);	LCD_WriteData(0x0001);

	//*************AVDD Set AVDD 5.2V*************//
	LCD_WriteCmd(0xB000);	LCD_WriteData(0x0000);
	LCD_WriteCmd(0xB001);	LCD_WriteData(0x0000);
	LCD_WriteCmd(0xB002);	LCD_WriteData(0x0000);

	//************AVDD ratio****************//
	LCD_WriteCmd(0xB600);	LCD_WriteData(0x0034);
	LCD_WriteCmd(0xB601);	LCD_WriteData(0x0034);
	LCD_WriteCmd(0xB602);	LCD_WriteData(0x0034);
	 
	//************AVEE  -5.2V****************//
	LCD_WriteCmd(0xB100);	LCD_WriteData(0x0000);
	LCD_WriteCmd(0xB101);	LCD_WriteData(0x0000);
	LCD_WriteCmd(0xB102);	LCD_WriteData(0x0000);

	//***********AVEE ratio*************//
	LCD_WriteCmd(0xB700);	LCD_WriteData(0x0034);
	LCD_WriteCmd(0xB701);	LCD_WriteData(0x0034);
	LCD_WriteCmd(0xB702);	LCD_WriteData(0x0034);

	//***********VCL  -2.5V*************//
	LCD_WriteCmd(0xB200);	LCD_WriteData(0x0000);
	LCD_WriteCmd(0xB201);	LCD_WriteData(0x0000);
	LCD_WriteCmd(0xB202);	LCD_WriteData(0x0000);

	//**************VCL ratio*****************//
	LCD_WriteCmd(0xB800);	LCD_WriteData(0x0005);
	LCD_WriteCmd(0xB801);	LCD_WriteData(0x0005);
	LCD_WriteCmd(0xB802);	LCD_WriteData(0x0005);


	//*************VGH 15V  (Free pump)*********//
	LCD_WriteCmd(0xBF00);	LCD_WriteData(0x0001);
	LCD_WriteCmd(0xB300);	LCD_WriteData(0x000F);
	LCD_WriteCmd(0xB301);	LCD_WriteData(0x000F);
	LCD_WriteCmd(0xB302);	LCD_WriteData(0x000F);

	//*************VGH ratio*****************//
	LCD_WriteCmd(0xB900);	LCD_WriteData(0x0024);
	LCD_WriteCmd(0xB901);	LCD_WriteData(0x0024);
	LCD_WriteCmd(0xB902);	LCD_WriteData(0x0024);

	//***************VGL_REG -10V**************//
	LCD_WriteCmd(0xB500);	LCD_WriteData(0x0008);
	LCD_WriteCmd(0xB501);	LCD_WriteData(0x0008);
	LCD_WriteCmd(0xB502);	LCD_WriteData(0x0008);

//	LCD_WriteCmd(0xC2,0x00);	LCD_WriteData(0x00,0x03);
		 
	//*****************VGLX ratio***************//
	LCD_WriteCmd(0xBA00);	LCD_WriteData(0x0014);
	LCD_WriteCmd(0xBA01);	LCD_WriteData(0x0014);
	LCD_WriteCmd(0xBA02);	LCD_WriteData(0x0014);

	//*************VGMP/VGSP 4.5V/0V*************//
	LCD_WriteCmd(0xBC00);	LCD_WriteData(0x0000);
	LCD_WriteCmd(0xBC01);	LCD_WriteData(0x00BC);
	LCD_WriteCmd(0xBC02);	LCD_WriteData(0x0000);

	//************VGMN/VGSN -4.5V/0V****************//
	LCD_WriteCmd(0xBD00);	LCD_WriteData(0x0000);
	LCD_WriteCmd(0xBD01);	LCD_WriteData(0x00BC);
	LCD_WriteCmd(0xBD02);	LCD_WriteData(0x0000);

	//************VCOM  -1.25V****************//
	LCD_WriteCmd(0xBE00);	LCD_WriteData(0x0000);
	LCD_WriteCmd(0xBE01);	LCD_WriteData(0x002D);

	//************Gamma Setting******************//

	LCD_WriteCmd(0xD100); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD101); LCD_WriteData(0x0037);
	LCD_WriteCmd(0xD102); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD103); LCD_WriteData(0x0049);
	LCD_WriteCmd(0xD104); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD105); LCD_WriteData(0x006B);
	LCD_WriteCmd(0xD106); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD107); LCD_WriteData(0x0086);
	LCD_WriteCmd(0xD108); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD109); LCD_WriteData(0x009D);
	LCD_WriteCmd(0xD10A); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD10B); LCD_WriteData(0x00C3);
	LCD_WriteCmd(0xD10C); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD10D); LCD_WriteData(0x00E0);
	LCD_WriteCmd(0xD10E); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD10F); LCD_WriteData(0x000D);
	LCD_WriteCmd(0xD110); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD111); LCD_WriteData(0x002F);
	LCD_WriteCmd(0xD112); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD113); LCD_WriteData(0x0061);
	LCD_WriteCmd(0xD114); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD115); LCD_WriteData(0x0086);
	LCD_WriteCmd(0xD116); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD117); LCD_WriteData(0x00BD);
	LCD_WriteCmd(0xD118); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD119); LCD_WriteData(0x00E7);
	LCD_WriteCmd(0xD11A); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD11B); LCD_WriteData(0x00E8);
	LCD_WriteCmd(0xD11C); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD11D); LCD_WriteData(0x000C);
	LCD_WriteCmd(0xD11E); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD11F); LCD_WriteData(0x0030);
	LCD_WriteCmd(0xD120); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD121); LCD_WriteData(0x0045);
	LCD_WriteCmd(0xD122); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD123); LCD_WriteData(0x0063);
	LCD_WriteCmd(0xD124); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD125); LCD_WriteData(0x007E);
	LCD_WriteCmd(0xD126); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD127); LCD_WriteData(0x00B1);
	LCD_WriteCmd(0xD128); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD129); LCD_WriteData(0x00E0);
	LCD_WriteCmd(0xD12A); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD12B); LCD_WriteData(0x0026);
	LCD_WriteCmd(0xD12C); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD12D); LCD_WriteData(0x0060);
	LCD_WriteCmd(0xD12E); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD12F); LCD_WriteData(0x00B4);
	LCD_WriteCmd(0xD130); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD131); LCD_WriteData(0x00B9);
	LCD_WriteCmd(0xD132); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD133); LCD_WriteData(0x00C1);

	LCD_WriteCmd(0xD200); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD201); LCD_WriteData(0x0037);
	LCD_WriteCmd(0xD202); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD203); LCD_WriteData(0x0049);
	LCD_WriteCmd(0xD204); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD205); LCD_WriteData(0x006B);
	LCD_WriteCmd(0xD206); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD207); LCD_WriteData(0x0086);
	LCD_WriteCmd(0xD208); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD209); LCD_WriteData(0x009D);
	LCD_WriteCmd(0xD20A); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD20B); LCD_WriteData(0x00C3);
	LCD_WriteCmd(0xD20C); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD20D); LCD_WriteData(0x00E0);
	LCD_WriteCmd(0xD20E); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD20F); LCD_WriteData(0x000D);
	LCD_WriteCmd(0xD210); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD211); LCD_WriteData(0x002F);
	LCD_WriteCmd(0xD212); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD213); LCD_WriteData(0x0061);
	LCD_WriteCmd(0xD214); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD215); LCD_WriteData(0x0086);
	LCD_WriteCmd(0xD216); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD217); LCD_WriteData(0x00BD);
	LCD_WriteCmd(0xD218); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD219); LCD_WriteData(0x00E7);
	LCD_WriteCmd(0xD21A); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD21B); LCD_WriteData(0x00E8);
	LCD_WriteCmd(0xD21C); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD21D); LCD_WriteData(0x000C);
	LCD_WriteCmd(0xD21E); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD21F); LCD_WriteData(0x0030);
	LCD_WriteCmd(0xD220); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD221); LCD_WriteData(0x0045);
	LCD_WriteCmd(0xD222); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD223); LCD_WriteData(0x0063);
	LCD_WriteCmd(0xD224); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD225); LCD_WriteData(0x007E);
	LCD_WriteCmd(0xD226); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD227); LCD_WriteData(0x00B1);
	LCD_WriteCmd(0xD228); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD229); LCD_WriteData(0x00E0);
	LCD_WriteCmd(0xD22A); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD22B); LCD_WriteData(0x0026);
	LCD_WriteCmd(0xD22C); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD22D); LCD_WriteData(0x0060);
	LCD_WriteCmd(0xD22E); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD22F); LCD_WriteData(0x00B4);
	LCD_WriteCmd(0xD230); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD231); LCD_WriteData(0x00B9);
	LCD_WriteCmd(0xD232); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD233); LCD_WriteData(0x00C1);

	LCD_WriteCmd(0xD300); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD301); LCD_WriteData(0x0037);
	LCD_WriteCmd(0xD302); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD303); LCD_WriteData(0x0049);
	LCD_WriteCmd(0xD304); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD305); LCD_WriteData(0x006B);
	LCD_WriteCmd(0xD306); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD307); LCD_WriteData(0x0086);
	LCD_WriteCmd(0xD308); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD309); LCD_WriteData(0x009D);
	LCD_WriteCmd(0xD30A); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD30B); LCD_WriteData(0x00C3);
	LCD_WriteCmd(0xD30C); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD30D); LCD_WriteData(0x00E0);
	LCD_WriteCmd(0xD30E); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD30F); LCD_WriteData(0x000D);
	LCD_WriteCmd(0xD310); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD311); LCD_WriteData(0x002F);
	LCD_WriteCmd(0xD312); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD313); LCD_WriteData(0x0061);
	LCD_WriteCmd(0xD314); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD315); LCD_WriteData(0x0086);
	LCD_WriteCmd(0xD316); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD317); LCD_WriteData(0x00BD);
	LCD_WriteCmd(0xD318); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD319); LCD_WriteData(0x00E7);
	LCD_WriteCmd(0xD31A); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD31B); LCD_WriteData(0x00E8);
	LCD_WriteCmd(0xD31C); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD31D); LCD_WriteData(0x000C);
	LCD_WriteCmd(0xD31E); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD31F); LCD_WriteData(0x0030);
	LCD_WriteCmd(0xD320); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD321); LCD_WriteData(0x0045);
	LCD_WriteCmd(0xD322); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD323); LCD_WriteData(0x0063);
	LCD_WriteCmd(0xD324); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD325); LCD_WriteData(0x007E);
	LCD_WriteCmd(0xD326); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD327); LCD_WriteData(0x00B1);
	LCD_WriteCmd(0xD328); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD329); LCD_WriteData(0x00E0);
	LCD_WriteCmd(0xD32A); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD32B); LCD_WriteData(0x0026);
	LCD_WriteCmd(0xD32C); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD32D); LCD_WriteData(0x0060);
	LCD_WriteCmd(0xD32E); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD32F); LCD_WriteData(0x00B4);
	LCD_WriteCmd(0xD330); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD331); LCD_WriteData(0x00B9);
	LCD_WriteCmd(0xD332); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD333); LCD_WriteData(0x00C1);

	LCD_WriteCmd(0xD400); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD401); LCD_WriteData(0x0037);
	LCD_WriteCmd(0xD402); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD403); LCD_WriteData(0x0049);
	LCD_WriteCmd(0xD404); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD405); LCD_WriteData(0x006B);
	LCD_WriteCmd(0xD406); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD407); LCD_WriteData(0x0086);
	LCD_WriteCmd(0xD408); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD409); LCD_WriteData(0x009D);
	LCD_WriteCmd(0xD40A); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD40B); LCD_WriteData(0x00C3);
	LCD_WriteCmd(0xD40C); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD40D); LCD_WriteData(0x00E0);
	LCD_WriteCmd(0xD40E); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD40F); LCD_WriteData(0x000D);
	LCD_WriteCmd(0xD410); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD411); LCD_WriteData(0x002F);
	LCD_WriteCmd(0xD412); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD413); LCD_WriteData(0x0061);
	LCD_WriteCmd(0xD414); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD415); LCD_WriteData(0x0086);
	LCD_WriteCmd(0xD416); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD417); LCD_WriteData(0x00BD);
	LCD_WriteCmd(0xD418); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD419); LCD_WriteData(0x00E7);
	LCD_WriteCmd(0xD41A); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD41B); LCD_WriteData(0x00E8);
	LCD_WriteCmd(0xD41C); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD41D); LCD_WriteData(0x000C);
	LCD_WriteCmd(0xD41E); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD41F); LCD_WriteData(0x0030);
	LCD_WriteCmd(0xD420); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD421); LCD_WriteData(0x0045);
	LCD_WriteCmd(0xD422); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD423); LCD_WriteData(0x0063);
	LCD_WriteCmd(0xD424); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD425); LCD_WriteData(0x007E);
	LCD_WriteCmd(0xD426); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD427); LCD_WriteData(0x00B1);
	LCD_WriteCmd(0xD428); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD429); LCD_WriteData(0x00E0);
	LCD_WriteCmd(0xD42A); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD42B); LCD_WriteData(0x0026);
	LCD_WriteCmd(0xD42C); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD42D); LCD_WriteData(0x0060);
	LCD_WriteCmd(0xD42E); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD42F); LCD_WriteData(0x00B4);
	LCD_WriteCmd(0xD430); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD431); LCD_WriteData(0x00B9);
	LCD_WriteCmd(0xD432); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD433); LCD_WriteData(0x00C1);

	LCD_WriteCmd(0xD500); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD501); LCD_WriteData(0x0037);
	LCD_WriteCmd(0xD502); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD503); LCD_WriteData(0x0049);
	LCD_WriteCmd(0xD504); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD505); LCD_WriteData(0x006B);
	LCD_WriteCmd(0xD506); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD507); LCD_WriteData(0x0086);
	LCD_WriteCmd(0xD508); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD509); LCD_WriteData(0x009D);
	LCD_WriteCmd(0xD50A); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD50B); LCD_WriteData(0x00C3);
	LCD_WriteCmd(0xD50C); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD50D); LCD_WriteData(0x00E0);
	LCD_WriteCmd(0xD50E); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD50F); LCD_WriteData(0x000D);
	LCD_WriteCmd(0xD510); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD511); LCD_WriteData(0x002F);
	LCD_WriteCmd(0xD512); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD513); LCD_WriteData(0x0061);
	LCD_WriteCmd(0xD514); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD515); LCD_WriteData(0x0086);
	LCD_WriteCmd(0xD516); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD517); LCD_WriteData(0x00BD);
	LCD_WriteCmd(0xD518); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD519); LCD_WriteData(0x00E7);
	LCD_WriteCmd(0xD51A); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD51B); LCD_WriteData(0x00E8);
	LCD_WriteCmd(0xD51C); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD51D); LCD_WriteData(0x000C);
	LCD_WriteCmd(0xD51E); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD51F); LCD_WriteData(0x0030);
	LCD_WriteCmd(0xD520); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD521); LCD_WriteData(0x0045);
	LCD_WriteCmd(0xD522); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD523); LCD_WriteData(0x0063);
	LCD_WriteCmd(0xD524); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD525); LCD_WriteData(0x007E);
	LCD_WriteCmd(0xD526); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD527); LCD_WriteData(0x00B1);
	LCD_WriteCmd(0xD528); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD529); LCD_WriteData(0x00E0);
	LCD_WriteCmd(0xD52A); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD52B); LCD_WriteData(0x0026);
	LCD_WriteCmd(0xD52C); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD52D); LCD_WriteData(0x0060);
	LCD_WriteCmd(0xD52E); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD52F); LCD_WriteData(0x00B4);
	LCD_WriteCmd(0xD530); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD531); LCD_WriteData(0x00B9);
	LCD_WriteCmd(0xD532); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD533); LCD_WriteData(0x00C1);

	LCD_WriteCmd(0xD600); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD601); LCD_WriteData(0x0037);
	LCD_WriteCmd(0xD602); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD603); LCD_WriteData(0x0049);
	LCD_WriteCmd(0xD604); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD605); LCD_WriteData(0x006B);
	LCD_WriteCmd(0xD606); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD607); LCD_WriteData(0x0086);
	LCD_WriteCmd(0xD608); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD609); LCD_WriteData(0x009D);
	LCD_WriteCmd(0xD60A); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD60B); LCD_WriteData(0x00C3);
	LCD_WriteCmd(0xD60C); LCD_WriteData(0x0000);
	LCD_WriteCmd(0xD60D); LCD_WriteData(0x00E0);
	LCD_WriteCmd(0xD60E); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD60F); LCD_WriteData(0x000D);
	LCD_WriteCmd(0xD610); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD611); LCD_WriteData(0x002F);
	LCD_WriteCmd(0xD612); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD613); LCD_WriteData(0x0061);
	LCD_WriteCmd(0xD614); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD615); LCD_WriteData(0x0086);
	LCD_WriteCmd(0xD616); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD617); LCD_WriteData(0x00BD);
	LCD_WriteCmd(0xD618); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD619); LCD_WriteData(0x00E7);
	LCD_WriteCmd(0xD61A); LCD_WriteData(0x0001);
	LCD_WriteCmd(0xD61B); LCD_WriteData(0x00E8);
	LCD_WriteCmd(0xD61C); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD61D); LCD_WriteData(0x000C);
	LCD_WriteCmd(0xD61E); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD61F); LCD_WriteData(0x0030);
	LCD_WriteCmd(0xD620); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD621); LCD_WriteData(0x0045);
	LCD_WriteCmd(0xD622); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD623); LCD_WriteData(0x0063);
	LCD_WriteCmd(0xD624); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD625); LCD_WriteData(0x007E);
	LCD_WriteCmd(0xD626); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD627); LCD_WriteData(0x00B1);
	LCD_WriteCmd(0xD628); LCD_WriteData(0x0002);
	LCD_WriteCmd(0xD629); LCD_WriteData(0x00E0);
	LCD_WriteCmd(0xD62A); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD62B); LCD_WriteData(0x0026);
	LCD_WriteCmd(0xD62C); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD62D); LCD_WriteData(0x0060);
	LCD_WriteCmd(0xD62E); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD62F); LCD_WriteData(0x00B4);
	LCD_WriteCmd(0xD630); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD631); LCD_WriteData(0x00B9);
	LCD_WriteCmd(0xD632); LCD_WriteData(0x0003);
	LCD_WriteCmd(0xD633); LCD_WriteData(0x00C1);


	//**************LV2 Page 0 enable*************//
	LCD_WriteCmd(0xF000);	LCD_WriteData(0x0055);
	LCD_WriteCmd(0xF001);	LCD_WriteData(0x00AA);
	LCD_WriteCmd(0xF002);	LCD_WriteData(0x0052);
	LCD_WriteCmd(0xF003);	LCD_WriteData(0x0008);
	LCD_WriteCmd(0xF004);	LCD_WriteData(0x0000);

	//*************480x800*********************//
	LCD_WriteCmd(0xB500);	LCD_WriteData(0x0050);

	//***************Display control**************//
	LCD_WriteCmd(0xB100);	LCD_WriteData(0x00CC);
	//LCD_WriteCmd(0xB101);	LCD_WriteData(0x0000);

	//***************Source hold time*************//
	LCD_WriteCmd(0xB600);	LCD_WriteData(0x0002);

	//**************Gate EQ control***************//
	//LCD_WriteCmd(0xB700);	LCD_WriteData(0x0070);
	//LCD_WriteCmd(0xB701);	LCD_WriteData(0x0070);

	//*************Source EQ control (Mode 2)******//
	LCD_WriteCmd(0xB800);	LCD_WriteData(0x0001);
	LCD_WriteCmd(0xB801);	LCD_WriteData(0x0003);
	LCD_WriteCmd(0xB802);	LCD_WriteData(0x0003);
	LCD_WriteCmd(0xB803);	LCD_WriteData(0x0003);
					
	//************Inversion mode  (2-dot)***********//
	LCD_WriteCmd(0xBC00);	LCD_WriteData(0x0005);
	LCD_WriteCmd(0xBC01);	LCD_WriteData(0x0005);
	LCD_WriteCmd(0xBC02);	LCD_WriteData(0x0005);
					 
	//***************Frame rate***************//      
	//LCD_WriteCmd(0xBD00);	LCD_WriteData(0x0001);
	//LCD_WriteCmd(0xBD01);	LCD_WriteData(0x0084);
	LCD_WriteCmd(0xBD02);	LCD_WriteData(0x0007);  //0X1C
	LCD_WriteCmd(0xBD03);	LCD_WriteData(0x0031);
	LCD_WriteCmd(0xBE02);	LCD_WriteData(0x0007);  
	LCD_WriteCmd(0xBE03);	LCD_WriteData(0x0031);
	LCD_WriteCmd(0xBF02);	LCD_WriteData(0x0007);
	LCD_WriteCmd(0xBE03);	LCD_WriteData(0x0031);
	
	
	LCD_WriteCmd(0xFF00);	LCD_WriteData(0x00AA);
	LCD_WriteCmd(0xFF01);	LCD_WriteData(0x0055);    
	LCD_WriteCmd(0xFF02);	LCD_WriteData(0x0025);
	LCD_WriteCmd(0xFF03);	LCD_WriteData(0x0001);
	
	LCD_WriteCmd(0xF306);	LCD_WriteData(0x0010);
	LCD_WriteCmd(0xF408);	LCD_WriteData(0x0000);
	

	//********Timing control 4H w/ 4-Delayms *******//
	/*
	LCD_WriteCmd(0xC900);	LCD_WriteData(0x00D0);
	LCD_WriteCmd(0xC901);	LCD_WriteData(0x0002); 
	LCD_WriteCmd(0xC902);	LCD_WriteData(0x0050);
	LCD_WriteCmd(0xC903);	LCD_WriteData(0x0050);
	LCD_WriteCmd(0xC904);	LCD_WriteData(0x0050);
	*/
	LCD_WriteCmd(0x3600);	LCD_WriteData(0x00C0);//����ɨ�跽ʽ��RGB  BGR
	LCD_WriteCmd(0x3500);	LCD_WriteData(0x0000);
	
	LCD_WriteCmd(0x3A00);	LCD_WriteData(0x0005);	//70
	 
	LCD_WriteCmd(0x1100);
	HAL_Delay(120);
	LCD_WriteCmd(0x2900);
	HAL_Delay(50);
#endif

#ifdef TFTLCD_ILI9486
	LCD_WriteCmd(0xB0);
	LCD_WriteData(0x00);
	LCD_WriteCmd(0x11);
	HAL_Delay(20);

	LCD_WriteCmd(0xB3);
	LCD_WriteData(0x02);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);

	LCD_WriteCmd(0xC0);
	LCD_WriteData(0x10);//13
	LCD_WriteData(0x3B);//480
	LCD_WriteData(0x00);
	LCD_WriteData(0x02);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);
	LCD_WriteData(0x00);//NW
	LCD_WriteData(0x43);

	LCD_WriteCmd(0xC1);
	LCD_WriteData(0x10);//LCD_WriteData(0x08);
	LCD_WriteData(0x10);//LCD_WriteData(0x16);//CLOCK
	LCD_WriteData(0x08);
	LCD_WriteData(0x08);

	LCD_WriteCmd(0xC4);
	LCD_WriteData(0x11);
	LCD_WriteData(0x07);
	LCD_WriteData(0x03);
	LCD_WriteData(0x03);

	LCD_WriteCmd(0xC6);
	LCD_WriteData(0x00);

	LCD_WriteCmd(0xC8);//GAMMA
	LCD_WriteData(0x03);
	LCD_WriteData(0x03);
	LCD_WriteData(0x13);
	LCD_WriteData(0x5C);
	LCD_WriteData(0x03);
	LCD_WriteData(0x07);
	LCD_WriteData(0x14);
	LCD_WriteData(0x08);
	LCD_WriteData(0x00);
	LCD_WriteData(0x21);
	LCD_WriteData(0x08);
	LCD_WriteData(0x14);
	LCD_WriteData(0x07);
	LCD_WriteData(0x53);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x13);
	LCD_WriteData(0x03);
	LCD_WriteData(0x03);
	LCD_WriteData(0x21);
	LCD_WriteData(0x00);

	LCD_WriteCmd(0x35);
	LCD_WriteData(0x00);

	LCD_WriteCmd(0x36);  
	LCD_WriteData(0x00);

	LCD_WriteCmd(0x3A);
	LCD_WriteData(0x55);

	LCD_WriteCmd(0x44);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);

	LCD_WriteCmd(0xB6);
	LCD_WriteData(0x00);
	LCD_WriteData(0x22);//0 GS SS SM ISC[3:0];����GS SS������ʾ����ͬʱ�޸�R36
	LCD_WriteData(0x3B);

	LCD_WriteCmd(0xD0);
	LCD_WriteData(0x07);
	LCD_WriteData(0x07);//VCI1
	LCD_WriteData(0x1D);//VRH

	LCD_WriteCmd(0xD1);
	LCD_WriteData(0x00);
	LCD_WriteData(0x03);//VCM
	LCD_WriteData(0x00);//VDV

	LCD_WriteCmd(0xD2);
	LCD_WriteData(0x03);
	LCD_WriteData(0x14);
	LCD_WriteData(0x04);

	LCD_WriteCmd(0x29);
	HAL_Delay(20);

	LCD_WriteCmd(0xB4);
	LCD_WriteData(0x00);
	HAL_Delay(20);
	LCD_WriteCmd(0x2C);

#endif

	LCD_Display_Dir(TFTLCD_DIR);  //0������  1������  Ĭ������
	LCD_Clear(lcdColor_BLACK);	  //
}


//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ�Ⱥ͸߶�,�������0!!
//�����С:width*height. 
void LCD_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{    
#ifdef TFTLCD_HX8357D	
	LCD_WriteCmd(0x2A);
    LCD_WriteData(sx>>8);
    LCD_WriteData(sx&0XFF);
    LCD_WriteData(width>>8);
    LCD_WriteData(width&0XFF);

    LCD_WriteCmd(0x2b);
    LCD_WriteData(sy>>8);
    LCD_WriteData(sy&0XFF);
    LCD_WriteData(height>>8);
    LCD_WriteData(height&0XFF);
    LCD_WriteCmd(0x2c); 
#endif	
	
#ifdef TFTLCD_HX8352C
	LCD_WriteCmd(0x02);LCD_WriteData(sx/256);   
	LCD_WriteCmd(0x03);LCD_WriteData(sx%256); 	 
	LCD_WriteCmd(0x04);LCD_WriteData(width/256); 
	LCD_WriteCmd(0x05);LCD_WriteData(width%256);
	
	LCD_WriteCmd(0x06);LCD_WriteData(sy/256);  
	LCD_WriteCmd(0x07);LCD_WriteData(sy%256);
	LCD_WriteCmd(0x08);LCD_WriteData(height/256); 
	LCD_WriteCmd(0x09);LCD_WriteData(height%256); 	

	LCD_WriteCmd(0x22);

#endif

#ifdef TFTLCD_ILI9488
	LCD_WriteCmd(0x2a);
	LCD_WriteData(sx/256);   
	LCD_WriteData(sx%256); 	 
	LCD_WriteData(width/256); 
	LCD_WriteData(width%256);
	
	LCD_WriteCmd(0x2b);
	LCD_WriteData(sy/256);  
	LCD_WriteData(sy%256);
	LCD_WriteData(height/256); 
	LCD_WriteData(height%256);

	LCD_WriteCmd(0x2C);

#endif

#ifdef TFTLCD_ILI9327
	LCD_WriteCmd(0x2A);
	LCD_WriteData(sx/256);   
	LCD_WriteData(sx%256); 	 
	LCD_WriteData(width/256); 
	LCD_WriteData(width%256);
	
	LCD_WriteCmd(0x2B);
	LCD_WriteData(sy/256);  
	LCD_WriteData(sy%256);
	LCD_WriteData(height/256); 
	LCD_WriteData(height%256); 	

	LCD_WriteCmd(0x2C);

#endif

#ifdef TFTLCD_ST7793	
	if(lcdPara.dir==0)
	{
		LCD_WriteCmd(0x0210);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0211);  
	    LCD_WriteData(width);
		LCD_WriteCmd(0x0212);   
	    LCD_WriteData(sy);
		LCD_WriteCmd(0x0213);   
	    LCD_WriteData(height);
	
		LCD_WriteCmd(0x0200);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0201);   
	    LCD_WriteData(sy);	
	}   	
	else
	{
		LCD_WriteCmd(0x0212);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0213);  
	    LCD_WriteData(width);
		LCD_WriteCmd(0x0210);   
	    LCD_WriteData(sy);
		LCD_WriteCmd(0x0211);   
	    LCD_WriteData(height);
	
		LCD_WriteCmd(0x0201);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0200);   
	    LCD_WriteData(sy);	
	}
	LCD_WriteCmd(0x0202);		
#endif

#ifdef TFTLCD_NT35510	
	LCD_WriteCmd(0X2A00);LCD_WriteData(sx>>8);  
	LCD_WriteCmd(0X2A01);LCD_WriteData(sx&0XFF);	  
	LCD_WriteCmd(0X2A02);LCD_WriteData(width>>8);   
	LCD_WriteCmd(0X2A03);LCD_WriteData(width&0XFF);   
	LCD_WriteCmd(0X2B00);LCD_WriteData(sy>>8);   
	LCD_WriteCmd(0X2B01);LCD_WriteData(sy&0XFF);  
	LCD_WriteCmd(0X2B02);LCD_WriteData(height>>8);   
	LCD_WriteCmd(0X2B03);LCD_WriteData(height&0XFF);
	LCD_WriteCmd(0x2C00);
#endif	

#ifdef TFTLCD_ILI9486
	LCD_WriteCmd(0x2A);
	LCD_WriteData(sx/256);   
	LCD_WriteData(sx%256); 	 
	LCD_WriteData(width/256); 
	LCD_WriteData(width%256);
	
	LCD_WriteCmd(0x2B);
	LCD_WriteData(sy/256);  
	LCD_WriteData(sy%256);
	LCD_WriteData(height/256); 
	LCD_WriteData(height%256); 	

	LCD_WriteCmd(0x2C);
#endif
}

//��������
//color:Ҫ���������ɫ
void LCD_Clear(uint16_t color)
{
	uint16_t i, j ;
	LCD_Set_Window(0, 0, lcdPara.width-1, lcdPara.height-1);	 //��������
  	for(i=0; i<lcdPara.width; i++)
		for (j=0; j<lcdPara.height; j++)
			LCD_WriteData_Color(color);
}


//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd, uint16_t color)
{          
	uint16_t temp;

    if((xStart > xEnd) || (yStart > yEnd))
    {
        return;
    }   
	LCD_Set_Window(xStart, yStart, xEnd, yEnd); 
    xStart = xEnd - xStart + 1;
	yStart = yEnd - yStart + 1;

	while(xStart--)
	{
	 	temp = yStart;
		while (temp--)
	 	{			
			LCD_WriteData_Color(color);	
		}
	}	
} 

//����
//x,y:����
//FRONT_COLOR:�˵����ɫ
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	LCD_Set_Window(x, y, x, y);  //���õ��λ��
	LCD_WriteData_Color(lcdFRONT_COLOR);	
}

//���ٻ���
//x,y:����
//color:��ɫ
void LCD_DrawFRONT_COLOR(uint16_t x,uint16_t y,uint16_t color)
{	   
	LCD_Set_Window(x, y, x, y);
	LCD_WriteData_Color(color);	
}

//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
uint16_t LCD_ReadPoint(uint16_t x,uint16_t y)
{
 	uint16_t r=0,g=0,b=0;
	if(x>=lcdPara.width||y>=lcdPara.height)return 0;	//�����˷�Χ,ֱ�ӷ���		     
	LCD_Set_Window(x, y, x, y);
	
#ifdef TFTLCD_HX8357D	
	LCD_WriteCmd(0X2E);     		 				    
 	r=LCD_ReadData();								//dummy Read	   
 	r=LCD_ReadData();  		  						//ʵ��������ɫ
#endif
	
#ifdef TFTLCD_HX8352C	
	LCD_WriteCmd(0X22);     		 				    
 	r=TFTLCD->LCD_DATA;	
	r=LCD_ReadData();
#endif	

#ifdef TFTLCD_ILI9488	
	LCD_WriteCmd(0X2e);
	r=LCD_ReadData();								//dummy Read     		 				    
	r=LCD_ReadData();								//ʵ��������ɫ	
	//printf("r=%X\r\n",r);
	b=LCD_ReadData();
	g=LCD_ReadData(); 
	//printf("g=%X\r\n",g);
	//printf("b=%X\r\n",b);
	return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));
#endif

#ifdef TFTLCD_ILI9327	
	LCD_WriteCmd(0X2e);
	r=LCD_ReadData();								//dummy Read     		 				    
	r=LCD_ReadData();								//ʵ��������ɫ	
	r=(r<<8)|(r>>8);
	return r;
#endif

#ifdef TFTLCD_ST7793	
	if(x>=lcdPara.width||y>=lcdPara.height)return 0;	//�����˷�Χ,ֱ�ӷ���		     
	LCD_Set_Window(x, y, x, y);
	LCD_WriteCmd(0x0202);     		 				    
 	r=LCD_ReadData();  		  						//ʵ��������ɫ
#endif
	
#ifdef TFTLCD_NT35510	
	LCD_WriteCmd(0X2E00);
	r=LCD_ReadData();								//dummy Read     		 				    
	r=LCD_ReadData();								//ʵ��������ɫ
	
	b=LCD_ReadData(); 
	g=r&0XFF;		//����9341/5310/5510,��һ�ζ�ȡ����RG��ֵ,R��ǰ,G�ں�,��ռ8λ
	g<<=8;
	
	return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));
#endif

#ifdef TFTLCD_ILI9486	
	LCD_WriteCmd(0X2e);
	r=LCD_ReadData();								//dummy Read     		 				    
	r=LCD_ReadData();								//ʵ��������ɫ	
	//printf("r=%X\r\n",r);
	b=LCD_ReadData();
	g=LCD_ReadData(); 
	//printf("g=%X\r\n",g);
	//printf("b=%X\r\n",b);
	return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));
#endif
 	return r;						
}

//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t;
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}  

void LCD_DrawLine_Color(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	uint16_t t;
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawFRONT_COLOR(uRow,uCol,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

// ��һ��ʮ�ֵı��
// x����ǵ�X����
// y����ǵ�Y����
// color����ǵ���ɫ
void LCD_DrowSign(uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t i;

    /* ���� */
    LCD_Set_Window(x-1, y-1, x+1, y+1);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color);   
    }

    /* ���� */
    LCD_Set_Window(x-4, y, x+4, y);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color); 
    }

    /* ���� */
    LCD_Set_Window(x, y-4, x, y+4);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color); 
    }
}

//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 

//���������С��ֻӰ��������ʾ
void	LCD_setFontSize(uint8_t	fontSize)//	���������С��ֻ����12��16����24
{
	if ((fontSize != 12) || (fontSize != 16) ||(fontSize != 24))
		return;
	LCD_FS=fontSize;
}

//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//charCode: Ҫ��ʾ���ַ���ASCII��:" "--->"~"
//fontSize:�����С 12/16/24
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t charCode,uint8_t mode)
{
	uint8_t fontSize=LCD_FS;
	LCD_CurPosX=x+fontSize/2;
	LCD_CurPosY=y;


    uint8_t temp,t1,t;
	uint16_t y0=y;
	uint8_t csize=(fontSize/8+((fontSize%8)?1:0))*(fontSize/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���
 	charCode=charCode-' ';	//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0; t<csize; t++)
	{   
		if(fontSize==12)
			temp=ascii_1206[charCode][t]; 	 	//����1206����
		else if(fontSize==16)
			temp=ascii_1608[charCode][t];	//����1608����
		else if(fontSize==24)
			temp=ascii_2412[charCode][t];	//����2412����
		else
			return;		//û�е��ֿ�

		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)
				LCD_DrawFRONT_COLOR(x,y,lcdFRONT_COLOR);
			else if(mode==0)
				LCD_DrawFRONT_COLOR(x,y,lcdBACK_COLOR);
			temp<<=1;
			y++;
			if(y>=lcdPara.height)
				return;		//��������
			if((y-y0)==fontSize)
			{
				y=y0;
				x++;
				if(x>=lcdPara.width)
					return;	//��������
				break;
			}
		}  	 
	}

}   
//m^n����
//����ֵ:m^n�η�.
uint32_t LCD_Pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;
	while(n--)
		result*=m;
	return result;
}			 
//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
//void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size)
//{
//	uint8_t t,temp;
//	uint8_t enshow=0;
//	for(t=0;t<len;t++)
//	{
//		temp=(num/LCD_Pow(10,len-t-1))%10;
//		if(enshow==0&&t<(len-1))
//		{
//			if(temp==0)
//			{
//				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
//				continue;
//			}else enshow=1;
//
//		}
//	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0);
//	}
//}

//��ʾ����,���ݽ�������num������ int8_t, int16_t, int32_t
void LCD_ShowInt(uint16_t x,uint16_t y,int32_t num)
{
	char buf[20];
	siprintf(buf,"%ld",num);	//<stdio.h>�еĺ�����ת��Ϊ�ַ���,�Զ���'\0'
	LCD_ShowString(x,y,(uint8_t*)buf);
}

//��ʾ�޷�������,���ݽ�������num������ uint8_t, uint16_t, uint32_t
void LCD_ShowUint(uint16_t x,uint16_t y,uint32_t num)
{
	char buf[20];
	siprintf(buf,"%lu",num);	//ת��Ϊ�ַ���,�Զ���'\0'
	LCD_ShowString(x,y,(uint8_t*)buf);
}

//ʮ��������ʾ�޷�������
// show0X ����ʱ��ʾǰ���� "0x"
void LCD_ShowUintHex(uint16_t x,uint16_t y,uint32_t num, uint8_t show0X)
{
	char buf[20];
	if (show0X)
		siprintf(buf,"0x%lX",num);	//ת��Ϊ�ַ���,�Զ���'\0'
	else
		siprintf(buf,"%lX",num);		//ת��Ϊ�ַ���,�Զ���'\0'

	LCD_ShowString(x,y,(uint8_t*)buf);
}

//��ʾ�޷�������,���ݽ�������num������ uint8_t, uint16_t, uint32_t, ����digiCount��ʾ���ָ���
void LCD_ShowUintX(uint16_t x,uint16_t y,uint32_t num, uint8_t digiCount)
{
	char buf[20];
	siprintf(buf,"%lu",num);	//ת��Ϊ�ַ���,�Զ���'\0'

	uint8_t  len=strlen(buf);	//<string.h>�еĺ���
	if (len>=digiCount)	//���ʵ�ʳ��ȴ�����Ҫ��ʾ��λ����ֱ����ʾ
	{
		LCD_ShowString(x,y,(uint8_t*)buf);
		return;
	}

	char buf2[20];
	uint8_t	i,j;
	for(i=0; i<(digiCount-len); i++)
		buf2[i]='0';	//ǰ�����ַ�0�

	j=digiCount-len;
	for(i=0; i<len; i++, j++)
		buf2[j]=buf[i];	//����
	buf2[j]=0x00;	//������

	LCD_ShowString(x,y,(uint8_t*)buf2);
}

//��ʾ��������value��Ҫ��ʾ����ֵ��decimals��С�����λ������
void LCD_ShowFloat(uint16_t x,uint16_t y,float value, uint8_t decimals)//��ʾ������
{
	char buf[20];
//1. �����Ҫ��ʾ��С��λΪ�����ֱ��ת��Ϊ��������ʾ
	if (decimals==0)  //��ʾ����
	{
		long int intVal=lrintf(value);	// <math.h>�еĺ�����������ת��Ϊ������
		siprintf(buf,"%ld",intVal);	//�޷�ֱ��ת��������,ֻ��
		LCD_ShowString(x,y,(uint8_t*)buf);
		return;
	}

//2. �ж��������� ��value=-423.1763
	uint8_t  sign=0;	//����
	if (value<0)	//����
	{
		sign=1;	//����
		value =-value;	//ת��Ϊ����value=423.1763
	}

//3. ��������
	uint8_t i;
	float 	value10x=value;
	for(i=0; i<decimals; i++)
		value10x=10*value10x;	//����10X
	long int intFrac=roundf(value10x);	// <math.h>�еĺ���, ����Ϊ����,intFrac=42318

//4. ת��Ϊ�����ַ������� intFrac=42318, buf="81.324"
	uint8_t  len=0; //�������ֵĳ���
	uint8_t digi;
	while (1)
	{
		digi= intFrac % 10;	//��ȡ�������Ӻ���ǰȡ
		intFrac=intFrac / 10; //������������С10��
		buf[len]=0x30+digi;  //����
		len++;
		if (len==decimals)
		{
			buf[len]='.';  //����С����
			len++;
		}

		if (intFrac<=0)
			break;
	}
	buf[len]=0x00;  //������

//5. ������
	char bufSeq[20];
	i=0;
	if (sign)
	{
		bufSeq[0]='-';
		i=1;
	}

	for (int8_t j=len-1; j>=0; j--,i++)
	{
		digi=buf[j];
		bufSeq[i]=digi;
	}
	bufSeq[i]=0x00;// ������
	LCD_ShowString(x,y,(uint8_t*)bufSeq);
}

//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
//void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode)
//{
//	uint8_t t,temp;
//	uint8_t enshow=0;
//	for(t=0;t<len;t++)
//	{
//		temp=(num/LCD_Pow(10,len-t-1))%10;
//		if(enshow==0&&t<(len-1))
//		{
//			if(temp==0)
//			{
//				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);
//				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);
// 				continue;
//			}else enshow=1;
//
//		}
//	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01);
//	}
//}


//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
//void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p)
void LCD_ShowString(uint16_t x,uint16_t y,uint8_t *p)
{         
	uint8_t x0=x;
//	while((*p<='~')&&(*p>=' '))  //�ж��ǲ��ǷǷ��ַ�,����'\0'�Զ�����
	while(*p!=0x00)  //����'\0'�Զ�����
	{
		if(x>=LCD_W)	//�ƶ�����һ��
		{
			x =x0;
			y += LCD_FS;
		}
		if(y>=LCD_H) //������Ļ����
			break;	 //�˳�

		LCD_ShowChar(x,y,*p,0);
		x += LCD_FS/2;
		p++;
	}
}



/****************************************************************************
*��������LCD_ShowFontHZ
*��  �룺x��������ʾ��X����
*      * y��������ʾ��Y����
*      * cn��Ҫ��ʾ�ĺ���
*      * wordColor�����ֵ���ɫ
*      * backColor��������ɫ
*��  ����
*��  �ܣ�д���ſ��庺��
****************************************************************************/
#if 0
void LCD_ShowFontHZ(uint16_t x, uint16_t y, uint8_t *cn)
{  
	uint8_t i, j, wordNum;
	uint16_t color;
	while (*cn != '\0')
	{
		LCD_Set_Window(x, y, x+31, y+28);
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNumɨ���ֿ������
			if ((CnChar32x29[wordNum].Index[0]==*cn)
			     &&(CnChar32x29[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<116; i++) 
				{	//MSK��λ��
					color=CnChar32x29[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							LCD_WriteData_Color(lcdFRONT_COLOR); 						
						} 						
						else
						{
							LCD_WriteData_Color(lcdBACK_COLOR); 
						} 
						color<<=1;
					}//for(j=0;j<8;j++)����
				}    
			}
		} //for (wordNum=0; wordNum<20; wordNum++)���� 	
		cn += 2;
		x += 32;
	}
}
#endif


#if 1
void LCD_ShowFontHZ(uint16_t x, uint16_t y, uint8_t *cn)
{
	uint8_t i, j, wordNum;
	uint16_t color;
	uint16_t x0=x;
	uint16_t y0=y;
	while (*cn != '\0')
	{
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNumɨ���ֿ������
			if ((CnChar32x29[wordNum].Index[0]==*cn)
			     &&(CnChar32x29[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<116; i++) 
				{	//MSK��λ��
					color=CnChar32x29[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							LCD_DrawFRONT_COLOR(x,y,lcdFRONT_COLOR);
						} 						
						else
						{
							LCD_DrawFRONT_COLOR(x,y,lcdBACK_COLOR);
						} 
						color<<=1;
						x++;
						if((x-x0)==32)
						{
							x=x0;
							y++;
							if((y-y0)==29)
							{
								y=y0;
							}
						}
					}//for(j=0;j<8;j++)����
				}	
			}
			
		} //for (wordNum=0; wordNum<20; wordNum++)���� 	
		cn += 2;
		x += 32;
		x0=x;
	}
}	
#endif

void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t wide, uint16_t high,uint8_t *pic)
{
	uint16_t temp = 0;
	long tmp=0,num=0;
	LCD_Set_Window(x, y, x+wide-1, y+high-1);
	num = wide * high*2 ;
	do
	{  
		temp = pic[tmp + 1];
		temp = temp << 8;
		temp = temp | pic[tmp];
		LCD_WriteData_Color(temp);//�����ʾ
		tmp += 2;
	}
	while(tmp < num);	
}


//��ʾ16*16 �����С�ĺ��֣�
//ʹ��HzLib.c�ﶨ���GB2312���ֿ�  ����ȡģ  16*16  ��ʾ���⺺��
#ifdef	USE_HZ_LIB
void LCD_ShowHZ16(uint16_t x, uint16_t y, uint8_t *str)
{
	uint8_t i,j;
	uint8_t buffer[32];
	uint16_t tmp_char=0;

	GetGBKCode(buffer,str);  /* ȡ��ģ���� */

	for ( i = 0; i < 16; i++ )
	{
		tmp_char = buffer[i*2];
		tmp_char = ( tmp_char << 8 );
		tmp_char |= buffer[2*i+1];
		for (j = 0; j < 16; j++ )
		{
			if ( (tmp_char >> 15-j ) & 0x01 == 0x01 )
				LCD_DrawFRONT_COLOR(x+j,y+i,lcdFRONT_COLOR);  /* �ַ���ɫ */
			else
				LCD_DrawFRONT_COLOR(x+j,y+i,lcdBACK_COLOR);  /* ������ɫ */
		}
	}

}
#endif


