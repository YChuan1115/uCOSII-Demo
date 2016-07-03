#include "includes.h"

void LCD_DrawVLine(u16 x,u16 y,u16 L,u8 color)//画垂直线，指定起点，长度，颜色
{
	u16 i;
	for(i=0;i<L;i++)
	{
		LCD_SetPoint(x,y+i,color);
	}
}

void LCD_DrawHLine(u16 x,u16 y,u16 L,u8 color)//画水平线，指定起点，长度，颜色
{
	u16 i;
	for(i=0;i<L;i++)
	{
		LCD_SetPoint(x+i,y,color);
	}
}

void LCD_DrawRec(u16 x,u16 y,u16 w,u16 h,u8 color)//指定起、长度、宽度和线框的颜色画矩形，线宽默认1像素
{
	LCD_DrawHLine(x,y,w,color);
	LCD_DrawVLine(x,y,h,color);
	LCD_DrawVLine(x+w-1,y,h,color);
	LCD_DrawHLine(x,y+h-1,w,color);
}









