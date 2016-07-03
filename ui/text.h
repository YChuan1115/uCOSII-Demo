#ifndef TEXT_H
#define TEXT_H
#include "stm32f10x.h"

typedef struct
{
	u16 x;
	u16 y;
	u8 bcolor;
	u8 fcolor;
	char *str;
}TEXT;

void LCD_DrawText(TEXT t);

#endif

