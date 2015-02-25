/*
 * Sampling1.c
 *
 * Created: 21.02.2015 17:10:17
 *  Author: Strice
 */ 

#include "Sampling1.h"

float U_ADC;
float I_ADC;
int cnt;
int sample_cnt;

char str[4];
char str2[4];

ISR(TIMER1_COMPA_vect){
	smp_sample(&U_ADC, &I_ADC);
	sample_cnt++;
	rtc_checkSecondsAndRemainder();
}

int main(void)
{
	debug_init();
	sampling_init();
	cnt = 0;
    while(1)
    {
		if(cnt > 9999){
			cnt = 0;
		}
		
        _delay_ms(500);
		lcd_gotoxy(0,0);
		debug_ledToggle();
		cli();
		sprintf(str,"I %04i U %04i", (int)I_ADC, (int)U_ADC);
		lcd_puts(str);
		lcd_gotoxy(0,1);
		sprintf(str2,"SMPs %d",sample_cnt);
		lcd_puts(str2);
		sei();
		sample_cnt = 0;
		cnt++;
    }
}

void sampling_init(void){
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_puts("LCD OK");
	
	smp_init();
	lcd_puts(" ADC OK");
	
	lcd_gotoxy(0,1);
	rtc_initSample();
	lcd_puts("RTC OK");
	
	_delay_ms(1000);
	lcd_clrscr();
}


