
#include <iostm8S105c6.h>
#include <intrinsics.h>
void delay(long int n)   
{
  long int i , j ;
   for( i=n;i>0;i-- )
   {for ( j=10; j>0 ;j-- );
   }
}
void initSPI(void)
{
  
    SPI_CR1_SPE = 0;  // DISABLE SPI 
    SPI_CR1_CPOL = 0;
    SPI_CR1_CPHA = 0;
    SPI_CR1_BR = 7;
    SPI_CR1_MSTR = 1;
    SPI_ICR_TXIE = 0;
    SPI_CR1_LSBFIRST = 0;
    SPI_CR2_BDM = 0;
    SPI_CR2_RXONLY = 0;
   // SPI_CR2_CRCEN = 0;
    SPI_CR2_SSM = 0;
    SPI_CR1_SPE = 1;
  
    
   
}
/*void txUART(unsigned char *str)
{
    unsigned char *msg = str;
    while (*msg)
    {
        UART2_DR = (unsigned char) *msg;     // load one character to the data registor 
        while (UART2_SR_TXE == 0);          //  wait for complete transmission 
        msg++;                               //  increase pointer to point to  next charater in the array 
    }
}*/
void main()
{
    __disable_interrupt();
   // CLK_CKDIVR = 0;   
    PA_DDR = 0xff;   
    PA_ODR = 0;             //
    PA_CR2 = 0xff;          //
    PA_CR1 = 0xff; 
    initSPI();
    PA_ODR_bit.ODR6=1;
    
    __enable_interrupt();
    SPI_DR = 0X0A;
    
    while (1)
    {
      if(SPI_SR_TXE == 1)
        if(SPI_SR_BSY == 0)
        {SPI_CR1_SPE = 0;
         PA_ODR_bit.ODR5=1;
         delay(1);
         PA_ODR_bit.ODR5=0;
         break;
        }
    }
    while (1);
}