/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

///**
//  * @brief  This function handles SysTick Handler.
//  * @param  None
//  * @retval None
//  */
//void SysTick_Handler(void)
//{
// if(count!=0){
//		count--;
//	}
//}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/*****************************USART**************************/
/**
  * @brief  This function handles USART1 Handler.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
	uint8_t RxData = 0;
	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) != RESET) {
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//		RxData = USART_ReceiveData(USART1);
		
		InterruptTask_USART1(RxData);
	}
}

/**
  * @brief  This function handles USART3 Handler.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
	uint8_t RxData = 0;
	if (USART_GetFlagStatus(USART2, USART_IT_RXNE) != RESET) {
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
//		RxData = USART_ReceiveData(USART2);
		
		InterruptTask_USART2(RxData);
	}
}

/*****************************TIMER**************************/

/**
* @brief 定时器2中断函数
* @param none
* @return none
*/	
void TIM2_IRQHandler(void)
{	
	//每隔1ms进入一次更新中断
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);//清除标志位
		InterruptTask_TIM2();
	}
}

/**
* @brief 定时器3中断函数，5ms
* @param none
* @return none
*/	
void TIM3_IRQHandler(void)
{	
	//每隔10ms进入一次更新中断
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {	
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);      //清除标志位
		InterruptTask_TIM3();
	}
}


/**
* @brief 定时器5中断函数，
* @param none
* @return none
*/	
void TIM5_IRQHandler(void)
{
	//每隔15ms进入一次更新中断
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) {	
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);      //清除标志位
		InterruptTask_TIM5();
	}
}

/**
* @brief 定时器7中断函数，
* @param none
* @return none
*/	
void TIM7_IRQHandler(void)
{	  
	//每隔1ms进入一次更新中断
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) {	
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);      //清除标志位
		TIM7_DelayCount_Run();
	}
}



/**************************CAN**************************/

/**
* @brief CAN1中断函数
* @param none
* @return none
*/	


void CAN1_TX_IRQHandler(void)
{
	if (CAN_GetITStatus(CAN1,CAN_IT_TME) != RESET)
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
	}
}

void CAN1_RX0_IRQHandler(void)
{
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0) != RESET)
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_FF0);
		CAN_ClearFlag (CAN1, CAN_IT_FF0);
	}
}



/*****************************DMA**************************/
//不能用
void DMA2_Stream0_IRQHandler(void) {
	if (DMA_GetFlagStatus(DMA2_Stream0, DMA_FLAG_TCIF0) == SET) {
		DMA_ClearITPendingBit(DMA2_Stream0, DMA_FLAG_TCIF0);
		DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0);//清传输完成标志
	}
}

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
