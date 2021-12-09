#include "led.h"

void RED_LED_INIT()
{
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;					//Initializing clock
    PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;		//clearing port b pin 18
    PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(1);			//choosing port b pin 18 as gpio
    GPIOB->PDDR |= (1 << RED_LED_PIN);					//setting pin direction as output
}


void GREEN_LED_INIT()
{
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;					//Initializing clock
    PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;	//clearing port b pin 19
    PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(1);		//choosing port b pin 19 as gpio
    GPIOB->PDDR |= (1 << GREEN_LED_PIN);				//setting pin direction as output
}


void BLUE_LED_INIT()
{
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;					//Initializing clock
    PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;		//clearing port d pin 1
    PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(1);		//choosing port d pin 1 as gpio
    GPIOD->PDDR |= (1 << BLUE_LED_PIN);					//setting pin direction as output
}

void RED_LED_ON()
{
	RED_LED_INIT();
    GPIOB->PCOR |= (1 << RED_LED_PIN);		//clearing LED bit
}

void BLUE_LED_ON()
{
	BLUE_LED_INIT();
    GPIOD->PCOR |= (1 << BLUE_LED_PIN);		//clearing LED bit
}

void GREEN_LED_ON()
{
	GREEN_LED_INIT();
    GPIOB->PCOR |= (1 << GREEN_LED_PIN);		//clearing LED bit
}

void WHITE_LED_ON()
{
	RED_LED_ON();
	BLUE_LED_ON();
	GREEN_LED_ON();
}

void LED_ON(int LED_COLOR)
{
	switch(LED_COLOR)
	{
	case WHITE:
		WHITE_LED_ON();
		break;

	case RED:
		RED_LED_ON();
		break;

	case BLUE:
		BLUE_LED_ON();
		break;

	case GREEN:
		GREEN_LED_ON();
		break;

	default:
		break;
	}
}


void RED_LED_OFF()
{
	RED_LED_INIT();
	GPIOB->PSOR |= (1 << RED_LED_PIN);		//setting led bit to 1
}

void BLUE_LED_OFF()
{
	BLUE_LED_INIT();
	GPIOD->PSOR |= (1 << BLUE_LED_PIN);		//setting led bit to 1
}

void GREEN_LED_OFF()
{
	GREEN_LED_INIT();
	GPIOB->PSOR |= (1 << GREEN_LED_PIN);	//setting led bit to 1
}

void WHITE_LED_OFF()
{
	RED_LED_OFF();			//setting all LED bits to 1
	BLUE_LED_OFF();
	GREEN_LED_OFF();
}

void LED_OFF(int LED_COLOR)
{
	switch (LED_COLOR)
	{
	case WHITE:
		WHITE_LED_OFF();
		break;

	case RED:
		RED_LED_OFF();
		break;

	case BLUE:
		BLUE_LED_OFF();
		break;

	case GREEN:
		GREEN_LED_OFF();
		break;

	default:
		break;
	}
}
