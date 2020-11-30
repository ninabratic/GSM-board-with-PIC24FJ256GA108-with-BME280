/* 
 * File:   Clock.h
 * Author: Nikolina
 *
 * Created on 26. oktobar 2020., 09.52
 */

#ifndef CLOCK_H
#define	CLOCK_H

#ifdef	__cplusplus
extern "C" {
#endif

#define FCY 16000000
#define FSCL 400000
    
#define __delay_ms(d) __delay32( (unsigned long) (d)*(FCY/1000))
#define __delay_us(d) __delay32( (unsigned long) (d)*(FCY/1000000))
    
void clock_init();

#ifdef	__cplusplus
}
#endif

#endif	/* CLOCK_H */

