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

/* 	OTHER FILES TO BE INCLUDED	*/
#include "command_process.h"

/*	GENERIC PROTOTYPE FOR HANDLE FUNCTIONS*/
typedef void (*cmd_handler_t)(int, char * argv[]);

/*		STRUCTURE OF COMMANDS AND THEIR DATA	*/
typedef struct{
	const char *cmd_name;
	cmd_handler_t handler;
	const char * help_string;
}cmd_table_t;

/*	HANDLER FUNCTION PROTOTYPES	*/

/*
 * @brief: 		this function is called when user types
 * 				"author" in the command terminal.
 *
 * @returns: 	none
 */
static void author_handler	(int argc, char * argv[]);

/*
 * @brief: 		this function is called when user types
 * 				"dump" in the command terminal. Prints
 * 				the hexdump of requested byte from specific
 * 				memory location.
 *
 * @returns: 	none
 */
static void dump_handler	(int argc, char * argv[]);

/*
 * @brief: 		this function is called when user types
 * 				"help" in the command terminal. Prints
 * 				the brief of all the commands available
 * 				to the user.
 *
 * @returns: 	none
 */
static void help_handler	(int argc, char * argv[]);


/*	TABLE OF COMMANDS EXECUTED IN RESPONSE TO THE USER INPUT 	*/
static const cmd_table_t commands[] = {
		{"author",author_handler,"Prints the name of the Author\r\n"},
		{"dump",dump_handler,"Print a dump of memory represented as hex values. Write dump <start address> <length of dump>\n\r"},
		{"help",help_handler,"Print this help message\r\n"},
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
	 if(!command) {printf("Invalid command: %s\r\n",argv[0]);}
}

static void author_handler(int a, char * argv[])
{
	printf("Tanmay Mahendra Kothale\n\rtanmay.kothale@colorado.edu\n\rGitHub: tanmay-mk\r\n");
}

static void dump_handler(int a, char * argv[])
{
	uint32_t len = 0;
	uint32_t start = 0;

	sscanf(argv[1],"%x",&start);

	if(strstr((char*)argv[2],"0x") || strstr((char*)argv[2],"0X"))//if input is in hex
		{sscanf(argv[2],"%x",&len);}
	else
		{sscanf(argv[2],"%d",&len);}
}

static void help_handler(int argc,char * argv[])
{
	printf("1. author\r\n");
	printf("%s",commands[0].help_string);
	printf("2. dump\r\n");
	printf("%s",commands[1].help_string);
	printf("3. help\r\n");
	printf("%s",commands[2].help_string);
}

