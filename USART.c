#include "Common.h"

volatile unsigned int temp_received;
volatile unsigned int i;
unsigned int state;
char receiveBuffer[RECEIVE_BUFFER_LENGHT];

void USART_init(){
    
    U1MODEbits.RTSMD = 1;	// Bit11 Simplex Mode
    
    U1BRG = ( FCY/((double) 16 * BAUDRATE)) - 1;
    
    U1MODEbits.UARTEN = 1;	// And turn the peripheral on
    IPC2bits.U1RXIP = 1;
    U1STAbits.UTXEN = 1;
    
    IEC0bits.U1TXIE = 0;
	IEC0bits.U1RXIE = 1; 
    
    //GPIO USART Configuration
    TRISDbits.TRISD9 = 1;  //RX Input
    TRISDbits.TRISD10 = 0;  //TX Output
    
    //Assignment PINs for USART, use uart for debug
    //RPINR18bits.U1RXR = 26;
    //RPOR9bits.RP19R = 3;
 
    //Assignment PINs for USART
    RPINR18bits.U1RXR = 4;//PIN 43=RD9=RP4 RX za zelenu UART1
    RPOR1bits.RP3R = 3;//PIN 44=RD10=RP3 TX za zelenu UART1
}

void __attribute__((interrupt,no_auto_psv)) _U1RXInterrupt()
{
    IFS0bits.U1RXIF = 0;         
    temp_received = U1RXREG;
    
    for (i = 0; i < RECEIVE_BUFFER_LENGHT - 1; i++){
        receiveBuffer[i] = receiveBuffer[i+1];
    }
    receiveBuffer[RECEIVE_BUFFER_LENGHT - 1] = temp_received;
}

void clear_buffer(){
    
    int j;
    
    for (j = 0; j < RECEIVE_BUFFER_LENGHT; j++){
        receiveBuffer[j] = '0';
    }
}

unsigned char parse_buffer(char * bufferWhere,const char * bufferWhat){
    
    unsigned int result;
    char *ptrBuffer;
    
    ptrBuffer = strstr(bufferWhere, bufferWhat);
    
    if (ptrBuffer != NULL) 
        result = ptrBuffer - bufferWhere + 1;  
    
    else 
        result = 0;
     
    return result;
}

void USART_send_char (unsigned char data){
    
    while (!U1STAbits.TRMT);
    U1TXREG = data;
}

void USART_send_string(char *data){
  
  unsigned int i;
  for(i = 0; data[i]!='\0'; i++){
      
      while(!U1STAbits.TRMT);
      if(*data == 13) 
          USART_send_char(13);
      if(*data == 10) 
          USART_send_char(10);
      U1TXREG = data[i];
  }
}