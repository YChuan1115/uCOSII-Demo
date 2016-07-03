#include "includes.h"

void LCD_DrawProg(PROG p)
{
	LCD_DrawRec(p.x,p.y,p.w,p.h,p.color);
	LCD_Clear(p.x+1,p.y+1,(u16)(p.per*(p.w-2)),p.h-2,p.IN_Color);
	Show_Dec(p.per*100,3,p.x+p.w,p.y-2);
	Show_Char('%',p.x+p.w+24,p.y-3);
}


