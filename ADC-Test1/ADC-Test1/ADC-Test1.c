/*
 * ADC_Test1.c
 *
 * Created: 04.01.2015 17:32:52
 *  Author: Strice
 */ 

#include <stdio.h>
#include <avr/io.h>

#include "../../inc/lcd.h"
#include "../../inc/adc.h"

unsigned int ADC_result;
char str[4];
int counter = 0;
int main(void)
{
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	
	adc_init(2);
	lcd_puts("ADC ready!");
	
	while(1){
		ADC_result = adc_readUnsigned();
		if(counter>9999){
			counter = 0;
		}
		lcd_gotoxy(0,1);
		sprintf(str,"%04d ADC:%04d",counter,ADC_result);
		lcd_puts(str);
		counter++;
	}
}