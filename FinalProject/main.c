#include "motor_driver.h"
#include "esp.h"
#include "test_comm.h"

int main(void){
	SystemCoreClockUpdate();
	initUART2(9600);
	InitGPIO();
	initMotorPWM();
	while(1) {
		//unsigned char data = dequeue(&buffer);
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
	}
}