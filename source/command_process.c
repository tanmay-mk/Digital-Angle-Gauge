/************************************************************************************************
PES Assignment 6
File Name: command_process.c
Author: Tanmay Mahendra Kothale - tanmay.kothale@colorado.edu - GitHub: tanmay-mk
		Howdy Pierce - howdy.pierce@colorado.edu
*************************************************************************************************/

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
	touch_command
};

/*	HANDLER FUNCTION PROTOTYPES	*/

static void author_handler	(int argc, char * argv[]);

static void help_handler	(int argc, char * argv[]);

static void brightness_handler	(int argc, char * argv[]);

static void angle_handler(int argc, char * argv[]);

static void color_handler(int argc, char * argv[]);

static void touch_handler(int argc, char * argv[]);

static void calibrate_handler(int argc, char * argv[]);

/*	TABLE OF COMMANDS EXECUTED IN RESPONSE TO THE USER INPUT 	*/
static cmd_table_t commands[] = {
		{"author",author_handler,"Prints the name of the Author\r\n", BLUE},
		{"help",help_handler,"Print this help message\r\n", GREEN},
		{"brightness",brightness_handler,"Adjusts the brightness of the LED. Write 'brightness <percent>'. \n\rFor example, brightness 50 will set the brightness of LED to 50%.\r\n", MAGENTA},
		{"angle", angle_handler, "Allows user to set a desired angle and then starts blinking the LED until the desired angle is reached. \n\rWrite 'angle <desired angle in degrees>'.\n\r", YELLOW},
		{"color", color_handler, "TO DO.\n\r", CYAN},
		{"touch", touch_handler, "TO DO.\n\r", WHITE},
		{"calibrate", calibrate_handler, "TO DO.\n\r", WHITE},
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

	for(p = input; p < end; p++){

		switch(in_token){

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
	if(argc == 0){//no command found
		return;
	}

	//Todo:Handle the command
	for (int i=0; i < cmd_nos; i++) {
	    if (strcasecmp(argv[0], commands[i].cmd_name) == 0) {
	      commands[i].handler(argc, argv);
	      command = true;
	      break;
	    }

	  }
	 if(!command)
	 {
		 LED_ON(RED, brightness);
		 printf("Invalid command: %s\r\n",argv[0]);
	 }
}

static void brightness_handler(int argc, char * argv[])
{

	uint32_t factor;

	if (argv[1]==0)
	{
		printf("Too few arguments for brightness command.\n\r");
		printf("Type help for more information.\n\r");
		return;
	}

	else
	{
		sscanf(argv[1], "%d", &factor);

		if (factor == 100)
		{
			brightness = 1;
		}
		else if (factor == 0)
		{
			brightness = MAX_DUTY_CYCLE;
		}
		else
		{
			brightness = (int) (MAX_DUTY_CYCLE - (factor * MAX_DUTY_CYCLE)/100);
		}
		LED_ON(commands[brightness_command].led_color, brightness);
	}
}

static void angle_handler(int argc, char * argv[])
{

	uint32_t user_angle;
	int angle=0;

	if (argv[1]==0)
	{
		printf("Too few arguments for brightness command.\n\r");
		printf("Type help for more information.\n\r");
		return;
	}
	else
	{
		sscanf(argv[1], "%d", &user_angle);
		desired_angle = user_angle;
		while (1)
		{
		   	read_full_xyz();
		  	convert_xyz_to_roll_pitch();
		   	angle= fabs(tilt)-calibrated_angle;
		   	printf("Angle: %d\n\r", angle);
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
}

static void color_handler(int argc, char * argv[])
{
	LED_ON(commands[color_command].led_color, brightness);
	bool command = false;
	char color_name[10];
	uint32_t instruction_id = 0xFF;

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

	 else
	 {
		 printf("Invalid color %s\n\r", color_name);
	 }
}

static void touch_handler(int argc, char * argv[])
{
	uint32_t variable;

	if (brightness == 1)
	{
		variable = 100;
	}
	else
	{
		variable = -(((brightness - MAX_DUTY_CYCLE)*100)/MAX_DUTY_CYCLE);
	}

	bool flag = true;
	while (1)
	{
		int touch = get_tsi_value();
		//printf("touch: %d\n\r", touch);
		if (touch > 1000)
		{
			break;
		}

		if (touch > 150)
		{
			if (variable >= 100)
			{
				flag = true;
				//printf("1\n\r");
			}

			if (variable <= 50)
			{
				flag = false;
				//printf("2\n\r");
			}

			if (flag)
			{
				variable-=10;
				//printf("3\n\r");
			}

			if (!flag)
			{
				variable+=10;
				//printf("4\n\r");
			}
			//printf("var: %d\n\r", variable);
			//delay(100);
			if (variable == 100)
			{
				brightness = 1;
			}
			else
			{
				brightness = (int) (MAX_DUTY_CYCLE - (variable * MAX_DUTY_CYCLE)/100);
			}
			LED_ON(commands[touch_command].led_color, brightness);
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
}
