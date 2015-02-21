/*
 * RTC_Test1.c
 *
 * Created: 20.02.2015 12:19:32
 *  Author: Strice
 */ 

/*
#include "rtc.h"
#include <util/delay.h>

ISR(TIMER1_COMPA_vect){
	TCNT1 = 0;
	tgl(PORTD,2);
}

int main(void)
{
   rtc_init();

	while(1){
		_delay_ms(100);
		tgl(PORTD,3);
	}
}*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/signal.h>
#include "../../inc/BitUtilities.h"

#ifndef OCR1A
#define OCR1A OCR1  // 2313 support
#endif

#ifndef WGM12
#define WGM12 CTC1  // 2313 support
#endif

#ifndef PINC
#define KEY_INPUT   PIND    // 2313
#else
#define KEY_INPUT   PINC    // Mega8
#endif
#define LED_DIR     DDRD

//#define XTAL      11059201L   // nominal value
#define XTAL        F_CPU   // after measuring deviation: 1.5s/d

#define DEBOUNCE    4000L        // debounce clock (256Hz = 4msec)

#define uchar unsigned char
#define uint unsigned int

uchar prescaler;
uchar volatile second;          // count seconds


ISR(TIMER1_COMPA_vect)
{
	/************************************************************************/
	/*          Insert Key Debouncing Here          */
	/************************************************************************/
	tgl(PORTD,2);
	#if XTAL % DEBOUNCE                     // bei rest
	OCR1A = XTAL / DEBOUNCE - 1;      // compare DEBOUNCE - 1 times
	#endif
	if( --prescaler == 0 ){
		prescaler = (uchar)DEBOUNCE;
		second++;               // exact one second over
		#if XTAL % DEBOUNCE         // handle remainder
		OCR1A = XTAL / DEBOUNCE + XTAL % DEBOUNCE - 1; // compare once per second
		#endif
	}
}


int main( void )
{
	LED_DIR = 0xFF;
	//while( KEY_INPUT & 1 );               // start with key 0 pressed
	
	TCCR1B = (1<<WGM12) | (1<<CS10);      // divide by 1
	// clear on compare
	OCR1A = XTAL / DEBOUNCE - 1;          // Output Compare Register
	TCNT1 = 0;                            // Timmer startet mit 0
	second = 0;
	prescaler = (uchar)DEBOUNCE;          //software teiler
	
	TIMSK1 = 1<<OCIE1A;                    // beim Vergleichswertes Compare Match
	// Interrupt (SIG_OUTPUT_COMPARE1A)
	sei();
	
	for(;;){
		if( second == 60 )
		second = 0;
		//PORTD = second;         // display second (binary)
		//tgl(PORTD,3);
	}
}