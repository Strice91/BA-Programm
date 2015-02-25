/*
 * sample.c
 *
 * Created: 25.02.2015 14:05:42
 *  Author: Strice
 */ 
 
// includes
#include "sample.h"

void smp_init(void){
	adc_init(ADC_VREF_2V56, ADC_PRESCALER_DIV128, ADC_AUTOTRIGGER_SOURCE_FREERUNNING);
}

void smp_sample(float *U, float *I){
	*U = (float)adc_readUnsigned(ADC_MUX_ADC0);
	*I = (float)adc_readUnsigned(ADC_MUX_ADC1);
}