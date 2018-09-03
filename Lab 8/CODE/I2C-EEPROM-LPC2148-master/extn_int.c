/************************************************************/
/* PROJECT NAME: EXTERNAL INTERRUPT	                       	*/
/* Device:       LPC2148                										*/
/* Filename:     ExtInt.c                                   */
/* Language:     C                      	                	*/
/* Compiler:     Keil ARM				                						*/
/* For more detail visit www.binaryupdates.com		        	*/
/************************************************************/

#include <LPC214x.H>  
#include "type.h"
void delay1(int count);
void init_ext_interrupt(void);
__irq void Ext_ISR(void);

int count;
extern uint8 main2(void);

int main1 (void) 
{ return (count);
	
}


void init_ext_interrupt()  // Initialize Interrupt
{
  EXTMODE = 0x4; 		//Edge sensitive mode on EINT2
  
  EXTPOLAR &= ~(0x4); 	//Falling Edge Sensitive

  PINSEL0 |= 0x80000000; //Select Pin function P0.15 as EINT2
  
  /* initialize the interrupt vector */
  VICIntSelect &= ~ (1<<16);        	// EINT2 selected as IRQ 16
  VICVectAddr5 = (int ) Ext_ISR; // address of the ISR
  VICVectCntl5 = (1<<5) | 16;			// 
  VICIntEnable = (1<<16);           	// EINT2 interrupt enabled

  EXTINT &= ~(0x4);
   count = main2();	
}

__irq void Ext_ISR(void) // Interrupt Service Routine-ISR 
{
	//IO1DIR |= (1<<25);
	//IO1CLR |= (1<<25); 	 // Turn ON Buzzer
	//delay1(12000);
  //IO1SET |= (1<<25); 	 // Turn OFF Buzzer
  VICIntEnable= 0x00000000;
	delay1(40000);
	count++;
	EXTINT |= 0x4; 		 //clear interrupt
	VICVectAddr = 0; 	 // End of interrupt execution
	VICIntEnable = (1<<16); 
}

void delay1(int count)
{
  int j=0,i=0;

  for(j=0;j<count;j++)
  {
    /* At 60Mhz, the below loop introduces
    delay of 10 us */
    for(i=0;i<35;i++);
  }
}
