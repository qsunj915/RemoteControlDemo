/**
  ******************************************************************************
  * @file    bsp_key.h
  * @author  
  * @version v1.0
  * @date    21-10-21
  * @brief   
  ******************************************************************************
  */
#ifndef __KEY_H
#define __KEY_H

/* 0~15位为按键键值分为0/1,其他为为0 */

#include "stm32f4xx.h"
#include "stdio.h"

#define GPIO_KEY_NUM           16    //定义按键总数
#define KEY_MAX_NUMBER         16    //定义按键最大数
#define KEY_TIMER_MS           1
#define SCAN_TIME              1
/*----------------------------------
             自定义类型
----------------------------------*/
__packed typedef struct
{
	uint8_t            keyNum;         //按键编号
	uint32_t           keyRccPeriph;   //按键时钟
	GPIO_TypeDef       *keyPort;       //按键所在端口
	uint32_t           keyGpio;        //按键所在的IO口
}keyTypedef_t;

__packed typedef struct
{
	uint8_t      keyTotolNum;          //按键总数
	keyTypedef_t *pSingleKey;          //该指针单个按键的结构参数
}keysTypedef_t;

/*----------------------------------
             变量
----------------------------------*/
extern keysTypedef_t    keys;
extern uint8_t          KEY_G[16];


/*----------------------------------
             函数
----------------------------------*/
/* 按键扫描函数 */
void keyHandle(keysTypedef_t *pkeyS);

/* 按键初始化 */
void Key_Init(void);
keyTypedef_t keyInitOne(uint32_t keyRccPeriph,
                        GPIO_TypeDef * keyPort, 
                        uint32_t keyGpio);
void keyParaInit(keysTypedef_t *pkeys);


uint32_t getKey(keysTypedef_t *keyS);
uint32_t readKeyValue(keysTypedef_t *keyS);
void G_SET_BIT(uint32_t *readKey, uint8_t keyNum);
void G_RESET_BIT(uint32_t *readKey, uint8_t keyNum);

void Key_Set(uint32_t keyvalue);
#endif
