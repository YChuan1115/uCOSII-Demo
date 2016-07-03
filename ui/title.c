#include "includes.h"

void LCD_DrawTitleBar(TITLE t)
{
	LCD_Clear(0,0,240,t.h,t.bcolor);
	Set_Color(t.bcolor,t.fcolor);
	Show_String(t.str,4,2);
}

