#ifndef EDIT_H
#define EDIT_H
#include "stm32f10x.h"

typedef struct 
{
	u16 x;
	u16 y;
	u16 w;
	u16 h;
	u8  color;
}EDIT;

void LCD_DrawEdit(EDIT e);//画文本框

#endif

