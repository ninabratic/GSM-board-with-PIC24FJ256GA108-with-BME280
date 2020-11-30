#ifndef GSM_H
#define	GSM_H

#ifdef	__cplusplus
extern "C" {
#endif


#define CONNECTION_CHECK  0
#define SMS_FORMAT_DEFINE 1
#define SMS_LIST 2
#define SMS_READ 3
#define SMS_SEND 4
#define SMS_DELETE 5
    
extern unsigned int GSM_temp_modemConnection;
extern char message_index;
extern unsigned int temp_phone;
extern unsigned char number;
extern unsigned char phone_number[16];

void GSM_checking_connectionState ();
void GSM_check_modemConnection();
void GSM_defineSMS();
void GSM_modemSMS_list();
void GSM_modemSMS_read();
void GSM_modemSMS_send();
void GSM_modemSMS_delete();
void GSM_sendingData();

#ifdef	__cplusplus
}
#endif

#endif	/* GSM_H */

