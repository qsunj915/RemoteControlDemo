/**
  ******************************************************************************
  * @file    oled_gui.h
  * @author  qsunj
  * @version v1.0
  * @date    
  * @brief   copy
  ******************************************************************************
  */
#ifndef __GUI_H
#define __GUI_H

#include "bsp_oled.h"
#include "bsp_key.h"
#include <stdio.h>
#include "drv_adc.h"


/* OLED屏幕有7行 */
#define line1 0
#define line2 1
#define line3 2
#define line4 3
#define line5 4
#define line6 5
#define line7 6
#define line8 7
/* OLED屏幕有128的点,也就是16列（16*8） */
#define byte(data)  data*8

void GUI_Init(void);
void GUI_Key_Updata(void);
void GUI_ADC_Updata(void);

void OLED_GUI_Task(void);

#endif
