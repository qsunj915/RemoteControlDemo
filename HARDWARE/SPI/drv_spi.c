/**
  ******************************************************************************
  * @file    drv_spi.c
  * @author  qsunj
  * @date    21-5-30
  * @brief  
  ******************************************************************************
  */
  
#include "drv_spi.h"

#define SPI_WAIT_TIMEOUT			((uint16_t)0x00FF)

/**
  * @brief :SPI����
  * @param :��
  * @note  :
  * @retval:��
  */

void SPI2_Init() {
	SPI_InitTypeDef		SpiInitStructer;
	
	GPIO_Format_Init(GPIOB,SPI_CLK_GPIO_PIN | SPI_MISO_GPIO_PIN | SPI_MOSI_GPIO_PIN ,GPIO_Mode_AF\
					,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_50MHz);
	
	GPIO_PinAFConfig(SPI_CLK_GPIO_PORT,GPIO_PinSource13,GPIO_AF_SPI2);
	GPIO_PinAFConfig(SPI_MOSI_GPIO_PORT,GPIO_PinSource14,GPIO_AF_SPI2);
	GPIO_PinAFConfig(SPI_MISO_GPIO_PORT,GPIO_PinSource15,GPIO_AF_SPI2);
	GPIO_SetBits( SPI_MISO_GPIO_PORT, SPI_MISO_GPIO_PIN );
	
	GPIO_Format_Init(GPIOA, SPI_NSS_GPIO_PIN,GPIO_Mode_OUT\
					,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_100MHz);

	GPIO_SetBits( SPI_MISO_GPIO_PORT, SPI_MISO_GPIO_PIN );
	
	/** SPI���� */
	SPI_I2S_DeInit( SPI_PORT );			//��λSPI
	RCC_APB1PeriphClockCmd( SPI_PORT_CLK, ENABLE );
	SPI_Cmd( SPI_PORT, DISABLE );		//�ر�SPI���裬����ǰ�ر�
	
	SpiInitStructer.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;    //˫��ȫ˫��
	SpiInitStructer.SPI_Mode              = SPI_Mode_Master;                    //����ģʽ
	SpiInitStructer.SPI_CPOL              = SPI_CPOL_Low;                       //����״̬Ϊ�͵�ƽ 
	SpiInitStructer.SPI_CPHA              = SPI_CPHA_1Edge;                     //��һ�����زɼ�����
	SpiInitStructer.SPI_DataSize          = SPI_DataSize_8b;                    //8λ����
	SpiInitStructer.SPI_NSS               = SPI_NSS_Soft;                       //�ӻ��������
	SpiInitStructer.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;            //64��Ƶ
	SpiInitStructer.SPI_FirstBit          = SPI_FirstBit_MSB;                   //���λ�ȷ���
	SpiInitStructer.SPI_CRCPolynomial     = 7;                                  //CRC����ʽ,Ĭ�ϲ�ʹ��SPI�Դ�CRC	 
	
	SPI_Init( SPI_PORT, &SpiInitStructer );
	SPI_Cmd( SPI_PORT, ENABLE );
}

/**
  * @brief :SPI�շ�һ���ֽ�
  * @param :
  *			@TxByte: ���͵������ֽ�
  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
  * @retval:���յ����ֽ�
  */
uint8_t drv_spi_read_write_byte( uint8_t TxByte )
{
	uint8_t l_Data = 0;
	uint16_t l_WaitTime = 0;
	
	while( RESET == SPI_I2S_GetFlagStatus( SPI_PORT, SPI_I2S_FLAG_TXE ) )		//�ȴ����ͻ�����Ϊ��
	{
		if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
		{
			break;			//����ȴ���ʱ���˳�
		}
	}
	l_WaitTime = SPI_WAIT_TIMEOUT / 2;		//�������ý��յȴ�ʱ��(��ΪSPI���ٶȺܿ죬����������ڷ������֮��������յ����ݣ��ȴ�ʱ�䲻��Ҫ����)
	SPI_PORT->DR = TxByte;	//��������
	
	while( RESET == SPI_I2S_GetFlagStatus( SPI_PORT, SPI_I2S_FLAG_RXNE ) )		//�ȴ����ջ������ǿ�
	{
		if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
		{
			break;			//����ȴ���ʱ���˳�
		}
	}
	
	l_Data = (uint8_t)SPI_PORT->DR;		//��ȡ��������
	
	return l_Data;		//����
}

/**
  * @brief :SPI�շ��ַ���
  * @param :
  *			@ReadBuffer: �������ݻ�������ַ
  *			@WriteBuffer:�����ֽڻ�������ַ
  *			@Length:�ֽڳ���
  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
  * @retval:��
  */
void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length )
{
	GPIO_ResetBits( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);	  		//����Ƭѡ
	while( Length-- )
	{
		*ReadBuffer = drv_spi_read_write_byte( *WriteBuffer );		//�շ�����
		ReadBuffer++;
		WriteBuffer++;			                                    	//��д��ַ��1
	}
	GPIO_SetBits( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);				  //����Ƭѡ
}

