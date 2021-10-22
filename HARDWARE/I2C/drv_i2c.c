/**
  ******************************************************************************
  * @file    drv_i2c.c
  * @author  
  * @date    21-5-21
  * @brief  
  ******************************************************************************
  */

#include "drv_i2c.h"

//#define __I2C_DELAYMODE
#define TIMEOUT 1000

/**
  * @brief :I2C1��ʼ��
  * @param :��
  * @note  :��ʱֻ����I2C2;ע�⿪©(OD)�Ͳ���(NOPULL)
  * @retval:��
  */ 
void I2C1_Init()
{
	I2C_InitTypeDef I2C_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1 ,ENABLE);
	GPIO_Format_Init(GPIOB,I2C1_SCL|I2C1_SDA,GPIO_Mode_AF,GPIO_OType_OD,GPIO_PuPd_NOPULL,GPIO_Speed_50MHz);

	GPIO_PinAFConfig(GPIOB ,I2C1_SCL_AFPORT ,GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB ,I2C1_SDA_AFPORT ,GPIO_AF_I2C1);
	
	I2C_InitStructure.I2C_Mode                = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle           = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1         = 0x30;
	I2C_InitStructure.I2C_Ack                 = I2C_Ack_Enable;
	I2C_InitStructure.I2C_ClockSpeed          = 400000;			//SCL���400KHZ
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Cmd(I2C1 ,ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	
//	I2C1->CR1 |= 0x80;//��ֹʱ���ӳ�
	
	Serial_Send(Serial1,"I2C1,Init OK!\r\n");
}

/**
  * @brief :I2Cд��
  * @param :
  *			I2Cx:ʹ�õ�I2C��
  *			addr:Ҫд��ļĴ�����ַ
  *			data:Ҫд������ݣ������ֽڣ�
  * @note  :���ȶ�����ʱ�����ԭ������while����;�����ó�ʱ�˳�����
  * @retval:��
  */ 
void I2C_WriteByte(I2C_TypeDef * I2Cx, uint8_t addr, uint8_t reg, uint8_t data)
{
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
		
	I2C_GenerateSTART(I2Cx, ENABLE);//����I2C2
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,��ģʽ*/

	I2C_Send7bitAddress(I2Cx, addr, I2C_Direction_Transmitter);//������ַ
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2Cx, reg);//�Ĵ�����ַ
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2Cx, data);//��������
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2Cx, ENABLE);//�ر�I2C1����
}

/**
  * @brief :I2C����
  * @param :
  *			@addr:Ҫ�����ļĴ�����ַ
  *			@data:���ն���������
	* @note  :Ĭ��I2C2����
  * @retval:��
 */ 
uint8_t I2C_Read(I2C_TypeDef * I2Cx, uint8_t addr, uint8_t reg, uint8_t *data)
{
	int time=0,flag=0;
	
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY)){
		if(time++ == TIMEOUT) 
		{	flag=1;
			break;
		}
	}
	time=0;
	
  I2C_AcknowledgeConfig(I2Cx, ENABLE);
	I2C_GenerateSTART(I2Cx, ENABLE);//����I2C2
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))//EV5,��ģʽ
		if(time++ == TIMEOUT) 
		{	flag=1;
			break;
		}
	time=0;
	

	//�豸��ַ--д
	I2C_Send7bitAddress(I2Cx, addr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
	
	I2C_SendData(I2Cx, reg);//�Ĵ�����ַ(Ҫ���ĵ�ַ)
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		if(time++ == TIMEOUT) 
		{	flag=1;
			break;
		}
	time=0;

	
	
	I2C_GenerateSTART(I2Cx, ENABLE);
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
		if(time++ == TIMEOUT) 
		{	flag=1;
			break;
		}
	time=0;

	
	//�豸��ַ--��
	I2C_Send7bitAddress(I2Cx, addr, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
		if(time++ == TIMEOUT) 
		{	flag=1;
			break;
		}
	time=0;

	
	
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	I2C_GenerateSTOP(I2Cx, ENABLE);
	
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))  /* EV7 */
		if(time++ == TIMEOUT) 
		{	flag=1;
			break;
		}
	time=0;
	
	
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	*data = I2C_ReceiveData(I2Cx);
	
	if(flag==1)	Serial_Send(Serial1, "ERROR, The function I2C_Read() is TIMEOUT!\r\n");
	return 0;
}


/**
  * @brief :I2C����д��
  * @param :
  *			@addr:Ҫд��ļĴ�����ַ
  *			@data:Ҫд�������ָ��
  *			@Num:Ҫд������ݵĳ���
  * @note  :��
  * @retval:��
  */ 
void I2C_WriteData(uint8_t addr, uint8_t *data, uint32_t Num)
{
  while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C2, ENABLE);//����I2C2
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,��ģʽ*/

	I2C_Send7bitAddress(I2C2, I2C2_SLAVE_ADDRESS, I2C_Direction_Transmitter);//������ַ(��λ--���һλ��w/r��־λ)
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C2, addr);//�Ĵ�����ַ
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	while(Num--)
	{
		I2C_SendData(I2C2, *data);//��������
		while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		data++;
	}
	
	I2C_GenerateSTOP(I2C2, ENABLE);//�ر�I2C1����
}

