#pragma once

#include "MKL25Z4.h"   

#define RED_LED 18 // PortB Pin 18
#define GREEN_LED 19 // PortB Pin 19
#define BLUE_LED 1 // PortD Pin 1
#define MASK(x) (1 << (x))

void InitGPIO(void);

typedef enum{
	red,
	green,
	blue
} color_t;

void clear_led(color_t);

void set_led(color_t);

void led_control(color_t);