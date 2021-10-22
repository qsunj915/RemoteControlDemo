/**
  ******************************************************************************
  * @file    drv_adc.h
  * @author  
  * @version v1.0
  * @date    
  * @brief   copy
  ******************************************************************************
  */
#ifndef __ADC_H
#define __ADC_H

#include "drv_gpio.h"
#include "drv_timer.h"
#include "wave_filter.h"

#define   ADC_DMA           0x02
#define   JOY_ADC_DEAD_BAN  350


extern uint32_t  ADC_Value_G[8];

void ADC1_Init(void);
void ADC_DMA_Config(void);
void JOY_ADC_Calibration(void);
void JOY_ADC_Pro(void);

#endif
