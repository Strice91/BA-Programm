/*
 * Sampling1.c
 *
 * Created: 21.02.2015 17:10:17
 *  Author: Strice
 */ 

#include "Sampling1.h"

volatile int16_t U_ADC;					// converted analog value U
volatile int16_t I_ADC;					// converted analog value I

int16_t I_MEAN = 0, U_MEAN = 0;			// mean values 
int32_t i_adc_sum = 0, u_adc_sum = 0;	// analog value sum
uint64_t U_sqSum = 0, I_sqSum = 0;		// square sum
uint32_t U_RMS = 0, I_RMS = 0;			// root mean square
uint32_t S = 0;							// apparent power
int32_t P = 0;							// active power
int64_t P_Sum = 0;						// sum of instantaneous active power

int smp_cnt = 0;						// sample counter

int screen = 0;							// screen index

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
			debug_ledToggle();
			cli();
			smp_mainCalculation();
			
			if(screen>3) screen = 0;
			
			switch(screen){
				case 0: writeTwoLines("PS"," P",P_Sum,P); break;
				case 1: writeTwoLines("US","IS",U_sqSum,I_sqSum); break;
				case 2: writeTwoLines("UR","IR",U_RMS,I_RMS); break;
				case 3: writeTwoLines("UM","IM",U_MEAN,I_MEAN); break;
			}
			screen++;
			
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
	// read converted analog values
	U_ADC = adc_readUnsigned(ADC_MUX_ADC0);
	I_ADC = adc_readUnsigned(ADC_MUX_ADC1);
	// increase sample counter
	smp_cnt++;
}

void smp_sampleCalculation(void){
	/* Calculation which have to be made
	   right after new samples are read */
	
	// instantaneous values
	int32_t i_temp;
	int32_t u_temp;
	int32_t p_temp;
	
	// add up measured waveforms from ADC
	u_adc_sum += (int32_t)U_ADC;
	i_adc_sum += (int32_t)I_ADC;
	
	// subtract mean 
	u_temp = (int32_t)(U_ADC - U_MEAN);	//TO DO: LP-Filter 
	//u_temp = (int16_t)(A1 * (u_temp + B * (float)u_temp_OLD)); Phase angle correction
	//u_temp = (Const_U * u_temp); // Calib Factor
	i_temp = (int32_t)(I_ADC - I_MEAN); //TO DO: LP-Filter
	//i_temp = (Const_I * i_temp); // Calib Factor
	
	// calculate square sum
	U_sqSum += (uint64_t)(u_temp * u_temp);
	I_sqSum += (uint64_t)(i_temp * i_temp);
	
	// instantaneous active power
	p_temp = ((int64_t)u_temp * (int64_t)i_temp); //TO DO: LP-Filter
	
	// sum up instantaneous active power
	P_Sum += p_temp;
}

void smp_mainCalculation(void){
	/* Calculations which are made once after
	   every measurement period (e.g. 1 sec) */
	
	// calculate RMS values
	U_RMS = (uint32_t)sqrt((U_sqSum/smp_cnt));	//TO DO: smoothing | - Offset?
	I_RMS = (uint32_t)sqrt((I_sqSum/smp_cnt));	//TO DO: smoothing | - Offset?
	
	//TO Do cut of to small values of U_RMS, I_RMS -> noise
	
	// apparent power
	// S = (U_RMS/100) * (I_RMS/1000)
	S = (uint32_t)((uint64_t)U_RMS * (uint64_t)I_RMS); // -> / 100000 ?
	
	// active power
	P = (int32_t)(P_Sum/smp_cnt); // -> + Offest?
	
	// update mean values form this measurement period 
	U_MEAN = (int16_t)(u_adc_sum/smp_cnt);
	I_MEAN = (int16_t)(i_adc_sum/smp_cnt);
	
}

void smp_reset(void){
	/* Reset all sums and counters for the
	   next measurement period */
	
	smp_cnt = 0;
	U_sqSum = 0;
	I_sqSum = 0;
	P_Sum = 0;
	u_adc_sum = 0;
	i_adc_sum = 0;
}

void writeTwoLines(char *name1, char *name2, int32_t V1, int32_t V2){
	char line1[15];
	char line2[15];
	
	sprintf(line1,"%s: %ld",name1,V1);
	sprintf(line2,"%s: %ld",name2,V2);
	
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts(line1);
	lcd_gotoxy(0,1);
	lcd_puts(line2);
}
