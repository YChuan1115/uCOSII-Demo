#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include "stm32f10x.h"

#define RST GPIO_Pin_11    //PA11 ��λ��
#define RD  GPIO_Pin_1	   //PA1  ������
#define WR  GPIO_Pin_0	   //PA0  д����
#define RS  GPIO_Pin_8	   //PA8  �������ѡ��
#define CS  GPIO_Pin_0     //PB0  Ƭѡ
//#define DB_Port 				 //PB8-PB15���ݿ�

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
void Write_Reg(u16 reg,u16 dat);//д�Ĵ���
void LCD_Config(void);
void LCD_Reset(void);
void LCD_SetPoint(u16 x,u16 y,u8 color);//д���ص�
u16  LCD_GetPoint(u16 x,u16 y);//�����ص�
void LCD_Clear(u16 x,u16 y,u16 w,u16 h,u8 color);
u16  Read_ID(void);//���豸ID 0xB509

void Set_Color(u8 bcolor,u8 fcolor);//���ñ���ɫ��ǰ��ɫ
COLOR Get_Color(void);
void Set_Area(u16 x1,u16 y1,u16 x2,u16 y2);//������ʾ����
void Set_Addr(u16 x,u16 y);//ѡ���

void Show_Char(char ch,u16 x,u16 y);//��ʾ����Ϊ8x16���ַ�
void Show_String(char *p,u16 x,u16 y);//��ʾ����Ϊ8x16�ַ���
void Show_Hex(u16 hex,u16 x,u16 y);//��ʾ4λ16������
void Show_Bin(u16 bin,u16 x,u16 y);//��ʾ16λ��������
void Show_Dec(u16 dec,u16 len,u16 x,u16 y);//��ʾָ��λ����10������

void Clear(u8 color);

#endif



