#include<xc.h>                      // processor SFR definitions
#include<sys/attribs.h>             // __ISR macro
#include<cp0defs.h>
#include "i2c_master_noint.h"

// DEVCFG0
#pragma config DEBUG = OFF // no debugging
#pragma config JTAGEN = OFF // no jtag
#pragma config ICESEL = ICS_PGx1 // use PGED1 and PGEC1
#pragma config PWP = OFF // no write protect
#pragma config BWP = OFF // no boot write protect
#pragma config CP = OFF // no code protect

// DEVCFG1
#pragma config FNOSC = PRIPLL // use primary oscillator with pll, this uses external crystal*
#pragma config FSOSCEN = OFF // turn off secondary oscillator
#pragma config IESO = OFF // no switching clocks
#pragma config POSCMOD = HS // high speed crystal mode*
#pragma config OSCIOFNC = OFF // free up secondary osc pins
#pragma config FPBDIV = DIV_1 // divide CPU freq by 1 for peripheral bus clock
#pragma config FCKSM = CSDCMD // do not enable clock switch
#pragma config WDTPS = PS1048576 // slowest wdt
#pragma config WINDIS = OFF // no wdt window
#pragma config FWDTEN = OFF // wdt off by default
#pragma config FWDTWINSZ = WINSZ_25 // wdt window at 25%

// DEVCFG2 - get the CPU clock to 48MHz
#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz
#pragma config UPLLIDIV = DIV_2 // divider for the 8MHz input clock,then multiply by 12 to get 48MHz for USB
#pragma config UPLLEN = ON // USB clock on

// DEVCFG3
#pragma config USERID = 0 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = ON // allow multiple reconfigurations
#pragma config IOL1WAY = ON // allow multiple reconfigurations
#pragma config FUSBIDIO = ON // USB pins controlled by USB module
#pragma config FVBUSONIO = ON // USB BUSON controlled by USB module

#define ADDR 0b01000000

void initExpander(){
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    i2c_master_setup();
}

void i2cwrite(unsigned char reg, unsigned char val){
    i2c_master_start();
    i2c_master_send(ADDR<<1|0);
    i2c_master_send(reg);
    i2c_master_send(val);
    i2c_master_stop();
}

unsigned char i2cread() {
    i2c_master_start();
    i2c_master_send(ADDR<<1|0);
    i2c_master_send(0x09);
    i2c_master_restart();
    i2c_master_send(ADDR<<1|1);
    unsigned char r = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    return r;
}

int main(){
    unsigned char master;
    initExpander();
    i2cwrite(0x00,0xF0);
    i2cwrite(0x06,0xFF);
    TRISAbits.TRISA4=0;
    
    while(1){
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT()<24000000/5){;}
    LATAbits.LATA4=1;
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT()<24000000/5){;}
    LATAbits.LATA4=0;

    master = i2cread(); 
    if (master==0b10000000){
        i2cwrite(0x0A, 0x0F);
    }    
    else {   
        i2cwrite(0x0A, 0x00);
    }
    }

    }




