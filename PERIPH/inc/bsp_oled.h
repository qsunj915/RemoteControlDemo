/**
  ******************************************************************************
  * @file    oled
  * @author  qsunj
  * @version v1.0
  * @date    
  * @brief   copy
  ******************************************************************************
  */
#ifndef __OLED_H
#define __OLED_H

#include "stm32f4xx.h"
#include "drv_systick.h"
#include "stdlib.h"
#include "drv_i2c.h"

#define OLED_MODE 	  0
#define SIZE 		  8
#define XLevelL		  0x00
#define XLevelH		  0x10
#define Max_Column	  128
#define Max_Row		  64
#define	Brightness	  0xFF 
#define X_WIDTH 	  128
#define Y_WIDTH 	  64	   

/* OLED��Ļ��7�� */
#define line1 0
#define line2 1
#define line3 2
#define line4 3
#define line5 4
#define line6 5
#define line7 6
#define line8 7
/* OLED��Ļ��128�ĵ�,Ҳ����16�У�16*8�� */
#define byte(data)  data*8
//-----------------OLED IIC�˿ڶ���----------------  					   

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


//OLED�����ú���
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ClearBlue(void);
void OLED_ClearLine(u8 line);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, char *p,u8 Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,const char data[][16],u8 num);
void OLED_ShowCHinese7x7(u8 x,u8 y,const char data[][16],u8 num);
void OLED_ShowCHineseString(u8 x,u8 y,const char data[][16],u8 num);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture(void);

void I2C_WriteConCmd(unsigned char I2C_Command);//д����
void I2C_WriteDataCmd(unsigned char I2C_Data);//д����

#endif


