#include "includes.h"

extern u16 colors[10];

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//打开IO口及复用功能时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);//调试口设置为普通IO口
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void BSP_Init(void)
{
	NVIC_Config();
	GPIO_Config();
	Exti_Config();
	LCD_Config();
	ADC_Config();
	Touch_Init();
	Led_Init();
	Motor_Init();
	Beep_Init();
}

void SysTick_Init(void)
{
	SysTick_Config(SystemFrequency/OS_TICKS_PER_SEC);
}

void SysTick_Handler(void)
{
	OSIntEnter();
	OSTimeTick();
	OSIntExit();
}

void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//设置优先级组
	NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;//设置中断通道为5
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占式优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;//响应优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//使能中断
	NVIC_Init(&NVIC_InitStructure);
}


#ifdef LCD_READ_DEBUG
void Sys_Check(void)
{
	u16 ID,pixel;
	u8 f1,f2,f3;
	Show_String("Checking Device Code...",0,0);
	ID=Read_ID();
	Show_Hex(ID,0,16);
	if(ID==0xB509)
	{
		Show_String("......OK!",48,16);
		f1=1;
	}
	else
	{
		Show_String("......ERROR!",48,16);
		f1=0;
	}
	Show_String("Testing Pixel Read 1...",0,32);
	pixel=LCD_GetPoint(100,100);
	Show_Hex(pixel,0,48);
	if(pixel==colors[GRAY])
	{	
		Show_String("......OK!",48,48);
		f2=1;
	}
	else
	{	
		Show_String("......ERROR!",48,48);
		f2=0;
	}
	Show_String("Testing Pixel Read 2...",0,64);
	pixel=LCD_GetPoint(200,200);
	Show_Hex(pixel,0,80);
	if(pixel==colors[GRAY])
	{	
		Show_String("......OK!",48,80);
		f3=1;
	}
	else
	{	
		Show_String("......ERROR!",48,80);
		f3=0;
	}
	if(f1&&f2&&f3)
	{
		Show_String("System Check Complete!",0,96);	
	}
	else
	{
		Show_String("System Error!",0,96);
	}
	Show_Hex(0x55AA,0,112);
	Show_Bin(0x55AA,0,128);
	Show_Dec(65535,5,0,144);
	Show_String("Touch Screen To Continue...",0,160);
	while(1)
	{
		DelayM(50);
		if(!Touch_Pen())
			break;
	}
	LCD_Clear(0,0,240,400,GRAY);
}
#endif


