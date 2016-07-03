#include "includes.h"
#include "os_cpu.h"

extern TOUCH_KEY touch;
extern OS_EVENT *PENIRQ;

void Exti_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_ClearITPendingBit(EXTI_Line5);//清除中断标志
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5);//选择中断引脚PA5
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;//选择中断线路5
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//设置为中断请求
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;//外部中断使能
	EXTI_Init(&EXTI_InitStructure);
}

void Exti_Set(u8 s)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
	if(!s)
	{
		EXTI_InitStructure.EXTI_LineCmd=DISABLE;
	}
	else
	{
		EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	}
	EXTI_Init(&EXTI_InitStructure);
}

void EXTI9_5_IRQHandler(void)
{
		OSIntEnter();
		if(EXTI_GetITStatus(EXTI_Line5)!=RESET)
		{	
				OSSemPost(PENIRQ);
				EXTI_ClearITPendingBit(EXTI_Line5);	
		}
		OSIntExit();
}


