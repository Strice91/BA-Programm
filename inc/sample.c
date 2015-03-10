/*
 * sample.c
 *
 * Created: 25.02.2015 14:05:42
 *  Author: Strice
 */ 
 
// includes
#include "sample.h"

float U_old = 0;
float U_temp;
float I_temp;

void smp_init(void){
	adc_init(ADC_VREF_2V56, ADC_PRESCALER_DIV128, ADC_AUTOTRIGGER_SOURCE_FREERUNNING);
}

void smp_sample(int16_t *U, int16_t *I, int smp_cnt){
	// read converted analog values
	U_ADC = adc_readUnsigned(ADC_MUX_ADC0);
	I_ADC = adc_readUnsigned(ADC_MUX_ADC1);
	// increase sample counter
	smp_cnt++;
}

void smp_addToSquareSum(float *U_SUM, float *I_SUM, float *P_SUM, float *U, float *I){
	*U_SUM = *U_SUM + *U * *U;
	*I_SUM = *I_SUM + *I * *I;
	*P_SUM = *P_SUM + (Ku * *U) * (Ki * *I);
}