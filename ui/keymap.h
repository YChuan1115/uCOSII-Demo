#ifndef KEYMAP_H
#define KEYMAP_H
#include "stm32f10x.h"

void Show_KeyMap(void);//显示键盘
void LCD_DrawKeyNum(u16 num,u16 x,u16 y);//显示键盘数字
void LCD_DrawKeyDel(u16 x,u16 y);
void LCD_DrawKeyOK(u16 x,u16 y);

#endif




