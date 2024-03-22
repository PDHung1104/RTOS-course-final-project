#include "led_manager.h"    

void initLEDGPIO(void) {
	//config front LED GPIO pins
	SIM->SCGC5 |= ((SIM_SCGC5_PORTA_MASK) | (SIM_SCGC5_PORTD_MASK) | (SIM_SCGC5_PORTC_MASK));
	
	// Configure MUX settings to make all 3 pins GPIO
	//Front LEDs 1, 2, 4, 5, 6 are connected to PORTA
	PORTA->PCR[FRONT_LED1] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[FRONT_LED1] |= PORT_PCR_MUX(1);
	
	PORTA->PCR[FRONT_LED2] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[FRONT_LED2] |= PORT_PCR_MUX(1);
	
	PORTA->PCR[FRONT_LED4] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[FRONT_LED4] |= PORT_PCR_MUX(1);
	
	PORTA->PCR[FRONT_LED5] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[FRONT_LED5] |= PORT_PCR_MUX(1);
	
	PORTA->PCR[FRONT_LED6] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[FRONT_LED6] |= PORT_PCR_MUX(1);
	
	//Front LED 3 is connected to PORTD
	PORTD->PCR[FRONT_LED3] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[FRONT_LED3] |= PORT_PCR_MUX(1);
	
	//Front LEDs 7, 8 are connected to PORTC
	PORTC->PCR[FRONT_LED7] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[FRONT_LED7] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[FRONT_LED8] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[FRONT_LED8] |= PORT_PCR_MUX(1);
	
	// Set Data Direction Registers for PortB and PortD
	PTD->PDDR |= MASK(FRONT_LED3);
	PTA->PDDR |= (MASK(FRONT_LED1) | MASK(FRONT_LED2) | MASK(FRONT_LED4) | MASK(FRONT_LED5) | MASK(FRONT_LED6));
	PTC->PDDR |= (MASK(FRONT_LED7) | MASK(FRONT_LED8));
	
	//config rear LED GPIO pin
	// Configure MUX settings to make all 3 pins GPIO
	PORTA->PCR[REAR_LED] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[REAR_LED] |= PORT_PCR_MUX(1);
	
	// Set Data Direction Registers for PortB and PortD
	PTA->PDDR |= MASK(REAR_LED);
}

void clear_led_front(int index){
		GPIOA_PCOR |= MASK(FRONT_LED1);
		GPIOA_PCOR |= MASK(FRONT_LED2);
		GPIOD_PCOR |= MASK(FRONT_LED3);
		GPIOA_PCOR |= MASK(FRONT_LED4);
		GPIOA_PCOR |= MASK(FRONT_LED5);
		GPIOA_PCOR |= MASK(FRONT_LED6);
		GPIOC_PCOR |= MASK(FRONT_LED7);
		GPIOC_PCOR |= MASK(FRONT_LED8);
}

void set_led_front(int index) {
		switch (index) {
		case 1:
			GPIOA_PSOR |= MASK(FRONT_LED1);
			break;
		case 2:
			GPIOA_PSOR |= MASK(FRONT_LED2);
			break;
		case 3:
			GPIOD_PSOR |= MASK(FRONT_LED3);
			break;
		case 4:
			GPIOA_PSOR |= MASK(FRONT_LED4);
			break;
		case 5:
			GPIOA_PSOR |= MASK(FRONT_LED5);
			break;
		case 6:
			GPIOA_PSOR |= MASK(FRONT_LED6);
			break;
		case 7:
			GPIOC_PSOR |= MASK(FRONT_LED7);
			break;
		case 8:
			GPIOC_PSOR |= MASK(FRONT_LED8);
			break;
		default:
			break;
	}
}

void set_all_front_led(void) {
		GPIOA_PSOR |= MASK(FRONT_LED1);
		GPIOA_PSOR |= MASK(FRONT_LED2);
		GPIOD_PSOR |= MASK(FRONT_LED3);
		GPIOA_PSOR |= MASK(FRONT_LED4);
		GPIOA_PSOR |= MASK(FRONT_LED5);
		GPIOA_PSOR |= MASK(FRONT_LED6);
		GPIOC_PSOR |= MASK(FRONT_LED7);
		GPIOC_PSOR |= MASK(FRONT_LED8);
}

void set_led_rear() {
		GPIOA_PSOR |= MASK(REAR_LED);
}

void clear_led_rear() {
		GPIOA_PCOR |= MASK(REAR_LED);
}