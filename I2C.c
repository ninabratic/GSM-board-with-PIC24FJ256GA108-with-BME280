#include "Common.h"

void I2C_init(){

    TRISGbits.TRISG2 = 1;   //SCL1 input
    TRISGbits.TRISG3 = 1;  //SDA1 input
    
    I2C1CONbits.DISSLW = 1; //disable slave rate
    I2C1CONbits.I2CEN = 1;  //I2C ENABLE
    
    I2C1BRG = ((FCY/FSCL) - (FCY/10000000)) - 1;  //400kHz speed 
}
void I2C_Wait(){
    
    while ( (I2C1CON & 0x001F ) || ( I2C1STAT & 0x04 )); //cekamo da se komunikacije zavrsi, jedan od status ili controlni reg bude nula 
}

void I2C_start(){
    
    I2C_Wait();
    I2C1CONbits.SEN = 1; //start bit for i2c
    while(I2C1CONbits.SEN); //sen na 1
}

void I2C_stop(){
    
    I2C_Wait();
    I2C1CONbits.PEN = 1; //stop condition 
    while(I2C1CONbits.PEN);
}

void I2C_write(unsigned char byte){
    
    //__delay_us(100);
    I2C1TRN = byte; //smjestam parametar koji upisujem u registar za slanje
    while (I2C1STATbits.TBF); //dok god je statusni bit aktivan imam upis
    I2C_Wait(); //cekaj komunikaciju
}

unsigned char I2C_read(){
    
    unsigned char temp; //lokalna prom, poslije iyvrsenja brise se sa steka
    
    I2C_Wait();
    I2C1CONbits.RCEN = 1; //receive enable da primamo podatke
    temp = I2C1RCV; //registar za prijem sijestimo u lokalnu prom.
    I2C_Wait();
    I2C1CONbits.ACKEN = 1; //ack bit, yavrsena sekvenca slanja
    I2C1CONbits.ACKDT = 1; //zavrsena i2c, ack data bit 0 ako je primio pod, 1 ako je nack nije zavrsio i2c
    
    return temp; //vrati pod.
}

void writeRegister_I2C(unsigned char command, unsigned char value){ //komanda i vrijednost
    
    I2C_start();
    I2C_write(command);
    I2C_write(value);
    I2C_stop();
}

void writeRegisters_I2C(unsigned char commOne, unsigned char commTwo, unsigned char value){
    
    I2C_start();
    I2C_write(commOne);
    I2C_write(commTwo);
    I2C_write(value);
    I2C_stop();
}

unsigned int readRegister_I2C(unsigned char command){

    unsigned int value;
    
    I2C_start();
    I2C_write(command);
    value = I2C_read(); 
    I2C_stop();
    
    return value;
}