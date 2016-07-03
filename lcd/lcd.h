#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include "stm32f10x.h"

#define RST GPIO_Pin_11    //PA11 复位口
#define RD  GPIO_Pin_1	   //PA1  读数据
#define WR  GPIO_Pin_0	   //PA0  写数据
#define RS  GPIO_Pin_8	   //PA8  命令、数据选择
#define CS  GPIO_Pin_0     //PB0  片选
//#define DB_Port 				 //PB8-PB15数据口

#define WIDTH 240
#define HEIGHT 400

#define RED    0
#define GREEN  1
#define BLUE   2
#define YELLOW 3
#define PINK   4
#define ORANGE 5
#define PURPLE 6
#define GRAY   7
#define WHITE  8
#define BLACK  9

typedef struct
{
	u8 BC;
	u8 FC;
}COLOR;


void LCD_Init(void);
void Set_Read(void);
void Set_Write(void);
u16  LCD_Read(void);
void LCD_Write(u16 type,u16 data);
void Write_COM(u16 com);
void Write_DAT(u16 dat);
void Write_Reg(u16 reg,u16 dat);//写寄存器
void LCD_Config(void);
void LCD_Reset(void);
void LCD_SetPoint(u16 x,u16 y,u8 color);//写像素点
u16  LCD_GetPoint(u16 x,u16 y);//读像素点
void LCD_Clear(u16 x,u16 y,u16 w,u16 h,u8 color);
u16  Read_ID(void);//读设备ID 0xB509

void Set_Color(u8 bcolor,u8 fcolor);//设置背景色和前景色
COLOR Get_Color(void);
void Set_Area(u16 x1,u16 y1,u16 x2,u16 y2);//设置显示区域
void Set_Addr(u16 x,u16 y);//选择点

void Show_Char(char ch,u16 x,u16 y);//显示字体为8x16的字符
void Show_String(char *p,u16 x,u16 y);//显示字体为8x16字符串
void Show_Hex(u16 hex,u16 x,u16 y);//显示4位16进制数
void Show_Bin(u16 bin,u16 x,u16 y);//显示16位二进制数
void Show_Dec(u16 dec,u16 len,u16 x,u16 y);//显示指定位数的10进制数

void Clear(u8 color);

#endif



