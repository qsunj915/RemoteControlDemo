/**
  ******************************************************************************
  * @file    pack_deal.h
  * @author  qsunj
  * @date    21-5-26
  * @brief  
  ******************************************************************************
  */
#ifndef __PACK_DEAL_H
#define __PACK_DEAL_H
#include "stm32f4xx.h"
#include "init.h"

#define FRAMELENGTH_KEY 16	//���ݳ���key
#define FRAMELENGTH_KEY_TTL ( FRAMELENGTH_KEY / 8 )	//���ݳ���key���Ϻ󳤶�
#define FRAMELENGTH_FLOAT 8	//���ݳ���adc
#define DATALOCATEFEX 1//����λ������(У��λ����)

#define FRAMELENGTH (2+8*2+2)	//���ݳ���=key+adc*2+2
//ע�����ݳ��Ȳ��ܳ���32


/**********************************************************************
	********����֡�о���ֵ�Ķ�����get���������������ﲻ���ı�****
***********************************************************************/
typedef enum TransmitDataLocateNum {
	K_PECK1 = 0x0,
	K_PECK2 = 0x1,
	
	R_X = 2,
	R_Y = 4,
	
	L_X = 6,
	L_Y = 8,
	
	K23 = 10,
	K24 = 12,
	K25 = 14,
	K26 = 16,
	
	K1 = 20,
	K2 = 21,
	K3,
	K4,
	K5,
	K6,
	K7,
	K8,
	K9,
	K10,
	K11,
	K12,
	K13,
	K14,
	K15,
	K16,
	
	K21,
	K22,
}TransmitDataLocateNum;

uint8_t* Get_TransmitData_SendFrame_Address(void);
void TransmitData_Pack(void);
void Insert_transmitdata_buffer_key(uint8_t data, uint8_t locate);
void Insert_transmitdata_buffer_float(uint16_t data, uint8_t locate);
void TransmitData_Pack(void);
void TransmitData_UnPack(uint8_t receive_data);

void ReceiveData_Task(void);
uint16_t Get_NRF_Deal_ReceiveData(TransmitDataLocateNum num);

extern uint8_t TransmitData_SendFrame[FRAMELENGTH];

#endif

