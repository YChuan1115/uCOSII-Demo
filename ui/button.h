#ifndef BUTTON_H
#define BUTTON_H
#include "stm32f10x.h"
typedef struct
{
	u16 x;
	u16 y;
	u16 w;
	u16 h;
	char *str;
	u8 len;
	u8 line_color;
}BUTTON;

void LCD_DrawButton(BUTTON b);

#endif

