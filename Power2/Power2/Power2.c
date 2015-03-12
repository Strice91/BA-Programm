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
uint32_t U_RMS = 0, I_RMS = 0;			// root mean square
int32_t i_sum = 0, u_sum = 0;			// analog value sum
int64_t Psum = 0;						// sum of instantaneous active power

uint32_t S = 0;							// apparent power
int32_t P = 0;							// active power
int16_t power_factor;

int16_t U_Array[500];					
int16_t I_Array[500];					

int smp_cnt = 0;								// sample counter
char str[100];
int i;



void smp_sample(void){
	// read converted analog values
	U_ADC = adc_readUnsigned(ADC_MUX_ADC0);
	I_ADC = adc_readUnsigned(ADC_MUX_ADC1);
	
	// Copy Values to Array
	U_Array[smp_cnt] = U_ADC;
	I_Array[smp_cnt] = I_ADC;
	
	// increase sample counter
	smp_cnt++;

}

//void smp_sampleCalculation(uint64_t UsqSum, uint64_t IsqSum, int64_t Psum, int16_t U_MEAN, int16_t I_MEAN, int16_t U, int16_t I){
void smp_sampleCalculation(void){
	/* Calculation which have to be made
	   right after new samples are read */
	int32_t u_temp;
	int32_t i_temp;
	int32_t p_temp;
	
	u_sum += (int32_t)U_ADC;
	i_sum += (int32_t)I_ADC;
	
	u_temp = ((int32_t)U_ADC - (int32_t)U_MEAN);
	i_temp = ((int32_t)I_ADC - (int32_t)I_MEAN);
	p_temp = (int64_t)u_temp * (int64_t)i_temp;
	
	UsqSum += (uint64_t)(u_temp * u_temp);
	IsqSum += (uint64_t)(i_temp * i_temp);
	Psum += p_temp;
}

void smp_mainCalculation(void){
	/* Calculations which are made once after
	   every measurement period (e.g. 1 sec) */
	
	// calculate RMS values
	U_RMS = (uint32_t)sqrt((UsqSum*100/smp_cnt));	//TO DO: smoothing | - Offset?
	I_RMS = (uint32_t)sqrt((IsqSum*100/smp_cnt));	//TO DO: smoothing | - Offset?
	
	//TO Do cut of to small values of U_RMS, I_RMS -> noise
	
	// apparent power
	// S = (U_RMS/100) * (I_RMS/1000)
	S = (uint32_t)((uint64_t)U_RMS * (uint64_t)I_RMS); // -> / 100000 ?
	
	// active power
	P = (int32_t)(Psum/smp_cnt)*100; // -> + Offest?
	
	power_factor = (int16_t)(1000*(float)P/(float)S);
	
	// update mean values form this measurement period 
	U_MEAN = (int16_t)(u_sum/smp_cnt);
	I_MEAN = (int16_t)(i_sum/smp_cnt);
	
}

void smp_reset(void){
	/* Reset all sums and counters for the
	   next measurement period */
	smp_cnt = 0;
	UsqSum = 0;
	IsqSum = 0;
	u_sum = 0;
	i_sum = 0;
	Psum = 0;
}

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
	uart_init();
	adc_init(ADC_VREF_2V56, ADC_PRESCALER_DIV128, ADC_AUTOTRIGGER_SOURCE_FREERUNNING);
	rtc_initSample();
	uart_puts("OK\n\r\n\r");
	
    while(1)
    {

		if(second == 1){
			cli();
			debug_ledOn();
			
			smp_mainCalculation();
			
			_delay_ms(500);
			sprintf(str,"UsqSum|%10lu| IsqSum|%10lu| Psum|%10li| Umean|%5i| Imean|%5i| URMS|%10lu| IRMS|%10lu| S|%10lu| P|%10li| cos|%5i|\n\r",(uint32_t)UsqSum,(uint32_t)IsqSum,(int32_t)Psum,U_MEAN,I_MEAN,U_RMS,I_RMS,S,P,power_factor);
			uart_puts(str);
			
			/*
			uart_puts("S\n\r");
			for(i=0;i<=499;i++){
				sprintf(str,"%i\n\r",U_Array[i]);
				uart_puts(str);
			}
			for(i=0;i<=499;i++){
				sprintf(str,"%i\n\r",I_Array[i]);
				uart_puts(str);
			}
			uart_puts("E\n\r");
			*/
			second = 0;
			debug_ledOff();
			
			smp_reset();
			sei();
		}
    }
}