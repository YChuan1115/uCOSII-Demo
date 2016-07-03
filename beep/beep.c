#include "beep.h"
#include "stm32f10x_gpio.h"
void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=BEEP;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void Beep_Con(u8 con)
{
	if(con==0)
	{
		GPIO_ResetBits(GPIOB,BEEP);
	}
	else
	{
		GPIO_SetBits(GPIOB,BEEP);
	}
}

