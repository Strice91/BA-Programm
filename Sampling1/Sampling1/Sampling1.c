/*
 * Sampling1.c
 *
 * Created: 21.02.2015 17:10:17
 *  Author: Strice
 */ 

#include "Sampling1.h"

float U_ADC;
float I_ADC;

float U_old = 0;
float U_temp;
float I_temp;

float SCALE = 1023.0;

int cnt = 0;
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
	
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_puts("LCD OK");
	
	smp_init();
	lcd_puts(" ADC OK");
	
	lcd_gotoxy(0,1);
	rtc_initSample();
	lcd_puts("RTC OK");
		
    while(1)
    {
		if(cnt > 9999){
			cnt = 0;
		}
		if(second == 1){
			//_delay_ms(100);
			lcd_gotoxy(0,0);
			debug_ledToggle();
			cli();
			sprintf(str,"I %04i U %04i", (int)(I_ADC*1), (int)(U_ADC*1));
			lcd_puts(str);
			lcd_gotoxy(0,1);
			sprintf(str2,"SMPs %d",sample_cnt);
			lcd_puts(str2);
			sei();
			sample_cnt = 0;
			cnt++;
			second = 0;
		}

    }
}

void smp_init(void){
	adc_init(ADC_VREF_2V56, ADC_PRESCALER_DIV128, ADC_AUTOTRIGGER_SOURCE_FREERUNNING);
}

void smp_sample(float *U, float *I){
	U_temp = (float)(adc_readUnsigned(ADC_MUX_ADC0) - U_DC_OFFSET);
	I_temp = (float)(adc_readUnsigned(ADC_MUX_ADC1) - I_DC_OFFSET);
	U_temp = A * ((U_temp / SCALE) + Betha * U_old);
	*U = U_temp;
	U_old = U_temp;
	*I = I_temp / SCALE;
	
	//*U = (float)(adc_readUnsigned(ADC_MUX_ADC0) - U_DC_OFFSET);
	//*I = (float)(adc_readUnsigned(ADC_MUX_ADC1) - I_DC_OFFSET);
}

void smp_addToSquareSum(float *U_SUM, float *I_SUM, float *P_SUM, float *U, float *I){
	*U_SUM = *U_SUM + *U * *U;
	*I_SUM = *I_SUM + *I * *I;
	*P_SUM = *P_SUM + (Ku * *U) * (Ki * *I);
}


