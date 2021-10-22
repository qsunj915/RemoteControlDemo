/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  qsunj
  * @date    21-5-25
  * @brief  注意不能同时用两个Task
  ******************************************************************************
  */

#include "bsp_led.h"
/**
  * @brief  LED_Init
  * @param  None
  * @retval None
  */
void LED_Init(void) {
	GPIO_Format_Init(GPIOC,GPIO_Pin_6 | GPIO_Pin_7,
					GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_100MHz);
	
	GPIO_SetBits(GPIOC,GPIO_Pin_6 | GPIO_Pin_7); //初始点亮
}

/**
  * @brief  LED_Task
  * @param  LEDn, interval
  * @note	注意不能同时用两个Task
  * @retval None
  */
void LED_Flip( LEDNum_t LEDn )
{
	static uint8_t led_stateflag[2] = {0,0};
	
	if ( LEDn == LED0 ) {
		if ( !led_stateflag[0] ) {
			GPIO_ResetBits(GPIOC,LEDn); 
		} else {
			GPIO_SetBits(GPIOC,LEDn);
		}
		led_stateflag[0] = 1 - led_stateflag[0];
	} else if ( LEDn == LED1 ) {
		if ( !led_stateflag[1] ) {
			GPIO_ResetBits(GPIOC,LEDn); 
		} else {
			GPIO_SetBits(GPIOC,LEDn);
		}
		led_stateflag[1] = 1 - led_stateflag[1];
	}
	
}


void LED_FilpForISR(LEDNum_t LEDx, uint32_t interval)
{
	static uint16_t val[2]  = {0};
	static uint16_t Flag[2] = {0};
	uint16_t        num     =  0 ;
	
	switch(LEDx)
	{
		case(LED0):
		{
			num = 0;
		}
		case(LED1):
		{
			num = 1;
		}
	}
	if(val[num] >= interval)
	{
		if(Flag[num])
		{
			GPIO_ResetBits(GPIOC,LEDx); 
			Flag[num] = 0;
		}
		else
		{
			GPIO_SetBits(GPIOC,LEDx); 
			Flag[num] = 1;
		}
		val[num] = 0;
	}
	val[num]++;
}


