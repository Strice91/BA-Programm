/*
 * RTC_Test2.c
 *
 * Created: 21.02.2015 11:01:42
 *  Author: Strice
 */ 


#include <avr/io.h>
#include "../../inc/rtc.h"

ISR(TIMER1_COMPA_vect){
	// ISR for the Timer on Compare Interrupt
	
	//------------------------------------------//
	//			Call Sample Method				//
	//------------------------------------------//
	
	tgl(PORTD,2);
	
	//------------------------------------------//
	//		Seconds and Remainder handling		//
	//------------------------------------------//
	
	#if XTAL % SAMPLE_FREQ						// if there is a remainder
		OCR1A = XTAL / SAMPLE_FREQ - 1;			// compare SAMPLE_FREQ - 1 times
	#endif
	if( --timerCounter == 0 ){
		timerCounter = (uint)SAMPLE_FREQ;		// Reset timer Counter for next second
		second++;								// one second is over
		tgl(PORTD,3);
		#if XTAL % SAMPLE_FREQ					// handle remainder
			OCR1A = XTAL / SAMPLE_FREQ + XTAL % SAMPLE_FREQ - 1; 
		#endif
	}
}

int main(void)
{
	rtc_initSample();
	DDRD = 0xFF;
	sei();
	for(;;){
		if( second == 60 ){
			second = 0;
		}
	}
}