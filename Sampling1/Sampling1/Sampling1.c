/*
 * Sampling1.c
 *
 * Created: 21.02.2015 17:10:17
 *  Author: Strice
 */ 

#include "Sampling1.h"

ISR(TIMER1_COMPA_vect){
	debug_ledToggle();
	rtc_checkSecondsAndRemainder();
}

int main(void)
{
	debug_init();
	sampling_init();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

void sampling_init(void){
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_puts("LCD OK");
	
	adc_init(2);
	debug_ledOn();
	lcd_puts(" ADC OK");
	
	lcd_gotoxy(0,1);
	rtc_initSample();
	lcd_puts("RTC OK");
	
}

