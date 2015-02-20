/*
 * ADC_Test2.c
 *
 * Created: 16.02.2015 14:10:13
 *  Author: Strice
 */ 
//#include <util/delay.h>
#include <stdio.h>

#include "../../inc/adc.h"
#include "../../inc/lcd.h"
#include "def.c"
#include "../../inc/BitUtilities.h"

unsigned int ADC_result;
char str[4];
int counter = 0;
int i;
int main(void)
{
	DDRD = 0xFF;
	sbi(PORTD,RTC_LED);
	lcd_init(LCD_DISP_ON); // LDC Display und Cursor intialisieren
	lcd_clrscr();
	lcd_puts("LCD");

	adc_init(5);
	lcd_puts(" ADC");
	lcd_gotoxy(0,1);
	
	
	for(i=0;i<100;i++)
    while(1){
		
		
		if(counter>9999){
			counter = 0;
		}
		 
		ADC_result = 0;
		for(i=0;i<100;i++){
			ADC_result = ADC_result + adc_readUnsigned();
			tgl(PORTD,PULSE_LED);
		}
		ADC_result = ADC_result / 100;
		
	    lcd_gotoxy(0,1);
	    sprintf(str,"%04d ADC:%04d",counter,ADC_result);
	    lcd_puts(str);
	    counter++;
    }
}