#ifndef TOUCH_H
#define TOUCH_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define Xmin  650
#define Xmax	3930
#define Ymin	550
#define Ymax	3870

//引脚定义
//输入 笔中断信号
#define PEN   GPIO_Pin_5

//输入 数据输出
#define TDO		GPIO_Pin_4

//输入	忙状态
#define BUSY	GPIO_Pin_6

//输出 数据输入
#define TDI		GPIO_Pin_2

//输出 片选信号
#define TCS		GPIO_Pin_7

//输出 时钟信号
#define TCLK	GPIO_Pin_3

#define Touch_Pen()	  GPIO_ReadInputDataBit(GPIOA,PEN)
#define Is_Busy()     GPIO_ReadInputDataBit(GPIOA,BUSY)?1:0

void Touch_Init(void);//初始化
void SPI_Start(void);//SPI开始
void Touch_Write(u8 byte);//发送字节
u16  Touch_Read(void);//读取
u16  Read_AD(u8 cmd);//读取AD值
u16  Read_ADS(u8 cmd);//多次读取
u8   Read_XY(u16 *x,u16 *y);//读取坐标值
u8   Read_XY_2(u16 *x,u16 *y);//两次读取，提高准确率
u16  CalcXY(u16 ad,u8 xy);
u16  Get_Key(u16 pid,u16 x,u16 y);

#endif
