#include "iostm8S105C6.h"  // include header files already defined in IAR compiler
#include "intrinsics.h"  // to execute" __enable_interrupt" and "__disable_interrupt" intrinsic functions
int count= 0 , ldnum=0;      // global integer is defined as it has to be used in both main function and interrupt handler function
void delay(int n)
{
  int i , j ;
   for( i=n;i>0;i-- )
   {for ( j=100; j>0 ;j-- );
   }
}
void set_leds()
{
   switch(count)
		{
                case 0:
		PD_ODR_bit.ODR0=0; // structure named PD_ODR_bit is used 
                                 //    structure must be defined in the header file 
	        break;              // to manipulate each bit of ODR register 
		case 1:
		PD_ODR_bit.ODR0=1; 
               
	        break;
		case 2:
		PD_ODR_bit.ODR1=1;
                
		break;
		case 3:
		PD_ODR_bit.ODR2=1;
                
		break;
		case 4:
		PD_ODR_bit.ODR3=1;
               
		break;
		case 5:
		PD_ODR_bit.ODR0 = 0;  // make all leds off 
                PD_ODR_bit.ODR1 = 0;  
                PD_ODR_bit.ODR2 = 0;
                PD_ODR_bit.ODR3 = 0;
                count = 0;   // again initialize count variable to zero 
               
	        break;
                }
}

#pragma vector = 8   // 
__interrupt void EXTI_PORTD_IRQHandler(void) // "__interrupt" is a function attribute it 
{                                            // adds an attribute to the function that it 
    count++;                           // neither receive nor pass any argument 
   set_leds();
}
void setoutport()
{ 
    PA_DDR = 0xff;   
    PA_ODR = 0;             //
    PA_CR2 = 0xff;          //
    PA_CR1 = 0xff;          //  
                            //  
    PG_DDR = 0xff;
    PG_ODR = 0;             //
    PG_CR1 = 0xff;          //  
    PG_CR2 = 0xff;          //  

}

#pragma vector = ADC1_EOC_vector
__interrupt void ADC1_EOC_IRQHandler()
{
    int low, high , read;
    ADC_CSR_EOC = 0; //make eoc bit low 
    low = ADC_DRL;
    high = ADC_DRH;
    read = high ;                    //logic for conversion 
    read = read << 8;
    read = read | low ; 
   //----------------------- // make proper led glow //---------------------------//
    if ( read >= 0 && read <= 10)
    { PA_ODR_bit.ODR3 = 0;
      PA_ODR_bit.ODR4 = 0;  
      PA_ODR_bit.ODR5 = 0;
      PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
    }

     else if ( read > 11 && read <= 68)
    { ldnum=1;
      //PA_ODR_bit.ODR3 = 0;
      PA_ODR_bit.ODR4 = 0;  
      PA_ODR_bit.ODR5 = 0;
      PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
      TIM2_PSCR = 0x08;
       
    }                                         
     else if ( read >= 69 && read <= 136)
    { ldnum=1;
      PA_ODR_bit.ODR4 = 0;  
      PA_ODR_bit.ODR5 = 0;
      PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
       TIM2_PSCR = 0x06;                                //pwm wave 2 at port A3      
    }   
    else if ( read >= 137 && read <= 203)
    { ldnum=1;
      PA_ODR_bit.ODR4 = 0;  
      PA_ODR_bit.ODR5 = 0;
      PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
      TIM2_PSCR = 0x04;                                   //pwm wave 3 at port A3
    }   
    else if ( read == 204)
    {  ldnum=0;
       PA_ODR_bit.ODR3=1;                  //high at port A3
      PA_ODR_bit.ODR4 = 0;  
      PA_ODR_bit.ODR5 = 0;
      PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
    }   
    else if ( read >= 205 && read <= 270)
    {  ldnum=2;
      PA_ODR_bit.ODR3=1;                                         // high port A3
      //PA_ODR_bit.ODR4 = 0;  
      PA_ODR_bit.ODR5 = 0;
      PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
      TIM2_PSCR = 0x08;                                   // pwm wave 1 at port A4        
    }   
    else if ( read >=270 && read <= 336)
    { ldnum=2;
      PA_ODR_bit.ODR3=1;                                      // high port A3
      // PA_ODR_bit.ODR4 = 0;  
      PA_ODR_bit.ODR5 = 0;
      PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
      TIM2_PSCR = 0x06;                                 // pwm wave 2 at port A4   
    }   
     else if ( read >=337 && read <= 402)
    {    ldnum=2;
        PA_ODR_bit.ODR3=1;                                         // high port A3
         // PA_ODR_bit.ODR4 = 0;  
      PA_ODR_bit.ODR5 = 0;
      PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
      TIM2_PSCR = 0x04;                                // pwm wave 3 at port A4   
    }   
    else if ( read == 403)
    { ldnum=0;
      PA_ODR_bit.ODR3=1;                      // high port A3 A4
       PA_ODR_bit.ODR4=1;                                       
      PA_ODR_bit.ODR5 = 0;
      PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
    }   
    else if ( read >= 404 && read <= 470)
    {
      ldnum=3;
      PA_ODR_bit.ODR3=1;                     // high port A3 A4
      PA_ODR_bit.ODR4=1;                     // pwm wave 1 at port A5                        
      //PA_ODR_bit.ODR4 = 0;  
      //PA_ODR_bit.ODR5 = 0;
      PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
      TIM2_PSCR = 0x08;
    }   
    else if ( read >= 471 && read <= 536)
    {
       ldnum=3;
       PA_ODR_bit.ODR3=1;                     // high port A3 A4
       PA_ODR_bit.ODR4=1;      
      // PA_ODR_bit.ODR4 = 0;  
     // PA_ODR_bit.ODR5 = 0;
      PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
      TIM2_PSCR = 0x06;                                   // pwm wave 2 at port A5    
    }   
    else if ( read >= 537 && read <= 600)
    { 
      ldnum=3;
      PA_ODR_bit.ODR3=1;                     // high port A3 A4
      PA_ODR_bit.ODR4=1;   
      //  PA_ODR_bit.ODR4 = 0;  
     // PA_ODR_bit.ODR5 = 0;
      PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
      TIM2_PSCR = 0x04;                                    // pwm wave 3 at port A5  
    }   
   
  else if ( read ==601 )
    {
      ldnum=0;
      PA_ODR_bit.ODR3=1;              
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5
       // PA_ODR_bit.ODR4 = 0;  
      PA_ODR_bit.ODR5 = 1;
      PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;                        
    }  
    else if ( read >= 602 && read <= 668)
    {
      ldnum=4;
      PA_ODR_bit.ODR3=1;              
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5
      // PA_ODR_bit.ODR4 = 0;  
      PA_ODR_bit.ODR5 = 1;
     // PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
     TIM2_PSCR = 0x08;                                       // pwm wave 1 at port A6    
    }   
    else if ( read >= 669 && read <= 733)
    {
      ldnum=4;
      PA_ODR_bit.ODR3=1;                     // high port A3 A4 A5
      PA_ODR_bit.ODR4=1;     
       //PA_ODR_bit.ODR4 = 0;  
      PA_ODR_bit.ODR5 = 1;
      //PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
      TIM2_PSCR = 0x06;                                   // pwm wave 2 at port A6 
    }   
    else if ( read >= 734 && read <= 799)
    {
      ldnum=4;
        PA_ODR_bit.ODR3=1;   
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5
      PA_ODR_bit.ODR5=1;                      // pwm wave 3 at port A6               
       // PA_ODR_bit.ODR4 = 0;  
    //  PA_ODR_bit.ODR5 = 0;
     // PA_ODR_bit.ODR6 = 0;
      PG_ODR_bit.ODR0 = 0;
     TIM2_PSCR = 0x04;
    
    }   
    else if ( read == 800)
    {
      ldnum=0;
        PA_ODR_bit.ODR3=1;   
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5 A6
      PA_ODR_bit.ODR5=1;            
      PA_ODR_bit.ODR6=1;                                        
      PG_ODR_bit.ODR0 = 0;
    }   
    else if ( read >= 801 && read <= 866)
    {
      ldnum=5;
      PA_ODR_bit.ODR3=1;   
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5 A6
      PA_ODR_bit.ODR5=1;     
      PA_ODR_bit.ODR6=1; 
      TIM2_PSCR = 0x08;                                 // pwm wave 1 at port G0
    }   
     else if ( read >= 867 && read <= 931)
    {
      ldnum=5;
       PA_ODR_bit.ODR3=1;   
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5 A6
      PA_ODR_bit.ODR5=1;    
      PA_ODR_bit.ODR6=1;                        // pwm wave 2 at port G0
      TIM2_PSCR = 0x06;
    }   
    else if ( read >= 932 && read <= 1010)
    {
      ldnum=5;
      PA_ODR_bit.ODR3=1;   
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5 A6
      PA_ODR_bit.ODR5=1;        
      PA_ODR_bit.ODR6=1;                       // pwm wave 3 at port G0
      TIM2_PSCR = 0x04;
    }   
    else if ( read >= 1010 && read <= 1023)
    {
      ldnum=0;
     PA_ODR_bit.ODR3=1;   
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5 A6 G0
      PA_ODR_bit.ODR5=1;    
     PG_ODR_bit.ODR0=1; 
      PA_ODR_bit.ODR6=1;
    }   
  
}

void Timer2_start()
{
TIM2_CCER1 = 0;
TIM2_CCER2 = 0;
TIM2_CCER1 = 0;
TIM2_CCER2 = 0;
TIM2_CR1 = 0;               
TIM2_IER = 0; 
//TIM2_IER_UIE = 1;       //  update interrupt enable to generate interrupt after counter overflow 
TIM2_SR2 = 0;
TIM2_CCMR1 = 0;
TIM2_CCMR2 = 0;
TIM2_CCMR3 = 0;
TIM2_CNTRH = 0;   //counter register value start with zero
TIM2_CNTRL = 0;
TIM2_CCR1H = 0;
TIM2_CCR1L = 0;
TIM2_CCR2H = 0;
TIM2_CCR2L = 0;
TIM2_CCR3H = 0;
TIM2_CCR3L = 0;
TIM2_SR1 = 0;       
TIM2_PSCR = 0x08;   
//TIM2_PSCR = 0;
TIM2_ARRH  = 0x0f;  // random preload values are used
TIM2_ARRL  = 0x5f;  // start counting with  upto end 65535
TIM2_IER_UIE = 1;
TIM2_CR1_CEN = 1;       // start the timer
}
#pragma vector = TIM2_OVR_UIF_vector
__interrupt void TIM2_UPD_OVF_IRQHandler(void)
{

// Timer 1 interrupt handler
  switch(ldnum)
    {
    case 0 :
      
      break;
    case 1:
      PA_ODR_bit.ODR3= !PA_ODR_bit.ODR3; 
      break;
     case 2 :
      PA_ODR_bit.ODR4= !PA_ODR_bit.ODR4; 
      break;
    case 3 :
      PA_ODR_bit.ODR5= !PA_ODR_bit.ODR5; 
      break;
    case 4 :
      PA_ODR_bit.ODR6= !PA_ODR_bit.ODR6; 
      break;
    case 5 :
      PG_ODR_bit.ODR0= !PG_ODR_bit.ODR0; 
      break;
      }
   TIM2_SR1_UIF = 0;  //zeroth bit (update interrupt flag of status flag registor
}
void SetupADC()
{   ADC_CR1_ADON = 1;       //  switch on the  ADC      
    ADC_CSR_CH = 0x04;      //   channel  AIN4 is selected,PB4 is used 
    ADC_CR2_ALIGN = 1;      //   right alignment used.
    ADC_CR1_CONT = 1;       // continuous mode activated
    ADC_CSR_EOCIE = 1;      //  enable  interrupt again
}


void main()
{
   
    __disable_interrupt();   // intrinsic function calling for fast execution
    PD_ODR = 0;             //  All pins are turned off.
    PD_DDR = 0xff;          //  All pins high
    PD_CR1 = 0xff;          //  Push-Pull outputs.
    PD_CR2 = 0xff;          //  Output speeds upto 10 MHz.
    
    PD_DDR_DDR4 = 0;        //  PD4  input.
    PD_CR1_C14 = 0;         // make PD4 floating input.
    
    EXTI_CR1_PDIS = 2;      //  Interrupt on falling edge
    EXTI_CR2_TLIS = 0;      //  Falling edge only.
                        // set up ADC
     setoutport();
    SetupADC();
    delay(3000);
     Timer2_start();
     ADC_CR1_ADON = 1;
     delay(4000);
    __enable_interrupt();   // intrinsic function calling for fast execution
//------------------------------  MAIN LOOP --------------------------------------------------------------------      
    while (1)
    {
       __wait_for_interrupt();
  
    }
}

