/*
 * sample.c
 *
 * Created: 25.02.2015 14:05:42
 *  Author: Strice
 */ 
 
// includes
#include "sample.h"

float U_old = 0;

void smp_init(void){
	adc_init(ADC_VREF_2V56, ADC_PRESCALER_DIV128, ADC_AUTOTRIGGER_SOURCE_FREERUNNING);
}

int16_t smp_sampleU(void){
	// read converted analog values
	return (int16_t)adc_readUnsigned(ADC_MUX_ADC0);
}

int16_t smp_sampleI(void){
	// read converted analog values
	return (int16_t)adc_readUnsigned(ADC_MUX_ADC1);

}

void smp_sampleCalculation(uint64_t *UsqSum, uint64_t *IsqSUM, int64_t *Psum, int16_t U_mean, int16_t I_mean, int16_t U, int16_t I){
	int32_t u_temp;
	int32_t i_temp;
	int32_t p_temp;
	
	u_temp = ((int32_t)U - (int32_t)U_mean);
	i_temp = ((int32_t)I - (int32_t)I_mean);
	p_temp = (int64_t)u_temp * (int64_t)i_temp;
	
	*UsqSum += (uint64_t)(u_temp * u_temp);
	*IsqSUM += (uint64_t)(i_temp * i_temp);
	*Psum += p_temp;
	
}

void smp_reset(int *smp_cnt){
	/* Reset all sums and counters for the
	   next measurement period */
	*smp_cnt = 0;
}