#ifndef __INIT_H
#define __INIT_H

#include "stm32f4xx.h"
#include "drv_systick.h"
#include "drv_usart.h"
#include "bsp_led.h"
#include "drv_timer.h"
#include "bsp_key.h"
#include "drv_adc.h"
#include "oled_gui.h"
#include "pack_deal.h"
#include "bsp_rf24l01.h"

void System_Init(void);

#endif

