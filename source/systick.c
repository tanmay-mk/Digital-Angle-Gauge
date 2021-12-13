/*********************************************************************************************
 * PES Assignment 4
 * File Name: systick.c
 * Author: Tanmay Mahendra Kothale (tanmay.kothale@colorado.edu) (GitHub: tanmay-mk)
 ********************************************************************************************/
/*
 * OTHER FILES TO BE INCLUDED
 */
#include "systick.h"

/*
 * GLOBAL VARIABLES
 */

/*
 * @brief:
 * 		timer_interrupt_count	: A variable that is returned in get_timer()
 * 								function, and is reset every time when a state
 * 								transition occurs.
 * 		systick_count			: A variable that returns the value of the time
 * 								elapsed since last reset in 1/20 of a second.
 */
uint32_t timer_interrupt_count=0, systick_count=0;

void Init_SysTick()
{
	SysTick->LOAD = ONE_MILLISECOND;  	//initialize systick with top value corresponding to 50mSec
	NVIC_SetPriority (SysTick_IRQn, 3);		//set interrupt priority to 3
	SysTick->VAL = 0;						//force the systick counter to reload
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler()
{
	timer_interrupt_count++;
	systick_count++;
}

void reset_timer()
{
	systick_count = 0;
	timer_interrupt_count = 0;
}

void delay (int milliseconds)
{
	reset_timer();
	while (timer_interrupt_count < milliseconds)
		;
}
