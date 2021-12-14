/*
 * PES Course Project
 *
 * File Name	: test_modules.h
 *
 * Author		: Tanmay Mahendra Kothale
 * 				  tanmay.kothale@colorado.edu
 * 				  GitHub : tanmay-mk
 *
 * Date			: December 12, 2021
 */

#ifndef _TEST_MODULES_H_
#define _TEST_MODULES_H_

/*	FUNCTION PROTOTYPES	*/
/*-------------------------------------------------------------------------------
 * @brief			:	test suite for circular buffers
 *
 * @parameters		:	none
 *
 * @returns			:	none
 -------------------------------------------------------------------------------*/
void test_cbfifo();

/*-------------------------------------------------------------------------------
 * @brief			:	test suite for RGB LED
 *
 * @parameters		:	none
 *
 * @returns			:	none
 -------------------------------------------------------------------------------*/
void test_tpm_led();

/*-------------------------------------------------------------------------------
 * @brief			:	test suite for accelerometer
 *
 * @parameters		:	none
 *
 * @returns			:	none
 -------------------------------------------------------------------------------*/
void self_test_accelerometer();

/*-------------------------------------------------------------------------------
 * @brief			:	checks whether I2C and MMA8451 are initialized
 * 						correctly or not
 *
 * @parameters		:	none
 *
 * @returns			:	none
 -------------------------------------------------------------------------------*/
void test_accelerometer();

#endif /*_TEST_MODULES_H_*/
