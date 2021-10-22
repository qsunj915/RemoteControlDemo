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

static uint8_t	 keyTotolNum = 0;        //有与统计有多少个按键

/**
* @brief key init function   按键初始化函数
* @param [in] keyRccPeriph ：按键对应的外设时钟
* @param [in] keyPort：      IO端口
* @param [in] keyGpio：      IO管脚
* @param [in] press :  按键回调函数
* @return key structure?pointer
*/
keyTypedef_t keyInitOne(uint32_t keyRccPeriph,
                        GPIO_TypeDef * keyPort, 
                        uint32_t keyGpio)
{
	static uint8_t key_total = 0; 

	keyTypedef_t singleKey;                 //结构体变量，用于保存按键IO的参数

	//平台定义IO口
	singleKey.keyRccPeriph = keyRccPeriph;  //保存按键IO口所在的外设时钟总线
	singleKey.keyPort      = keyPort;       //保存按键所在的端口
	singleKey.keyGpio      = keyGpio;       //保存按键所在的IO口
	singleKey.keyNum       = key_total++;   //保存每个按键都有单独的编号
	
	keyTotolNum++;      //全局静态变量，统计有多少个按键

	return singleKey;   //返回初始化的按键IO的参数的结构体变量
}


/**
* 按键初始化函数
* @param none
* @return none
*/
void Key_Init(void)
{
    /*将按键端口参数保存到singleKey结构体数组中，
    参数包括：外设端口、IO端口、IO管脚、函数指针*/
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
	keys.pSingleKey = (keyTypedef_t *)&singleKey; //pSingKey指针指向singleKey数组
	keyParaInit(&keys);                           //初始化按键所在的IO口并初始化定时器
}

/*
 *@brief 按键参数初始化：GPIO初始化，并启动定时器来检测按键状态
 *@param [in] pkeys:按键全局变量结构体 内含所有按键参数
 *@return none
*/
void keyParaInit(keysTypedef_t *pkeys)
{
	uint8_t i = 0;//判断传入的指针是否有指向
	
	if(NULL == pkeys) 
	{
		return;//如果没有指向，则直接返回，不往下执行
	}
	
	pkeys -> keyTotolNum = keyTotolNum; //获取按键总数
  /*误差判断，限制最多16个按键，可以通过修改宏KEY_MAX_NUMBER来实现支持更多的按键*/
	if( pkeys->keyTotolNum > KEY_MAX_NUMBER )
	{
		 pkeys->keyTotolNum = KEY_MAX_NUMBER;
	}

	for(i = 0; i < pkeys->keyTotolNum; i++)   //取出所有的按键的参数，采用的是下标偏移法
	{
		GPIO_InitTypeDef GPIO_InitStructure;  //定义结构体，用于初始化IO参数
        //取出某按键的外设端口时钟，并使能其时钟
		RCC_AHB1PeriphClockCmd(pkeys->pSingleKey[i].keyRccPeriph, ENABLE);  
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  //使能IO口速度
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;      //使能IO口的模式：上拉模式
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Pin   = pkeys -> pSingleKey[i].keyGpio;//取出某按键的管脚编号
		GPIO_Init(pkeys ->pSingleKey[i].keyPort,&GPIO_InitStructure);//取出某按键的端口号，进行按键初始化
	}
}

/**
* @brief 读取按键的状态，按键按下都是低电平
* @param keys : 按键全局结构体指针Key
* @return 按键的状态
*/
uint32_t getKey(keysTypedef_t *keyS)
{
	uint8_t  i = 0;
	uint32_t readKey = 0; //使用一个32位的变量用来保存16个按键的状态值,如果按键按下，位置1

	for(i = 0; i < keys.keyTotolNum; i++)  //通过循环来读取所有的按键值
	{
		if(!GPIO_ReadInputDataBit(
                         (GPIO_TypeDef*)keyS->pSingleKey[i].keyPort,
                         keyS->pSingleKey[i].keyGpio)
                              )
		{
			 G_SET_BIT(&readKey, keyS->pSingleKey[i].keyNum);  //置位   
		}
		else
		{
			 G_RESET_BIT(&readKey, keyS->pSingleKey[i].keyNum);  //取消置位   			
		}
	}
	return readKey;
}

/**
* @brief Read the KEY value 读取所有按键的按键值
* @param [in] keys :Key global structure pointer
* @return GPIO status
*/
uint32_t readKeyValue(keysTypedef_t *keyS)
{
	static uint8_t keyCountTime     = 0;
	uint32_t newKeyValue			= 0;
	keyCountTime ++;		//每进入一次加1
	
	if(keyCountTime >= (SCAN_TIME / KEY_TIMER_MS))     //该条件语句是为了进入n次扫描一次按键，改变宏的值可以实现灵活控制按键扫描频率
	{
		keyCountTime = 0;
		newKeyValue = getKey(keyS); //读取按键的值，还需要进行位域判断才能获知按下的按键是哪个
	}
	return newKeyValue;
}

/**
* @brief 检测按键
* @param [in] keys : 全局按键参数结构体
* @return none
*/
void keyHandle(keysTypedef_t *pkeyS)    //定时处理函数
{
	Key_Set( readKeyValue(pkeyS) );
}

/**
* @brief 给readKey的第keyNum位置1
* @param [in] keyNum :按键序号
							readKey:原始输入数据
* @return 置位完成的readKey
*/
void G_SET_BIT(uint32_t *readKey, uint8_t keyNum)   
{
	*readKey = *readKey | (0x0001<<keyNum);
	
}
				
/**
* @brief 给readKey的第keyNum位置0
* @param [in] keyNum :按键序号
							readKey:原始输入数据
* @return 置位完成的readKey
*/
void G_RESET_BIT(uint32_t *readKey, uint8_t keyNum)   
{				
	*readKey = *readKey & ((0xfffe<<keyNum)|(0xffff>>(16-keyNum)));
}

/**
* 键值处理
* @param  keyvalue
* @return 
* 检测到按键按下记录 发送完清空
*/
void Key_Set( uint32_t keyvalue )
{
	uint8_t i=0;
	for ( i=0; i<keyTotolNum; i++ ) {
		KEY_G[i] = keyvalue&(0x0001 << i) ? 1: 0;
	}
}
