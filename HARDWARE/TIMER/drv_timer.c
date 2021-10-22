/**
  ******************************************************************************
  * @file    drv_timer.c
  * @author  qsunj
  * @date    21-5-25
  * @brief  
  ******************************************************************************
  */
#include "drv_timer.h"

uint16_t	G_delaytime_count = 0;
uint8_t		G_TIM7_status = 0;		//0Ϊ�رգ�1Ϊ����

/**
  * @brief  TIM2��ʼ��
  * @param  arr�Զ���װ��ֵ
  *			pscԤ��Ƶֵ
  * @note	����ֵ�ο���8399,9--1ms
  * @retval 
  */
void TIM2_Init(uint16_t arr, uint16_t psc) {
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //��ʱ��2ʱ��ʹ��

	//��ʱ��2��ʼ��
	TIM_TimeBaseStructure.TIM_Period		= arr;					//��������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler		= psc;					//���÷�Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision	= TIM_CKD_DIV1;			//���÷�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;	//��������ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             	//���ṹ�������ڳ�ʼ����ʱ��2

	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE );           //ʹ�ܶ�ʱ��2�����ж�

	//�����жϲ���
	NVIC_InitStructure.NVIC_IRQChannel						= TIM2_IRQn;            		//��ʱ��2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= TIMER2_PreemptionPriority;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= TIMER2_SubPriority;			//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;						//ʹ���ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//��ʼ���ж�
	TIM_Cmd(TIM2, ENABLE);//ʹ�ܶ�ʱ��
}

void TIM3_Init(uint16_t arr, uint16_t psc) {
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //��ʱ��3ʱ��ʹ��

	//��ʱ��2��ʼ��
	TIM_TimeBaseStructure.TIM_Period		= arr;					//��������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler		= psc;					//���÷�Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision	= TIM_CKD_DIV1;			//���÷�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;	//��������ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             	//���ṹ�������ڳ�ʼ����ʱ��2

	TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE );           //ʹ�ܶ�ʱ��2�����ж�

	//�����жϲ���
	NVIC_InitStructure.NVIC_IRQChannel						= TIM3_IRQn;            		//��ʱ��3�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= TIMER3_PreemptionPriority;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= TIMER3_SubPriority;			//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;						//ʹ���ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//��ʼ���ж�
	TIM_Cmd(TIM3, ENABLE);//ʹ�ܶ�ʱ��
}

void TIM5_Init(uint16_t arr, uint16_t psc) {
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //��ʱ��5ʱ��ʹ��

	//��ʱ��2��ʼ��
	TIM_TimeBaseStructure.TIM_Period		= arr;					//��������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler		= psc;					//���÷�Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision	= TIM_CKD_DIV1;			//���÷�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;	//��������ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);             	//���ṹ�������ڳ�ʼ����ʱ��2

	TIM_ITConfig(TIM5, TIM_IT_Update,ENABLE );           //ʹ�ܶ�ʱ��5�����ж�

	//�����жϲ���
	NVIC_InitStructure.NVIC_IRQChannel						= TIM5_IRQn;            		//��ʱ��5�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= TIMER5_PreemptionPriority;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= TIMER5_SubPriority;			//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;						//ʹ���ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//��ʼ���ж�
	TIM_Cmd(TIM5, ENABLE);//ʹ�ܶ�ʱ��
}



/**
  * @brief  TIM7��ʱ���ܶ�ʱ����ʼ��
  * @param  time--��ʱʱ��ms
  * @note	
  * @retval 
  */
void TIM7_DelayFunction_ms_Init(void) {
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //��ʱ��7ʱ��ʹ��

	//��ʱ��2��ʼ��
	TIM_TimeBaseStructure.TIM_Period		= 8399;					//��������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler		= 9;					//���÷�Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision	= TIM_CKD_DIV1;			//���÷�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;	//��������ģʽ
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);             	//���ṹ�������ڳ�ʼ����ʱ��2

	TIM_ITConfig(TIM7, TIM_IT_Update,ENABLE );           //ʹ�ܶ�ʱ��7�����ж�

	//�����жϲ���
	NVIC_InitStructure.NVIC_IRQChannel						= TIM7_IRQn;            		//��ʱ��7�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= TIMER7_PreemptionPriority;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= TIMER7_SubPriority;			//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;						//ʹ���ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//��ʼ���ж�
	TIM_Cmd(TIM7, DISABLE);//ʧ�ܶ�ʱ��
}

/**
  * @brief  TIM7��ʱ����
  * @param  ״̬��ʾֵ 1��0
  * @note	���ڴ�ӡ������Ϣ˵�������˶����ʱ���ļ�ʱ��ֻ�ܿ���һ����ʱ��
  * @retval ״ֵ̬ 0Ϊ��ʼ��1Ϊ����
  */
void TIM7_Runtimetest_Scheduler(const uint8_t comm) {
	static uint8_t flag = 0;
	if (flag == 0) {
		flag++;
		TIM7_Delay_Start();
	} else {
		TIM7_DelayCount_End();
		flag = 0;
		Serial_Send(Serial1, "Code Run time:%dms==>", G_delaytime_count);
	}
	
	if ( comm == flag ) {
		Serial_Send(Serial_Error, "Funtion **TIM7_Runtimetest_Scheduler** Error==>!");
	}
}

/**
  * @brief  TIM7��ʱ����
  * @param  time--��ʱʱ��ms
  * @note	
  * @retval 
  */
void TIM7_Delay_ms(const uint16_t time) {
	if ( !TIM7_Delay_Start() ) return;
	while (G_delaytime_count<time);
	TIM7_DelayCount_End();
}


uint16_t Get_TIM7_CountTime(void) {
	return G_delaytime_count;
}

uint8_t TIM7_Delay_Start(void) {
	TIM_Cmd(TIM7, ENABLE);//ʹ�ܶ�ʱ��
	if ( !G_TIM7_status ) {
		G_TIM7_status = 1;
	} else {
		TIM7_ERRTask();
		return 0;
	}
	G_delaytime_count = 0;
	return 1;
}

void TIM7_DelayCount_Run(void) {
	G_delaytime_count++;
}

void TIM7_DelayCount_End(void) {
	TIM_Cmd(TIM7, DISABLE);//ʧ�ܶ�ʱ��
	if ( G_TIM7_status ) {
		G_TIM7_status = 0;
	} else {
		Serial_Send(Serial_Error, "Function **TIM7_DelayCount_End** is NOT safe!\r\n");
		return;
	}

}

void TIM7_ERRTask(void)
{
	Serial_Send(Serial_Error, "Function **TIM7_Delay_Start** Corrupt!\r\n");
}

