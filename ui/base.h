#ifndef BASE_H
#define BASE_H
#include "stm32f10x.h"
void LCD_DrawVLine(u16 x,u16 y ,u16 L,u8 color);//画竖线
void LCD_DrawHLine(u16 x,u16 y,u16 L,u8 color);//画横线
void LCD_DrawRec(u16 x,u16 y,u16 w,u16 h,u8 color);//画矩形

#endif

