#include "NU32.h"

#pragma config DEBUG = OFF          // Background Debugger disabled
#pragma config FWDTEN = OFF         // WD timer: OFF
#pragma config WDTPS = PS4096       // WD period: 4.096 sec
#pragma config POSCMOD = HS         // Primary Oscillator Mode: High Speed crystal
#pragma config FNOSC = PRIPLL       // Oscillator Selection: Primary oscillator w/ PLL
#pragma config FPLLMUL = MUL_20     // PLL Multiplier: Multiply by 20
#pragma config FPLLIDIV = DIV_2     // PLL Input Divider:  Divide by 2
#pragma config FPLLODIV = DIV_1     // PLL Output Divider: Divide by 1
#pragma config FPBDIV = DIV_1       // Peripheral Bus Clock: Divide by 1
//#pragma config UPLLEN = ON          // USB clock uses PLL
//#pragma config UPLLIDIV = DIV_2     // Divide 8 MHz input by 2, mult by 12 for 48 MHz
//#pragma config FUSBIDIO = ON        // USBID controlled by USB peripheral when it is on
//#pragma config FVBUSONIO = ON       // VBUSON controlled by USB peripheral when it is on
#pragma config FSOSCEN = OFF        // Disable second osc to get pins back
#pragma config BWP = ON             // Boot flash write protect: ON
#pragma config ICESEL = ICS_PGx2    // ICE pins configured on PGx2
//#pragma config FCANIO = OFF         // Use alternate CAN pins
//#pragma config FMIIEN = OFF         // Use RMII (not MII) for ethernet
//#pragma config FSRSSEL = PRIORITY_6 // Shadow Register Set for interrupt priority 6


// Perform startup routines:
//  Make NU32_LED1 and NU32_LED2 pins outputs (NU32_USER is by default an input)
//  Initialize the serial port - UART3 (no interrupt) 
//  Enable interrupts
void NU32_Startup() {
  // disable interrupts
  __builtin_disable_interrupts();

  // enable the cache 
  // This command sets the CP0 CONFIG register
  // the lower 4 bits can be either 0b0011 (0x3) or 0b0010 (0x2)
  // to indicate that kseg0 is cacheable (0x3) or uncacheable (0x2)
  // see Chapter 2 "CPU for Devices with M4K Core" of the PIC32 reference manual
  // most of the other bits have prescribed values
  // microchip does not provide a _CP0_SET_CONFIG macro, so we directly use
  // the compiler built-in command _mtc0
  // to disable cache, use 0xa4210582 
  __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583); 
  
  // set the prefectch cache wait state to 2, as per the
  // electrical characteristics data sheet
 // CHECONbits.PFMWS = 0x2;   

  //enable prefetch for cacheable and noncacheable memory
  //CHECONbits.PREFEN = 0x3; 

  // 0 data RAM access wait states
  BMXCONbits.BMXWSDRM = 0x0;
  
  // enable multi vector interrupts
  INTCONbits.MVEC = 0x1;

  __builtin_enable_interrupts();
}
