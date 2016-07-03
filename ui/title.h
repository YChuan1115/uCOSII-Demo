#ifndef TITLE_H
#define TITLE_H
#include "stm32f10x.h"
typedef struct
{
	u16 h;
	u8  fcolor;
	u8  bcolor;
	char *str;
}TITLE;

void LCD_DrawTitleBar(TITLE t);

#endif



