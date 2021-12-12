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

/*
 * @brief: Interrupt service routine of Systick Timer
 *
 * @parameters: none
 *
 * @returns: none
 */
void SysTick_Handler(void);

/*
 * @brief: Keeps track of total time passed since last reset
 *
 * @parameters: none
 *
 * @returns: systick_count : a value that represents the time
 * 			elapsed since last reset in 1/20 of a second
 */
ticktime_t now();

/*
 * @brief: Keeps track of total time passed since change of state
 *
 * @parameters: none
 *
 * @returns: timer_interrupt_count : a value that represents the time
 * 			elapsed since the last state was changed
 */
ticktime_t get_timer();

/*
 * @brief: Resets the timer
 *
 * @parameters: none
 *
 * @returns: none
 */
void reset_timer();

/*
 * @brief: A function that resets a temporary count which contains
 * 			time elapsed since last change of state
 *
 * @parameters: none
 *
 * @returns: none
 */
void reset_count();

void delay (int milliseconds);

#endif /*_SYSTICK_H_*/
