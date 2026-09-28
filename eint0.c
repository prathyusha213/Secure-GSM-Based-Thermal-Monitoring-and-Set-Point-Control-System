#include <LPC21xx.h>

#include "types.h"
#include "defines.h"
#include "menu.h"

#define EINT0_PIN      16	
#define EINT0_VIC_CHNO 14	

void eint0_isr(void) __irq
{
	DisplayMenu();
	implementMenu();
	EXTINT |= (1<<0);
	VICVectAddr = 0;
}	


void  Enable_EINT0(void)
{
	PINSEL1 = ((PINSEL1&~(3<<0))|(1<<0));
	VICIntEnable |= (1<<EINT0_VIC_CHNO);
	VICVectCntl0 = ((1<<5) | EINT0_VIC_CHNO);
	VICVectAddr0 = (unsigned int)eint0_isr;
	EXTMODE	|= (1<<0);
	EXTPOLAR = 0X00;
}


