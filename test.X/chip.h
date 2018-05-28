#ifndef CHIP_H
#define CHIP_H

// define the address of the registers and the device address
#define WHO_AM_I 0x07
#define CTRL_REG1 0x10
#define CTRL_REG2 0x11
#define DEVICE_ADDRESS  0x0E
#define OUT_X_MSB  0x01

//functions
unsigned char read_chip(unsigned char address);
float read_data(unsigned char address);
void write_chip(unsigned char address, unsigned char content);

unsigned char read_chip2(unsigned char address);
float read_data2(unsigned char address);
void write_chip2(unsigned char address, unsigned char content);
# endif