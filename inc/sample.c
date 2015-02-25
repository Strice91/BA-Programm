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

void smp_sample(float *U, float *I){
	/*
	U_temp = (float)(adc_readUnsigned(ADC_MUX_ADC0) - U_DC_OFFSET);
	I_temp = (float)(adc_readUnsigned(ADC_MUX_ADC1) - I_DC_OFFSET);
	U_temp = U_temp;
	*U = A * (U_temp / + Betha * U_old);
	*I = I_temp;*/
	
	*U = (float)(adc_readUnsigned(ADC_MUX_ADC0) - U_DC_OFFSET);
	*I = (float)(adc_readUnsigned(ADC_MUX_ADC1) - I_DC_OFFSET);
}

void smp_addToSquareSum(float *U_SUM, float *I_SUM, float *P_SUM, float *U, float *I){
	*U_SUM = *U_SUM + *U * *U;
	*I_SUM = *I_SUM + *I * *I;
	*P_SUM = *P_SUM + (Ku * *U) * (Ki * *I);
}