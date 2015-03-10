/*
 * Power2.c
 *
 * Created: 10.03.2015 16:51:24
 *  Author: ga68bow
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include "../../inc/uart.h"
#include "../../inc/adc.h"
#include "../../inc/rtc.h"
#include "../../inc/debug.h"

volatile int16_t U_ADC;					// converted analog value U
volatile int16_t I_ADC;					// converted analog value I

int16_t I_MEAN = 0, U_MEAN = 0;			// mean values
uint64_t UsqSum = 0, IsqSum = 0;		// square sum
int64_t Psum = 0;						// sum of instantaneous active power

int16_t U_Array[500];					
int16_t I_Array[500];					

int smp_cnt = 0;								// sample counter
char str[100];
int i;

//void smp_sampleCalculation(uint64_t UsqSum, uint64_t IsqSum, int64_t Psum, int16_t U_MEAN, int16_t I_MEAN, int16_t U, int16_t I){
void smp_sampleCalculation(void){
	int32_t u_temp;
	int32_t i_temp;
	int32_t p_temp;
	
	u_temp = ((int32_t)U_ADC - (int32_t)U_MEAN);
	i_temp = ((int32_t)I_ADC - (int32_t)I_MEAN);
	p_temp = (int64_t)u_temp * (int64_t)i_temp;
	
	UsqSum += (uint64_t)(u_temp * u_temp);
	IsqSum += (uint64_t)(i_temp * i_temp);
	Psum += p_temp;
}

void smp_sample(void){
	// read converted analog values
	U_ADC = adc_readUnsigned(ADC_MUX_ADC0);
	I_ADC = adc_readUnsigned(ADC_MUX_ADC1);
	
	// Copy Values to Array
	U_Array[smp_cnt] = U_ADC;
	I_Array[smp_cnt] = I_ADC;
	
	smp_sampleCalculation();
	
	// increase sample counter
	smp_cnt++;

}

void smp_reset(void){
	/* Reset all sums and counters for the
	   next measurement period */
	smp_cnt = 0;
	UsqSum = 0;
	IsqSum = 0;
	Psum = 0;
}

ISR(TIMER1_COMPA_vect){
	tic();
	smp_sample();
	//smp_sampleCalculation();
	rtc_checkSecondsAndRemainder();
	toc();
}

int main(void)
{
	debug_init();
	uart_init();
	adc_init(ADC_VREF_2V56, ADC_PRESCALER_DIV128, ADC_AUTOTRIGGER_SOURCE_FREERUNNING);
	rtc_initSample();
	uart_puts("OK");
	/*
	long long x ;
	long z = 0;
	while(1){
		for(x=100000;x>z;x++){
			sprintf(str,"%lld\n\r",x);
			uart_puts(str);
		}
		
	}*/
	
    while(1)
    {
		//sprintf(str,"%i\n",clock1);
		//uart_puts(str);
		if(second == 1){
			cli();
			debug_ledOn();
			_delay_ms(500);
			sprintf(str,"UsqSum: %012lu \n\r",(int32_t)UsqSum);
			uart_puts(str);
			/*
			uart_puts("S\n");
			
			for(i=0;i<=499;i++){
				sprintf(str,"UsqSum:%lld\n",UsqSum);
				//sprintf("%" PRIu64 "\n", UsqSum);
				uart_puts(str);
			}
			
			for(i=0;i<=499;i++){
				sprintf(str,"%i\n",I_Array[i]);
				uart_puts(str);
			}
			
			uart_puts("E\n");
			*/
			second = 0;
			debug_ledOff();
			smp_reset();
			sei();
		}
    }
}