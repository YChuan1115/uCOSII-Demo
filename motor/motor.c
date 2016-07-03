#include "motor.h"
#include "stm32f10x_gpio.h"

void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=MOTOR1|MOTOR2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void Motor_On(u8 m)
{
	if(m==1)
		GPIO_SetBits(GPIOA,MOTOR1);
	else if(m==2)
		GPIO_SetBits(GPIOA,MOTOR2);
	else;
}

void Motor_Off(u8 m)
{
	if(m==1)
		GPIO_ResetBits(GPIOA,MOTOR1);
	else if(m==2)
		GPIO_ResetBits(GPIOA,MOTOR2);
	else;
}


