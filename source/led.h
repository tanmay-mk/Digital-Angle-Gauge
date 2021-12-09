/*********************************************************************************************
 * PES Assignment 4
 * File Name: pwm.h
 * Author: Alexander G. Dean
 * GitHub Link:https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_7/PWM_LED/Source/timers.c
 ********************************************************************************************/
#ifndef _LED_H_
#define _LED_H_

/*
 * LIBRARY FILES TO BE INCLUDED
 */
#include "MKL25Z4.h"

/*
 * MACROS
 */
#define RED_LED_PIN 		18
#define GREEN_LED_PIN 		19
#define BLUE_LED_PIN 		1

enum color_names
{
	RED,			//0xFF0000
	GREEN,			//0x00FF00
	BLUE,			//0x0000FF
	WHITE,			//0xFFFFFF
	YELLOW,			//0xFFFF00
	MAGENTA,		//0xFF00FF
	CYAN,			//0x00FFFF
	TOTAL_COLORS
};

typedef struct color_configuration
{
	uint32_t red_value;
	uint32_t green_value;
	uint32_t blue_value;
}color_config;

extern color_config color[TOTAL_COLORS];
extern int brightness;

void LED_init();

void LED_Color_Config();

/*
 * @brief: 					Turns on LED with specific RGB value.
 *
 * @parameters:
 * 			red_value:		Turns ON the LED with a specific duty cycle
 * 							for RED color.
 * 			green_value: 	Turns ON the LED with a specific duty cycle
 * 							for GREEN color.
 * 			blue_value:		Turns ON the LED with a specific duty cycle
 * 							for BLUE color.
 *
 * @returns: 				None.
 */
void LED_ON(uint32_t color_name, int brightness);


#endif /*_LED_H_*/
