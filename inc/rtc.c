/*
 * rtc.c
 *
 * Created: 20.02.2015 15:48:38
 *  Author: Strice
 */ 

#include "rtc.h"

volatile int tc;

void rtc_initSample(void){
	/*sbi(TIMSK1,OCIE1A);		// Enable Interrupt when Timer reaches value in register OCR1A
	//TCCR1A = 0x80;

	// Prescaler F_CPU / 1024
	sbi(TCCR1B,CS10);
	sbi(TCCR1B,CS12);

	OCR1A = XTAL / SAMPLE_TIME - 1;*/
	TCCR1B = (1<<WGM12) | (1<<CS10);
	OCR1A = XTAL / SAMPLE_FREQ - 1;

	TCNT1 = 0;
	second = 0;
	prescaler = (uchar)SAMPLE_FREQ;
	sbi(TIMSK1,OCIE1A);			// Enable Interrupt when Timer reaches value in register OCR1A
}

void rtc_initSecond(void){
	
}