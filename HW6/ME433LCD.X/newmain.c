#include <xc.h>
#include <sys/attribs.h>  // __ISR macro
#include <stdio.h>   // to use sprintf()
#include "ST7735.h"

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

void LCD_drawCharacter(unsigned short x, unsigned short y, char ch, unsigned short color){
    int i,j;
    if ((x<_GRAMWIDTH-5)&&(y<_GRAMHEIGH-8)){
        for (i=0;i<5;i++){
            for(j=0;j<8;j++){
                if(((ASCII[ch-0x20][i])>>j)&(0x01))
                    LCD_drawPixel(x+i,y+j,color);
                else
                    LCD_drawPixel(x+i,y+j,BLACK); 
            }
        }
    }
}

void LCD_drawString(unsigned short x, unsigned short y, char ch[], unsigned short color){
    int i=0,k=0;
    while(1){
        if (ch[i] == '\0')
            break;
        LCD_drawCharacter(x+k,y,ch[i],color);
        i++;
        k+=6;
    }
}

void LCD_drawBar(unsigned short x, unsigned short y, char length, unsigned short color){
    int i,j;
    for (i=0;i<length;i++){
        for(j=0;j<2;j++){
            LCD_drawPixel(x+i,y+j,color);
        }
    }
    if (length < 100){
        for (i=length;i<100;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(x+i,y+j,BLUE);
            }
        }
    }
}

//#define CS LATBbits.LATB7  // SPI chip select pin

int main() {
    
  char str1[100],str2[100];
  int timer=10;
  float FPS=0.0;
  // some initialization function to set the right speed setting
  __builtin_disable_interrupts();
  
  SPI1_init();
  LCD_init();
  LCD_clearScreen(BLACK);

  __builtin_enable_interrupts();
  while(1) {
      for (timer=0;timer<=100;timer++){
            _CP0_SET_COUNT(0);
            sprintf(str1,"Hello World! %d  ",timer);
            LCD_drawString(28,32,str1,BLUE); //String
            LCD_drawBar(20,48,timer,GREEN);    //Bar
            FPS = 24000000/_CP0_GET_COUNT(); //FPS
            sprintf(str2,"FPS: %1.1f",FPS);
            LCD_drawString(28,80,str2,BLUE);
            while(_CP0_GET_COUNT() < 2400000){;} // 24MHz/10Hz = 2400000
      }
      //LCD_clearScreen(BACKGROUND);
  }
  return 0;
}