#include <LPC21xx.H>                     /* LPC21xx definitions               */
#include "Serial.h"

#define CR     0x0D


/* implementation of putchar (also used by printf function to output data)    */


char uart0_getkey (void)  {                     /* Read character from Serial Port   */

  while (!(U0LSR & 0x01));

  return (U0RBR);
}

int uart1_getkey (void)  {                     /* Read character from Serial Port   */

  while (!(U1LSR & 0x01));

  return (U1RBR);
}

void uart1_init()
{
  PINSEL0 = (PINSEL0 & ~(3 << 16)) | (1 << 16);
  PINSEL0 = (PINSEL0 & ~(3 << 18)) | (1 << 18);
  /* initialize the serial interface   */
  //PINSEL0 = 0x00050000;           /* Enable RxD1 and TxD1                     */
  U1LCR = 0x83;                   /* 8 bits, no Parity, 1 Stop bit            */
  U1DLL = 0x5E;                     /* 9600 Baud Rate @ 15MHz VPB Clock         */
  U1LCR = 0x03;                   /* DLAB = 0                                 */
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send character 1 time via UART1-----------------------//
//------------------------------------------------------------------------------------------------//
void uart1_putc(char c)
{
	while(!(U1LSR & 0x20)); // Wait until UART1 ready to send character     
	U1THR = c;  // Send character
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send string via UART1---------------------------------//
//------------------------------------------------------------------------------------------------//
void uart1_puts(char *p)
{
	while(*p) // Point to character
	{
		uart1_putc(*p++);   // Send character then point to next character
	}
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for Initial UART0 ----------------------------------------//
//------------------------------------------------------------------------------------------------//
void uart0_init()
{
  PINSEL0 = (PINSEL0 & ~(3 << 0)) | (1 << 0);
  PINSEL0 = (PINSEL0 & ~(3 << 2)) | (1 << 2);

  	U0LCR=0x83;
		U0FDR=0xF1;
		U0DLL=110;
  	U0DLM=0x01;	  // Baud Rate 9600;
		U0LCR &=0x0F;
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send character 1 time via UART0-----------------------//
//------------------------------------------------------------------------------------------------//
void uart0_putc(char c)
{
	while(!(U0LSR & 0x20)); // Wait until UART0 ready to send character  
	U0THR = c; // Send character
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send string via UART1---------------------------------//
//------------------------------------------------------------------------------------------------//
void uart0_puts(char *p)
{
	while(*p) // Point to character
	{
		uart0_putc(*p++);  // Send character then point to next character
	}
}
