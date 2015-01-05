/*
 * LCD_Atmel.c
 *
 * Created: 02.01.2015 12:15:42
 *  Author: Strice
 */ 

// #include-Dateien
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "inc\lcd.h"			// LCD Ansteuerung

// Variablen Deklaration
volatile int tc;
char hr=20, min=0, sec=0;
char str[2];

ISR(TIMER1_OVF_vect)
{	
	TCNT1 = 34286; tc++;
}


int main()
{
	TIMSK1 |= _BV(TOIE1); 	// aktivate overflow interrupt of timer1
	TCCR1B |= (1<<CS12);	// prescaler = 256
	TCNT1 = 0xFFFF; 		// FFFF for start
	sei();
	
	initLDC();				// LDC Display und Cursor intialisieren
	
	lcdSetCursor(1,4);
	lcdWrite("20:00:00");
	
	while(1)
	{
		sec=tc;
		if (sec==60)
		{
			tc=0; sec=0; min++;
			if (min==60) 
			{
				min=0; hr++; 
				if (hr==24) hr=0;
			}
			
			sprintf(str,"%02d",min);
			lcdSetCursor(1,7);
			lcdWrite(str);
			
			sprintf(str,"%02d",hr);
			lcdSetCursor(1,4);
			lcdWrite(str);
		}
		
		sprintf(str,"%02d",sec);
		lcdSetCursor(1,10);
		lcdWrite(str);
		
		while(sec == tc);
	}
	
	return 0;
	
	
}