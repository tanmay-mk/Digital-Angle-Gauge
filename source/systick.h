/*********************************************************************************************
 * PES Assignment 4
 * File Name: systick.h
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 ********************************************************************************************/

#ifndef _SYSTICK_H_
#define _SYSTICK_H_

/*
 * LIBRARY FILES TO BE INCLUDED
 */
#include "MKL25Z4.h"

/*
 * MACROS
 */
#define ONE_MILLISECOND 3000L

typedef uint32_t ticktime_t;

/*
 * @brief: Initializes systick timer to generate an interrupt
 * 			every 50 milliseconds
 *
 * @parameters: none
 *
 * @returns: none
 */
void Init_SysTick(void);

void delay (int milliseconds);

#endif /*_SYSTICK_H_*/
