#include<lpc21xx.h>
#include"defines.h"
#include"Interrupts.h"
#include"types.h"
extern u32 eint0_flag,eint1_flag;
void Enable_EINT0(void)
{
	CFGPIN(PINSEL0,1,FUNC4);
	SSETBIT(VICIntEnable,14);
	VICVectCntl0=0x20|14;
	VICVectAddr0=(unsigned)eint0_isr;
	SCLRBIT(EXTINT,0);
  SETBIT(EXTMODE,0);
  SETBIT(EXTPOLAR,0);
}

void Enable_EINT1(void)
{
	CFGPIN(PINSEL0,3,FUNC4);
	SSETBIT(VICIntEnable,15);
	VICVectCntl1=0x20|15;
	VICVectAddr1=(unsigned)eint1_isr;
	SCLRBIT(EXTINT,1);
  SETBIT(EXTMODE,1);
  SETBIT(EXTPOLAR,1);	
}


void eint0_isr(void) __irq
{
    eint0_flag++;
    eint1_flag=0;
	SSETBIT(EXTINT,0);//clear EINT0 flag
	VICVectAddr=0;//dummy write to clear 
	              //interrupt flag in VIC	
}

void eint1_isr(void) __irq
{
    eint1_flag++;
    eint0_flag=0;
	SSETBIT(EXTINT,1);//clear EINT1 flag
	VICVectAddr=0;//dummy write;

}	
