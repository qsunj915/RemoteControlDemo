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

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   


/**
  * @brief :I2C写命令
  * @param :
  *			@I2C_Command:要写入的命令
  * @note  :用于和原来的文件兼容
  * @retval:无
  */ 
void I2C_WriteConCmd(unsigned char I2C_Command)//写命令
{
	I2C_WriteByte(I2C1, 0x78, 0x00, I2C_Command);
}

/**
  * @brief :I2C写数据
  * @param :
  *			@I2C_Command:要写入的数据
  * @note  :
  * @retval:无
  */ 
void I2C_WriteDataCmd(unsigned char I2C_Data)//写数据
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

//坐标设置
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)
			OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}

//清蓝屏函数	  
void OLED_ClearBlue(void)  
{  
	u8 i,n;		    
	for(i=2;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}
//清行函数
void OLED_ClearLine(u8 line)
{
	u8 n;
	OLED_WR_Byte (0xb0+line,OLED_CMD);    //设置页地址（0~7）
	OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
	OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
	for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
}

void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //更新显示
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 8/6
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;
	c=chr-' ';//得到偏移后的值			
	if(x>Max_Column-1)
	{
		x=0;
		y=y+2;
	}
	if(Char_Size ==8)//字体为8号
	{
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
	}
	else 
	{	 ////字体为6号
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
			OLED_WR_Byte(F6x8[c][i],OLED_DATA);
	}
}

//m^n函数
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)
		result*=m;    
	return result;
}

//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
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

//显示一个字符号串
void OLED_ShowString(u8 x,u8 y,char *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{	
		OLED_ShowChar(x,y,chr[j],Char_Size);
		x+=Char_Size;//字间距
		if(x>120) 
		{
			x=0;y+=2;
		}
		j++;
	}
}

//显示汉字
//x,y :起点坐标	 
//data[][16] 汉字取模
//num:二维数组行数	16x16
void OLED_ShowCHinese(u8 x,u8 y,const char data[][16],u8 num)
{      			    
	u8 t;
	OLED_Set_Pos(x,y);//设置坐标
	for(t=0;t<16;t++)
	{
		OLED_WR_Byte(data[2*num][t],OLED_DATA);
	}	
	OLED_Set_Pos(x,y+1);//设置坐标
	for(t=0;t<16;t++)
	{	
		OLED_WR_Byte(data[2*num+1][t],OLED_DATA);
	}					
}

//显示汉字
//x,y :起点坐标	 
//data[][16] 汉字取模
//num:二维数组行数	7x7
void OLED_ShowCHinese7x7(u8 x,u8 y,const char data[][16],u8 num)
{      			    
	u8 t;
	OLED_Set_Pos(x,y);//设置坐标
	for(t=0;t<7;t++)
	{
		OLED_WR_Byte(data[2*num][t],OLED_DATA);
	}	
	OLED_Set_Pos(x,y+1);//设置坐标
	for(t=0;t<7;t++)
	{	
		OLED_WR_Byte(data[2*num+1][t],OLED_DATA);
	}	
}

//显示一串汉字
//x,y :起点坐标	 
//data[][16] 汉字取模
//num:二维数组行数	16x16
void OLED_ShowCHineseString(u8 x,u8 y,const char data[][16],u8 num)
{      			    
	u8 i;
	for(i=0;i<num;i++)
		OLED_ShowCHinese(x+i*16,y,data,i);
}

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
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

