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

#define MAX_DUTY_CYCLE		0xFF

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
void LED_OFF(void);
void LED_Color_Config();
void LED_ON(uint32_t color_name, int brightness);
void test_LED_ON(uint32_t red_value, uint32_t green_value, uint32_t blue_value);

#endif /*_LED_H_*/
