/*
 * PES Course Project
 *
 * File Name	: led.c
 *
 * Author		: Tanmay Mahendra Kothale
 * 				  tanmay.kothale@colorado.edu
 * 				  GitHub : tanmay-mk
 *
 * Date			: December 12, 2021
 */
#include "led.h"

color_config color[TOTAL_COLORS] = {0};
int brightness = 100;

void LED_Color_Config()
{
	color[RED].red_value 			= 0xFF;
	color[RED].green_value 			= 0x00;
	color[RED].blue_value 			= 0x00;

	color[GREEN].red_value 			= 0x00;
	color[GREEN].green_value 		= 0xFF;
	color[GREEN].blue_value 		= 0x00;

	color[BLUE].red_value 			= 0x00;
	color[BLUE].green_value 		= 0x00;
	color[BLUE].blue_value 			= 0xFF;

	color[WHITE].red_value 			= 0xFF;
	color[WHITE].green_value 		= 0xFF;
	color[WHITE].blue_value 		= 0xFF;

	color[YELLOW].red_value 		= 0xFF;
	color[YELLOW].green_value 		= 0xFF;
	color[YELLOW].blue_value 		= 0x00;

	color[MAGENTA].red_value 		= 0xFF;
	color[MAGENTA].green_value 		= 0x00;
	color[MAGENTA].blue_value 		= 0xFF;

	color[CYAN].red_value 			= 0x00;
	color[CYAN].green_value 		= 0xFF;
	color[CYAN].blue_value 			= 0xFF;

	color[NEON].red_value 			= 0x70;
	color[NEON].green_value 		= 0xFF;
	color[NEON].blue_value 			= 0x07;

	color[SKY_BLUE].red_value 		= 0x07;
	color[SKY_BLUE].green_value 	= 0x70;
	color[SKY_BLUE].blue_value 		= 0xFF;

	color[PINK].red_value 		= 0xFF;
	color[PINK].green_value 	= 0x70;
	color[PINK].blue_value 		= 0xFF;
}


/*
 * @brief: 					Initializes the Blue LED to function in Timer and
 * 							PWM mode.
 *
 * @parameters:				None.
 *
 * @returns: 				None.
 */
static void Init_Blue_LED_PWM();

/*
 * @brief: 					Initializes the Red LED to function in Timer and
 * 							PWM mode.
 *
 * @parameters:				None.
 *
 * @returns: 				None.
 */
static void Init_Red_LED_PWM();

/*
 * @brief: 					Initializes the Grenn LED to function in Timer and
 * 							PWM mode.
 *
 * @parameters:				None.
 *
 * @returns: 				None.
 */
static void Init_Green_LED_PWM();


static void Init_Blue_LED_PWM()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;;
	PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(4);

	// Configure TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	//set clock source for tpm: 48 MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	//load the counter and mod
	TPM0->MOD = MAX_DUTY_CYCLE;
	//set TPM count direction to up with a divide by 2 prescaler
	TPM0->SC =  TPM_SC_PS(1);
	// Continue operation in debug mode
	TPM0->CONF |= TPM_CONF_DBGMODE(3);
	// Set channel 1 to edge-aligned low-true PWM
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	// Set initial duty cycle
	//TPM0->CONTROLS[1].CnV = 150;
	// Start TPM
	TPM0->SC |= TPM_SC_CMOD(1);
}

static void Init_Red_LED_PWM()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;;
	PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(3);

	// Configure TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	//set clock source for tpm: 48 MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	//load the counter and mod
	TPM2->MOD = MAX_DUTY_CYCLE;
	//set TPM count direction to up with a divide by 2 prescaler
	TPM2->SC =  TPM_SC_PS(1);
	// Continue operation in debug mode
	TPM2->CONF |= TPM_CONF_DBGMODE(3);
	// Set channel 0 to edge-aligned low-true PWM
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	// Set initial duty cycle
	//TPM2->CONTROLS[0].CnV = 20;
	// Start TPM
	TPM2->SC |= TPM_SC_CMOD(1);
}

static void Init_Green_LED_PWM()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;;
	PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(3);

	// Configure TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	//set clock source for tpm: 48 MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	//load the counter and mod
	TPM2->MOD = MAX_DUTY_CYCLE;
	//set TPM count direction to up with a divide by 2 prescaler
	TPM2->SC =  TPM_SC_PS(1);
	// Continue operation in debug mode
	TPM2->CONF |= TPM_CONF_DBGMODE(3);
	// Set channel 0 to edge-aligned low-true PWM
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	// Set initial duty cycle
	//TPM2->CONTROLS[1].CnV = 100;
	// Start TPM
	TPM2->SC |= TPM_SC_CMOD(1);
}

void LED_init()
{
	Init_Blue_LED_PWM();
	Init_Green_LED_PWM();
	Init_Red_LED_PWM();
}

void LED_ON(uint32_t color_name, int factor)
{
	uint32_t red_value, green_value, blue_value;

	if (color[color_name].red_value == 0)
	{
		red_value = 0;
	}
	else
	{
		red_value = (factor*color[color_name].red_value)/100;
	}

	if (color[color_name].green_value == 0)
	{
		green_value = 0;
	}
	else
	{
		green_value = (factor*color[color_name].green_value)/100;
	}

	if (color[color_name].blue_value == 0)
	{
		blue_value = 0;
	}
	else
	{
		blue_value = (factor*color[color_name].blue_value)/100;
	}

	//printf("r: %d g: %d, b: %d\n\r", red_value, green_value, blue_value);
		TPM2->CONTROLS[0].CnV = red_value;
		TPM2->CONTROLS[1].CnV = green_value;
		TPM0->CONTROLS[1].CnV = blue_value;
}

void LED_OFF(void)
{
		TPM2->CONTROLS[0].CnV = 0;
		TPM2->CONTROLS[1].CnV = 0;
		TPM0->CONTROLS[1].CnV = 0;
}

void test_LED_ON(uint32_t red_value, uint32_t green_value, uint32_t blue_value)
{
		TPM2->CONTROLS[0].CnV = red_value;
		TPM2->CONTROLS[1].CnV = green_value;
		TPM0->CONTROLS[1].CnV = blue_value;
}

/*EOF*/
