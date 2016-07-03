#ifndef BEEP_H
#define BEEP_H
#include "stm32f10x.h"
#define BEEP GPIO_Pin_1
void Beep_Init(void);
void Beep_Con(u8 con); 
#endif

