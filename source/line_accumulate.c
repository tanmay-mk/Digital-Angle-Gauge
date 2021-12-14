/*
 * PES Course Project
 *
 * File Name	: line_accumulate.c
 *
 * Author		: Tanmay Mahendra Kothale
 * 				  tanmay.kothale@colorado.edu
 * 				  GitHub : tanmay-mk
 *
 * Date			: December 12, 2021
 *
 * References	: Alexander G. Dean, https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/main.c
 */

/*	LIBRARY FILES	*/
#include <stdio.h>
#include <stdint.h>

/*	OTHER FILES TO BE INCLUDED	*/
#include "line_accumulate.h"
#include "command_process.h"
#include "touch.h"

void accumulate_line(void)
{
	uint8_t c=0;
	uint8_t buffer[80];
	uint8_t bp = 0;

	while((c != '\r' ) && (c != '\n'))
	{
		c = getchar();
		if(c == '\b')		//check for backspace
		{
			if(bp==0)
			{
				//do nothing if bp=0
				//ignore any more backspaces at this moment
			}
			else
			{
				//if backspace is present, overwrite
				bp--;
				printf("\b \b");
			}
		}
		else
		{
			buffer[bp] = c;
			bp++;
			printf("%c",(char)c);
			//printf("%d",(int)c);
		}
	}
	buffer[bp] = '\0';
	printf("\r\n");
	bp = 0;
	process_command((char *)buffer);
	printf("\n\r? ");
	c = 0;
}

/*EOF*/
