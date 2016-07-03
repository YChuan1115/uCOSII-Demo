#include "includes.h"

void LCD_DrawEdit(EDIT e)//画文本框，指定宽度和高度，线框颜色默认黑色
{
	LCD_DrawRec(e.x,e.y,e.w,e.h,e.color);
	LCD_Clear(e.x+1,e.y+1,e.w-2,e.h-2,WHITE);
}

