#include "MKL25Z4.h"  
#define UART_RX_PORTE23 23
#include <stdio.h>
#include "circular_buffer.h"
/**
	Use UART2 for communication. Only Rx is used for the MCU
*/

/**
Will implement circular buffer in later updates
*/

//Q_T buffer;
unsigned char buffer;
void UART2_IRQHandler(void){
	if (UART2->S1 && UART_S1_RDRF_MASK) {
		buffer = UART2->D;
	}
}

void initUART2(uint32_t baud_rate) {
	uint32_t divisor, bus_clk;
	
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	//use PORTE23 to read the data from ESP32
	PORTE->PCR[UART_RX_PORTE23] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[UART_RX_PORTE23] |= PORT_PCR_MUX(4);
	
	UART2->C2 &= ~((UART_C2_RE_MASK | UART_C2_RIE_MASK));
	
	
	bus_clk = (DEFAULT_SYSTEM_CLOCK)/2;
	divisor = bus_clk / (baud_rate * 16);
	UART2->BDH = UART_BDH_SBR(divisor >> 8);
	UART2->BDL = UART_BDL_SBR(divisor);
	
	UART2->C1 = 0;
	UART2->S2 = 0;
	UART2->C3 = 0;
	
	NVIC_SetPriority(UART2_IRQn, 128);
	NVIC_ClearPendingIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART2_IRQn);
	
	UART2->C2 |= (UART_C2_RE_MASK | UART_C2_RIE_MASK);
	Q_init(&buffer);
}
