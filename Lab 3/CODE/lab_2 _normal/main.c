#include "iostm8S105C6.h"  // include header files already defined in IAR compiler
#include "intrinsics.h"  // to execute" __enable_interrupt" and "__disable_interrupt" intrinsic functions
int count= 0 , ldnum=0;      // global integer is defined as it has to be used in both main function and interrupt handler function
void delay(unsigned int n)
{
    while (n-- > 0);
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
    PA_ODR = 0x00;             //
    PA_CR2 = 0xff;          //
    PA_CR1 = 0xff;          //  
                            //  
    PG_DDR = 0xff;
    PG_ODR = 0x00;             //
    PG_CR1 = 0xff;          //  
    PG_CR2 = 0xff;          //  

}

#pragma vector = ADC1_EOC_vector
__interrupt void ADC1_EOC_IRQHandler()
{
    int low, high , read;
    ADC_CSR_EOC = 0;
    low = ADC_DRL;
    high = ADC_DRH;
    read = ((high*256)+low) ;                    //logic for conversion 
    //read = read << 8;
   // read = read | low ; 
   //----------------------- // make proper led glow //---------------------------//
    if ( read >= 0 && read <= 50)
    { 
      ldnum =1;
    }                                         
     else if ( read >= 50 && read <= 100)
    { 
       ldnum =1;                                         //pwm wave 2 at port A3      
    }   
    else if ( read >= 100 && read <= 150)
    { 
       ldnum =1;                      //pwm wave 3 at port A3
    }   
    else if ( read >= 150 && read <= 200)
    {  ldnum=0;
       PA_ODR_bit.ODR3=1;                  //high at port A3
    }   
    else if ( read >= 200 && read <= 250)
    {  ldnum=2;
      PA_ODR_bit.ODR3=1;                                         // high port A3
      TIM1_PSCRH = 0X0F;
      TIM1_PSCRL = 0XFF;                                     // pwm wave 1 at port A4        
    }   
    else if ( read >=250 && read <= 300)
    { ldnum=2;
      PA_ODR_bit.ODR3=1;                                      // high port A3
      TIM1_PSCRH = 0X00;
      TIM1_PSCRL = 0XFF;                                     // pwm wave 2 at port A4   
    }   
     else if ( read >=300 && read <= 350)
    {    ldnum=2;
        PA_ODR_bit.ODR3=1;                                         // high port A3
      TIM1_PSCRH = 0X00;
      TIM1_PSCRL = 0X0F;                                     // pwm wave 3 at port A4   
    }   
    else if ( read >= 350 && read <= 400)
    { ldnum=0;
      PA_ODR_bit.ODR3=1;                      // high port A3 A4
       PA_ODR_bit.ODR4=1;                                      
      
    }   
    else if ( read >= 400 && read <= 450)
    {
      ldnum=3;
      PA_ODR_bit.ODR3=1;                     // high port A3 A4
      PA_ODR_bit.ODR4=1;                     // pwm wave 1 at port A5                        
      TIM1_PSCRH = 0X0F;
      TIM1_PSCRL = 0XFF;
    }   
    else if ( read >= 450 && read <= 500)
    {
       ldnum=3;
       PA_ODR_bit.ODR3=1;                     // high port A3 A4
       PA_ODR_bit.ODR4=1;      
       TIM1_PSCRH = 0X00;
      TIM1_PSCRL = 0XFF;                                    // pwm wave 2 at port A5    
    }   
    else if ( read >= 500 && read <= 550)
    { 
      ldnum=3;
      PA_ODR_bit.ODR3=1;                     // high port A3 A4
      PA_ODR_bit.ODR4=1;   
      TIM1_PSCRH = 0X00;
      TIM1_PSCRL = 0X0F;                                     // pwm wave 3 at port A5  
    }   
   
  else if ( read >= 550 && read <= 600)
    {
      ldnum=0;
      PA_ODR_bit.ODR3=1;              
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5
                              
    }  
    else if ( read >= 600 && read <= 650)
    {
      ldnum=4;
      PA_ODR_bit.ODR3=1;              
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5
      TIM1_PSCRH = 0X0F;
      TIM1_PSCRL = 0XFF;                                        // pwm wave 1 at port A6    
    }   
    else if ( read >= 650 && read <= 700)
    {
      ldnum=4;
      PA_ODR_bit.ODR3=1;                     // high port A3 A4 A5
      PA_ODR_bit.ODR4=1;     
      TIM1_PSCRH = 0X00;
      TIM1_PSCRL = 0XFF;                                     // pwm wave 2 at port A6 
    }   
    else if ( read >= 700 && read <= 750)
    {
      ldnum=4;
        PA_ODR_bit.ODR3=1;   
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5
      PA_ODR_bit.ODR5=1;                      // pwm wave 3 at port A6               
      TIM1_PSCRH = 0X00;
      TIM1_PSCRL = 0X0F; 
    
    }   
    else if ( read >= 750 && read <= 800)
    {
      ldnum=0;
        PA_ODR_bit.ODR3=1;   
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5 A6
      PA_ODR_bit.ODR5=1;            
      PA_ODR_bit.ODR6=1;                                        
    }   
    else if ( read >= 800 && read <= 850)
    {
      ldnum=5;
      PA_ODR_bit.ODR3=1;   
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5 A6
      PA_ODR_bit.ODR5=1;     
      PA_ODR_bit.ODR6=1; 
      TIM1_PSCRH = 0X0F;
      TIM1_PSCRL = 0XFF;                                 // pwm wave 1 at port G0
    }   
     else if ( read >= 850 && read <= 900)
    {
      ldnum=5;
       PA_ODR_bit.ODR3=1;   
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5 A6
      PA_ODR_bit.ODR5=1;    
      PA_ODR_bit.ODR6=1;                        // pwm wave 2 at port G0
      TIM1_PSCRH = 0X00;
      TIM1_PSCRL = 0XFF;
    }   
    else if ( read >= 900 && read <= 950)
    {
      ldnum=5;
      PA_ODR_bit.ODR3=1;   
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5 A6
      PA_ODR_bit.ODR5=1;        
      PA_ODR_bit.ODR6=1;                       // pwm wave 3 at port G0
      TIM1_PSCRH = 0X00;
      TIM1_PSCRL = 0X0F;
    }   
    else if ( read >=950 && read <= 1023)
    {
      ldnum=0;
     PA_ODR_bit.ODR3=1;   
      PA_ODR_bit.ODR4=1;                      // high port A3, A4 ,A5 A6 G0
      PA_ODR_bit.ODR5=1;    
     PG_ODR_bit.ODR0=1; 
      PA_ODR_bit.ODR6=1;
    }   
  
}
void blink_led()
{
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
}
void SetupADC()
{   ADC_CR1_ADON = 1;       //  switch on the  ADC      
    delay(30000);
    ADC_CSR_CH = 0x04;      //   channel  AIN4 is selected
    ADC_CR2_ALIGN = 1;      //   right alignment used.
    ADC_CR1_CONT = 1;                        // continuous mode activated
    ADC_CSR_EOCIE = 1;      //  enable  interrupt again
}
void main()
{
   
    __disable_interrupt();   // intrinsic function calling for fast execution
    PD_ODR = 0;             //  All pins are turned off.
    PD_DDR = 0xff;          //  All pins except PD4 are outputs.
    PD_CR1 = 0xff;          //  Push-Pull outputs.
    PD_CR2 = 0xff;          //  Output speeds upto 10 MHz.
    //
    //  Now configure the input pin.
    //
    PD_DDR_DDR4 = 0;        //  PD4 is input.
    PD_CR1_C14 = 0;         //  PD4 is floating input.
    //
    //  Set up the interrupt.
    //
    EXTI_CR1_PDIS = 2;      //  Interrupt on falling edge
    EXTI_CR2_TLIS = 0;      //  Falling edge only.
                        // set up ADC
    SetupADC();
    setoutport();
     ADC_CR1_ADON = 1;
     delay(20000);
    //Timer1_start();
    __enable_interrupt();   // intrinsic function calling for fast execution
//------------------------------  MAIN LOOP --------------------------------------------------------------------      
    while (1)
    {
       __wait_for_interrupt();
    
    }
}
