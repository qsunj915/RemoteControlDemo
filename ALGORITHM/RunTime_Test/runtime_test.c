/**
  ******************************************************************************
  * @file	runtime_test.c
  * @author	qsunj
  * @date	21-5-25
  * @brief   
  ******************************************************************************
  */

#include "runtime_test.h"
#include "oled_gui.h"

uint16_t G_testtime_count = 0;

uint16_t TIM7_ProgramRunTime_Test(void) {
	TIM_Cmd(TIM7, ENABLE);//使能定时器
	G_testtime_count=0;
	
	TIM7_TestTask();
	
	return G_testtime_count;
}

void TIM7_TestTask() {
	
}


