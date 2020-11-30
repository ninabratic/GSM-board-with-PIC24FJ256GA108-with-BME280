#include "Common.h"

void clock_init(){
    
    RCONbits.SWDTEN = 0;
    CLKDIVbits.DOZEN = 0;
    CLKDIVbits.DOZE = 0;
    CLKDIVbits.RCDIV = 0;
    CLKDIVbits.ROI = 0;
}