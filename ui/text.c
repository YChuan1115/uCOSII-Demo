#include "includes.h"

void LCD_DrawText(TEXT t)
{
	Set_Color(t.bcolor,t.fcolor);
	Show_String(t.str,t.x,t.y);
}





