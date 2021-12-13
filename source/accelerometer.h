
#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <stdint.h>

#define MMA_ADDR 0x3A

#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06

#define REG_WHOAMI 0x0D
#define REG_CTRL1  0x2A
#define REG_CTRL2  0x2B
#define REG_CTRL4  0x2D

#define CTRL_REG1_ACTIVE 0x01
#define WHOAMI 0x1A

#define COUNTS_PER_G (4096.0)
#define M_PI (3.14159265)
#define X_REFERENCE (300)					// Reference Value of x axis when used in Self test mode
#define Y_REFERENCE (300)					// Reference Value of y axis when used in Self test mode
#define Z_REFERENCE (3000)					// Reference Value of z axis when used in Self test mode

#define ON (1)								// This is the variable to switch ON the self test mode
#define OFF (0)								// This is the variable to switch OFF the self test mode


int init_accelerometer(void);
void read_full_xyz(void);
void read_xyz(void);
void convert_xyz_to_roll_pitch(void);



extern float tilt, tilt_value;

extern int desired_angle;

extern int16_t acc_X, acc_Y, acc_Z;

#endif /* ACCELEROMETER_H_ */
