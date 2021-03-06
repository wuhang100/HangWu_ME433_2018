#ifndef I2C2_H__
#define I2C2_H__
// Header file for i2c2.c
// helps implement use I2C1 as a master without using interrupts

void i2c_master_setup2(void);              // set up I2C 1 as a master, at 100 kHz

void i2c_master_start2(void);              // send a START signal
void i2c_master_restart2(void);            // send a RESTART signal
void i2c_master_send2(unsigned char byte); // send a byte (either an address or data)
unsigned char i2c_master_recv2(void);      // receive a byte of data
void i2c_master_ack2(int val);             // send an ACK (0) or NACK (1)
void i2c_master_stop2(void);               // send a stop

#endif
