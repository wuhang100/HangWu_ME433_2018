#include<xc.h>
#include "IMU.h"
#include "i2c_master_noint.h"
#include "ST7735.h"

#define imuadd 0b1101010  // SDO pin is connected to ground

//initialize I/O expander
void init(){
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    i2c_master_setup();
    
    // CTRL1_XL  0b10000010
    i2c_master_start();
    i2c_master_send(imuadd<<1);
    i2c_master_send(0x10);
    i2c_master_send(0x82); 
    i2c_master_stop();
    
    // CTRL2_G     0b10001000 
    i2c_master_start();
    i2c_master_send(imuadd<<1);
    i2c_master_send(0x11);
    i2c_master_send(0x88);
    i2c_master_stop();
    
    // CTRL3_C     0b00000100
    i2c_master_start();
    i2c_master_send(imuadd<<1);   // R/W = 0 = write
    i2c_master_send(0x12);  // 0x12 = CTRL3_C
    i2c_master_send(0x04);  // default = 0x04, IF_INC = 1(default)
    i2c_master_stop();
}

void I2C_read_multiple(unsigned char addr, unsigned char regist, unsigned char * data, int length){
    char i;
    i2c_master_start();
    i2c_master_send(addr<<1);   
    i2c_master_send(regist);  // 0x20
    i2c_master_restart(); 
    i2c_master_send((addr<<1)|1); // R/W = 1 = read
    for(i=0;i<length-1;i++){
        data[i] = i2c_master_recv(); // receive a byte from GP7
        i2c_master_ack(0);
    }
    data[length-1]=i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
}

float read_x(unsigned char * data) { 
    float value;
    short int x = data[9]<<8 | data[8];
    value = ((float)x/(float)16000);
    return value;
}

float read_y(unsigned char * data) { 
    float value;
    short int y = data[11]<<8 | data[10];
    value = ((float)y/(float)16000);
    return value;
}

#define len 60

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

void LCD_drawString(unsigned short x, unsigned short y, char * str1, unsigned short color){
    int i=0,k=0;
    while(1){
        if (str1[i] == '\0')
            break;
        LCD_drawCharacter(x+k,y,str1[i],color);
        i++;
        k+=6;
    }
}

void acc_display(float Gx, float Gy){
    int i,j;
    char xlength = abs(Gx * len);
    char ylength = abs(Gy * len);
    if (Gx>0){
        for (i=0;i<xlength;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64+i,64+j,GREEN);
            }
        }
        if (xlength < len){
            for (i=xlength;i<len;i++){
                for(j=0;j<2;j++){
                    LCD_drawPixel(64+i,64+j,BLUE);
                }
            }
        }
        for (i=1;i<len;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64-i,64+j,BLUE);
            }
        }    
    }
    else{
        for (i=0;i<xlength;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64-i,64+j,GREEN);
            }
        }
        if (xlength < len){
            for (i=xlength;i<len;i++){
                for(j=0;j<2;j++){
                    LCD_drawPixel(64-i,64+j,BLUE);
                }
            }
        }
        for (i=1;i<len;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64+i,64+j,BLUE);
            }
        } 
    }
    if (Gy>0){
        for (i=0;i<ylength;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64+j,64+i,GREEN);
            }
        }
        if (ylength < len){
            for (i=ylength;i<len;i++){
                for(j=0;j<2;j++){
                    LCD_drawPixel(64+j,64+i,BLUE);
                }
            }
        }
        for (i=1;i<len;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64+j,64-i,BLUE);
            }
        }
    }
    else{
        for (i=0;i<ylength;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64+j,64-i,GREEN);
            }
        }
        if (ylength < len){
            for (i=ylength;i<len;i++){
                for(j=0;j<2;j++){
                    LCD_drawPixel(64+j,64-i,BLUE);
                }
            }
        }
        for (i=1;i<len;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64+j,64+i,BLUE);
            }
        }
    }
    
}

