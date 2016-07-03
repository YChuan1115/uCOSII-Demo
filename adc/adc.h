#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"

#define AD_RDY    GPIO_Pin_3 //PB3  输出
#define AD_SCLK	  GPIO_Pin_4 //PB4  输出
#define AD_SDI	  GPIO_Pin_5 //PB5  输出
#define AD_SDO	  GPIO_Pin_6 //PB6  输入

void ADC_Init(void);
void ADC_Reset(void);
void ADC_Write(u8 byte);
u16  ADC_Read(void);
void ADC_Config(void);
u16  Get_ADC(void);

#endif


