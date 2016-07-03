#include "includes.h"

void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=LED0;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=LED1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void Led_Off(u8 led)
{
	if(!led)
		GPIO_ResetBits(GPIOA,GPIO_Pin_15);//P3.7
	else
		GPIO_ResetBits(GPIOB,GPIO_Pin_7);//P2.0
}

void Led_On(u8 led)
{
	if(!led)
		GPIO_SetBits(GPIOA,GPIO_Pin_15);
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
}

