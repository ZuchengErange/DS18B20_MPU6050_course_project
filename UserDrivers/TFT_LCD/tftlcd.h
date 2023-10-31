#ifndef _tftlcd_H
#define _tftlcd_H


#include "stm32f4xx_hal.h"

//����LCD��������������  �ɸ����Լ����ϵĲ��������ͺ���ѡ�����������
//#define TFTLCD_HX8357D 

#define TFTLCD_HX8352C	//3.6����������оƬ,�ֱ���400*240

//#define TFTLCD_ILI9488

//#define TFTLCD_ST7793

//#define TFTLCD_ILI9327

//#define TFTLCD_NT35510

//#define TFTLCD_ILI9486		//3.5����������оƬ,

#define		USE_HZ_LIB		//������ţ��Ƿ�ʹ�ú��ֿ�,�����ʹ�þ�ע�͵�����

#define TFTLCD_DIR	0	//0������  1������  Ĭ������


//TFTLCD��ַ�ṹ��
typedef struct
{
	uint16_t LCD_CMD;
	uint16_t LCD_DATA;
}TFTLCD_TypeDef;


//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11, A6��Ϊ��������������
//ע������ʱSTM32�ڲ�������һλ����! 111 1110=0X7E			    
#define TFTLCD_BASE        ((uint32_t)(0x6C000000 | 0x0000007E))
#define TFTLCD             ((TFTLCD_TypeDef *) TFTLCD_BASE)


//TFTLCD��Ҫ����
typedef struct  
{										    
	uint16_t width;			//LCD ���
	uint16_t height;		//LCD �߶�
	uint16_t id;			//LCD ID
	uint8_t  dir;            //LCD ����
}TFTLCD_ParaDef;

//һЩȫ�ֱ���
extern	uint16_t LCD_W;		//LCD ���,����LCD_Display_Dir()�������ʼ��
extern	uint16_t LCD_H;		//LCD �߶�
extern	uint8_t	 LCD_FS;	//fontsize, һ���ַ����Ϊ��������С
extern	uint16_t LCD_CurPosX;	//��ǰλ��X
extern	uint16_t LCD_CurPosY;	//��ǰλ��Y


//LCD����
extern TFTLCD_ParaDef lcdPara;	//����LCD��Ҫ����
//LCD��ǰ����ɫ�ͱ���ɫ	   
extern uint16_t  lcdFRONT_COLOR;//ǰ����ɫ Ĭ�Ϻ�ɫ
extern uint16_t  lcdBACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

//�����С����
#define		lcdFont_Size12	0x0C		//����12
#define		lcdFont_Size16	0x10		//����16
#define		lcdFont_Size24	0x18		//����24

//������ɫ
#define 	lcdColor_WHITE         	 0xFFFF
#define 	lcdColor_BLACK         	 0x0000
#define 	lcdColor_BLUE         	 0x001F
#define 	lcdColor_BRED            0XF81F
#define 	lcdColor_GRED 			 0XFFE0
#define 	lcdColor_GBLUE			 0X07FF
#define 	lcdColor_RED           	 0xF800
#define 	lcdColor_MAGENTA       	 0xF81F
#define 	lcdColor_GREEN         	 0x07E0
#define 	lcdColor_CYAN          	 0x7FFF
#define 	lcdColor_YELLOW        	 0xFFE0
#define 	lcdColor_BROWN 			 0XBC40 //��ɫ
#define 	lcdColor_BRRED 			 0XFC07 //�غ�ɫ
#define 	lcdColor_GRAY  			 0X8430 //��ɫ



/* LCD������дָ��  */
void LCD_WriteCmd(uint16_t cmd);	//дָ��
void LCD_WriteData(uint16_t data);	//д����
void LCD_WriteCmdData(uint16_t cmd,uint16_t data);	//дָ�������
void LCD_WriteData_Color(uint16_t color);	//д��ɫ����

//uint16_t LCD_ReadData(void);	//ȱ�����������������

/*  LCD�����ʼ�� */
void TFTLCD_Init(void);           //��ʼ��

/* LCD��ʾ�������ܺ�������   */
//���ô���,���Զ����û������굽�������Ͻ�(sx,sy)
void LCD_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height);

void LCD_Clear(uint16_t Color);	 	//����

//==========��ͼ��غ���==============================
//��ɫ���һ����������
void LCD_Fill(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd, uint16_t color);

void LCD_DrawPoint(uint16_t x,uint16_t y);	//����

void LCD_DrawFRONT_COLOR(uint16_t x,uint16_t y,uint16_t color);

//��ȡ��ĳ�����ɫֵ
uint16_t LCD_ReadPoint(uint16_t x,uint16_t y);

//����
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

//��ָ����ɫ����
void LCD_DrawLine_Color(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);

// ��һ��ʮ�ֵı��
void LCD_DrowSign(uint16_t x, uint16_t y, uint16_t color);

//������
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

//��ָ��λ�û�һ��ָ����С��Բ
void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r);

//=========�ַ���������ʾ=========
//��ָ��λ����ʾһ���ַ�,�����Сֻ����12,16,24������
void LCD_setFontSize(uint8_t	fontSize);//	���������С��ֻ����12��16����24
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t charCode,uint8_t mode);

//��ʾ����,��λΪ0,����ʾ
//void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size);

//����4����������ά�������
void LCD_ShowInt(uint16_t x,uint16_t y,int32_t num);	//��ʾ����
void LCD_ShowUint(uint16_t x,uint16_t y,uint32_t num);	//��ʾ�޷�������
void LCD_ShowUintHex(uint16_t x,uint16_t y,uint32_t num, uint8_t show0X);	//ʮ��������ʾ�޷�������
void LCD_ShowUintX(uint16_t x,uint16_t y,uint32_t num, uint8_t digiCount);//�̶�����λ����ʾ��ǰ�˲�0
void LCD_ShowFloat(uint16_t x,uint16_t y,float value, uint8_t decimals);//��ʾ������

//��ʾ����,��λΪ0,������ʾ
//void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode);

//��ʾ�ַ���
void LCD_ShowString(uint16_t x,uint16_t y,uint8_t *p);
//void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p);

//��ʾ���֣���ģ��С32*29�����Լ�����ģ
void LCD_ShowFontHZ(uint16_t x, uint16_t y, uint8_t *cn);

void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t wide, uint16_t high,uint8_t *pic);

//ʹ��HzLib.c�ﶨ���GB2312���ֿ�  ����ȡģ  16*16  ��ʾ���⺺��
#ifdef	USE_HZ_LIB
	void LCD_ShowHZ16(uint16_t x, uint16_t y, uint8_t *str);
#endif

#endif
