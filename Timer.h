#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

extern volatile unsigned int sys_time;
extern volatile unsigned char timer_flag;
extern volatile unsigned int GSM_connectionCounter;
extern volatile unsigned int GSM_receive_data;
extern volatile unsigned int GSM_temp_timer;
extern volatile unsigned char GSM_timeout_timer;

extern void timer1_init();

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

