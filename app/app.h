#ifndef APP_H
#define APP_H

void Startup_Task(void *parg);
void Cursor_Task(void *parg);
void Timer_Task(void *parg);
void Input_Task(void *parg);
void ADC_Task(void *parg);
void Led_Task(void *parg);

u16  CalcDec(u8 *p,u8 len);

#endif

