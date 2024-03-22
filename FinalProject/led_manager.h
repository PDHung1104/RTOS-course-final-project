#pragma once
#include "MKL25Z4.h"    
#include "delay.h"
#define REAR_LED 13 //PTA13
#define FRONT_LED1 1 //PTA1
#define FRONT_LED2 2 //PTA2
#define FRONT_LED3 4 //PTD4
#define FRONT_LED4 12 //PTA12
#define FRONT_LED5 4 //PTA4
#define FRONT_LED6 5 //PTA5
#define FRONT_LED7 8 //PTC8
#define FRONT_LED8 9 //PTC9
#define MASK(x) (1 << (x))

/**
	Initialize the GPIO pins of the front LEDs
*/
void initLEDGPIO(void);

/**
	Light up a front LED with a particular index
*/
void set_led_front(int);

/**
	Turn off a front LED with a particular index
*/
void clear_led_front(int);

void set_led_rear(void);

void clear_led_rear(void);

void set_all_front_led(void);