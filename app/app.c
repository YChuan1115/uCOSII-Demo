#include "includes.h"

//ÿ��������ĵ�ѹֵΪ0.98mv
#define VPG 0.98  

extern CURSOR    cursor;
extern TOUCH_KEY touch;
extern OS_EVENT  *PENIRQ;

extern BUTTON button1;
extern PROG   prog1;
extern PROG   prog2;
extern EDIT   input;

u16  VALUE1=0;
u16  VALUE2=0;
u16  VALUE3=0;

void Startup_Task(void *parg)
{
	Show_Main(0,0,0,0);
	Led_Off(0);
	Led_Off(1);
	OSTaskSuspend(CURSOR_TASK_PRIO);
	OSTaskSuspend(TIMER_TASK_PRIO);
	OSTaskSuspend(ADC_TASK_PRIO);
	OSTaskDel(STARTUP_TASK_PRIO);//�h���Լ�
}

void Led_Task(void *parg)
{
	for(;;)
	{
		Led_On(0);
		OSTimeDlyHMSM(0,0,1,500);
		Led_Off(0);
		OSTimeDlyHMSM(0,0,1,500);
	}
}

void ADC_Task(void *parg)
{
	u16 value[3];
	u16 arg;
	float v;
	u16 G;
	u16 n;
	(void)parg;
	for(;;)
	{
		value[0]=Get_ADC();//������ADֵ
		value[1]=Get_ADC();
		value[2]=Get_ADC();
		arg=(value[0]+value[1]+value[2])/3;
		v=(arg*5000)/65535;//ת���ɵ�ѹ
		G=(u16)(v/VPG);//������������λ�ˣ��ֱ���1g
		if(G==0)
		{
			Motor_On(1);//����ǿ����
			Motor_On(2);//����������
		}
		else
		{
			if(G>=VALUE1)//ǰ������
			{
				Motor_Off(1);//�ر�ǿ����
				if(G==VALUE2*0.99)//�����ﵽ�趨ֵ
				{
					Motor_Off(2);//�ر�������
					n++;
					prog2.per=n/VALUE3;
					LCD_DrawProg(prog2);
				}
			}
			prog1.per=G/VALUE2;
			LCD_DrawProg(prog1);
		}
		OSTimeDlyHMSM(0,0,0,250);
	}
}

void Cursor_Task(void *parg)//������ʾ��˸�Ĺ��
{
	COLOR ctmp;
	(void)parg;
	for(;;)
	{
		ctmp=Get_Color();
		Set_Color(WHITE,BLACK);
		Show_Char('|',cursor.x,cursor.y);
		Set_Color(ctmp.BC,ctmp.FC);
		OSTimeDlyHMSM(0,0,0,500);//��ʱ500ms
		ctmp=Get_Color();
		Set_Color(WHITE,BLACK);
		Show_Char(' ',cursor.x,cursor.y);
		Set_Color(ctmp.BC,ctmp.FC);
		OSTimeDlyHMSM(0,0,0,500);//��ʱ500ms
	}
}

#ifndef TOUCH_CALIBRATION
void Input_Task(void *parg)
{
	u8 err;
	u8 OK=0;
	u8 buffer[4]={0};
	u8 LEN=0;
	u8 flag=0;
	u16 e=0;
	OS_CPU_SR cpu_sr;
	(void)parg;
	for(;;)
	{
		OSSemPend(PENIRQ,0,&err);
		Exti_Set(0);
		OS_ENTER_CRITICAL();
		touch.FLAG=Read_XY_2(&touch.AD_X,&touch.AD_Y);
		OS_EXIT_CRITICAL();
		if(touch.FLAG)
		{
			Led_On(1);
			touch.FLAG=0;
			touch.LCD_X=CalcXY(touch.AD_X,0);
			touch.LCD_Y=CalcXY(touch.AD_Y,1);
			touch.KEY=Get_Key(touch.PID,touch.LCD_X,touch.LCD_Y);
			if(touch.KEY<=10)
			{
				OS_ENTER_CRITICAL();
				Set_Color(WHITE,BLACK);
				if(touch.KEY==10)
					Show_Char('.',cursor.x,cursor.y);
				else
				{
					Show_Dec(touch.KEY,1,cursor.x,cursor.y);
					if(LEN<4)
					{
						buffer[LEN]=touch.KEY;
						LEN++;
					}
				}
				if(cursor.x<224)
				{
					cursor.x+=8;
					if(cursor.x>=224)
						cursor.x=224;
				}
				OS_EXIT_CRITICAL();
			}
		
			else if(touch.KEY==11)
			{
				OK++;
				if(OK==1)
				{
					VALUE1=CalcDec(buffer,LEN);
					Set_Color(BLACK,GREEN);
					Show_String(">>VALUE1:",2,22);
					Show_Dec(VALUE1,LEN,82,22);
					OS_ENTER_CRITICAL();
					LCD_Clear(4,121,232,38,WHITE);
					cursor.x=8;
					cursor.y=132;
					OS_EXIT_CRITICAL();
					buffer[0]=0;
					buffer[1]=0;
					buffer[2]=0;
					buffer[3]=0;
					LEN=0;
				}
				else if(OK==2)
				{
					VALUE2=CalcDec(buffer,LEN);
					Set_Color(BLACK,GREEN);
					Show_String(">>VALUE2:",2,38);
					Show_Dec(VALUE2,LEN,82,38);
					OS_ENTER_CRITICAL();
					LCD_Clear(4,121,232,38,WHITE);
					cursor.x=8;
					cursor.y=132;
					OS_EXIT_CRITICAL();
					buffer[0]=0;
					buffer[1]=0;
					buffer[2]=0;
					buffer[3]=0;
					LEN=0;
				}
				else if(OK==3)
				{
					VALUE3=CalcDec(buffer,LEN);
					Set_Color(BLACK,GREEN);
					Show_String(">>VALUE3:",2,54);
					Show_Dec(VALUE3,LEN,82,54);
					OS_ENTER_CRITICAL();
					LCD_Clear(4,121,232,38,WHITE);
					cursor.x=8;
					cursor.y=132;
					OS_EXIT_CRITICAL();
					buffer[0]=0;
					buffer[1]=0;
					buffer[2]=0;
					buffer[3]=0;
					LEN=0;
				}
			
				else if(OK==4)
				{
					if(VALUE2>0&&VALUE2<=5000)
					{
						if(VALUE1<VALUE2&&VALUE1>0)
						{
							if(VALUE3>0&&VALUE3<10000)
							{
								e=0;
								Set_Color(BLACK,GREEN);
								Show_String(">>OK!",2,70);
							}
							else
							{
								e=1;
							}
						}
						else
						{
							e=1;
						}
					}
					else
					{
						e=1;
					}

					if(e)	
					{
						Set_Color(BLACK,GREEN);
						Show_String(">>ERROR!",2,70);
					}
				}
				else if(OK==5)
				{
					if(!e)
					{
						OK=0;
						OSTaskSuspend(CURSOR_TASK_PRIO);
						Show_Main(VALUE1,VALUE2,VALUE3,1);
					}
					else
					{
						OK=0;
						e=0;
						LCD_Clear(2,20,236,100,BLACK);
						LCD_DrawEdit(input);
						Set_Cursor(8,132);
					}
					VALUE1=0;
					VALUE2=0;
					VALUE3=0;
				}
				else;
			}
		
			else if(touch.KEY==12)
			{
				OS_ENTER_CRITICAL();
			
				if(LEN>0)
				{
					LEN--;
				}
						
				if(cursor.x>=8) 
				{	
					LCD_Clear(cursor.x,cursor.y,8,16,WHITE);
					cursor.x-=8;
					if(cursor.x<8)
					{
						cursor.x=8;
					}
				}	
				OS_EXIT_CRITICAL();
			}
		
			else if(touch.KEY==13)
			{
				if(flag==0)
				{
					flag=1;
					button1.str="stop";
					button1.len=4;
					button1.line_color=GREEN;
					LCD_DrawButton(button1);
					OSTaskResume(TIMER_TASK_PRIO);
				}
				else
				{
					flag=0;
					button1.str="start";
					button1.len=5;
					button1.line_color=BLACK;
					LCD_DrawButton(button1);
					OSTaskSuspend(TIMER_TASK_PRIO);
				}
			}
		
			else if(touch.KEY==14)
			{
				OSTaskSuspend(TIMER_TASK_PRIO);
				Show_KeyMap();
				OSTaskResume(CURSOR_TASK_PRIO);
			}
			
			else if(touch.KEY==99)//�oЧݔ��
			{}
			else;
			OSTimeDlyHMSM(0,0,0,50);
			Led_Off(1);
		}
		Exti_Set(1);
	}
}

#endif

#ifdef TOUCH_CALIBRATION
void Input_Task(void *parg)
{
	u8 err;
	OS_CPU_SR cpu_sr;
	for(;;)
	{
		OSSemPend(PENIRQ,0,&err);
		Exti_Set(0);
		OS_ENTER_CRITICAL();
		touch.FLAG=Read_XY_2(&touch.AD_X,&touch.AD_Y);
		OS_EXIT_CRITICAL();
		if(touch.FLAG)
		{
			touch.FLAG=0;
			touch.LCD_X=CalcXY(touch.AD_X,0);
			touch.LCD_Y=CalcXY(touch.AD_Y,1);
			Set_Color(BLACK,GREEN);
			Show_String(">>AD_X:",2,22);
			Show_Dec(touch.AD_X,4,58,22);
			Show_String("AD_Y:",98,22);
			Show_Dec(touch.AD_Y,4,138,22);
			
			Show_String(">>LCD_X:",2,38);
			Show_Dec(touch.LCD_X,4,66,38);
			Show_String("LCD_Y:",106,38);
			Show_Dec(touch.LCD_Y,4,154,38);
		}
		Led_Off(1);
	}
}

#endif



//��ʱ����
void Timer_Task(void *parg)//��ʱ����,�ɿ�ʼ��ť����
{
	u8 h=0,m=0,s=0;
	(void)parg;
	for(;;)
	{
		OSTimeDlyHMSM(0,0,1,0);
		Set_Color(GRAY,BLACK);
		s++;
		if(s==60)
		{
			s=0;
			m++;
			if(m==60)
			{
				h++;
				if(h==100)
				{
					h=0;
				}
				Show_Dec(h,2,110,180);
			}
			Show_Dec(m,2,134,180);
		}
		Show_Dec(s,2,158,180);
	}
}


u16 CalcDec(u8 *p,u8 len)
{
	u16 dec;
	switch(len)
	{
		case 0:dec=0;break;
		case 1:dec=p[0];break;
		case 2:dec=p[0]*10+p[1];break;
		case 3:dec=p[0]*100+p[1]*10+p[2];break;
		case 4:dec=p[0]*1000+p[1]*100+p[2]*10+p[3];break;
		default:break;
	}
	return dec;
}

