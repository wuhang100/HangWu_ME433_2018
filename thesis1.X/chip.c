#include "NU32.h"         
#include "i2c_master_noint.h"
#include "i2c2.h"
#include <stdio.h>
#include "chip.h"

unsigned char read_chip(unsigned char address){
	unsigned char master_read0;
	i2c_master_start();                     // Begin the start sequence
    i2c_master_send(DEVICE_ADDRESS << 1);   // send the slave address, left shifted by 1
	i2c_master_send(address);               // the register address
	i2c_master_restart();
	i2c_master_send((DEVICE_ADDRESS << 1)|1);
	master_read0 = i2c_master_recv();
	i2c_master_stop();
    return master_read0;
}

float read_data(unsigned char address){
	unsigned char master_read0,master_read1;
	short int xy_mag;
	float xy_value; 
	i2c_master_start();                     // Begin the start sequence
    i2c_master_send(DEVICE_ADDRESS << 1);   // send the slave address, left shifted by 1
	i2c_master_send(address);
	i2c_master_restart();
	i2c_master_send((DEVICE_ADDRESS << 1)|1);
	master_read0 = i2c_master_recv();
	i2c_master_ack(0);
	master_read1 = i2c_master_recv();
	i2c_master_ack(1);
	xy_mag=(master_read0 <<8)|master_read1;
	xy_value=((float)xy_mag)/((float)10);
	i2c_master_stop();
    return xy_value;
}

void write_chip(unsigned char address, unsigned char content){
	i2c_master_start(); 
	i2c_master_send(DEVICE_ADDRESS << 1);
	i2c_master_send(address);
	i2c_master_send(content);
	i2c_master_stop();	
}

unsigned char read_chip2(unsigned char address){
	unsigned char master_read0;
	i2c_master_start2();                     // Begin the start sequence
    i2c_master_send2(DEVICE_ADDRESS << 1);   // send the slave address, left shifted by 1
	i2c_master_send2(address);               // the register address
	i2c_master_restart2();
	i2c_master_send2((DEVICE_ADDRESS << 1)|1);
	master_read0 = i2c_master_recv2();
	i2c_master_stop2();
    return master_read0;
}

float read_data2(unsigned char address){
	unsigned char master_read0,master_read1;
	short int xy_mag;
	float xy_value; 
	i2c_master_start2();                     // Begin the start sequence
    i2c_master_send2(DEVICE_ADDRESS << 1);   // send the slave address, left shifted by 1
	i2c_master_send2(address);
	i2c_master_restart2();
	i2c_master_send2((DEVICE_ADDRESS << 1)|1);
	master_read0 = i2c_master_recv2();
	i2c_master_ack2(0);
	master_read1 = i2c_master_recv2();
	i2c_master_ack2(1);
	xy_mag=(master_read0 <<8)|master_read1;
	xy_value=((float)xy_mag)/((float)10);
	i2c_master_stop2();
    return xy_value;
}

void write_chip2(unsigned char address, unsigned char content){
	i2c_master_start2(); 
	i2c_master_send2(DEVICE_ADDRESS << 1);
	i2c_master_send2(address);
	i2c_master_send2(content);
	i2c_master_stop2();	
}


