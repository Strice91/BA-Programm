/*
 * RTC_Test2.c
 *
 * Created: 21.02.2015 11:01:42
 *  Author: Strice
 */ 


#include <avr/io.h>
#include "../../inc/rtc.h"
#include "../../inc/debug.h"

ISR(TIMER1_COMPA_vect){
	// ISR for the Timer on Compare Interrupt
	
	//------------------------------------------//
	//			Call Sample Method				//
	//------------------------------------------//
	
	tic();
	rtc_checkSecondsAndRemainder();
	toc();
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