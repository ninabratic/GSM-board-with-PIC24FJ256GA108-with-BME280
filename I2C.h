#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

void I2C_init();
void I2C_Wait();
void I2C_start();
void I2C_stop();
void send_ACK();
void send_NACK();
void I2C_write(unsigned char byte);
unsigned int readRegister_I2C(unsigned char command);
void writeRegister_I2C(unsigned char command, unsigned char value);
void writeRegisters_I2C(unsigned char commOne, unsigned char commTwo, unsigned char value);
unsigned char I2C_read();


#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

