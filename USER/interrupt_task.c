/**
  ******************************************************************************
  * @file	interrupt_task.h
  * @author	qsunj
  * @date	21-7-14
  * @brief   
  ******************************************************************************
  */
#include "interrupt_task.h"

/****************USART**************************/
void InterruptTask_USART1(uint8_t rx_data)
{
//	TransmitData_UnPack( RxData );
}

void InterruptTask_USART2(uint8_t rx_data)
{

}

void InterruptTask_USART3(uint8_t rx_data)
{

}

void InterruptTask_USART6(uint8_t rx_data)
{

}

/******************TIM**********************/
void InterruptTask_TIM2(void)
{
	static uint8_t i=0;
	
	keyHandle((keysTypedef_t *)&keys);
	for (i=0; i<FRAMELENGTH_KEY; i++) {
		Insert_transmitdata_buffer_key(KEY_G[i], i);
	}
	
	JOY_ADC_Calibration();	//0ms
	for (i=0; i<FRAMELENGTH_FLOAT; i++) {
		Insert_transmitdata_buffer_float(ADC_Value_G[i], i);
	}
	
	TransmitData_Pack();
	NRF24L01_TxPacket( TransmitData_SendFrame, FRAMELENGTH );	//12ms
}


void InterruptTask_TIM5(void)
{
	OLED_GUI_Task();	//34ms
	LED_FilpForISR( LED1, 25 );
}


void InterruptTask_TIM3(void) 
{
	
}
//不提供TIM7接口
