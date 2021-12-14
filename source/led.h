/*
 * PES Course Project
 *
 * File Name	: led.h
 *
 * Author		: Tanmay Mahendra Kothale
 * 				  tanmay.kothale@colorado.edu
 * 				  GitHub : tanmay-mk
 *
 * Date			: December 12, 2021
 */

#ifndef _LED_H_
#define _LED_H_

/*	LIBRARY FILES	*/
#include "MKL25Z4.h"

/*	MACROS	*/
#define RED_LED_PIN 		18
#define GREEN_LED_PIN 		19
#define BLUE_LED_PIN 		1
#define MAX_DUTY_CYCLE		0xFF

/*	ENUM OF COLORS	*/
enum color_names
{
	RED,			//0xFF0000
	GREEN,			//0x00FF00
	BLUE,			//0x0000FF
	WHITE,			//0xFFFFFF
	YELLOW,			//0xFFFF00
	MAGENTA,		//0xFF00FF
	CYAN,			//0x00FFFF
	NEON,			//0x70FF07
	SKY_BLUE,		//0x0770FF
	PINK,			//0xFF70FF
	TOTAL_COLORS
};

/*	STRUCTURES TO HOLD RGB VALUES OF COLORS FOR CONFIGURATION	*/
typedef struct color_configuration
{
	uint16_t red_value;
	uint16_t green_value;
	uint16_t blue_value;
}color_config;

/*	GLOBAL VARIABLES	*/
extern color_config color[TOTAL_COLORS];
extern int brightness;

/*	FUNCTION_PROTOTYPES	*/
/*------------------------------------------------------------------------
 * @brief: 		Initializes Red, Green and Blue LED
 *
 * @parameters: none
 *
 * @returns: 	none
 ------------------------------------------------------------------------*/
void LED_init();

/*------------------------------------------------------------------------
 * @brief: 		Turns OFF Red, Green and Blue LED
 *
 * @parameters: none
 *
 * @returns: 	none
 ------------------------------------------------------------------------*/
void LED_OFF(void);

/*------------------------------------------------------------------------
 * @brief: 		Configures the colors according to their hex RGB values
 *
 * @parameters: none
 *
 * @returns: 	none
 ------------------------------------------------------------------------*/
void LED_Color_Config();

/*------------------------------------------------------------------------
 * @brief: 		Turns on LED with the specific color and brightness
 *
 * @parameters: color_name	: 	name of the color, the value of which is
 * 								mentioned in the enum above
 * 				factor		:	the amount of brightness intended to be seen by
 * 								user
 *
 * @returns: 	none
 ------------------------------------------------------------------------*/
void LED_ON(uint32_t color_name, int factor);

/*------------------------------------------------------------------------
 * @brief: 		Turns on LED with the specific RGB values
 *
 * @parameters: red_value	: R value for the intended color
 * 				green_value	: G value for the intended color
 * 				blue_value	: B value for the intended color
 *
 * @returns: 	none
 ------------------------------------------------------------------------*/
void test_LED_ON(uint32_t red_value, uint32_t green_value, uint32_t blue_value);

#endif /*_LED_H_*/
