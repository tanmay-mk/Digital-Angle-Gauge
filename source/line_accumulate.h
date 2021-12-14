/*
 * PES Course Project
 *
 * File Name	: line_accumulate.h
 *
 * Author		: Tanmay Mahendra Kothale
 * 				  tanmay.kothale@colorado.edu
 * 				  GitHub : tanmay-mk
 *
 * Date			: December 12, 2021
 *
 * References	: Alexander G. Dean, https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/main.c
 */
#ifndef _LINE_ACCUMULATE_H_
#define _LINE_ACCUMULATE_H_

/*	LIBRARY FILES	*/
#include <stdio.h>

/*	FUNCTION PROTOTYPE	*/

/*------------------------------------------------------------------------
 * @brief: 		this function accumulates the line in command
 * 				terminal and also handles backspaces
 *
 * @parameters: none
 *
 * @returns: 	none
 ------------------------------------------------------------------------*/
void accumulate_line(void);

#endif /* _LINE_ACCUMULATE_H_ */
