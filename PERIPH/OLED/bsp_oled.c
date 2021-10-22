/**
  ******************************************************************************
  * @file    oled
  * @author  qsunj
  * @version v1.0
  * @date    
  * @brief   
  ******************************************************************************
  */
#include "bsp_oled.h"
#include "oled_font.h"

//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   


/**
  * @brief :I2Cд����
  * @param :
  *			@I2C_Command:Ҫд�������
  * @note  :���ں�ԭ�����ļ�����
  * @retval:��
  */ 
void I2C_WriteConCmd(unsigned char I2C_Command)//д����
{
	I2C_WriteByte(I2C1, 0x78, 0x00, I2C_Command);
}

/**
  * @brief :I2Cд����
  * @param :
  *			@I2C_Command:Ҫд�������
  * @note  :
  * @retval:��
  */ 
void I2C_WriteDataCmd(unsigned char I2C_Data)//д����
{
	I2C_WriteByte(I2C1, 0x78, 0x40, I2C_Data);
}



void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
		I2C_WriteDataCmd(dat);
		
	}
	else 
	{
		I2C_WriteConCmd(dat);
	}
}


/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		 //low column start address
		OLED_WR_Byte(0x10,0);		 //high column start address
		for(n=0;n<128;n++)
		{
			OLED_WR_Byte(fill_Data,1);
		}
	}
}

/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}

//��������
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  
//����OLED��ʾ    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)
			OLED_WR_Byte(0,OLED_DATA); 
	} //������ʾ
}

//����������	  
void OLED_ClearBlue(void)  
{  
	u8 i,n;		    
	for(i=2;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //������ʾ
}
//���к���
void OLED_ClearLine(u8 line)
{
	u8 n;
	OLED_WR_Byte (0xb0+line,OLED_CMD);    //����ҳ��ַ��0~7��
	OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
	OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
	for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
}

void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //������ʾ
}

//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 8/6
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;
	c=chr-' ';//�õ�ƫ�ƺ��ֵ			
	if(x>Max_Column-1)
	{
		x=0;
		y=y+2;
	}
	if(Char_Size ==8)//����Ϊ8��
	{
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
	}
	else 
	{	 ////����Ϊ6��
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
			OLED_WR_Byte(F6x8[c][i],OLED_DATA);
	}
}

//m^n����
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)
		result*=m;    
	return result;
}

//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+size*t,y,' ',size);
				continue;
			}
			else 
				enshow=1; 
		}
	 	OLED_ShowChar(x+size*t,y,temp+'0',size); 
	}
}

//��ʾһ���ַ��Ŵ�
void OLED_ShowString(u8 x,u8 y,char *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{	
		OLED_ShowChar(x,y,chr[j],Char_Size);
		x+=Char_Size;//�ּ��
		if(x>120) 
		{
			x=0;y+=2;
		}
		j++;
	}
}

//��ʾ����
//x,y :�������	 
//data[][16] ����ȡģ
//num:��ά��������	16x16
void OLED_ShowCHinese(u8 x,u8 y,const char data[][16],u8 num)
{      			    
	u8 t;
	OLED_Set_Pos(x,y);//��������
	for(t=0;t<16;t++)
	{
		OLED_WR_Byte(data[2*num][t],OLED_DATA);
	}	
	OLED_Set_Pos(x,y+1);//��������
	for(t=0;t<16;t++)
	{	
		OLED_WR_Byte(data[2*num+1][t],OLED_DATA);
	}					
}

//��ʾ����
//x,y :�������	 
//data[][16] ����ȡģ
//num:��ά��������	7x7
void OLED_ShowCHinese7x7(u8 x,u8 y,const char data[][16],u8 num)
{      			    
	u8 t;
	OLED_Set_Pos(x,y);//��������
	for(t=0;t<7;t++)
	{
		OLED_WR_Byte(data[2*num][t],OLED_DATA);
	}	
	OLED_Set_Pos(x,y+1);//��������
	for(t=0;t<7;t++)
	{	
		OLED_WR_Byte(data[2*num+1][t],OLED_DATA);
	}	
}

//��ʾһ������
//x,y :�������	 
//data[][16] ����ȡģ
//num:��ά��������	16x16
void OLED_ShowCHineseString(u8 x,u8 y,const char data[][16],u8 num)
{      			    
	u8 i;
	for(i=0;i<num;i++)
		OLED_ShowCHinese(x+i*16,y,data,i);
}

/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
	unsigned int j=0;
	unsigned char x,y;

	if(y1%8==0) 
		y=y1/8;      
	else 
		y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
		for(x=x0;x<x1;x++)
		{      
			OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
		}
	}
}

void OLED_Init(void)
{ 
	I2C1_Init();

	OLED_WR_Byte(0xAE,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0x20,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0x10,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xb0,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xc8,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0x10,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0x40,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0x81,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xff,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xa1,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xa6,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xa8,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0x3F,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xa4,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xd3,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xd5,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xf0,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xd9,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0x22,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xda,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0x12,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xdb,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0x20,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0x8d,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0x14,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xaf,OLED_CMD);//--turn on oled panel
	
	Serial_Send(Serial1, "oled execute OK!\r\n");
}  

