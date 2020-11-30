#ifndef USART_H
#define	USART_H

#ifdef	__cplusplus
extern "C" {
#endif

#define BAUDRATE 9600
#define RECEIVE_BUFFER_LENGHT 100

void USART_init();
void USART_send_char (unsigned char data);
void USART_send_string (char *data);
unsigned char parse_buffer(char * bufferWhere,const char * bufferWhat);
void clear_buffer();

extern char receiveBuffer[RECEIVE_BUFFER_LENGHT];
extern volatile unsigned int temp_received;
extern volatile unsigned int i;
extern unsigned int state;

#ifdef	__cplusplus
}
#endif

#endif	/* USART_H */

