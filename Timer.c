#include "Common.h"

volatile unsigned int sys_time = 0;
volatile unsigned char timer_flag = 0;
volatile unsigned int GSM_connectionCounter;
volatile unsigned int GSM_receive_data;
volatile unsigned int GSM_temp_timer;
volatile unsigned char GSM_timeout_timer;

void timer1_init(){
    
    T1CONbits.TON = 0;
	IFS0bits.T1IF = 0;

	T1CONbits.TSIDL = 1;
	T1CONbits.TGATE = 0;
	T1CONbits.TCKPS = 0;
	T1CONbits.TSYNC = 0;
	T1CONbits.TCS = 0;

	IPC0bits.T1IP = 1;
	IEC0bits.T1IE = 1;
    
    PR1 = ((double)FCY/1000); //Load the timer period value into the PR1 register, 155 and 156 page in datasheet 

	TMR1 = 0;

	T1CONbits.TON = 1;
}

void __attribute__ ((interrupt,no_auto_psv)) _T1Interrupt (void){
    
	TMR1 = 0;
    IFS0bits.T1IF = 0;  //Clear the interrupt flag		
    
    GSM_connectionCounter++;
    //sys_time++;

    /*if (sys_time == 2000) { //Wait 1 second
        sys_time = 0;
        timer_flag = 1;
    }*/
    
    if (GSM_connectionCounter == 5000){
        GSM_connectionCounter = 0;
        GSM_receive_data = 1;
    }
     
    if(GSM_temp_timer)
        GSM_temp_timer--;

    
    if (GSM_temp_timer == 0)
      GSM_timeout_timer = 1;   
}
