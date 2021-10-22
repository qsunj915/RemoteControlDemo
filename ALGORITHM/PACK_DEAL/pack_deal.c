/**
  ******************************************************************************
  * @file    pack_deal.c
  * @author  qsunj
  * @date    21-5-26
  * @brief  
  ******************************************************************************
  */
#include "pack_deal.h"


/******************���ݸ�ʽ******************
		֡ͷ��0x22
		
�м����ݣ�
		����ֵ��K1-K10��K11-K14��K21-K22
********����ֵ��ֵ���ϲ�������8�ֽ�ֵ�ҵͰ�λ��ǰ**********

		��λ�ƣ�ADC0-ADC7��K21��K22��K23-K26��
				ADC0:R_X, ADC1:R_Y, ADC2:L_X, ADC3:L_Y
********��λ�Ƶ�ֵ���ֽ������8�ֽ�ֵ�ҵͰ�λ��ǰ**********
		
		֡β��0xee
********************************************/
const uint8_t FRAMEHEAD		= '\"';//0x22
const uint8_t FRAMEHEAD_en	= 0xee;

const uint8_t FRAMETAIL_en	= 0xee;
const uint8_t FRAMETAIL		= 0xee;//'\"';//0x22

uint8_t tramsmitdata_buffer_key[ FRAMELENGTH_KEY ]		= {0};//��ֵ�ݴ���
uint16_t transmitData_buffer_float[ FRAMELENGTH_FLOAT ]	= {0};//������ֵ������

uint8_t TransmitData_SendFrame[FRAMELENGTH]		= {0};//�����������ڴ���
uint8_t TransmitData_ReceiveFrame[FRAMELENGTH]	= {0};//�����������ڴ���

/**
  * @brief :��ý���������
  * @param :��ѡ������K1-K14;K23-K26;R_X,R_Y,L_X,L_Y
  * @note  :
  * @retval:��
  */ 
uint16_t Get_NRF_Deal_ReceiveData(TransmitDataLocateNum num) {
	uint16_t returndata=0;
	if ( num < R_X ) {
		Serial_Send(Serial1, "The param of Get_ReceiveData is error!\r\n");
		return 0;
	} else if ( num < K1 ) {
		returndata = TransmitData_ReceiveFrame[num+1];
		returndata |= TransmitData_ReceiveFrame[num+2]<<8;		
	} else if ( num < K9 ) {
		returndata += TransmitData_ReceiveFrame[K_PECK1+1] & (1 << (8-(num-K1)) );
	} else if ( num < K16 ){
		returndata += TransmitData_ReceiveFrame[K_PECK2+1] & (1 << (8-(num-K9)) );
	}
	return returndata;
}




/**
  * @brief :���ݽ���������
  * @param :��
  * @note  :
  * @retval:��
  */ 
void ReceiveData_Task() {
	
}


/**
  * @brief :��ô���������֡ͷ
  * @param :��
  * @note  :
  * @retval:��
  */ 
uint8_t* Get_TransmitData_SendFrame_Address(void) {
//	TransmitData_Pack();
	return TransmitData_SendFrame;
}


/**
  * @brief :���ݴ������
  * @param :��
  * @note  :���������ݴ���� TransmitData_SendFrame(����) ��
  * @retval:��
  */ 
void TransmitData_Pack(void) {
	uint8_t i=0, ex_i=0;
	uint8_t *TransmitData_SendFrame_temppoint = &TransmitData_SendFrame[2-1];
	
	for (i=0, ex_i=0; i<FRAMELENGTH_KEY && ex_i<FRAMELENGTH_KEY_TTL; i++) {
		if ( i%8==0 && i!=0 ) {
			ex_i++;
		}
		
		TransmitData_SendFrame_temppoint[ex_i] <<= 1;
		TransmitData_SendFrame_temppoint[ex_i] |= tramsmitdata_buffer_key[i];
	}
	
	for (i=0; i<FRAMELENGTH_FLOAT; i++) {
		//�Ͱ�λ��ǰ
		TransmitData_SendFrame_temppoint[FRAMELENGTH_KEY_TTL+2*i] = transmitData_buffer_float[i] & 0xff;
		TransmitData_SendFrame_temppoint[FRAMELENGTH_KEY_TTL+2*i+1] = transmitData_buffer_float[i] >> 8;
	}
	
	TransmitData_SendFrame[0]				= FRAMEHEAD;
	TransmitData_SendFrame[FRAMELENGTH-1]	= FRAMETAIL;
}


/**
  * @brief :���ݽ������
  * @param :��
  * @note  :���������ݴ���� TransmitData_RecevieFrame(����) ��
  * @retval:��
  */ 
void TransmitData_UnPack(uint8_t receive_data) {
	static uint8_t transmit_processbit=0;//���̱�־λ:���ڿ�ʼ���ݽ��պͿ��ƽ������ݵ�λ��
	
	//���������������
	if (receive_data==FRAMEHEAD && !transmit_processbit) {
		TransmitData_ReceiveFrame[transmit_processbit] = receive_data;
		transmit_processbit = 1;
	} else if (transmit_processbit>1) {
		TransmitData_ReceiveFrame[transmit_processbit] = receive_data;
		transmit_processbit++;
		if (transmit_processbit==FRAMELENGTH) {
			transmit_processbit = 0;
		}
	} else {
		transmit_processbit = 0;
	}
	
	//����֡���
	if (TransmitData_ReceiveFrame[FRAMELENGTH-1]==FRAMETAIL) {
//		Serial_Send(Serial1, "Receive OK!\r\n");
		ReceiveData_Task();
		TransmitData_ReceiveFrame[FRAMELENGTH-1] = 0x00;
	} else {
		;
	}
}


/**
  * @brief :��ֵ������
  * @param :
  *			data:Ҫ���������
  *			locate:���ݵĲ����ַ
  * @note  :
  * @retval:��
  */ 
void Insert_transmitdata_buffer_key(uint8_t data, uint8_t locate) {
	tramsmitdata_buffer_key[locate] = data;
}


/**
  * @brief :ADCֵ������
  * @param :
  *			data:Ҫ���������
  *			locate:���ݵĲ����ַ
  * @note  :
  * @retval:��
  */ 
void Insert_transmitdata_buffer_float(uint16_t data, uint8_t locate) {
	transmitData_buffer_float[locate] = data;
}

