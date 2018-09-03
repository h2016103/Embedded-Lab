#include <iostm8S105c6.h>
#include <intrinsics.h>
void delay(long int n)   
{
  long int i , j ;
   for( i=n;i>0;i-- )
   {for ( j=100; j>0 ;j-- );
   }
}
void initUART(void)
{
  
   // unsigned char tmp = UART2_SR;
  //  tmp = UART2_DR;
    
    UART2_CR1 = 0;
    UART2_CR1_M = 0;        //  8 Data bits.
    UART2_CR1_PCEN = 0;     //  no parity bit used
    UART2_CR2 = 0;
    UART2_CR4 = 0;
    UART2_CR3 = 0;
    UART2_CR3_STOP = 0;     //  1 stop bit
    UART2_GTR = 0;
    UART2_PSCR = 0;
  
    
   // system clock is 16 MHz by default 
    
    UART2_BRR2 = 0x03;      //  Set the baud rate registers to 9600 baud
    UART2_BRR1 = 0x68;      
   
    UART2_CR2_TEN = 0;      //  initially  disable transmit bit 
    UART2_CR2_REN = 0;      //  initially  disable receive bit 
 
  
    UART2_CR2_TEN = 1; // make transmission enable bit high 
 
}
void txUART(unsigned char *str)
{
    unsigned char *msg = str;
    while (*msg)
    {
        UART2_DR = (unsigned char) *msg;     // load one character to the data registor 
        while (UART2_SR_TXE == 0);          //  wait for complete transmission 
        msg++;                               //  increase pointer to point to  next charater in the array 
    }
}
void main()
{
    __disable_interrupt();
    CLK_CKDIVR = 0;          
    PB_DDR = 0x00;         
    PB_CR1 = 0x00;          
    PB_CR2 = 0x00; 
    initUART();
    __enable_interrupt();
    while (1)
    {
      int n ;
      static int npre = 96; // random value assign only one time to npre integer 
      n =  PB_IDR;
      if (n == npre)
        continue;
      else
      {  npre = n ;
      switch(n)
      {
      case 0:
        txUART("PB.0 = low\n\r");
        txUART("PB.1 =low\n\r");
        break;
      case 1:
        txUART("PB.0 = high\n\r");
        txUART("PB.1 =low\n\r");
        break;
      case 2:
         txUART("PB.0 = low\n\r");
         txUART("PB.1 =high\n\r");
         break;
      case 3:
         txUART("PB.0 = high\n\r");
         txUART("PB.1 =high\n\r");
         break;
      }
      delay(10000);
    }
   }
}
