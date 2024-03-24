#pragma once
#include <cmsis_os2.h>
#include "MKL25Z4.h"  
#include "delay.h"
#include "pitches.h"
#define PTE31_Pin 31

typedef enum {
	track,
	end
} tone_type;

void initPWMBuzzer(void);

uint32_t freq_to_mod(uint32_t);

void track_tone(tone_type*);

void stop_tone(tone_type*);
