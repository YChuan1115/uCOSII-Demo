#ifndef BSP_H
#define BSP_H

#define SystemFrequency  72000000

void SysTick_Init(void);
void BSP_Init(void);
void SysTick_Handler(void);
void GPIO_Config(void);
void Sys_Check(void);
void NVIC_Config(void);

#endif
