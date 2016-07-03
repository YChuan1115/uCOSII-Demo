#include "includes.h"

void LCD_DrawButton(BUTTON b)
{
	LCD_DrawRec(b.x,b.y,b.w,b.h,b.line_color);
	LCD_Clear(b.x+1,b.y+1,b.w-2,b.h-2,GRAY);
	Set_Color(GRAY,BLACK);
	Show_String(b.str,b.x+(b.w-8*b.len)/2,b.y+(b.h-16)/2);
}

