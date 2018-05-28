#include "NU32.h"         
#include "i2c_master_noint.h"
#include "i2c2.h"
#include <stdio.h>
#include "chip.h"

#define WHO_AM_I 0x07
#define CTRL_REG1 0x10
#define CTRL_REG2 0x11
#define DEVICE_ADDRESS  0x0E
#define OUT_X_MSB  0x01

void delay(int i) {
	int j,m;
	for (j = 0; j < i; j++) { // number is 1 million
        m=j+1;
		}
	}

//void offset(void) {
//	int i;
//	int cache;
//	int offset_value;
//    int	v0, v1;
//	int value_zero;
//	int value_one;
//	
//	for (i=0;i<=9;i++){
//		value_zero=read_chip(0x01);
//		value_one=read_chip(0x02);
//		offset_value=(value_zero <<8)|value_one;
//		cache=offset_value+cache;
//		delay(1000000);
//	}
//	offset_value=cache/10;
//	v0=(offset_value&0xFF00)>>8;
//	v1=(offset_value&0xFF);
//	write_chip(0x09,v0);
//	write_chip(0x0A,v1);
//}

int main() {
  float x_value,x_offset;
  float x_value2,x_offset2;
  float x_warn;
  char buf[100] = {};                       // buffer for sending messages to the user
  unsigned char reset_reg1 = 0x00;           // reset CTRL_REG1
  unsigned char set_reg1 = 0x01;
  unsigned char set_reg2 = 0x80;           
  unsigned char master_read0  = 0x00;       // first received byte
  unsigned char master_read1  = 0x00;       // second received byte
  
  NU32_Startup();
    
  __builtin_disable_interrupts();
  i2c_master_setup();                       // init I2C1 as a master
 // i2c_master_setup2();
  __builtin_enable_interrupts();
 
  i2c_master_send(DEVICE_ADDRESS << 1);   // send the slave address, left shifted by 1
  i2c_master_send(WHO_AM_I);
  i2c_master_restart();
  i2c_master_send((DEVICE_ADDRESS << 1)|1);
  master_read0 = i2c_master_recv();
  TRISBbits.TRISB6=0;
  LATBbits.LATB6=1; 
//    if (master_read0==0xc4){
//    LATBbits.LATB6=0;
//    }
//    else{
//    LATBbits.LATB6=1;   
//    } 
  //test
  //master_read0=read_chip(0x07);

//  TRISBbits.TRISB6=0;
//    if (master_read0==0xc4){
//    LATBbits.LATB6=1;
//    }
//    else{
//    LATBbits.LATB6=0;   
//    }
  
 // This code is for chip one 
/* 	master_read0=read_chip(WHO_AM_I);
	sprintf(buf, "Who am I? 0x%x\r\n", master_read0);
    NU32_WriteUART3(buf);	

	write_chip(CTRL_REG1,reset_reg1);
	write_chip(CTRL_REG1,set_reg1);
	write_chip(CTRL_REG2,set_reg2);
	master_read0=read_chip(CTRL_REG1);
	sprintf(buf, "0x%x\r\n", master_read0);
    NU32_WriteUART3(buf);

	delay(500000);	
    x_offset=read_data(OUT_X_MSB);
	write_chip(0x09,0x00);
	write_chip(0xA0,0x00);

		
     while(1) {
    x_value=read_data(OUT_X_MSB);
	x_value=x_value-x_offset;
	sprintf(buf, "X-axis value: %f\r\n", x_value);
	NU32_WriteUART3(buf);
	delay(1000000);	
	}  */
	
	
	
 // This code is for chip two
/*  	master_read0=read_chip2(WHO_AM_I);
	sprintf(buf, "Who am I? 0x%x\r\n", master_read0);
    NU32_WriteUART3(buf);	

	write_chip2(CTRL_REG1,reset_reg1);
	write_chip2(CTRL_REG1,set_reg1);
	write_chip2(CTRL_REG2,set_reg2);
	master_read0=read_chip2(CTRL_REG1);
	sprintf(buf, "0x%x\r\n", master_read0);
    NU32_WriteUART3(buf);

	delay(500000);	
    x_offset=read_data2(OUT_X_MSB);
	write_chip2(0x09,0x00);
	write_chip2(0xA0,0x00);

		
     while(1) {
    x_value=read_data2(OUT_X_MSB);
	x_value=x_value-x_offset;
	sprintf(buf, "X-axis value: %f\r\n", x_value);
	NU32_WriteUART3(buf);
	delay(1000000);	
	}  */
	
	
//	master_read0=read_chip(WHO_AM_I);
//	sprintf(buf, "Who am I? 0x%x\r\n", master_read0);
//    NU32_WriteUART3(buf);	
//
//	write_chip(CTRL_REG1,reset_reg1);
//	write_chip(CTRL_REG1,set_reg1);
//	write_chip(CTRL_REG2,set_reg2);
//	master_read0=read_chip(CTRL_REG1);
//	sprintf(buf, "0x%x\r\n", master_read0);
//    NU32_WriteUART3(buf);
//
//	delay(500000);	
//    x_offset=read_data(OUT_X_MSB);
//	write_chip(0x09,0x00);
//	write_chip(0xA0,0x00);
//	
//	master_read0=read_chip2(WHO_AM_I);
//	sprintf(buf, "Who am I? 0x%x\r\n", master_read0);
//    NU32_WriteUART3(buf);	
//
//	write_chip2(CTRL_REG1,reset_reg1);
//	write_chip2(CTRL_REG1,set_reg1);
//	write_chip2(CTRL_REG2,set_reg2);
//	master_read0=read_chip2(CTRL_REG1);
//	sprintf(buf, "0x%x\r\n", master_read0);
//    NU32_WriteUART3(buf);
//
//	delay(500000);	
//    x_offset2=read_data2(OUT_X_MSB);
//	write_chip2(0x09,0x00);
//	write_chip2(0xA0,0x00);
//
//		
//     while(1) {
//    x_value=read_data(OUT_X_MSB);
//	x_value=x_value-x_offset;
//	x_value2=read_data2(OUT_X_MSB);
//	x_value2=x_value2-x_offset2;
//	x_warn=x_value-x_value2;
//	sprintf(buf, "X-axis value: %f\r\n", x_warn);
//	NU32_WriteUART3(buf);
//	delay(1000000);	
//	} 
 

  return 0;
}
