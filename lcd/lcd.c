#include "includes.h"
#include "char.h"

#define RD_0	GPIO_ResetBits(GPIOA,RD);//RD=0
#define RD_1	GPIO_SetBits(GPIOA,RD);//RD=1
#define WR_0	GPIO_ResetBits(GPIOA,WR);//WR=0
#define WR_1	GPIO_SetBits(GPIOA,WR);//WR=1
#define RS_0	GPIO_ResetBits(GPIOA,RS);//RS=0д����
#define RS_1	GPIO_SetBits(GPIOA,RS);//RS=1д����
#define CS_0	GPIO_ResetBits(GPIOB,CS);//CS=0
#define CS_1	GPIO_SetBits(GPIOB,CS);//CS=1
#define RST_0	GPIO_ResetBits(GPIOA,RST);//RST=0
#define RST_1	GPIO_SetBits(GPIOA,RST);//RST=1

extern COLOR color;

char HEX[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

u16 colors[10]=
{
	0xf800,//��ɫ
	0x07e0,//��ɫ
	0x001f,//��ɫ
	0xffe0,//��ɫ
	0xf81f,//�ۺ�
	0xfc08,//��ɫ
	0x801f,//��ɫ
	0x8430,//��ɫ
	0xffff,//��ɫ
	0x0000,//��ɫ
};

void LCD_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=CS|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|\
															GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=RST|RD|WR|RS;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void Set_Read(void)//��IO������Ϊ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|\
															GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void Set_Write(void)//��IO������Ϊд
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|\
															GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

u16 Read_ID(void)//���豸ID
{
	Write_COM(0x0000);
	return LCD_Read();
}

u16 LCD_Read()//������
{
	vu16 high,low;
	high=low=0x0000;
	
	CS_0;
	RS_1;
	WR_1;
	RD_0;
	Set_Read();
	RD_0;
	DelayN(2);
	high=GPIOB->IDR&0xff00;//��8λ��ȷ 0xB500
	RD_1;

	RD_0;
	DelayN(2);
	low=GPIOB->IDR&0xff00;
	low>>=8;							//��8λ���ܲ���ȷ�����������ݾ����䶯
	RD_1;

	CS_1;
	Set_Write();
	return (high|low);
}

void LCD_Write(u16 type,u16 data)//LCDд����type 0:���� 1:����
{
	if(type==0)//д����
	{
		RS_0;//RS=0д����
	}
	else
	{
		RS_1;//RS=1д����
	}
	CS_0;//CS=0
	RD_1;//RD=1
	WR_0;//WR=0
	GPIOB->BSRR=data&0xff00;
	GPIOB->BRR=(~data)&0xff00;
	WR_1;//WR=1
	WR_0;//WR=0
	GPIOB->BSRR=(data<<8)&0xff00;
	GPIOB->BRR=((~data)<<8)&0xff00;
	WR_1;//WR=1
	CS_1;//CS=1
}

void Write_COM(u16 com)//д����
{
	LCD_Write(0,com);
}

void Write_DAT(u16 dat)//д����
{
	LCD_Write(1,dat);
}

void Write_Reg(u16 reg,u16 dat)//д�Ĵ���
{
	Write_COM(reg);
	Write_DAT(dat);
}

void LCD_Reset()//LCD��λ
{
	RST_1;
	DelayM(5);
	RST_0;
	DelayM(5);
	RST_1;
	DelayM(5);
}

void LCD_Config()//LCD����
{
	LCD_Init();
	LCD_Reset();
	CS_0;//CS=0 ��Ƭѡ
	Write_Reg(0x0000,0x0000);
	Write_Reg(0x0000,0x0000);
	Write_Reg(0x0000,0x0000);
	Write_Reg(0x0000,0x0000);
	DelayM(2);
	Write_DAT(0x0000);
	Write_DAT(0x0000);
	Write_DAT(0x0000);
	Write_DAT(0x0000);
	DelayM(2);
	Write_Reg(0x0008,0x0808);
	Write_Reg(0x0400,0x6200);
	
	Write_Reg(0x0300,0x0c0c);
	Write_Reg(0x0301,0xff13);
	Write_Reg(0x0302,0x0f0f);
	Write_Reg(0x0303,0x150b);
	Write_Reg(0x0304,0x1020);
	Write_Reg(0x0305,0x0a0b);
	Write_Reg(0x0306,0x0003);
	Write_Reg(0x0307,0x0d06);
	Write_Reg(0x0308,0x0504);
	Write_Reg(0x0309,0x1030);
	
	Write_Reg(0x0010,0x001b);
	Write_Reg(0x0011,0x0101);
	Write_Reg(0x0012,0x0000);
	Write_Reg(0x0013,0x0001);

	Write_Reg(0x0100,0x0330);
	Write_Reg(0x0101,0x0247);
	Write_Reg(0x0103,0x1000);
	Write_Reg(0x0280,0xbf00);
	Write_Reg(0x0102,0xd1b0);
	DelayM(5);
	Write_Reg(0x0001,0x0100);
	Write_Reg(0x0002,0x0100);
	Write_Reg(0x0003,0x1030);
	Write_Reg(0x0009,0x0001);
	Write_Reg(0x000c,0x0000);
	Write_Reg(0x0090,0x8000);
	Write_Reg(0x000f,0x0000);
	
	Write_Reg(0x0210,0x0000);
	Write_Reg(0x0211,0x00ef);
	Write_Reg(0x0212,0x0000);
	Write_Reg(0x0213,0x018f);
	
	Write_Reg(0x0500,0x0000);
	Write_Reg(0x0501,0x0000);
	Write_Reg(0x0502,0x005f);
	Write_Reg(0x0401,0x0001);
	Write_Reg(0x0404,0x0000);
	DelayM(2);
	Write_Reg(0x0007,0x0100);
	DelayM(5);
	Write_Reg(0x0200,0x0000);
	Write_Reg(0x0201,0x0000);
	DelayM(2);
	Write_COM(0x0202);
	DelayM(2);
	CS_1;
}

void LCD_Clear(u16 x,u16 y,u16 w,u16 h,u8 color)//��ָ������ɫ���һ������
{
	u16 i;
	u16 j;
	Set_Area(x,y,x+w-1,y+h-1);//������ʾ����
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			Write_DAT(colors[color]);
		}
	}
}

void Set_Addr(u16 x,u16 y)//ѡ��ĳһ��
{
	Set_Area(x,y,x,y);
}

void LCD_SetPoint(u16 x,u16 y,u8 color)//��ָ������ɫ���ĳһ���ص�
{
	Set_Addr(x,y);
	Write_DAT(colors[color]);
}

u16 LCD_GetPoint(u16 x,u16 y)//��ȡĳ���ص����ɫֵ
{
	u16 pixel=0;
	Set_Addr(x,y);
	LCD_Read();
	DelayN(2);
	pixel=LCD_Read();
	return pixel;
}

void Set_Color(u8 bcolor,u8 fcolor)//���ñ���ɫ��ǰ��ɫ
{
	color.BC=bcolor;
	color.FC=fcolor;
}
COLOR Get_Color(void)
{
	COLOR co;
	co.BC=color.BC;
	co.FC=color.FC;
	return co;
}

void Set_Area(u16 x1,u16 y1,u16 x2,u16 y2)//������ʾ����
{
	Write_Reg(0x0200,x1);
	Write_Reg(0x0201,y1);//�����������
	
	Write_Reg(0x0210,x1);
	Write_Reg(0x0211,x2);//��ʾ����
	Write_Reg(0x0212,y1);
	Write_Reg(0x0213,y2);
	Write_COM(0x0202);
}

void Show_Char(char ch,u16 x,u16 y)//��ָ����λ����ʾһ���ַ��������СΪ8x16
{
	u16 temp;
	u16 i,j;
	ch=ch-32;
	if(x+7>239||ch=='\n')
	{
		y=y+16;
		x=0;
	}
	Set_Area(x,y,x+7,y+15);
	for(i=0;i<16;i++)
	{
		temp=F8x16[ch][i];
		for(j=0;j<8;j++)
		{
			if(temp&0x80)
			{
				Write_DAT(colors[color.FC]);
			}
			else
			{
				Write_DAT(colors[color.BC]);
			}
			temp<<=1;
		}
	}
}

void Show_String(char *p,u16 x,u16 y)//��ָ��λ����ʾ�ַ����������С8x16
{
	while(*p!='\0')
	{
		Show_Char(*p,x,y);
		x+=8;
		p++;
	}	
}

void Show_Hex(u16 hex,u16 x,u16 y)//��ָ��λ����ʾ4λ16�������������С8x16
{
	u16 i,tmp,offset=16;
	unsigned char h[4];
	for(i=0;i<4;i++)
	{
		offset=offset-4;
		tmp=(hex>>offset)&0x000f;
		h[i]=HEX[tmp];
	}
	Show_String("0x",x,y);
	x+=16;
	for(i=0;i<4;i++)
	{
		Show_Char(h[i],x,y);
		x+=8;
	}
}

void Show_Bin(u16 bin,u16 x,u16 y)//��ָ��λ����ʾ16λ�Ķ��������������С8x16
{
	u16 i;
	unsigned char b[16];
	for(i=0;i<16;i++)
	{
		if(bin&0x8000)
			b[i]=1;
		else
			b[i]=0;
		bin<<=1;
	}
	for(i=0;i<16;i++)
	{
		Show_Char(HEX[b[i]],x,y);
		x+=8;
	}
	
}

void Show_Dec(u16 dec,u16 len,u16 x,u16 y)//��ָ��λ����ʾһ���5λ��ʮ�������������С8x16
{
	unsigned char d[5];
	u16 i;
	switch(len)
	{
		case 1: d[0]=dec;break;
		case 2: d[0]=dec/10;d[1]=dec%10;break;
		case 3: d[0]=dec/100;d[1]=(dec%100)/10;d[2]=(dec%100)%10;break;
		case 4: d[0]=dec/1000;d[1]=(dec%1000)/100;d[2]=((dec%1000)%100)/10;d[3]=((dec%1000)%100)%10;break;
		case 5: d[0]=dec/10000;d[1]=(dec%10000)/1000;d[2]=((dec%10000)%1000)/100;d[3]=(((dec%10000)%1000)%100)/10;d[4]=(((dec%10000)%1000)%100)%10;break;
	}
	for(i=0;i<len;i++)
	{
		Show_Char(HEX[d[i]],x,y);
		x+=8;
	}
}

void Clear(u8 color)//���ˢ��
{
	u16 i,j;
	for(i=0;i<400;i++)
	{
		for(j=0;j<240;j++)
		{
			LCD_SetPoint(j,i,color);
		}
	}
}






