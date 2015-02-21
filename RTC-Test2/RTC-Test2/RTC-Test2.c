/*
 * RTC_Test2.c
 *
 * Created: 21.02.2015 11:01:42
 *  Author: Strice
 */ 


#include <avr/io.h>
#include "../../inc/rtc.h"

ISR(TIMER1_COMPA_vect)
{
	tgl(PORTD,2);
	
	/*
	if( --prescaler == 0 ){
		prescaler = (uchar) SAMPLE_FREQ;
		second++;      // exact one second over
	}
	#if XTAL % SAMPLE_FREQ
	if (prescaler <= XTAL % SAMPLE_FREQ)
	OCR1A += XTAL / SAMPLE_FREQ +1;   // um 1 Takt längere Periode um den Rest abzutragen 
	//else
	#endif
	OCR1A += XTAL / SAMPLE_FREQ;   // kurze Periode 
	*/
	
	#if XTAL % SAMPLE_FREQ						// bei rest
		OCR1A = XTAL / SAMPLE_FREQ - 1;			// compare DEBOUNCE - 1 times
	#endif
	if( --prescaler == 0 ){
		prescaler = (uchar)SAMPLE_FREQ;
		second++;               // exact one second over
		#if XTAL % SAMPLE_FREQ         // handle remainder
			OCR1A = XTAL / SAMPLE_FREQ + XTAL % SAMPLE_FREQ - 1; // compare once per second
		#endif
	}
	
}

/*
ISR(TIMER0_OVF_vect)
{
	tgl(PORTD,3);
	TCNT0 = 177L;
	#if XTAL % SAMPLE_FREQ                     // bei rest
	OCR0A = XTAL / SAMPLE_FREQ - 1;      // compare DEBOUNCE - 1 times
	#endif
	if( --prescaler == 0 ){
		prescaler = (uchar)SAMPLE_FREQ;
		second++;               // exact one second over
		#if XTAL % SAMPLE_FREQ         // handle remainder
		OCR0A = XTAL / SAMPLE_FREQ + XTAL % SAMPLE_FREQ - 1; // compare once per second
		#endif
	}
}*/


int main(void)
{
	rtc_initSample();
	DDRD = 0xFF;
	second = 0;
	//sbi(PORTD,3);
	sei();
	for(;;){
		if( second == 60 )
		second = 0;
		//PORTD = second;         // display second (binary)
		//tgl(PORTD,3);
	}
	
}