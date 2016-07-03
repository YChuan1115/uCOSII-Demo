#include "includes.h"

static OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];
static OS_STK input_task_stk[INPUT_TASK_STK_SIZE];
static OS_STK timer_task_stk[TIMER_TASK_STK_SIZE];
static OS_STK cursor_task_stk[CURSOR_TASK_STK_SIZE];
static OS_STK adc_task_stk[ADC_TASK_STK_SIZE];
static OS_STK led_task_stk[LED_TASK_STK_SIZE];

OS_EVENT *PENIRQ;
TOUCH_KEY touch;
CURSOR    cursor;
COLOR     color;

int main(void)
{
	BSP_Init();
	SysTick_Init();
	PENIRQ=OSSemCreate(0);
#ifdef TOUCH_CALIBRATION
	Show_KeyMap();
#endif
	OSInit();
#ifndef TOUCH_CALIBRATION
	OSTaskCreate((void (*) (void *))Startup_Task, (void *)0, &startup_task_stk[STARTUP_TASK_STK_SIZE-1], STARTUP_TASK_PRIO);
	OSTaskCreate((void (*) (void *))Timer_Task,   (void *)0, &timer_task_stk[TIMER_TASK_STK_SIZE-1],     TIMER_TASK_PRIO);
	OSTaskCreate((void (*) (void *))Cursor_Task,  (void *)0, &cursor_task_stk[CURSOR_TASK_STK_SIZE-1],   CURSOR_TASK_PRIO);
	OSTaskCreate((void (*) (void *))ADC_Task,     (void *)0, &adc_task_stk[ADC_TASK_STK_SIZE-1],         ADC_TASK_PRIO);
#endif
	OSTaskCreate((void (*) (void *))Led_Task,     (void *)0, &led_task_stk[LED_TASK_STK_SIZE-1],         LED_TASK_PRIO);
	OSTaskCreate((void (*) (void *))Input_Task,   (void *)0, &input_task_stk[INPUT_TASK_STK_SIZE-1],     INPUT_TASK_PRIO);
	OSStart(); 
	return 0;
}


