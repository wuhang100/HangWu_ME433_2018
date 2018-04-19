#include<xc.h>                      // processor SFR definitions
#include<sys/attribs.h>             // __ISR macro
#include<cp0defs.h>
#include <math.h>

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

#define CS LATBbits.LATB3       // chip select pin

// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}

// initialize spi4 and the ram module
void spi_init() {
  TRISBbits.TRISB2 = 0;
  TRISAbits.TRISA1 = 1;
  TRISBbits.TRISB3 = 0;
  RPB3Rbits.RPB3R = 0b0011;
  RPB2Rbits.RPB2R = 0b0011;
  SDI1Rbits.SDI1R = 0b0000;
  CS = 1;
  // setup spi4
  SPI1CON = 0;              // turn off the spi module and reset it
  SPI1BUF;                  // clear the rx buffer by reading from it
  SPI1BRG = 0x3;            // baud rate to 10 MHz [SPI4BRG = (80000000/(2*desired))-1]
  SPI1STATbits.SPIROV = 0;  // clear the overflow bit
  SPI1CONbits.CKE = 1;      // data changes when clock goes from hi to lo (since CKP is 0)
  SPI1CONbits.MSTEN = 1;    // master operation
  SPI1CONbits.ON = 1;       // turn on spi 4

}
void setVoltage(char a, int v){
    
    unsigned short t=0;
    t = a<<15;
    t = t | 0b0111000000000000;
    t = t | ((v&0b1111111111)<<2);
    
    CS = 0;
    spi_io(t>>8);
    spi_io(t&0xFF);
    CS = 1;


}
int main(void) {
    int i = 0;
    int j = 1;
    spi_init();
    int ki = 1;
    float f2 = 0;
    
    while(1){
    _CP0_SET_COUNT(0);
    
    float f = 512.0 + 512.0*sin(i*2*3.14/1000*10);
    
    if (j<=100){
        f2 = f2 + ki * 10.24;  
        j++;
    }
    else {
        ki = -ki;
        j = 1;
    }
    
    i++;
    
    setVoltage(0,(int)f);
    setVoltage(1,(int)f2);
    
    while(_CP0_GET_COUNT()<24000){}
    
    
    }
    

  return 0;
}

