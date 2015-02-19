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
int main(void)
{
	initLDC(); // LDC Display und Cursor intialisieren
	
	initADC(2);
	lcdWrite("ADC bereit");
	
	lcdSetCursor(2,0);
	
    while(1)
    {
        ADC_result = readADC();
		sprintf(str,"Cnt:%02dADC:%04d",counter,ADC_result);
		
		_delay_ms(500);
		
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