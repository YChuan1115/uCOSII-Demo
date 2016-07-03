#ifndef LED_H
#define LED_H

#define LED0 GPIO_Pin_15
#define LED1 GPIO_Pin_7

void Led_Init(void);
void Led_On(u8 led);
void Led_Off(u8 led);

#endif
