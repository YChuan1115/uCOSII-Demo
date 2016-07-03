#ifndef PROG_H
#define PROG_H
#include "stm32f10x.h"
typedef struct
{
	u16 x;
	u16 y;
	u16 w;
	u16 h;
	u8 color;
	u8 IN_Color;
	float per;
}PROG;

void LCD_DrawProg(PROG p);

#endif

