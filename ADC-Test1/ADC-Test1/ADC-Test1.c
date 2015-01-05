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

int main(void)
{
	initLDC(); // LDC Display und Cursor intialisieren
	
	initADC(5);
	lcdWrite("ADC bereit");
	
	lcdSetCursor(2,0);
	lcdWrite("0.00 V");
	
    while(1)
    {
        ADC_result = readADC();
		_delay_ms(100);
		sprintf(str,"%04d",ADC_result);
		lcdSetCursor(2,0);
		lcdWrite(str);
    }
}