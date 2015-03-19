/*
 * Sampling3.c
 *
 * Created: 27.02.2015 16:00:46
 *  Author: Strice
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "../../inc/uart.h"
#include "../../inc/adc.h"
#include "../../inc/rtc.h"
#include "../../inc/debug.h"

int16_t U_ADC[1000];					// converted analog value U
int16_t I_ADC[1000];					// converted analog value I

int smp_cnt = 0;								// sample counter
char str[4];
int i;

void smp_sample(void){
	// read converted analog values
	U_ADC[smp_cnt] = adc_readUnsigned(ADC_MUX_ADC0);
	I_ADC[smp_cnt] = adc_readUnsigned(ADC_MUX_ADC1);
	// increase sample counter
	smp_cnt++;

}

void smp_reset(void){
	/* Reset all sums and counters for the
	   next measurement period */
	
	smp_cnt = 0;
}

ISR(TIMER1_COMPA_vect){
	tic();
	smp_sample();
	//smp_sampleCalculation();
	rtc_checkSecondsAndRemainder();
	toc();
}

/*ISR(ADC_vect){
	debug_ledToggle();
}*/

int main(void)
{
	debug_init();
	uart_init();
	adc_init(ADC_VREF_AREF, ADC_PRESCALER_DIV128, ADC_AUTOTRIGGER_SOURCE_FREERUNNING);
	rtc_initSample();
	uart_puts("OK");
    while(1)
    {
		//sprintf(str,"%i\n",clock1);
		//uart_puts(str);
		if(second == 1){
			cli();
			debug_ledOn();
			uart_puts("S\n");
			
			for(i=0;i<=999;i++){
				sprintf(str,"%i\n",U_ADC[i]);
				uart_puts(str);
			}
			
			for(i=0;i<=999;i++){
				sprintf(str,"%i\n",I_ADC[i]);
				uart_puts(str);
			}
			
			uart_puts("E\n");
			
			second = 0;
			debug_ledOff();
			sei();
			smp_reset();
		}
    }
}