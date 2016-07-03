#include "includes.h"
#include<math.h>

#define TCS_0 	GPIO_ResetBits(GPIOA,TCS);
#define TCS_1	  GPIO_SetBits(GPIOA,TCS);
#define TCLK_0	GPIO_ResetBits(GPIOA,TCLK);
#define TCLK_1	GPIO_SetBits(GPIOA,TCLK);
#define DIN_0	  GPIO_ResetBits(GPIOA,TDI);
#define DIN_1	  GPIO_SetBits(GPIOA,TDI);

//读取15次AD值，按大小排序，只取中间5个数
#define COUNT     11
#define LOST      3
#define ERR_RANGE 50

u8 CMD_RDX=0xD0;
u8 CMD_RDY=0X90;

//初始化引脚配置
void Touch_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=BUSY|TDO;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=TDI|TCS|TCLK;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TCS_0;
}

void SPI_Start(void)
{
	TCLK_0;
	DelayN(10);
	TCS_1;
	DelayN(10);
	DIN_1;
	DelayN(10);
	TCLK_1;
	DelayN(10);
	TCS_0;
	DelayN(10);
}

//向xpt2046发送字节
void Touch_Write(u8 byte)
{
	u8 i=0;
	TCLK_0;
	for(i=0;i<8;i++)
	{
		if(byte&0x80)
		{
			DIN_1;//写1
		}
		else
		{
			DIN_0;//写0
		}
		byte<<=1;
		TCLK_0;//上升沿
		DelayN(10);
		TCLK_1;
		DelayN(10);
	}
}

//读取
u16 Touch_Read(void)
{	u16 i,dat;
	for(i=0;i<12;i++)
	{
		dat<<=1;
		TCLK_1;
		DelayN(10);
		TCLK_0;//数据在下降沿输出
		DelayN(10);
		if(GPIO_ReadInputDataBit(GPIOA,TDO))
			dat++;
	}
	return dat;
}

//读相应坐标的AD值
u16 Read_AD(u8 cmd)
{
	u16 value;
	SPI_Start();
	Touch_Write(cmd);
	//while(Is_Busy());//等待转换,该信号容易乱，不建议使用
	DelayN(10);
	TCLK_1;
	DelayN(10);
	TCLK_0;
	DelayN(10);
	value=Touch_Read();
	return value;
}

//多次读取求平均值
u16 Read_ADS(u8 cmd)
{
	u8 i,j;
	u16 temp;
	u16 buffer[COUNT];
	u16 avge,sum;
	for(i=0;i<COUNT;i++)
	{
		buffer[i]=Read_AD(cmd);
	}
	
	for(i=0;i<COUNT-1; i++)//升序排序
	{
		for(j=i+1;j<COUNT;j++)
		{
			if(buffer[i]>buffer[j])
			{
				temp=buffer[i];
				buffer[i]=buffer[j];
				buffer[j]=temp;
			}
		}
	}
	
	for(i=LOST;i<COUNT-LOST;i++)//取中间5个值
	{
		sum+=buffer[i];
	}
	avge=sum/(COUNT-2*LOST);
	return avge;
}

u8 Read_XY(u16 *x,u16 *y)//读取坐标值
{
	u16 xtmp=0,ytmp=0;
	xtmp=Read_ADS(CMD_RDX);
	ytmp=Read_ADS(CMD_RDY);
	if((xtmp<600||xtmp>3950)||(ytmp<500||ytmp>3900))
		return 0;
	else
	{
		*x=xtmp;
		*y=ytmp;
		return 1;
	}
}

u8 Read_XY_2(u16 *x,u16 *y)
{
	u16 flag;
	u16 x1,y1,x2,y2;
	int deltax,deltay;
	flag=Read_XY(&x1,&y1);
	if(flag==0) return 0;
	flag=Read_XY(&x2,&y2);
	if(flag==0) return 0;
	deltax=x1-x2;
	deltay=y1-y2;
	if(fabs(deltax)<=ERR_RANGE&&fabs(deltay)<=ERR_RANGE)
	{
		*x=(x1+x2)/2;
		*y=(y1+y2)/2;
		return 1;
	}
	else
		return 0;
}

//将AD值转换为屏幕上对应的坐标
//参数：ad-取得的AD值，xy-要转换的坐标 0：X轴 1：Y轴
//返回值：对应的坐标值
u16 CalcXY(u16 ad,u8 xy)
{
	u32 i,j;
	u16 dat,tmp;
	if(xy==0)
	{
		i=ad*240;
		j=Xmax-Xmin;
		tmp=i/j;
		tmp=(u16)tmp;
		if(tmp>0&&tmp<=45)
			dat=240;
		else if(tmp>45&&tmp<285)
			dat=285-tmp;
		else
			dat=0;
	}
	
	else
	{
		i=ad*400;
		j=Ymax-Ymin;
		tmp=i/j;
		tmp=(u16)tmp;
		if(tmp>0&&tmp<=64)
			dat=400;
		else if(tmp>64&&tmp<464)
			dat=464-tmp;
		else
			dat=0;
	}
	return dat;
}

u16 Get_Key(u16 pid,u16 x,u16 y)
{
	u16 key=99;//默认返回值为99，即当没有触摸或不在指定位置触摸时，返回99
	if(pid==0)
	{
		if(x>10&&x<230)
		{
				if(y>220&&y<268)
				{
					key=13;//Start
				}
				else if(y>300&&y<348)
				{
					key=14;//Settings
				}
				else
					key=99;
		}
	}
	else
	{
		if(y>160&&y<220)
		{
				if(x>0&&x<60)
				{
					key=1;
				}
				else if(x>60&&x<120)
				{
					key=2;
				}
				else if(x>120&&x<180)
				{
					key=3;
				}
				else if(x>180)
				{
					key=0;
				}
				else
					key=99;
		}
		else if(y>220&&y<280)
		{
				if(x>0&&x<60)
				{
					key=4;
				}
				else if(x>60&&x<120)
				{
					key=5;
				}
				else if(x>120&&x<180)
				{
					key=6;
				}
				else if(x>180)
				{
					key=10;//.
				}
				else
					key=99;
		}
		else if(y>280&&y<340)
		{
				if(x>0&&x<60)
				{
					key=7;
				}
				else if(x>60&&x<120)
				{
					key=8;
				}
				else if(x>120&&x<180)
				{
					key=9;
				}
				else if(x>180)
				{
					key=11;//enter
				}
				else
					key=99;
		}
		else if(y>340&&y<400)
		{
			if(x>0&&x<120)
			{
				key=12;//clear
			}
			else if(x>120)
			{
				key=11;//enter
			}
			else
				key=99;
		}
		else
			key=99;
	}
	return key;
}



