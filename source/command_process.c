/*
 * PES Course Project
 *
 * File Name	: command_process.c
 *
 * Author		: Tanmay Mahendra Kothale
 * 					tanmay.kothale@colorado.edu
 * 					GitHub : tanmay-mk
 *
 * Date			: December 12, 2021
 */

/* 	LIBRARY FILES	*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/* 	OTHER FILES TO BE INCLUDED	*/
#include "command_process.h"
#include "led.h"
#include "accelerometer.h"
#include "systick.h"
#include "touch.h"

/*	GENERIC PROTOTYPE FOR HANDLE FUNCTIONS	*/
typedef void (*cmd_handler_t)(int, char * argv[]);

/*		STRUCTURE OF COMMANDS AND THEIR DATA	*/
typedef struct{
	const char *cmd_name;
	cmd_handler_t handler;
	const char * help_string;
	uint32_t led_color;
}cmd_table_t;

int desired_angle = 45;
int calibrated_angle = 0;

enum commands {
	author_command,
	help_command,
	brightness_command,
	angle_command,
	color_command,
	touch_command,
	calibrate_command
};

/*	HANDLER FUNCTION PROTOTYPES	*/

/*
 * @brief	:	this function is called after the author
 * 				command is received
 */
static void author_handler		(int argc, char * argv[]);

/*
 * @brief	:	this function is called after the help
 * 				command is received
 */
static void help_handler		(int argc, char * argv[]);

/*
 * @brief	:	this function is called after the brightness
 * 				command is received
 */
static void brightness_handler	(int argc, char * argv[]);

/*
 * @brief	:	this function is called after the angle
 * 				command is received
 */
static void angle_handler		(int argc, char * argv[]);

/*
 * @brief	:	this function is called after the color
 * 				command is received
 */
static void color_handler		(int argc, char * argv[]);

/*
 * @brief	:	this function is called after the touch
 * 				command is received
 */
static void touch_handler		(int argc, char * argv[]);

/*
 * @brief	:	this function is called after the calibrate
 * 				command is received
 */
static void calibrate_handler	(int argc, char * argv[]);

/*	TABLE OF COMMANDS EXECUTED IN RESPONSE TO THE USER INPUT 	*/
static cmd_table_t commands[] =
{
		{"author",author_handler,"Prints the name of the Author\r\n", CYAN},

		{"help",help_handler,"Print this help message\r\n", NEON},

		{"brightness",brightness_handler,"Adjusts the brightness of the LED. Write 'brightness <percent>'. \n\r"						\
				"For example, brightness 50 will set the brightness of LED to 50%.\r\n", SKY_BLUE},

		{"angle", angle_handler, "Allows user to set a desired angle and then starts blinking the\n\r"									\
				"LED until the desired angle is reached. \n\rWrite 'angle <desired angle in degrees>'.\n\r", YELLOW},

		{"color", color_handler, "Allows you to change the LED color assigned to a specific instruction.\n\rAvailable colors are:\n\r"	\
				"color\t\tcodeword\n\rblue\t\tblue\n\rgreen\t\tgreen\n\ryellow\t\tyellow\n\rcyan\t\tcyan\n\rneon\t\tneon\n\r"			\
				"magenta\t\tmagenta\n\rsky blue\tskyblue\n\rpink\t\tpink\n\rwhite\t\twhite\n\r\n\r"										\
				"write 'color <instruction> <color code>'\n\r", MAGENTA},

		{"touch", touch_handler, "Allows user to adjust the brightness of the LED using the touch sensor\n\r"							\
				"If the brightness of the LED is greater than 0, first, the brightness will gradually decrease\n\r"						\
				"by 10%% and then once the brightness is 0 (LED OFF), the LED will start glowing again gradually\n\r"					\
				"with increase of 10%% in brightness. type 'touch' and then tap until your intended brightness is\n\r"					\
				"achieved. To exit the command, press the TSI sensor a bit harder.", BLUE},

		{"calibrate", calibrate_handler, "Calibrates the accelerometer to a certain value. For example if the\n\r"						\
				"we calibrate the accelerometer at 20 degrees, then 20 degrees become a reference axis (0 degrees)\n\r"					\
				"for the accelerometer and all the readings will be taken relative to 20.\n\r\n\r"										\
				"write 'calibrate <angle>'\n\r", GREEN},
};

static const int cmd_nos = sizeof(commands) / sizeof(cmd_table_t);	//computing number of commands

void process_command(char *input)
{
	bool in_token = false;
	char *argv[10];
	int argc = 0;

	bool command = false;						//variable to check whether a command
												//is present or not

	char *p = input;
	char *end;

	for(end=input ; *end!= '\0' ; end++)		//computing the end of the string
				;
	memset(argv,0,sizeof(argv)); 				//setting argv[] to 0

	for(p = input; p < end; p++)
	{
		switch(in_token)
		{
			case false:

				/*
				 * @brief: if the token state is false, we check for a valid character
				 * 			if we find a valid character, we look for first available white space,
				 * 			LF, CR or TAB.
				 */
				if(
						((*p>='a')&&(*p<='z')) ||
						((*p>='A')&&(*p<='Z')) ||
						((*p>='0')&&(*p<='9'))
				  )
				{
					argv[argc] = p;		//storing the word in argv
					argc++;				//incrementing argc index
					in_token = true;	//advance to next state
				}

			break;
			case true:

				/*
				 * @brief: in this state, we check for the first available white space,
				 * 			LF, CR, TAB, and then replace the character with null character.
				 */
				if(
						(*p == ' ')  ||
						(*p == '\t') ||
						(*p == '\n') ||
						(*p == '\r')
				  )
				{
					*p = '\0';
					in_token = false;		//advance to previous state
				}

			break;
		}
	}
	if(argc == 0)
	{
		return;		//no command found
	}

	//Todo:Handle the command
	for (int i=0; i < cmd_nos; i++)
	{
	    if (strcasecmp(argv[0], commands[i].cmd_name) == 0)
	    {
	      commands[i].handler(argc, argv);
	      command = true;
	      break;
	    }
	}
	 if(!command) 						//if no command is found, we print a message indicating that
	 {									//invalid command has been entered
		 LED_ON(RED, brightness);
		 printf("Invalid command: %s\r\n",argv[0]);
	 }
}

static void author_handler(int argc, char * argv[])
{
	printf("Tanmay Mahendra Kothale\n\rtanmay.kothale@colorado.edu\n\rGitHub: tanmay-mk\r\n");
	LED_ON(commands[author_command].led_color, brightness);
}

static void help_handler(int argc,char * argv[])
{
	LED_ON(commands[help_command].led_color, brightness);

	printf("1. author\r\n");
	printf("%s\n\r",commands[author_command].help_string);

	printf("2. help\r\n");
	printf("%s\n\r",commands[help_command].help_string);

	printf("3. brightness\r\n");
	printf("%s\n\r",commands[brightness_command].help_string);

	printf("4. angle\r\n");
	printf("%s\n\r",commands[angle_command].help_string);

	printf("5. color\r\n");
	printf("%s\n\r",commands[color_command].help_string);

	printf("6. color\r\n");
	printf("%s\n\r",commands[calibrate_command].help_string);
}

static void brightness_handler(int argc, char * argv[])
{
	uint32_t factor;		//a variable to store the value entered by user

	if (argv[1]==0)			//if user does not enter a number or a value
	{						//this error message will be printed
		printf("Too few arguments for brightness command.\n\r");
		printf("Type help for more information.\n\r");
		return;
	}

	else
	{
		sscanf(argv[1], "%d", &factor);
		brightness = factor;						//updating the global variable
		printf("Set the brightness of LED to %d%%\n\r", brightness);
		LED_ON(commands[brightness_command].led_color, brightness);
	}
}

static void angle_handler(int argc, char * argv[])
{
	uint32_t user_angle;		//a variable to store the value entered by user
	int angle=0;

	if (argv[1]==0)				//if user does not enter a number or a value
	{							//this error message will be printed
		printf("Too few arguments for angle command.\n\r");
		printf("Type help for more information.\n\r");
		return;
	}
	else
	{
		sscanf(argv[1], "%d", &user_angle);
		desired_angle = user_angle; 		//updating the global variable
		while (1)
		{									//this loop will keep running unless the desired
											//angle is reached
			//compute values of x, y and z axes
		   	compute_axes();
		   	//convert it to tilt value
		  	convert_axes_to_tilt();
		  	//compute angle
		   	angle = fabs(tilt)-calibrated_angle;
		   	//change the sign of the variable if angle is negative
		    angle = (angle<0)? angle*-1 : angle;
		    //print angle for user
		   	printf("Angle: %d\n\r", angle);
		   	//LED will be blinking unless the desired angle is reached
		   	LED_ON(commands[angle_command].led_color, brightness);
		   	delay(75);
		   	LED_OFF();
		   	delay(75);
		   	if (angle == desired_angle)
		   	{
		   		printf("Desired angle reached. Current Angle: %d\n\r", angle);
		   		LED_ON(commands[angle_command].led_color, brightness);
		   		break;
		   	}
		}
	}
}


static void color_handler(int argc, char * argv[])
{
	LED_ON(commands[color_command].led_color, brightness);

	bool command = false;			//variable to check whether the command was entered properly
	char color_name[10];			//array to store the color name
	uint32_t instruction_id = 0xFF;	//variable to store instruction id

	if (argv[1]==0 || argv[2]==0)
	{
		printf("Too few arguments for brightness command.\n\r");
		printf("Type help for more information.\n\r");
		return;
	}

	else
	{
		sscanf(argv[2], "%s", color_name);

		for (int i=0; i < cmd_nos; i++)
		{
			if (strcasecmp(argv[1], commands[i].cmd_name) == 0)
			{
		        instruction_id = i;
			    command = true;
			    break;
			}

		}
		if(!command)
		{
			printf("Invalid command: %s\r\n",argv[0]);
		}

		if (strcasecmp(color_name, "blue")==0)
		{
			commands[instruction_id].led_color = BLUE;
		}

		else if (strcasecmp(color_name, "green")==0)
		{
			commands[instruction_id].led_color = GREEN;
		}

		else if (strcasecmp(color_name, "yellow")==0)
		{
			commands[instruction_id].led_color = YELLOW;
		}

		else if (strcasecmp(color_name, "magenta")==0)
		{
			commands[instruction_id].led_color = MAGENTA;
		}

		else if (strcasecmp(color_name, "cyan")==0)
		{
			commands[instruction_id].led_color = CYAN;
		}

		else if (strcasecmp(color_name, "white")==0)
		{
			commands[instruction_id].led_color = WHITE;
		}

		else if (strcasecmp(color_name, "neon")==0)
		{
			commands[instruction_id].led_color = NEON;
		}

		else if (strcasecmp(color_name, "pink")==0)
		{
			commands[instruction_id].led_color = PINK;
		}

		else if (strcasecmp(color_name, "skyblue")==0)
		{
			commands[instruction_id].led_color = SKY_BLUE;
		}

		else
		{
			printf("Invalid color %s\n\r", color_name);
		}
	}
}

static void touch_handler(int argc, char * argv[])
{
	LED_ON(commands[touch_command].led_color, brightness);
	uint32_t variable;

	variable = brightness;

	bool flag = true;
	while (1)
	{
		int touch = get_tsi_value();
		delay(25);
		printf("touch: %d\n\r", touch);
		if (touch > 1000)
		{
			break;
		}

		if (touch > 300)
		{
			if (variable == 100)
			{
				flag = true;
			}

			if (variable == 0)
			{
				flag = false;
			}

			if (flag)
			{
				variable-=10;
			}

			if (!flag)
			{
				variable+=10;
			}
			brightness = variable;
			LED_ON(commands[touch_command].led_color, brightness);
			printf("Set the brightness of LED to %d%%\n\r", brightness);
		}
	}
}

static void calibrate_handler(int argc, char * argv[])
{
	int angle=0;

	if (argv[1]==0)
	{
		printf("Too few arguments for brightness command.\n\r");
		printf("Type help for more information.\n\r");
		return;
	}

	else
	{
		sscanf(argv[1], "%d", &angle);
		calibrated_angle = angle;
	}
	LED_ON(commands[calibrate_command].led_color, brightness);
}
