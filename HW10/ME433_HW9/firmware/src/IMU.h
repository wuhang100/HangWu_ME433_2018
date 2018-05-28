#ifndef IMU_H__
#define IMU_H__


void init(void);
void I2C_read_multiple(unsigned char, unsigned char, unsigned char *, int);
float read_x(unsigned char * );
float read_y(unsigned char * );
float read_z(unsigned char * );
float read_x0(unsigned char * );
float read_y0(unsigned char * );
float read_z0(unsigned char * );
short int raw_z(unsigned char *);

#endif