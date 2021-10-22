/**
  ******************************************************************************
  * @file	bsp_led.h
  * @author	qsunj
  * @date	21-5-21
  * @brief   
  ******************************************************************************
  */

#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "drv_gpio.h"

typedef enum LED_IDTypeDefine {
	LED0 = 0x0040,
	LED1 = 0x0080
}LEDNum_t;

void LED_Init(void);
void LED_Flip(LEDNum_t LEDx);
void LED_FilpForISR(LEDNum_t LEDx, uint32_t interval);

#endif

