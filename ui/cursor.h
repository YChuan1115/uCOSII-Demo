#ifndef CURSOR_H
#define CURSOR_H
#include "stm32f10x.h"
typedef struct
{
	u16 x;
	u16 y;
}CURSOR;


void   Set_Cursor(u16 x,u16 y);//设置光标位置
CURSOR Get_Cursor(void);//获取光标位置

#endif

