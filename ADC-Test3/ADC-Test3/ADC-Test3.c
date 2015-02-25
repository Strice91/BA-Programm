/*
 * ADC_Test3.c
 *
 * Created: 24.02.2015 15:07:43
 *  Author: ga68bow
 */ 


#include <avr/io.h>
#include <stdio.h>
#include "../../inc/adc.h"
#include "../../inc/lcd.h"
#include "../../inc/debug.h"
#include <util/delay.h>

char str[4];
uint16_t analog_val;

int main(void)
{
	debug_init();
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_puts("LCD OK");
	lcd_gotoxy(0,1);
	
	adc_init(ADC_VREF_2V56, ADC_PRESCALER_DIV128, ADC_AUTOTRIGGER_SOURCE_FREERUNNING);
	
	//debug_ledOn();
	
    while(1)
    {
		_delay_ms(500);
		analog_val = adc_readUnsigned(ADC_MUX_ADC0);
		sprintf(str,"CH 0 -> ADC:%04d",analog_val);
        lcd_puts(str);
		lcd_gotoxy(0,1);
		
		_delay_ms(500);
		analog_val = adc_readUnsigned(ADC_MUX_ADC1);
		sprintf(str,"CH 1 -> ADC:%04d",analog_val);
		lcd_puts(str);
		lcd_gotoxy(0,1);
    }
}