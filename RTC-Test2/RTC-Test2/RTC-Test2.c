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
	
	rtc_checkSecondsAndRemainder();
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