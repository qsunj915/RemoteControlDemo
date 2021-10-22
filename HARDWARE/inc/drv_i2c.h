/**
  ******************************************************************************
  * @file    drv_i2c.h
  * @author  
  * @date    21-5-21
  * @brief  
  ******************************************************************************
  */

#ifndef __DRV_I2C_H
#define __DRV_I2C_H

#include "stm32f4xx.h"
#include "drv_usart.h"
#include "drv_timer.h"


#define I2C1_SCL_AFPORT GPIO_PinSource8	//B8
#define I2C1_SDA_AFPORT GPIO_PinSource9	//B9
#define I2C1_SCL GPIO_Pin_8	//B8
#define I2C1_SDA GPIO_Pin_9	//B9

#define I2C2_SLAVE_ADDRESS 0x80//用于改变I2C从机地址==> PCA9685

void I2C1_Init(void);

void I2C_WriteByte(I2C_TypeDef * I2Cx, uint8_t addr, uint8_t reg, uint8_t data);
uint8_t I2C_Read(I2C_TypeDef * I2Cx, uint8_t addr, uint8_t reg, uint8_t *data);
void I2C_WriteData(uint8_t addr, uint8_t *data, uint32_t Num);

#endif

