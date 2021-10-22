/**
  ******************************************************************************
  * @file    oled_gui.c
  * @author  xjc
  * @version v1.0
  * @date    
  * @brief
  ******************************************************************************
  */
#include "oled_gui.h"

void GUI_Init(void)
{
	OLED_Init();
	OLED_Display_On();
	OLED_Clear();
	
	OLED_ShowString(byte(9),line1,"remote",8);
	OLED_ShowString(byte(0),line1,"RF:",8);
	//遥杆:
	OLED_ShowString(byte(0),line3,"L_X:",6);
	OLED_ShowString(byte(0),line4,"L_Y:",6);
	OLED_ShowString(byte(8),line3,"R_X:",6);
	OLED_ShowString(byte(8),line4,"R_Y:",6);
	//电位计：
	OLED_ShowString(0 ,line5,"K23:",6);
	OLED_ShowString(64,line5,"K24:",6);
	OLED_ShowString(0,line6,"K25:",6);
	OLED_ShowString(64,line6,"K26:",6);
	//按键：
	OLED_ShowString(byte(0),line7,"KEY",6);
}

void GUI_Key_Updata(void)
{
	static uint8_t i = 0;
/*-----------------------------------------------
			按键
------------------------------------------------*/
	for(i = 0;i < 16;i++)
	{
		if(i < 8)
		{
			OLED_ShowChar(50+10*i,line7,KEY_G[i]+48,6);
		}
		else
		{
			OLED_ShowChar(50+10*(i-8),line8,KEY_G[i]+48,6);
		}
	}
}

void GUI_ADC_Updata(void)
{
/*-----------------------------------------------
			ADC
------------------------------------------------*/
	char str[5];
	static char key_show=1;
	
	sprintf(str,"%5d",ADC_Value_G[0]);
		OLED_ShowString(94,line3,str,6);
	sprintf(str,"%5d",ADC_Value_G[1]);
		OLED_ShowString(94,line4,str,6);
	sprintf(str,"%5d",ADC_Value_G[2]);
		OLED_ShowString(30,line3,str,6);
	sprintf(str,"%5d",ADC_Value_G[3]);
		OLED_ShowString(30,line4,str,6);
	
	
	if ( key_show == 1 ) {
		sprintf(str,"%4d",ADC_Value_G[4]+2048);
		OLED_ShowString(30 ,line5,str,6);
	} else if ( key_show == 2 ) {
		sprintf(str,"%4d",ADC_Value_G[5]+2048);
		OLED_ShowString(94,line5,str,6);
	} else if ( key_show == 3 ) {
		sprintf(str,"%4d",ADC_Value_G[6]+2048);
		OLED_ShowString(30,line6,str,6);
	} else if ( key_show == 4 ) {
		sprintf(str,"%4d",ADC_Value_G[7]+2048);
		OLED_ShowString(94,line6,str,6);
		key_show = 0;
	}
	key_show++;
}

void OLED_GUI_Task() {
	GUI_ADC_Updata();
	GUI_Key_Updata();
}

