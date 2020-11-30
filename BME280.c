#include "Common.h"

long int dig_T1, dig_T2, dig_T3;
long int dig_P1, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
long int dig_H1, dig_H2, dig_H3, dig_H4, dig_H5, dig_H6;

unsigned char temp_msb, temp_lsb, temp_xlsb;
unsigned char press_msb, press_lsb, press_xlsb;
unsigned char hum_msb, hum_lsb;

long adc_t, adc_p, adc_h, t_fine;

long temp_T1, temp_T2, temp_T3, temp_T4;

char temp_buffer[16];
char press_buffer[16];
char hum_buffer[16];

unsigned char getID_BME280(){
    
    unsigned char chip_id;
    
    writeRegister_I2C(BME280_I2C_WRITE, BME280_CHIP_ID_ADRESS);
    chip_id = readRegister_I2C(BME280_I2C_READ);
    
    return chip_id;
}

void controlRegisters_BME280(){  
    
    unsigned char ctrl_hum;
       
    writeRegisters_I2C(BME280_I2C_WRITE, BME280_CTRL_MEAS_REG, OVERSAMPLING_CONTROL_REG); //Measurement control register
    writeRegister_I2C(BME280_I2C_WRITE, BME280_CTRL_HUM_REG); //Humidity control register
   
    ctrl_hum = readRegister_I2C(BME280_I2C_READ);
    writeRegisters_I2C(BME280_I2C_WRITE, BME280_CTRL_HUM_REG, ctrl_hum | 0b00000001); //Only write on three low bits
}

void configRegister_BME280(){
    
    writeRegisters_I2C(BME280_I2C_WRITE, BME280_CONFIG_REG, OVERSAMPLING_CONFIG_REG);
}

void readCalibration_BME280(){
    
    char msb, lsb;
    
    //Digital temperature 1
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_TEMPERATURE_CALIB_DIG_T1_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_T1 = (unsigned int) msb;
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_TEMPERATURE_CALIB_DIG_T1_LSB_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_T1 = (dig_T1 << 8) + lsb;
    
    //Digital temperature 2
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_TEMPERATURE_CALIB_DIG_T2_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_T2 = (unsigned int) msb;
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_TEMPERATURE_CALIB_DIG_T2_LSB_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_T2 = (dig_T2 << 8) + lsb;
    
    //Digital temperature 3
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_TEMPERATURE_CALIB_DIG_T3_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_T3 = (unsigned int) msb;
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_TEMPERATURE_CALIB_DIG_T3_LSB_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_T3 = (dig_T3 << 8) + lsb;
    
    //Digital pressure 1
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P1_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_P1 = (unsigned int) msb;
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P1_LSB_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_P1 = (dig_P1 << 8) + lsb;
    
    //Digital pressure 2
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P2_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_P2 = (int) msb;
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P2_LSB_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_P2 = (dig_P2 << 8) + lsb;
    
    //Digital pressure 3
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P3_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_P3 = (int) msb;
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P3_LSB_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_P3 = (dig_P3 << 8) + lsb;
    
    //Digital pressure 4
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P4_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_P4 = (int) msb;
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P4_LSB_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_P4 = (dig_P4 << 8) + lsb;
    
    //Digital pressure 5
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P5_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_P5 = (int) msb;
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P5_LSB_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_P5 = (dig_P5 << 8) + lsb;
    
    //Digital pressure 6
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P6_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_P6 = (int) msb;
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P6_LSB_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_P6 = (dig_P6 << 8) + lsb;
    
    //Digital pressure 7
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P7_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_P7 = (int) msb;
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P7_LSB_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_P7 = (dig_P7 << 8) + lsb;
    
    //Digital pressure 8
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P8_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_P8 = (int) msb;
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P8_LSB_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_P8 = (dig_P8 << 8) + lsb;
    
    //Digital pressure 9
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P9_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_P9 = (int) msb;
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_PRESSURE_CALIB_DIG_P9_LSB_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_P9 = (dig_P9 << 8) + lsb;
    
    //Digital humidity 1
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_HUMIDITY_CALIB_DIG_H1_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_H1 = (unsigned int) lsb;
    
    //Digital humidity 2
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_HUMIDITY_CALIB_DIG_H2_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_H2 = (unsigned int) msb;
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_HUMIDITY_CALIB_DIG_H2_LSB_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_H2 = (dig_H2 << 8) + lsb;
    
    //Digital humidity 3
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_HUMIDITY_CALIB_DIG_H3_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_H3 = (unsigned int) lsb;
    
    //Digital humidity 4
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_HUMIDITY_CALIB_DIG_H4_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_H4 = (unsigned int) msb;
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_HUMIDITY_CALIB_DIG_H4_LSB_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_H4 = (dig_H4 << 4) | (lsb & 0xF);
    
    //Digital humidity 5
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_HUMIDITY_CALIB_DIG_H5_MSB_REG);
    msb = readRegister_I2C(BME280_I2C_READ);
    dig_H5 = (unsigned int) msb;
    dig_H5 = (dig_H5 << 4) | (lsb >> 4);
    
    //Digital humidity 6
    writeRegister_I2C(BME280_I2C_WRITE ,BME280_HUMIDITY_CALIB_DIG_H6_REG);
    lsb = readRegister_I2C(BME280_I2C_READ);
    dig_H6 = (short int) lsb;
}

long compensateTemperature_BME280(){
    
    long temp1, temp2, T;

    temp1 = ((((adc_t >> 3) -((long)dig_T1 << 1))) * ((long)dig_T2)) >> 11;
    temp2 = (((((adc_t >> 4) - ((long)dig_T1)) * ((adc_t >> 4) - ((long)dig_T1))) >> 12) * ((long)dig_T3)) >> 14;
    t_fine = temp1 + temp2;
    T = (t_fine * 5 + 128) >> 8;
    
    return T;
}

unsigned long compensatePressure_BME280(){
    
    long press1, press2;
    unsigned long P;

    press1 = (((long)t_fine) >> 1) - (long)64000;
    press2 = (((press1 >> 2) * (press1 >> 2)) >> 11 ) * ((long)dig_P6);
    press2 = press2 + ((press1 * ((long)dig_P5)) << 1);
    press2 = (press2 >> 2)+(((long)dig_P4) << 16);
    press1 = (((dig_P3 * (((press1 >> 2) * (press1 >> 2)) >> 13 )) >> 3) + ((((long)dig_P2) * press1) >> 1)) >> 18;
    press1 =((((32768 + press1))*((long)dig_P1)) >> 15);
    
    if (press1 == 0) 
        return 0; //Avoid exception caused by division by zero
    
    P = (((unsigned long)(((long)1048576) - adc_p) - (press2 >> 12))) * 3125;
    if (P < 0x80000000) 
        P = (P << 1) / ((unsigned long)press1);
    else 
        P = (P / (unsigned long)press1) * 2;
    
    press1 = (((long)dig_P9) * ((long)(((P >> 3) * (P >> 3)) >> 13))) >> 12;
    press2 = (((long)(P >> 2)) * ((long)dig_P8)) >> 13;
    P = (unsigned long)((long)P + ((press1 + press2 + dig_P7) >> 4));
    return P;
}
unsigned long compensateHumidity_BME280(){
    
    long h1;
    h1 = (t_fine - ((long)76800));
    h1 = (((((adc_h << 14) - (((long)dig_H4) << 20) - (((long)dig_H5) * h1)) +
         ((long)16384)) >> 15) * (((((((h1 * ((long)dig_H6)) >> 10) * (((h1 *
         ((long)dig_H3)) >> 11) + ((long)32768))) >> 10) + ((long)2097152)) *
         ((long)dig_H2) + 8192) >> 14));
    
    h1 = (h1 - (((((h1 >> 15) * (h1 >> 15)) >> 7) * ((long)dig_H1)) >> 4));
    h1 = (h1 < 0 ? 0 : h1);
    h1 = (h1 > 419430400 ? 419430400 : h1);
    return (unsigned long)(h1 >> 12);
}

void readMeasurements_BME280(){

    //Read temperature measurements
    writeRegister_I2C(BME280_I2C_WRITE, BME280_TEMP_MSB);
    temp_msb = readRegister_I2C(BME280_I2C_READ);
    
    writeRegister_I2C(BME280_I2C_WRITE, BME280_TEMP_LSB);
    temp_lsb = readRegister_I2C(BME280_I2C_READ);
    
    writeRegister_I2C(BME280_I2C_WRITE, BME280_TEMP_XLSB);
    temp_xlsb = readRegister_I2C(BME280_I2C_READ);
    
    //Read pressure measurements
    writeRegister_I2C(BME280_I2C_WRITE, BME280_PRESS_MSB);
    press_msb = readRegister_I2C(BME280_I2C_READ);
    
    writeRegister_I2C(BME280_I2C_WRITE, BME280_PRESS_LSB);
    press_lsb = readRegister_I2C(BME280_I2C_READ);
    
    writeRegister_I2C(BME280_I2C_WRITE, BME280_PRESS_XLSB);
    press_xlsb = readRegister_I2C(BME280_I2C_READ);
    
    //Read humidity measurements
    writeRegister_I2C(BME280_I2C_WRITE, BME280_HUM_MSB);
    hum_msb = readRegister_I2C(BME280_I2C_READ);
    
    writeRegister_I2C(BME280_I2C_WRITE, BME280_HUM_LSB);
    hum_lsb = readRegister_I2C(BME280_I2C_READ);

    //Temperature values
    adc_t  = (unsigned long)temp_xlsb >> 4;
    adc_t |= (unsigned long)temp_lsb << 4;
    adc_t |= (unsigned long)temp_msb << 12;
    
    //Pressure values
    adc_p  = (unsigned long)press_xlsb >> 4;
    adc_p |= (unsigned long)press_lsb << 4;
    adc_p |= (unsigned long)press_msb << 12;
    
    //Humidity values
    adc_h = hum_lsb;
    adc_h |= (unsigned long)hum_msb << 8;
}

void showTemperature_BME280(){
    
    unsigned long temperature;
    
    temperature = compensateTemperature_BME280()/3;
            
    temp_T1 = temperature / 1000;
    temp_T2 = (temperature % 1000)/100;
    temp_T3 = ((temperature % 1000) % 100) / 10;
    temp_T4 = (((temperature % 1000) % 100) % 10);
 
    sprintf(temp_buffer, "%02u.%02u ", (unsigned int)(temperature/100), (unsigned int)(temperature%100));
}

void showPressure_BME280(){
    
    unsigned long pressure;
    
    pressure = compensatePressure_BME280();
    sprintf(press_buffer, "%lu Pa", pressure);
    
    //USART_send_string(press_buffer);
}

void showHumidity_BME280(){
    
    unsigned long humidity, calculated_humidity;
    
    humidity = compensateHumidity_BME280();
    calculated_humidity = humidity / 1000;
    sprintf(hum_buffer, "%lu", calculated_humidity);
    
   // USART_send_string(hum_buffer);
}