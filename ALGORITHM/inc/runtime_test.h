/**
  ******************************************************************************
  * @file	runtime_test.h
  * @author	qsunj
  * @date	21-5-25
  * @brief   
  ******************************************************************************
  */

#ifndef __RUNTIME_TEST_H
#define __RUNTIME_TEST_H

#include "drv_timer.h"

uint16_t TIM7_ProgramRunTime_Test(void);
uint16_t Get_TIM7_CountTime(void);

extern uint16_t G_testtime_count;

#endif
