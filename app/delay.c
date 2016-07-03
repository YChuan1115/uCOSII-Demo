#include "delay.h"

void DelayM(u8 n)
{
	u8 i;
	u16 j;
	for(i=0;i<n;i++)
		for(j=0;j<5000;j++);
}

void DelayN(u8 n)
{
	u8 i;
	u16 j;
	for(i=0;i<n;i++)
		for(j=0;j<20;j++);	
}


