#include "includes.h"

extern CURSOR cursor;

void Set_Cursor(u16 x,u16 y)
{
	cursor.x=x;
	cursor.y=y;
}

CURSOR Get_Cursor(void)
{
	CURSOR c;
	c.x=cursor.x;
	c.y=cursor.y;
	return c;
}

