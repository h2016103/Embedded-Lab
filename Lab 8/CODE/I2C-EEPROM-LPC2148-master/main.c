/***************************************************************************************************************
 Project       : I2CLPC2148
 File					 : main.c
 Date          : May 2016
 Target      	 : LPC2148
 Description   : Functions related to the I2C EEPROM. The program reads and write the data in EEPROM through I2C
				  
****************************************************************************************************************/
#include <LPC214X.H>
#include <stdio.h>
#include "Type.h"

#include "i2c.h"

#include "lcd.h"
uint8 read_buffer[1];
extern int count;
//extern unsigned char main1(void);
extern void init_ext_interrupt(void);
__irq extern void Ext_ISR(void);
uint8 main2();
uint8 main2 (void) 
{ return (read_buffer[0]);
}

/***************************************************
Main function.
***************************************************/

int main(void)
{
	char read_buffer1[50];
	
	
	
	uint32 delay;
	
	PINSEL0 |= 0x00000005 ;
		
//	UART0_Init(); // Initialize UART0
	i2c_lpc_init(I2C_SPEED_100);		// Initialize I2C0
	//TIMER_Init();	// Initialize Timer
	
	init_lcd();
	
	//lcd_putstring(0, "eeprom");

	//for(delay=0;delay<=50000;delay++);
	
	m24xx_read(EEPROM_24XX256, 0 , 0 , (char *)read_buffer , sizeof(read_buffer));
	
	
init_ext_interrupt();   // initialize the external interrupt
	
	//UART0_Write_Text("********* LPC2148 ARM7 I2C EEPROM Demo **********\n\n\r");
	//UART0_Write_Text("Initialization done. \n\r\n");
	
	
	while(1)
	{ 
		
	//	y = main1();
   //write_buffer[0]=(uint8)y;
		 //write_buffer[1]=0;
			lcd_putstring(0, "eeprom");
		for(delay=0;delay<=50000;delay++);
		sprintf(read_buffer1, "Intrpt_cnt:%d ", count);
	lcd_putstring(1, (char *)read_buffer1);
  // lcd_putstring(1, read_buffer1);
		
		
	
			
//if (I2C_ReadFromEEPROM(0, read_buffer, 20))		// read from EEPROM
	
		
		for(delay=0;delay<=50000;delay++);
	
	read_buffer[0]= count;
	
		m24xx_write(EEPROM_24XX256, 0 , 0 , (char *)read_buffer , sizeof(read_buffer));
	
	}
	
	//return 0 ;
}
