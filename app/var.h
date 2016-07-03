#ifndef VAR_H
#define VAR_H
#include "stm32f10x.h"
typedef struct
{
	u16 AD_X;
	u16 AD_Y;
	u16 LCD_X;
	u16 LCD_Y;
	u8  KEY;
	u8  PID;
	u8  FLAG;
	u8 	STATE;
}TOUCH_KEY;
#endif

