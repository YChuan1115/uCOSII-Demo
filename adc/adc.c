//AD7705驱动 模拟SPI

#include "includes.h"

#define ADC_SCLK(x)   x?GPIO_SetBits(GPIOB,AD_SCLK):GPIO_ResetBits(GPIOB,AD_SCLK)
#define	ADC_SDI(x)    x?GPIO_SetBits(GPIOB,AD_SDI):GPIO_ResetBits(GPIOB,AD_SDI)
#define ADC_SDO()     GPIO_ReadInputDataBit(GPIOB,AD_SDO)?1:0
#define ADC_RDY()     GPIO_ReadInputDataBit(GPIOB,AD_RDY)?1:0


void ADC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=AD_SCLK|AD_SDI;//输出
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=AD_SDO|AD_RDY;//输入
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void ADC_Reset(void)//在接口序列丢失的情况下，DIN引脚高电平保持足够长的时间(至少32个串行时钟)，AD将回到默认状态
{
	u8 i;
	ADC_SDI(1);
	for(i=0;i<36;i++)
	{
		ADC_SCLK(0);
		DelayN(1);
		ADC_SCLK(1);
		DelayN(1);
	}
}


void ADC_Write(u8 byte)
{
	u8 i;
	ADC_SCLK(0);
	DelayN(1);
	
	for(i=0;i<8;i++)
	{
		if(byte&0x80)
			ADC_SDI(1);
		else
			ADC_SDI(0);
		ADC_SCLK(1);
		DelayN(1);
		ADC_SCLK(0);
		DelayN(1);
		
		byte<<=1;
	}
	ADC_SDI(1);
}


u16 ADC_Read(void)
{
	u8 i;
	u16 temp;
	ADC_SCLK(0);
	DelayN(1);
	
	for(i=0;i<16;i++)
	{
		ADC_SCLK(1);
		DelayN(1);
		if(ADC_SDO())
		{
			temp++;
		}
		ADC_SCLK(0);
		DelayN(1);
	}
	return temp;
}

void ADC_Config(void)
{
	ADC_Init();
	ADC_Reset();//AD7705复位
	ADC_Write(0x20);//设置时钟寄存器   0 0 1 0 0 0 0 0
	DelayN(1);
	ADC_Write(0x03);//000 000 1 1  时钟2.4576MHz 200Hz
	DelayN(1);
	ADC_Write(0x10);//设置设置寄存器   0 0 0 1 0 0 0 0
	DelayN(1);
	ADC_Write(0x44);//0 1 0 0 0 1 0 0  自校准 单极性 非缓冲 增益为1
	DelayN(1); 
}


u16 Get_ADC(void)
{
	u16 dat;
	ADC_Write(0x38);//下次读数据寄存器
	while(ADC_RDY());
	dat=ADC_Read();
	return dat;
}


