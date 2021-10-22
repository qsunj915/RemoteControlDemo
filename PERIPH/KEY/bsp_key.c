/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  
  * @version v1.0
  * @date    21-10-21
  * @brief   
  ******************************************************************************
  */
	
#include "bsp_key.h"

keysTypedef_t    keys;
keyTypedef_t     singleKey[GPIO_KEY_NUM];
uint8_t          KEY_G[16] = {0};

static uint8_t	 keyTotolNum = 0;        //����ͳ���ж��ٸ�����

/**
* @brief key init function   ������ʼ������
* @param [in] keyRccPeriph ��������Ӧ������ʱ��
* @param [in] keyPort��      IO�˿�
* @param [in] keyGpio��      IO�ܽ�
* @param [in] press :  �����ص�����
* @return key structure?pointer
*/
keyTypedef_t keyInitOne(uint32_t keyRccPeriph,
                        GPIO_TypeDef * keyPort, 
                        uint32_t keyGpio)
{
	static uint8_t key_total = 0; 

	keyTypedef_t singleKey;                 //�ṹ����������ڱ��水��IO�Ĳ���

	//ƽ̨����IO��
	singleKey.keyRccPeriph = keyRccPeriph;  //���水��IO�����ڵ�����ʱ������
	singleKey.keyPort      = keyPort;       //���水�����ڵĶ˿�
	singleKey.keyGpio      = keyGpio;       //���水�����ڵ�IO��
	singleKey.keyNum       = key_total++;   //����ÿ���������е����ı��
	
	keyTotolNum++;      //ȫ�־�̬������ͳ���ж��ٸ�����

	return singleKey;   //���س�ʼ���İ���IO�Ĳ����Ľṹ�����
}


/**
* ������ʼ������
* @param none
* @return none
*/
void Key_Init(void)
{
    /*�������˿ڲ������浽singleKey�ṹ�������У�
    ��������������˿ڡ�IO�˿ڡ�IO�ܽš�����ָ��*/
	singleKey[0] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_0); 
	singleKey[1] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_1);
	
	singleKey[2] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_2);
	singleKey[3] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_3);
	
	singleKey[4] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_4);
	singleKey[5] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_5);
	singleKey[6] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_6);
	singleKey[7] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_7);
														
	singleKey[8] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_8);
	singleKey[9] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_9);
	singleKey[10] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_12);
	singleKey[11] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_13);
		
	singleKey[12] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_14);
	singleKey[13] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_15);
														
	singleKey[14] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_10);
	singleKey[15] = keyInitOne(RCC_AHB1Periph_GPIOD, 
                            GPIOD, GPIO_Pin_11);
		/************************************************/
	keys.pSingleKey = (keyTypedef_t *)&singleKey; //pSingKeyָ��ָ��singleKey����
	keyParaInit(&keys);                           //��ʼ���������ڵ�IO�ڲ���ʼ����ʱ��
}

/*
 *@brief ����������ʼ����GPIO��ʼ������������ʱ������ⰴ��״̬
 *@param [in] pkeys:����ȫ�ֱ����ṹ�� �ں����а�������
 *@return none
*/
void keyParaInit(keysTypedef_t *pkeys)
{
	uint8_t i = 0;//�жϴ����ָ���Ƿ���ָ��
	
	if(NULL == pkeys) 
	{
		return;//���û��ָ����ֱ�ӷ��أ�������ִ��
	}
	
	pkeys -> keyTotolNum = keyTotolNum; //��ȡ��������
  /*����жϣ��������16������������ͨ���޸ĺ�KEY_MAX_NUMBER��ʵ��֧�ָ���İ���*/
	if( pkeys->keyTotolNum > KEY_MAX_NUMBER )
	{
		 pkeys->keyTotolNum = KEY_MAX_NUMBER;
	}

	for(i = 0; i < pkeys->keyTotolNum; i++)   //ȡ�����еİ����Ĳ��������õ����±�ƫ�Ʒ�
	{
		GPIO_InitTypeDef GPIO_InitStructure;  //����ṹ�壬���ڳ�ʼ��IO����
        //ȡ��ĳ����������˿�ʱ�ӣ���ʹ����ʱ��
		RCC_AHB1PeriphClockCmd(pkeys->pSingleKey[i].keyRccPeriph, ENABLE);  
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  //ʹ��IO���ٶ�
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;      //ʹ��IO�ڵ�ģʽ������ģʽ
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Pin   = pkeys -> pSingleKey[i].keyGpio;//ȡ��ĳ�����Ĺܽű��
		GPIO_Init(pkeys ->pSingleKey[i].keyPort,&GPIO_InitStructure);//ȡ��ĳ�����Ķ˿ںţ����а�����ʼ��
	}
}

/**
* @brief ��ȡ������״̬���������¶��ǵ͵�ƽ
* @param keys : ����ȫ�ֽṹ��ָ��Key
* @return ������״̬
*/
uint32_t getKey(keysTypedef_t *keyS)
{
	uint8_t  i = 0;
	uint32_t readKey = 0; //ʹ��һ��32λ�ı�����������16��������״ֵ̬,����������£�λ��1

	for(i = 0; i < keys.keyTotolNum; i++)  //ͨ��ѭ������ȡ���еİ���ֵ
	{
		if(!GPIO_ReadInputDataBit(
                         (GPIO_TypeDef*)keyS->pSingleKey[i].keyPort,
                         keyS->pSingleKey[i].keyGpio)
                              )
		{
			 G_SET_BIT(&readKey, keyS->pSingleKey[i].keyNum);  //��λ   
		}
		else
		{
			 G_RESET_BIT(&readKey, keyS->pSingleKey[i].keyNum);  //ȡ����λ   			
		}
	}
	return readKey;
}

/**
* @brief Read the KEY value ��ȡ���а����İ���ֵ
* @param [in] keys :Key global structure pointer
* @return GPIO status
*/
uint32_t readKeyValue(keysTypedef_t *keyS)
{
	static uint8_t keyCountTime     = 0;
	uint32_t newKeyValue			= 0;
	keyCountTime ++;		//ÿ����һ�μ�1
	
	if(keyCountTime >= (SCAN_TIME / KEY_TIMER_MS))     //�����������Ϊ�˽���n��ɨ��һ�ΰ������ı���ֵ����ʵ�������ư���ɨ��Ƶ��
	{
		keyCountTime = 0;
		newKeyValue = getKey(keyS); //��ȡ������ֵ������Ҫ����λ���жϲ��ܻ�֪���µİ������ĸ�
	}
	return newKeyValue;
}

/**
* @brief ��ⰴ��
* @param [in] keys : ȫ�ְ��������ṹ��
* @return none
*/
void keyHandle(keysTypedef_t *pkeyS)    //��ʱ������
{
	Key_Set( readKeyValue(pkeyS) );
}

/**
* @brief ��readKey�ĵ�keyNumλ��1
* @param [in] keyNum :�������
							readKey:ԭʼ��������
* @return ��λ��ɵ�readKey
*/
void G_SET_BIT(uint32_t *readKey, uint8_t keyNum)   
{
	*readKey = *readKey | (0x0001<<keyNum);
	
}
				
/**
* @brief ��readKey�ĵ�keyNumλ��0
* @param [in] keyNum :�������
							readKey:ԭʼ��������
* @return ��λ��ɵ�readKey
*/
void G_RESET_BIT(uint32_t *readKey, uint8_t keyNum)   
{				
	*readKey = *readKey & ((0xfffe<<keyNum)|(0xffff>>(16-keyNum)));
}

/**
* ��ֵ����
* @param  keyvalue
* @return 
* ��⵽�������¼�¼ ���������
*/
void Key_Set( uint32_t keyvalue )
{
	uint8_t i=0;
	for ( i=0; i<keyTotolNum; i++ ) {
		KEY_G[i] = keyvalue&(0x0001 << i) ? 1: 0;
	}
}
