#include "includes.h"

extern COLOR     color;
extern TOUCH_KEY touch;
extern CURSOR    cursor;

TITLE title1={20,RED,BLUE,"Main User Interface"};
TEXT  text1={4,30,GRAY,BLACK,"Seted Val:"};
TEXT  text2={4,56,GRAY,BLACK,"Total Num:"};
TEXT  text3={4,92,GRAY,BLACK,"Current Progress:"};
TEXT  text4={4,132,GRAY,BLACK,"Total Progress:"};
TEXT  text5={4,180,GRAY,BLACK,"Elapsed Time:"};
TEXT  text6={110,180,GRAY,BLACK,"00:00:00"};
BUTTON button1={10,220,220,48,"Start",5,BLACK};
BUTTON button2={10,300,220,48,"Setting",7,BLACK};
EDIT   edit1={84,28,148,20,BLACK};
EDIT   edit2={84,54,148,20,BLACK};
PROG   prog1={4,110,190,10,BLACK,ORANGE,0};
PROG   prog2={4,150,190,10,BLACK,ORANGE,0};


void Show_Main(u16 v1,u16 v2,u16 v3,u8 f)
{
	touch.PID=0;
	Set_Color(GRAY,BLACK);
	LCD_Clear(0,0,240,400,color.BC);
	
	LCD_DrawRec(0,0,240,400,BLUE);
	LCD_DrawRec(1,1,238,398,BLUE);
	
	LCD_DrawTitleBar(title1);
	LCD_DrawText(text1);
	LCD_DrawEdit(edit1);
	LCD_DrawText(text2);
	LCD_DrawEdit(edit2);
	
	LCD_DrawText(text3);
	LCD_DrawProg(prog1);
	LCD_DrawText(text4);
	LCD_DrawProg(prog2);
	
	LCD_DrawText(text5);
	LCD_DrawText(text6);
	
	LCD_DrawButton(button1);
	LCD_DrawButton(button2);
	
  if(f)
	{
		Set_Color(WHITE,BLACK);
		Show_Dec(v1,4,112,30);
		Show_Dec(v2,4,172,30);
		Show_Dec(v3,4,142,56);
	}
	
}

