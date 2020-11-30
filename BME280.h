#ifndef BME280_H
#define	BME280_H

#ifdef	__cplusplus
extern "C" {
#endif


//Address for read or write
#define BME280_I2C_WRITE 0xEC //Write
#define BME280_I2C_READ  0xED //Read  
 
//Address for chip identification
#define BME280_CHIP_ID_ADRESS 0xD0

//Address for control registers
#define BME280_CTRL_MEAS_REG  0xF4
#define BME280_CTRL_HUM_REG   0xF2
    
//Address for configuration register
#define BME280_CONFIG_REG     0xF5

//Oversampling values
#define OVERSAMPLING_CONTROL_REG 0x6F //Oversempling x 1; p x 16 ; t x 2; Normal Mode
#define OVERSAMPLING_CONFIG_REG  0x10 //Oversempling x 1; p x 16 ; t x 2; Normal Mode 

//TEMPERATURE
    
//Address for temperature calibrations
#define BME280_TEMPERATURE_CALIB_DIG_T1_LSB_REG 0x88
#define BME280_TEMPERATURE_CALIB_DIG_T1_MSB_REG 0x89
#define BME280_TEMPERATURE_CALIB_DIG_T2_LSB_REG 0x8A
#define BME280_TEMPERATURE_CALIB_DIG_T2_MSB_REG 0x8B
#define BME280_TEMPERATURE_CALIB_DIG_T3_LSB_REG 0x8C
#define BME280_TEMPERATURE_CALIB_DIG_T3_MSB_REG 0x8D

//Address for temperature values 
#define BME280_TEMP_MSB  0xFA
#define BME280_TEMP_LSB  0xFB
#define BME280_TEMP_XLSB 0xFC
    
//PRESSURE
    
//Address for pressure calibrations
#define BME280_PRESSURE_CALIB_DIG_P1_LSB_REG 0x8E
#define BME280_PRESSURE_CALIB_DIG_P1_MSB_REG 0x8F
#define BME280_PRESSURE_CALIB_DIG_P2_LSB_REG 0x90
#define BME280_PRESSURE_CALIB_DIG_P2_MSB_REG 0x91
#define BME280_PRESSURE_CALIB_DIG_P3_LSB_REG 0x92
#define BME280_PRESSURE_CALIB_DIG_P3_MSB_REG 0x93
#define BME280_PRESSURE_CALIB_DIG_P4_LSB_REG 0x94
#define BME280_PRESSURE_CALIB_DIG_P4_MSB_REG 0x95
#define BME280_PRESSURE_CALIB_DIG_P5_LSB_REG 0x96
#define BME280_PRESSURE_CALIB_DIG_P5_MSB_REG 0x97
#define BME280_PRESSURE_CALIB_DIG_P6_LSB_REG 0x98
#define BME280_PRESSURE_CALIB_DIG_P6_MSB_REG 0x99
#define BME280_PRESSURE_CALIB_DIG_P7_LSB_REG 0x9A
#define BME280_PRESSURE_CALIB_DIG_P7_MSB_REG 0x9B
#define BME280_PRESSURE_CALIB_DIG_P8_LSB_REG 0x9C
#define BME280_PRESSURE_CALIB_DIG_P8_MSB_REG 0x9D
#define BME280_PRESSURE_CALIB_DIG_P9_LSB_REG 0x9E
#define BME280_PRESSURE_CALIB_DIG_P9_MSB_REG 0x9F
 
//Address for pressure values 
#define BME280_PRESS_MSB  0xF7
#define BME280_PRESS_LSB  0xF8
#define BME280_PRESS_XLSB 0xF9
    
//HUMIDITY
 
//Address for humidity calibrations
#define BME280_HUMIDITY_CALIB_DIG_H1_REG     0xA1
#define BME280_HUMIDITY_CALIB_DIG_H2_LSB_REG 0xE1
#define BME280_HUMIDITY_CALIB_DIG_H2_MSB_REG 0xE2
#define BME280_HUMIDITY_CALIB_DIG_H3_REG     0xE3
#define BME280_HUMIDITY_CALIB_DIG_H4_MSB_REG 0xE4
#define BME280_HUMIDITY_CALIB_DIG_H4_LSB_REG 0xE5
#define BME280_HUMIDITY_CALIB_DIG_H5_MSB_REG 0xE6
#define BME280_HUMIDITY_CALIB_DIG_H6_REG     0xE7
    
//Address for humidity values
#define BME280_HUM_MSB 0xFD
#define BME280_HUM_LSB 0xFE
    
#define TEMPERATURE_FLOAT_POINT    46
#define TEMPERATURE_CELSIUS_DEGREE 223
    
extern long int dig_T1, dig_T2, dig_T3;
extern long int dig_P1, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
extern long int dig_H1, dig_H2, dig_H3, dig_H4, dig_H5, dig_H6;

extern unsigned char temp_msb, temp_lsb, temp_xlsb;
extern unsigned char press_msb, press_lsb, press_xlsb;
extern unsigned char hum_msb, hum_lsb;

extern long adc_t, adc_p, adc_h, t_fine;

extern char temp_buffer[16];
extern char press_buffer[16];
extern char hum_buffer[16];

unsigned char getID_BME280();
void controlRegisters_BME280();
void configRegister_BME280();
void readCalibration_BME280();
void readMeasurements_BME280();
long compensateTemperature_BME280();
unsigned long compensatePressure_BME280();
unsigned long compensateHumidity_BME280();
void showTemperature_BME280();
void showPressure_BME280();
void showHumidity_BME280();

#ifdef	__cplusplus
}
#endif

#endif	/* BME280_H */

