#pragma once
#include "MKL25Z4.h"                    // Device header
#include "delay.h"
#define PTBO_Pin	0
#define PTB1_Pin	1
#define PTA2_Pin	2
#define PTA3_Pin	3

void initPWM(void);

/* int1PNM() */
void initMotorPWM(void) {
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

	// Configure PTB0 (TPM1_CH0) and PTB1 (TPM1_CH1) as PWM pins
	PORTB->PCR[PTBO_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTBO_Pin] |= PORT_PCR_MUX(3) ;

	PORTB->PCR[PTB1_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTB1_Pin] |= PORT_PCR_MUX(3);

	PORTB->PCR[PTA2_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTA2_Pin] |= PORT_PCR_MUX(3) ;

	PORTB->PCR[PTA3_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTA3_Pin] |= PORT_PCR_MUX(3);
	
	// Enable clock for TPM1
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	
	// Select Clock for TPM module
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);	// MCGFLLCLK // MCGPLLCLK / 2

	// MOD: 48000000 / 128 = 375000 / 7500 = 50Hz
	TPM1->MOD = 7500;
	TPM2->MOD = 7500;
	
	// Edge aligned PWM
	// Update SnC register: CMOD = 01, ps = 111 (128)
	TPM1->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM1->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS (7)) ;
	TPM1->SC &= ~(TPM_SC_CPWMS_MASK) ;
	
	TPM2->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM2->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS (7)) ;
	TPM2->SC &= ~(TPM_SC_CPWMS_MASK) ;

	// Enable PWM on TPM Channel 1
	TPM1_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | 
									(TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK) );
	TPM1_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	TPM1_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | 
									(TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK) );
	TPM1_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	// Enable PWM on TPM Channel 2
	TPM2_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | 
									(TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK) );
	TPM2_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
	TPM2_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | 
									(TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK) );
	TPM2_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
}

/**
Go forward
@param speed The desired speed (ranging from 0-100)
*/
void forward(int speed) {
	//change the value later
		TPM1_C1V = 0;
		TPM1_C0V = (speed * TPM1->MOD) / 100;
	
		TPM2_C1V = 0;
		TPM2_C0V = (speed * TPM2->MOD) / 100;
}

void backward(int speed) {
	//change the value later
		TPM1_C0V = 0; // 0xEA6 = 3750 (7500/2, 50% duty cycle)	
		TPM1_C1V = (speed * TPM1->MOD) / 100;
	
		TPM2_C0V = 0;
		TPM2_C1V = (speed * TPM2->MOD) / 100;
}

void stop(){
	TPM1_C1V = 0;
	TPM1_C0V = 0;

	TPM2_C1V = 0; 
	TPM2_C0V = 0;
}

void turn_left(int speed) {
		TPM1_C1V = (speed * TPM1->MOD) / 100;; 
		TPM1_C0V = 0;
	
		TPM2_C1V = 0;	
		TPM2_C0V = (speed * TPM2->MOD) / 100;
}

void turn_right(int speed) {
	//change the value later
		TPM1_C1V = 0;	
		TPM1_C0V = (speed * TPM1->MOD) / 100;
	
		TPM2_C1V = (speed * TPM2->MOD) / 100;
		TPM2_C0V = 0;
}