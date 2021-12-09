/*******************************************************************************
 * PES Course Project
 * File Name: led.h
 * Author: Tanmay Mahendra Kothale - tanmay.kothale@colorado.edu (tanmay-mk)
 *********************************************************************************/
#ifndef _LED_H_
#define _LED_H_

/*	LIBRARY FILES	*/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/*	MACROS	*/
#define RED_LED_PIN 			18
#define BLUE_LED_PIN 			1
#define GREEN_LED_PIN 			19

/*
 * @brief:an enumeration of colors as integer values
 */
enum {
	WHITE		= 0,
	RED			= 1,
	GREEN		= 2,
	BLUE		= 4
};

/*	FUNCTION PROTOTYPE	*/
/*
 * @brief			: Initializes Red LED
 * @parameters		: none
 * @returns			: none
 */
void RED_LED_INIT();

/*
 * @brief			: Initializes Blue LED
 * @parameters		: none
 * @returns			: none
 */
void BLUE_LED_INIT();

/*
 * @brief			: Initializes Green LED
 * @parameters		: none
 * @returns			: none
 */
void GREEN_LED_INIT();

/*
 * @brief			: Turns ON Red LED
 * @parameters		: none
 * @returns			: none
 */
void RED_LED_ON();

/*
 * @brief			: Turns ON Blue LED
 * @parameters		: none
 * @returns			: none
 */
void BLUE_LED_ON();

/*
 * @brief			: Turns ON Green LED
 * @parameters		: none
 * @returns			: none
 */
void GREEN_LED_ON();

/*
 * @brief			: Turns ON All LEDs
 * @parameters		: none
 * @returns			: none
 */
void WHITE_LED_ON();

/*
 * @brief			: Turns ON a LED of specific color
 * @parameters		: LED_COLOR
 * @returns			: none
 */
void LED_ON(int LED_COLOR);

/*
 * @brief			: Turns OFF Red LED
 * @parameters		: none
 * @returns			: none
 */
void RED_LED_OFF();

/*
 * @brief			: Turns OFF Blue LED
 * @parameters		: none
 * @returns			: none
 */
void BLUE_LED_OFF();

/*
 * @brief			: Turns OFF Green LED
 * @parameters		: none
 * @returns			: none
 */
void GREEN_LED_OFF();

/*
 * @brief			: Turns OFF All LEDs
 * @parameters		: none
 * @returns			: none
 */
void WHITE_LED_OFF();

/*
 * @brief			: Turns OFF LED of a specific color
 * @parameters		: LED_COLOR
 * @returns			: none
 */
void LED_OFF(int LED_COLOR);

#endif /*_LED_H_*/
