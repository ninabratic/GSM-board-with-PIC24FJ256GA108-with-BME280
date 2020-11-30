#include "Common.h"

unsigned int GSM_temp_modemConnection;
char message_index;
unsigned int temp_phone;
unsigned char number;
unsigned char phone_number[16];

void GSM_checking_connectionState (){
    
    if (GSM_timeout_timer){
            
        GSM_timeout_timer = 0;
        state = CONNECTION_CHECK;
    }
          
    clear_buffer();
    __delay_ms(500);
}

void GSM_check_modemConnection(){
    
    USART_send_string("AT\r");   //Starting A Command Line
        
    GSM_temp_timer = 2000;
    GSM_timeout_timer = 0;
    GSM_temp_modemConnection = 0;
   
    while((parse_buffer(receiveBuffer, "OK") == 0) && (GSM_timeout_timer == 0)) ;  //Wait "OK" as an answer
        
    GSM_temp_modemConnection = parse_buffer(receiveBuffer, "OK");                  //Returns the index in which part of the array it is located "OK"
 
    if(GSM_temp_modemConnection != 0)  
        state = SMS_FORMAT_DEFINE;              
                        
    GSM_checking_connectionState();     
}

void GSM_defineSMS(){
    
    USART_send_string("AT+CMGF=1\r"); //Format SMS message as a text
         
    GSM_temp_timer = 3000;
    GSM_timeout_timer = 0;
    GSM_temp_modemConnection = 0;
   
    while((parse_buffer(receiveBuffer, "OK")==0) && (GSM_timeout_timer == 0)) ;
    
    GSM_temp_modemConnection = parse_buffer(receiveBuffer, "OK");
    //USART_send_string("OK\r");
    if(GSM_temp_modemConnection != 0) 
        state = SMS_LIST;     
       
    GSM_checking_connectionState();
}

void GSM_modemSMS_list(){
    
    USART_send_string("AT+CMGL=ALL\r"); //List all messages
   
    GSM_temp_timer = 5000;
    GSM_timeout_timer = 0;
    GSM_temp_modemConnection = 0;
   
    while((parse_buffer(receiveBuffer, "REC UNREAD") == 0) && (GSM_timeout_timer == 0));
      
    GSM_temp_modemConnection = parse_buffer(receiveBuffer,"REC UNREAD");

    message_index = receiveBuffer[GSM_temp_modemConnection - 4];
                
    state = SMS_READ;
        
    GSM_checking_connectionState();              
    __delay_ms(500);
}

void GSM_modemSMS_read(){
    
    USART_send_string("AT+CMGR="); //Read message
    USART_send_char(message_index);
    USART_send_char('\r');
  
    GSM_temp_timer = 5000;
    GSM_timeout_timer = 0;
    GSM_temp_modemConnection = 0;
   
    while((parse_buffer(receiveBuffer,"Info") == 0) && (GSM_timeout_timer == 0));
      
    GSM_temp_modemConnection = parse_buffer(receiveBuffer, "Info");
                
    if(GSM_temp_modemConnection != 0){
            
        temp_phone = parse_buffer(receiveBuffer,",\"+");
        state = SMS_SEND;               
    }
                
    for(number = 0; number < 16; number++){   //Initialize a array to store a received phone number
        
        phone_number[number] = 0;             //Set all members of the array to 0
    }
                
    for(number = 0; receiveBuffer[temp_phone + number] != ','; number++){
        
        phone_number[number] = receiveBuffer[temp_phone + number];  //Storage number of received mobile phone
    }
               
    GSM_checking_connectionState();
}

void GSM_modemSMS_send(){
    
    USART_send_string("AT+CNMI=1,0,0,0,1\r"); //New Message Indications To Terminal Equipment
    __delay_ms(100);
            
    clear_buffer();
        
    USART_send_string("AT+CMGS=");           //Send SMS message
    
    const char* phoneNumber = (const char*) phone_number;
            
    for(number = 0; number < strlen(phoneNumber); number++){
        
        USART_send_char(phone_number[number]);  //Send number of mobile phone on UART terminal
    }
       
    USART_send_char('\r');
                
    GSM_temp_timer = 1000;
    GSM_timeout_timer = 0;
    GSM_temp_modemConnection = 0;
            
    while((parse_buffer(receiveBuffer, ">") == 0) && (GSM_timeout_timer == 0));
         
    GSM_temp_modemConnection = parse_buffer(receiveBuffer,">");
            
    if(GSM_temp_modemConnection != 0){ //In this loop everything will be send via SMS
        
        USART_send_string("Current Temperature: ");
        USART_send_string(temp_buffer);
        USART_send_char('\r');
        USART_send_string("Pressure: ");
        USART_send_string(press_buffer);
        USART_send_char('\r');
        USART_send_string("Humidity: ");
        USART_send_string(hum_buffer);
        USART_send_char('\r');
       
        USART_send_char(26);
    }
            
    GSM_temp_timer = 10000;
    GSM_timeout_timer = 0;
    GSM_temp_modemConnection = 0;
           
    while((parse_buffer(receiveBuffer,"OK")==0) && (GSM_timeout_timer == 0));
         
    GSM_temp_modemConnection = (parse_buffer(receiveBuffer, "OK"));
            
    if(GSM_temp_modemConnection != 0)
        state = SMS_DELETE;
            
    GSM_checking_connectionState();
}

void GSM_modemSMS_delete(){
    
    USART_send_string("AT+CMGD="); //Delete message
    USART_send_char(message_index);
    USART_send_char('\r');
                  
    GSM_temp_timer = 2000;
    GSM_timeout_timer = 0;
    GSM_temp_modemConnection = 0;
   
    while((parse_buffer(receiveBuffer, "OK") == 0) && (GSM_timeout_timer == 0));
   
    GSM_temp_modemConnection = parse_buffer(receiveBuffer, "OK");
                
    if(GSM_temp_modemConnection != 0)
        state = CONNECTION_CHECK;
                
    GSM_checking_connectionState();
}

void GSM_sendingData(){
    
    switch(state){
        
        case CONNECTION_CHECK:
                
            GSM_check_modemConnection();   
            break;
            
        case SMS_FORMAT_DEFINE:
                
            GSM_defineSMS();
            break;
            
        case SMS_LIST:
            
            GSM_modemSMS_list();
            break;
            
        case SMS_READ:
                
            GSM_modemSMS_read();    
            break;
            
        case SMS_SEND:
                
            GSM_modemSMS_send();
            break;
            
        case SMS_DELETE:
                
            GSM_modemSMS_delete();     
            break;
            
        default:
                    
            state = CONNECTION_CHECK;
    }         
}
