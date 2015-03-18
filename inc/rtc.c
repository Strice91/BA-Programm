/*
 * rtc.c
 *
 * Created: 20.02.2015 15:48:38
 *  Author: Strice
 *  Source: http://www.mikrocontroller.net/articles/AVR_-_Die_genaue_Sekunde_/_RTC
 */ 

#include "rtc.h"

void rtc_initSample(void){
	// Sets up a timer which causes an Interrupt
	// Interrupt will occur with the SAMPLE_FREQ
	
	// CTC Modus Clear Timer on Compare Match (Auto Reload)
	sbi(TCCR1B,WGM12);
	// F_CPU Prescaler = 1
	sbi(TCCR1B,CS10);
	// Set Output Compare Register
	// f_sample = f_CPU / (Prescaler * (OCRnx + 1))
	// OCRnx = (f_CPU / (Prescaler * f_sample) ) -1
	OCR1A = XTAL / SAMPLE_FREQ - 1;	
	
	// Initial Set Timer to 0
	TCNT1 = 0;
	// Set second counter to 0
	second = 0;
	// Set timerCounter to Sample Frequency
	// When the ISR was called Sample Frequency times one Second is over
	timerCounter = (uint)SAMPLE_FREQ;	
	// Enable On Compare Interrupt when timer reaches value in OCR1A
	sbi(TIMSK1,OCIE1A);	
	// Set global interrupt enable
	sei();
}

void rtc_checkSecondsAndRemainder(void){
	// Check if it is necessary to increase second counter
	// and update On Compare Register if sample frequency is no 
	// factor of CPU Frequency
	
	#if XTAL % SAMPLE_FREQ						// if there is a remainder
		OCR1A = XTAL / SAMPLE_FREQ - 1;			// compare SAMPLE_FREQ - 1 times
	#endif
	
	if( --timerCounter == 0 ){
		timerCounter = (uint)SAMPLE_FREQ;		// Reset timer Counter for next second
		second++;								// one second is over	
		#if XTAL % SAMPLE_FREQ					// handle remainder
			OCR1A = XTAL / SAMPLE_FREQ + XTAL % SAMPLE_FREQ - 1;
		#endif
	}
}