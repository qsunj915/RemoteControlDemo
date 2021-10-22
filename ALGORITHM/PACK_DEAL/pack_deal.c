/**
  ******************************************************************************
  * @file    pack_deal.c
  * @author  qsunj
  * @date    21-5-26
  * @brief  
  ******************************************************************************
  */
#include "pack_deal.h"


/******************数据格式******************
		帧头：0x22
		
中间数据：
		按键值：K1-K10，K11-K14，K21-K22
********按键值的值被合并成两个8字节值且低八位在前**********

		电位计：ADC0-ADC7（K21，K22，K23-K26）
				ADC0:R_X, ADC1:R_Y, ADC2:L_X, ADC3:L_Y
********电位计的值被分解成两个8字节值且低八位在前**********
		
		帧尾：0xee
********************************************/
const uint8_t FRAMEHEAD		= '\"';//0x22
const uint8_t FRAMEHEAD_en	= 0xee;

const uint8_t FRAMETAIL_en	= 0xee;
const uint8_t FRAMETAIL		= 0xee;//'\"';//0x22

uint8_t tramsmitdata_buffer_key[ FRAMELENGTH_KEY ]		= {0};//键值暂存区
uint16_t transmitData_buffer_float[ FRAMELENGTH_FLOAT ]	= {0};//浮点数值缓冲区

uint8_t TransmitData_SendFrame[FRAMELENGTH]		= {0};//打包后的数据内存区
uint8_t TransmitData_ReceiveFrame[FRAMELENGTH]	= {0};//解包后的数据内存区

/**
  * @brief :获得解包后的数据
  * @param :可选参数：K1-K14;K23-K26;R_X,R_Y,L_X,L_Y
  * @note  :
  * @retval:无
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
  * @brief :数据解包后的任务
  * @param :无
  * @note  :
  * @retval:无
  */ 
void ReceiveData_Task() {
	
}


/**
  * @brief :获得打包后的数据帧头
  * @param :无
  * @note  :
  * @retval:无
  */ 
uint8_t* Get_TransmitData_SendFrame_Address(void) {
//	TransmitData_Pack();
	return TransmitData_SendFrame;
}


/**
  * @brief :数据打包函数
  * @param :无
  * @note  :打包后的数据存放在 TransmitData_SendFrame(数组) 中
  * @retval:无
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
		//低八位在前
		TransmitData_SendFrame_temppoint[FRAMELENGTH_KEY_TTL+2*i] = transmitData_buffer_float[i] & 0xff;
		TransmitData_SendFrame_temppoint[FRAMELENGTH_KEY_TTL+2*i+1] = transmitData_buffer_float[i] >> 8;
	}
	
	TransmitData_SendFrame[0]				= FRAMEHEAD;
	TransmitData_SendFrame[FRAMELENGTH-1]	= FRAMETAIL;
}


/**
  * @brief :数据解包函数
  * @param :无
  * @note  :解包后的数据存放在 TransmitData_RecevieFrame(数组) 中
  * @retval:无
  */ 
void TransmitData_UnPack(uint8_t receive_data) {
	static uint8_t transmit_processbit=0;//过程标志位:用于开始数据接收和控制接收数据的位置
	
	//接收数据主体程序
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
	
	//数据帧检查
	if (TransmitData_ReceiveFrame[FRAMELENGTH-1]==FRAMETAIL) {
//		Serial_Send(Serial1, "Receive OK!\r\n");
		ReceiveData_Task();
		TransmitData_ReceiveFrame[FRAMELENGTH-1] = 0x00;
	} else {
		;
	}
}


/**
  * @brief :键值的输入
  * @param :
  *			data:要输入的数据
  *			locate:数据的插入地址
  * @note  :
  * @retval:无
  */ 
void Insert_transmitdata_buffer_key(uint8_t data, uint8_t locate) {
	tramsmitdata_buffer_key[locate] = data;
}


/**
  * @brief :ADC值的输入
  * @param :
  *			data:要输入的数据
  *			locate:数据的插入地址
  * @note  :
  * @retval:无
  */ 
void Insert_transmitdata_buffer_float(uint16_t data, uint8_t locate) {
	transmitData_buffer_float[locate] = data;
}

