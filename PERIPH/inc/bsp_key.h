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

/* 0~15λΪ������ֵ��Ϊ0/1,����ΪΪ0 */

#include "stm32f4xx.h"
#include "stdio.h"

#define GPIO_KEY_NUM           16    //���尴������
#define KEY_MAX_NUMBER         16    //���尴�������
#define KEY_TIMER_MS           1
#define SCAN_TIME              1
/*----------------------------------
             �Զ�������
----------------------------------*/
__packed typedef struct
{
	uint8_t            keyNum;         //�������
	uint32_t           keyRccPeriph;   //����ʱ��
	GPIO_TypeDef       *keyPort;       //�������ڶ˿�
	uint32_t           keyGpio;        //�������ڵ�IO��
}keyTypedef_t;

__packed typedef struct
{
	uint8_t      keyTotolNum;          //��������
	keyTypedef_t *pSingleKey;          //��ָ�뵥�������Ľṹ����
}keysTypedef_t;

/*----------------------------------
             ����
----------------------------------*/
extern keysTypedef_t    keys;
extern uint8_t          KEY_G[16];


/*----------------------------------
             ����
----------------------------------*/
/* ����ɨ�躯�� */
void keyHandle(keysTypedef_t *pkeyS);

/* ������ʼ�� */
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
