#include "includes.h"
#include "num.h"

extern u16 colors[10];
extern COLOR     color;
extern TOUCH_KEY touch;
extern CURSOR    cursor;

EDIT   input={2,120,236,40,ORANGE};
TITLE  title={20,RED,BLUE,"Input Interface"};

void LCD_DrawKeyNum(u16 num,u16 x,u16 y)
{
	u16 i,j,temp;
	const unsigned char *p;
	Set_Area(x+18,y+6,x+18+23,y+6+47);
	p=F24x48[num];
	for(i=0;i<144;i++)
	{
		temp=p[i];
		for(j=0;j<8;j++)
		{
			if(temp&0x01)
				Write_DAT(colors[color.FC]);
			else
				Write_DAT(colors[color.BC]);
			temp>>=1;
		}
	}
}

void LCD_DrawKeyDel(u16 x,u16 y)
{
	u16 i,j,temp;
	const unsigned char *p;
	p=DEL;
	Set_Area(x+36,y+24,x+36+47,y+24+10);
	for(i=0;i<66;i++)
	{
		temp=p[i];
		for(j=0;j<8;j++)
		{
				if(temp&0x01)
					Write_DAT(colors[color.FC]);
				else
					Write_DAT(colors[color.BC]);
				temp>>=1;
		}
	}
}

void LCD_DrawKeyOK(u16 x,u16 y)
{
	LCD_DrawKeyDel(x,y);
	LCD_DrawHLine(x+36+44,y+24+5,15,WHITE);
	LCD_DrawHLine(x+36+44,y+24+6,15,WHITE);
	LCD_DrawVLine(x+36+48+10,y+24+5-30,32,WHITE);
	LCD_DrawVLine(x+36+48+11,y+24+5-30,32,WHITE);
}

void Show_KeyMap(void)//»­Êý×Ö¼üÅÌ
{
	touch.PID=1;
	
	LCD_Clear(2,20,236,99,BLACK);
	
	LCD_Clear(0,160,240,300,BLUE);
	
	LCD_DrawTitleBar(title);
	LCD_DrawEdit(input);
	
	LCD_DrawHLine(0,160,240,BLACK);
	LCD_DrawHLine(0,220,240,BLACK);
	LCD_DrawHLine(0,280,240,BLACK);
	LCD_DrawHLine(0,340,180,BLACK);
	LCD_DrawHLine(0,399,240,BLACK);
	
	LCD_DrawVLine(60,160,180,BLACK);
	LCD_DrawVLine(120,160,240,BLACK);
	LCD_DrawVLine(180,160,180,BLACK);
	
	Set_Color(BLUE,WHITE);
	
	LCD_DrawKeyNum(1,0,160);
	LCD_DrawKeyNum(2,60,160);
	
	LCD_DrawKeyNum(3,120,160);
	LCD_DrawKeyNum(0,180,160);
	
	LCD_DrawKeyNum(4,0,220);
	LCD_DrawKeyNum(5,60,220);
	LCD_DrawKeyNum(6,120,220);
	LCD_DrawKeyNum(10,180,220);
	
	LCD_DrawKeyNum(7,0,280);
	LCD_DrawKeyNum(8,60,280);
	LCD_DrawKeyNum(9,120,280);
	
	LCD_DrawKeyDel(0,340);
	LCD_DrawKeyOK(120,340);	
	
	Set_Cursor(8,132);
}

