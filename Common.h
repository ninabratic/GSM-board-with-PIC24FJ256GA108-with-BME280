#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <p24FJ256GA106.h> 
#include <p24fxxxx.h>
#include <libpic30.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include <xc.h>
    
#include "Timer.h"
#include "Clock.h"
#include "USART.h"
#include "I2C.h"
#include "BME280.h"
#include "GSM.h"
    
//Macros for SET, RESET, TOGGLE and READ bit
/*#define SBIT(PORTx,PINx) PORTx |= (1 << PINx)
#define RBIT(PORTx,PINx) PORTx& =~ (1 << PINx)
#define TBIT(PORTx,PINx) PORTx ^= (1 << PINx)
#define ReadBIT(PINx,PINnum) PINx &(1 << PINnum)*/
    
#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

