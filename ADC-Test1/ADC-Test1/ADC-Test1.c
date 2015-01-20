/*
 * ADC_Test1.c
 *
 * Created: 04.01.2015 17:32:52
 *  Author: Strice
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "..\..\inc\adc.h"
#include "..\..\inc\lcd.h"

unsigned int ADC_result;
char str[4];
int counter = 0;
float v;
int main(void)
{
	initLDC(); // LDC Display und Cursor intialisieren
	
	//initADC(2);
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	ADMUX = 0x00;
	ADMUX |= (1<<REFS0) | (1<<REFS1);
	
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	v = ADCW;
	v = 0;
	lcdWrite("ADC bereit");
	
	lcdSetCursor(2,0);
	
    while(1)
    {
		ADMUX = 0x00;
		ADMUX |= (1<<REFS0) | (1<<REFS1);
		v = 0;
		
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		v = ADCW;
        //ADC_result = readADC();
		_delay_ms(500);
		sprintf(str,"Cnt:%02dADC:%0.4f",counter,v);
		lcdSetCursor(2,0);
		lcdWrite(str);
		if(counter > 9){
			counter = 0;	
		}
		else{
			counter++;
		}
    }
}