/**
  ******************************************************************************
  * @file   
  * @author  xjc
  * @version v1.0
  * @date    
  * @brief   
  ******************************************************************************
  */
#include "init.h"

void System_Init(void)
{
	SystemInit();
	SysTick_Init();
	NVIC_Priority_Init();
	
	USART1_Init(115200);
	Serial_Send(Serial1, "Serial1 init OK!\r\n");
	
	TIM7_DelayFunction_ms_Init();		//1ms--ר��������ʱ

	LED_Init();
	Serial_Send(Serial1, "LED init OK!\r\n");
	Key_Init();
	Serial_Send(Serial1, "KEY init OK!\r\n");
	GUI_Init();
	Serial_Send(Serial1, "GUI init OK!\r\n");
	ADC_DMA_Config();
	Serial_Send(Serial1, "ADC1 init OK!\r\n"); 
	
	NRF24L01_Gpio_Init();
	//���nRF24L01
	NRF24L01_check();
	RF24L01_Init();
	Serial_Send(Serial1, "NRF Ready!\r\n");
	
	GPIO_ResetBits(GPIOC,LED0);//������--nrf��ʼ������
	
	TIM2_Init(8399, 299);	//30ms,ר����ͨ��
	//TIM3_Init(8399, 99);	//10ms
	TIM5_Init(8399, 399);	//40ms
	Serial_Send(Serial1, "TIM init OK!\r\n");

	RF24L01_Set_Mode( MODE_TX );		//����ģʽ
	
	Serial_Send(Serial1, "All of init is OK!\r\n");
}

