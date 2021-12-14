/*
 * PES Course Project
 *
 * File Name	: accelerometer.h
 *
 * Author		: Tanmay Mahendra Kothale
 * 					tanmay.kothale@colorado.edu
 * 					GitHub : tanmay-mk
 *
 * Date			: December 12, 2021
 */

#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_

/*	LIBRARY FILES	*/
#include <stdint.h>

/*	MACROS	*/
#define MMA_ADDR 				0x3A

#define REG_XHI 				0x01
#define REG_XLO 				0x02
#define REG_YHI 				0x03
#define REG_YLO					0x04
#define REG_ZHI					0x05
#define REG_ZLO 				0x06

#define REG_WHOAMI 				0x0D
#define REG_CTRL1  				0x2A
#define REG_CTRL2  				0x2B
#define REG_CTRL4  				0x2D

#define CTRL_REG1_ACTIVE		0x01
#define WHOAMI 					0x1A

#define COUNTS_PER_G 			(4096.0)
#define M_PI 					(3.14159265)

#define X_REFERENCE 			300								// Reference Value of x axis when used in Self test mode
#define Y_REFERENCE 			300								// Reference Value of y axis when used in Self test mode
#define Z_REFERENCE 			3000							// Reference Value of z axis when used in Self test mode

#define ON 						1								// This is the variable to switch ON the self test mode
#define OFF 					0								// This is the variable to switch OFF the self test mode

/*	GLOBAL VARIABLES	*/
extern float tilt, tilt_value;
extern int desired_angle;
extern int16_t acc_X, acc_Y, acc_Z;

/*	FUNCTION PROTOTYPES	*/

/*-------------------------------------------------------------------------------
 * @brief			:	initializes MMA8451 3 axis accelerometer.
 *
 * @parameters		:	none
 *
 * @returns			:	none
 -------------------------------------------------------------------------------*/
int init_accelerometer(void);

/*-------------------------------------------------------------------------------
 * @brief			:	computes the values of x, y & z axis for further
 * 						computations.
 *
 * @parameters		:	none
 *
 * @returns			:	none
 -------------------------------------------------------------------------------*/
void compute_axes(void);

/*-------------------------------------------------------------------------------
 * @brief			:	computes a tilt value which is then used to compute
 * 						angle.
 *
 * @parameters		:	none
 *
 * @returns			:	none
 -------------------------------------------------------------------------------*/
void convert_axes_to_tilt(void);

#endif /*_ACCELEROMETER_H_*/
