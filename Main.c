#include "Common.h"

_CONFIG2(FNOSC_FRCPLL); //Fast RC Oscillator with Postscaler and PLL module with internal clock 8MHz
_CONFIG1(FWDTEN_OFF);   //Disable watchdog timer

int main(){
   
    clock_init();
    timer1_init();
    USART_init();
    I2C_init();
    
    state = CONNECTION_CHECK;
    
    controlRegisters_BME280();
    configRegister_BME280();
    
    while(1){
        
        readMeasurements_BME280();
        readCalibration_BME280();
        showTemperature_BME280();
        showPressure_BME280();
        showHumidity_BME280();
        
        GSM_sendingData();
       
    }
    return 0;
}
