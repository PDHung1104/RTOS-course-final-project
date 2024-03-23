#include "motor_driver.h"
#include "esp.h"
#include "led_manager.h"
#include <cmsis_os2.h>
#include "buzzer.h"

typedef enum {
	moving,
	stopping
} move_state;

typedef enum {
	track,
	end
} tone_type;

move_state state = stopping;
tone_type tone = track;

osThreadId_t brainId, motorId, frontId, rearId, audioId;

unsigned char buffer;
void UART2_IRQHandler(void){
	if (UART2->S1 && UART_S1_RDRF_MASK) {
		buffer = UART2->D;
		//set flag to put t_brain into READY
		osThreadFlagsSet(brainId, 0x0001);
	}
}

void tBrain(void) {
	for(;;){
		osThreadFlagsWait(0x0001, osFlagsWaitAny, osWaitForever);
		switch(buffer) {
			case 0x82: //stop
				osThreadFlagsSet(motorId, 0x0001);
				state = stopping;
				break;
			case 0x83: //forward
			case 0x84: //backward
			case 0x85: //turn left
			case 0x86: //turn right
				//add set flag here to put t_motor into READY
				osThreadFlagsSet(motorId, 0x0001);
				state = moving;
				break;
			case 0x87: //play end tone
				tone = end;
				break;
			case 0x88: //change back to track tone
				tone = track;
				break;
		}
		osThreadFlagsClear(0x0001); //clear the flag to block this thread
	}
}

void tMotorControl(void){
	for(;;) {
		//add wait flag here
		osThreadFlagsWait(0x0001, osFlagsWaitAny, osWaitForever);
		switch (buffer) {
			case 0x82: //stop
				stop();
				break;
			case 0x83: //forward
				forward(50);
				break;
			case 0x84: //backward
				backward(50);
				break;
			case 0x85: //turn left
				turn_left(50);
				break;
			case 0x86: //turn right
				turn_right(50);
				break;
		}
		// add clear flag here to block t_motor
		osThreadFlagsClear(0x0001);
	}
}

//break tLED into 2 sub-threads: tFront and tRear
void tFront(void) {
	for(;;){
		if (state == moving) {
			for(int i = 1; i <= 8 && state == moving; i++){
				set_led_front(i);
				osDelay(1000U);
				clear_led_front(i); 
				osDelay(1000U);
			}
		} else {
			set_all_front_led();
			osThreadYield();//switch to another task with the same priority
		}
	}
}

void tRear(void) {
	for(;;) {
		if (state == moving) {
			osDelay(500U);
			set_led_rear();
			osDelay(500U);
			clear_led_rear();
		} else {
			osDelay(250U);
			set_led_rear();
			osDelay(250U);
			clear_led_rear();
		}
	}
}

void tAudio(void) {
	for(;;) {
		if (tone == track) {
			track_tone();
		} else {
			stop_tone();
		}
	}
}

int main(void){
	SystemCoreClockUpdate();
	initUART2(9600);
	initMotorPWM();
	initLEDGPIO();
	initPWMBuzzer();
	
	osKernelInitialize();
	audioId = osThreadNew(tAudio, NULL, NULL);
	frontId = osThreadNew(tFront, NULL, NULL);
	rearId = osThreadNew(tRear, NULL, NULL);
	brainId = osThreadNew(tBrain, NULL, NULL);
	motorId = osThreadNew(tMotorControl, NULL, NULL);
	osThreadSetPriority(brainId, osPriorityHigh);
	osThreadSetPriority(motorId, osPriorityNormal);
	osThreadSetPriority(frontId, osPriorityLow);
	osThreadSetPriority(rearId, osPriorityLow);
	osThreadSetPriority(audioId, osPriorityLow);
	osKernelStart();
	for(;;);
}