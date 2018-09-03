#include "iostm8S105C6.h"  // include header files already defined in IAR compiler
#include "intrinsics.h"  // to execute" __enable_interrupt" and "__disable_interrupt" intrinsic functions
int data,F=0  ;      // global integer is defined as it has to be used in both main function and interrupt handler function
long int  dig=0;  // dig value to be printed on lcd 
void asiic(int);
void delay(int n)
{
  int i , j ;
   for( i=n;i>0;i-- )
   {for ( j=100; j>0 ;j-- );
   }
}
void sendcommand()    // to send the command to lcd 
{
 PA_ODR_bit.ODR3 = 0;  // make RS bit high 
 PD_ODR = data;  // put the command on LCD data line 
 PA_ODR_bit.ODR4 =1;  // make EN high 
 PA_ODR_bit.ODR4 = 0;  // make EN low 
 delay(50);  // delay to settle down LCD
}
#pragma vector = 8   // 
__interrupt void EXTI_PORTC_IRQHandler(void) // "__interrupt" is a function attribute it 
{                                            // adds an attribute to the function that it 
 // int high, low ;  
  if(F==0)
  { TIM2_CR1_CEN = 1;  // start timer counter 
  F = 1;}  
   else 
   {
     TIM2_CR1_CEN = 0;  // stop timer counter
                
     //high = TIM2_CNTRH;
     //low = TIM2_CNTRL ;
     //TIM2_CNTRH = 0;
     //TIM2_CNTRL = 0 ;
  //dig = 256*(high)+low ; 
   F = 0;
   }
    
}
void Timer2_start()  // TIMER INITIALIZATIONS
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
TIM2_PSCR = 0x01;   
//TIM2_PSCR = 0;
TIM2_ARRH  = 0x0f;  
TIM2_ARRL  = 0x5f;  
TIM2_IER_UIE = 1;
//TIM2_CR1_UDIS = 1;
//TIM2_CR1_URS = 1;
TIM2_CR1_CEN = 1;       // start the timer
}
#pragma vector = TIM2_OVR_UIF_vector
__interrupt void TIM2_UPD_OVF_IRQHandler(void)
{  // int high, low ;
   TIM2_CR1_CEN = 0;
                                // neither receive nor pass any argument
  
    dig++ ; 
  TIM2_SR1_UIF = 0;
  TIM2_CR1_CEN = 1;
}
void write_lcd()
{
  PA_ODR_bit.ODR3 = 1;
 PD_ODR = data;
 PA_ODR_bit.ODR4 =1;
 PA_ODR_bit.ODR4 = 0; 
 delay(50);
}
void setout()
{
    PA_DDR = 0xff;   
    PA_ODR = 0;             //
    PA_CR2 = 0xff;          //
    PA_CR1 = 0xff;          //  
                            //  
    PD_DDR = 0xff;
    PD_ODR = 0;             //
    PD_CR1 = 0xff;          //  
    PD_CR2 = 0xff;
     PC_ODR = 0;             //  All pins are turned off.
    PC_DDR = 0xff;          //  All pins  are outputs.
    PC_CR1 = 0xff;          //  Push-Pull outputs.
    PC_CR2 = 0xff;          //  Output speeds upto 10 MHz.
    //
    
    //
    PC_DDR_DDR4 = 0;        //  PC4 is input.
    PC_CR1_C14 = 0;         //  PC4 is floating input.
     EXTI_CR1_PCIS = 2;      //  Interrupt on falling edge
    EXTI_CR2_TLIS = 0;      //  Falling edge only.   
    
}
void set_lcd()      // TO START THE LCD
{
  delay(2000);  // initial delay for lcd to settle down
  data = 0x3C;  // to get 5 x 7 matrix and cursor
  sendcommand();
  data = 0x0E;  // to make lcd on 
  sendcommand();
  PD_ODR = 0x06;  // to right shift the cursor 
  sendcommand();
  data = 0x80;  //to set starting position for cursor
  sendcommand();
   data = 0x46; //ascii value of "F"
  write_lcd();
  data = 0x52; //ascii value of "R"
  write_lcd();
  data = 0x45; //ascii value of "E"
  write_lcd();
  data = 0x51; //ascii value of "Q"
  write_lcd();
  data = 0x3D; //ascii value of "="
  write_lcd();
}
void asiic(int k)    // this function returns the ascii value of each digit to be printed on 
{                          // LCD
 switch(k)
		{
                case 0:
		data = 0x30;  //ascii value of "0"
	        break;              
		case 1:
		data = 0x31; //ascii value of "1"
                break;
		case 2:
		data = 0x32;  //ascii value of "2"
		break;
		case 3:
		data = 0x33;   //ascii value of "3"
		break;
		case 4:
		data = 0x34;  //ascii value of "4"
		break;
		case 5:         
		data = 0x35;   //ascii value of "5"
                break;
                case 6:
		data = 0x36;
                break;
		case 7:
		data = 0x37;
	        break;
                case 8:
		data = 0x38;
		break;
		case 9:
		data = 0x39;
	        break;
               
                }


}
/*void set_beep()
{
  BEEP_CSR_bit.BEEPDIV=0x0E; //beep div factor = 16
  BEEP_CSR_bit.BEEPSEL=0x10; // beep sel for 2
  BEEP_CSR_bit.BEEPEN=1;
}*/
void main()
{ __disable_interrupt();
  //long int temp;
  setout();
  set_lcd();
  //set_beep();
  Timer2_start();
  //temp = dig ;
  __enable_interrupt();
   while (1)
   {  long int temp ;             // LOGIC TO PRINT THE DIGITS 
     temp = dig ;
      int j,k=0,l[16] ;            // DEFINE AN ARRAY OF 16 SIZE
      for(j=0;j<=15;j++)
      {
        k = temp%10;         // PARSE THE LAST DIGIT OF A NUMBER ONE BY ONE 
        
        if(temp != 0)       // STORE THAT NUM IN THE ARRAY AND THEN PRINT ALL THE NUMBERS IN THAT 
        {l[j] = k;
        temp = temp/10;           // ARRAY ONE BY ONE 
        }
        else{
          break;
        }
      }
      data = 0xC2;                // SET THE CURSOR IN THE SECOND LINE OF LCD 
      sendcommand();
      for(j=j-1;j>=0;j--)           // PRINT THE NUMBERS PRESENT IN THE ARRAY 
      { 
        asiic(l[j]); 
        write_lcd();
      
      }
      
  
    }
  
}
