/*
 * Sampling1.c
 *
 * Created: 21.02.2015 17:10:17
 *  Author: Strice
 */ 

#include "Sampling1.h"

volatile int16_t U_ADC;
volatile int16_t I_ADC;

int16_t I_MEAN = 0, U_MEAN = 0;
uint32_t U_RMS = 0, I_RMS = 0;
uint32_t P = 0;
int32_t i_mean_temp = 0, u_mean_temp = 0;

uint64_t U_sqSum = 0, I_sqSum = 0, P_Sum = 0;;

int smp_cnt;

ISR(TIMER1_COMPA_vect){
	tic();
	smp_sample();
	smp_sampleCalculation();
	rtc_checkSecondsAndRemainder();
	toc();
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
		if(second == 1){
			lcd_gotoxy(0,0);
			debug_ledToggle();
			cli();
			smp_mainCalculation();
			writeTwoLines(P_Sum,P);
			sei();
			smp_reset();
			second = 0;
		}
    }
}

void smp_init(void){
	adc_init(ADC_VREF_2V56, ADC_PRESCALER_DIV128, ADC_AUTOTRIGGER_SOURCE_FREERUNNING);
}

void smp_sample(void){
	U_ADC = adc_readUnsigned(ADC_MUX_ADC0);
	I_ADC = adc_readUnsigned(ADC_MUX_ADC1);
	smp_cnt++;
}

void smp_sampleCalculation(void){
	int32_t i_temp;
	int32_t u_temp;
	int32_t p_temp;
	
	u_mean_temp += (int32_t)U_ADC;
	i_mean_temp += (int32_t)I_ADC;
	
	u_temp = (int32_t)(U_ADC - U_MEAN);
	i_temp = (int32_t)(I_ADC - I_MEAN);
	
	U_sqSum += (uint64_t)(u_temp * u_temp);
	I_sqSum += (uint64_t)(i_temp * i_temp);
	
	p_temp = ((int64_t)u_temp * (int64_t)i_temp);
	P_Sum += p_temp;
}

void smp_mainCalculation(void){
	U_RMS = (uint32_t)(U_sqSum/smp_cnt);
	I_RMS = (uint32_t)(I_sqSum/smp_cnt);
	
	P = (uint32_t)(((uint64_t)U_RMS * (uint64_t)I_RMS) / 100000);
	
	U_MEAN = (int16_t)(u_mean_temp/smp_cnt);
	I_MEAN = (int16_t)(i_mean_temp/smp_cnt);
	
}

void smp_reset(void){
	smp_cnt = 0;
	U_sqSum = 0;
	I_sqSum = 0;
	P_Sum = 0;
	u_mean_temp = 0;
	i_mean_temp = 0;
}

void writeTwoLines(int V1, int V2){
	char line1[15];
	char line2[15];
	
	sprintf(line1,"V1: %07i",V1);
	sprintf(line2,"V2: %07i",V2);
	
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts(line1);
	lcd_gotoxy(0,1);
	lcd_puts(line2);
}
