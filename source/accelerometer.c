/*
 * PES Course Project
 *
 * File Name	: accelerometer.c
 *
 * Author		: Tanmay Mahendra Kothale
 * 					tanmay.kothale@colorado.edu
 * 					GitHub : tanmay-mk
 *
 * Date			: December 12, 2021
 */

/*	LIBRARY FILES	*/
#include <math.h>
#include <stdio.h>
#include "fsl_debug_console.h"
#include <MKL25Z4.H>

/*	OTHER FILES TO BE INCLUDED	*/
#include "i2c.h"
#include "accelerometer.h"
#include "systick.h"

/*	GLOBAL VARIABLES	*/
int16_t acc_X=0, acc_Y=0, acc_Z=0;
float tilt=0.0, tilt_value=0.0;

extern uint32_t DATA_READY;

//initializes mma8451 sensor
//i2c has to already be enabled
int init_accelerometer()
{
	//set active mode, 14 bit samples and 800 Hz ODR
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}

void compute_axes()
{
	int i;
	uint8_t data[6];
	int16_t temp[3];

	i2c_start();
	i2c_read_setup(MMA_ADDR , REG_XHI);

	// Read five bytes in repeated mode
	for( i=0; i<5; i++)	{
		data[i] = i2c_repeated_read(0);
	}
	// Read last byte ending repeated mode
	data[i] = i2c_repeated_read(1);

	for ( i=0; i<3; i++ ) {
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]);
	}

	// Align for 14 bits
	acc_X = temp[0]>>2;
	acc_Y = temp[1]>>2;
	acc_Z = temp[2]>>2;
	if(acc_X<0)
	{
		acc_X = acc_X*(-1);
	}
	if(acc_Y<0)
	{
		acc_Y = acc_Y*(-1);
	}
	if(acc_Z<0)
	{
		acc_Z = acc_Z*(-1);
	}
}

void convert_axes_to_tilt(void) {
	float ax = acc_X/COUNTS_PER_G,
		  ay = acc_Y/COUNTS_PER_G,
		  az = acc_Z/COUNTS_PER_G;

	tilt_value= (az / sqrt(ax*ax + ay*ay + az*az));
	tilt= acos(tilt_value)* 180/M_PI;
}

/*EOF*/
