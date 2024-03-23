#pragma once
#include <cmsis_os2.h>
#include "MKL25Z4.h"  
#include "delay.h"
#include "pitches.h"
#define PTE31_Pin 31

void initPWMBuzzer(void);

uint32_t freq_to_mod(uint32_t);

void track_tone(void);

void stop_tone(void);
