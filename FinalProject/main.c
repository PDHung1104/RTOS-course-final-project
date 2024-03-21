#include "motor_driver.h"
#include "esp.h"
#include "test_comm.h"

int main(void){
	SystemCoreClockUpdate();
	initUART2(9600);
	InitGPIO();
	while(1) {
		unsigned char data = dequeue(&buffer);
		switch (data) {
			case 0x82: //stop
				stop();
				break;
			case 0x83: //forward
				forward(70);
				break;
			case 0x84: //backward
				backward(70);
				break;
			case 0x85: //turn left
				
				break;
			case 0x86: //turn right
				
				break;
		}
	}
}