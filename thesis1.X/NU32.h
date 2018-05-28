#ifndef NU32__H__
#define NU32__H__

#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro


#define NU32_SYS_FREQ 50000000ul    // 80 million Hz

void NU32_Startup(void);


#endif // NU32__H__