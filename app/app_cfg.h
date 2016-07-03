#ifndef APP_CFG_H
#define APP_CFG_H

#define STARTUP_TASK_PRIO     4
#define STARTUP_TASK_STK_SIZE 32

#define CURSOR_TASK_PRIO	    7      //0.5s
#define CURSOR_TASK_STK_SIZE  32

#define INPUT_TASK_PRIO       9			//0.05
#define INPUT_TASK_STK_SIZE   64

#define TIMER_TASK_PRIO       6      //1s
#define TIMER_TASK_STK_SIZE   32

#define ADC_TASK_PRIO         8      //0.25s
#define ADC_TASK_STK_SIZE     64

#define LED_TASK_PRIO					5      //1.5s
#define LED_TASK_STK_SIZE     32

#endif

