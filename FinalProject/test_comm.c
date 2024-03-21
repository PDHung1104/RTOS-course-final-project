#include "test_comm.h"

void InitGPIO(void)
{
	// Enable Clock to PORTB and PORTD
	SIM->SCGC5 |= ((SIM_SCGC5_PORTB_MASK) | (SIM_SCGC5_PORTD_MASK));
	
	// Configure MUX settings to make all 3 pins GPIO
	PORTB->PCR[RED_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[GREEN_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED] |= PORT_PCR_MUX(1);
	
	PORTD->PCR[BLUE_LED] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED] |= PORT_PCR_MUX(1);
	
	// Set Data Direction Registers for PortB and PortD
	PTB->PDDR |= (MASK(RED_LED) | MASK(GREEN_LED));
	PTD->PDDR |= MASK(BLUE_LED);
}

void clear_led(color_t c){
	switch (c){
		case red:
			GPIOB_PSOR |= MASK(RED_LED);
			break;
		case green:
			GPIOB_PSOR |= MASK(GREEN_LED);
			break;
		case blue:
			GPIOD_PSOR |= MASK(BLUE_LED);
			break;
	}
}

void set_led(color_t c){
	switch (c){
		case red:
			GPIOB_PCOR |= MASK(RED_LED);
			break;
		case green:
			GPIOB_PCOR |= MASK(GREEN_LED);
			break;
		case blue:
			GPIOD_PCOR |= MASK(BLUE_LED);
			break;
	}
}

void led_control(color_t c){
	switch (c){
		case red:
			set_led(red);
			break;
		case green:
			set_led(green);
			break;
		case blue:
			set_led(blue);
			break;
	}
}