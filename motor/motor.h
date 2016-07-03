#ifndef MOTOR_H
#define MOTOR_H

#include "stm32f10x.h"

#define MOTOR1  GPIO_Pin_12 //PA12
#define MOTOR2  GPIO_Pin_13 //PA13

void Motor_Init(void);
void Motor_On(u8 m);
void Motor_Off(u8 m);
#endif

