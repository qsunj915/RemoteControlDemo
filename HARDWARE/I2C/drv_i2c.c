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
  * @brief :I2C1初始化
  * @param :无
  * @note  :暂时只能用I2C2;注意开漏(OD)和不拉(NOPULL)
  * @retval:无
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
	I2C_InitStructure.I2C_ClockSpeed          = 400000;			//SCL最大400KHZ
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Cmd(I2C1 ,ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	
//	I2C1->CR1 |= 0x80;//禁止时钟延长
	
	Serial_Send(Serial1,"I2C1,Init OK!\r\n");
}

/**
  * @brief :I2C写入
  * @param :
  *			I2Cx:使用的I2C口
  *			addr:要写入的寄存器地址
  *			data:要写入的数据（单个字节）
  * @note  :不稳定，有时会出现原因不明的while卡死;已内置超时退出报错
  * @retval:无
  */ 
void I2C_WriteByte(I2C_TypeDef * I2Cx, uint8_t addr, uint8_t reg, uint8_t data)
{
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
		
	I2C_GenerateSTART(I2Cx, ENABLE);//开启I2C2
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/

	I2C_Send7bitAddress(I2Cx, addr, I2C_Direction_Transmitter);//器件地址
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2Cx, reg);//寄存器地址
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2Cx, data);//发送数据
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2Cx, ENABLE);//关闭I2C1总线
}

/**
  * @brief :I2C读出
  * @param :
  *			@addr:要读出的寄存器地址
  *			@data:接收读出的数据
	* @note  :默认I2C2串口
  * @retval:无
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
	I2C_GenerateSTART(I2Cx, ENABLE);//开启I2C2
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))//EV5,主模式
		if(time++ == TIMEOUT) 
		{	flag=1;
			break;
		}
	time=0;
	

	//设备地址--写
	I2C_Send7bitAddress(I2Cx, addr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
	
	I2C_SendData(I2Cx, reg);//寄存器地址(要读的地址)
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

	
	//设备地址--读
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
  * @brief :I2C连续写入
  * @param :
  *			@addr:要写入的寄存器地址
  *			@data:要写入的数据指针
  *			@Num:要写入的数据的长度
  * @note  :无
  * @retval:无
  */ 
void I2C_WriteData(uint8_t addr, uint8_t *data, uint32_t Num)
{
  while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C2, ENABLE);//开启I2C2
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/

	I2C_Send7bitAddress(I2C2, I2C2_SLAVE_ADDRESS, I2C_Direction_Transmitter);//器件地址(七位--最后一位是w/r标志位)
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C2, addr);//寄存器地址
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	while(Num--)
	{
		I2C_SendData(I2C2, *data);//发送数据
		while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		data++;
	}
	
	I2C_GenerateSTOP(I2C2, ENABLE);//关闭I2C1总线
}

