/*
 * Power1.c
 *
 * Created: 10.03.2015 13:59:31
 *  Author: ga68bow
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
	adc_endable();
	U_ADC[smp_cnt] = adc_readUnsigned(ADC_MUX_ADC0);
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
	
}

ISR(ADC_vect){
	
	switch(ADMUX & (ADC_MUX_MASK)){
		case ADC_MUX_ADC0:
			I_ADC[smp_cnt] = adc_readUnsigned(ADC_MUX_ADC1);
		break;
		case ADC_MUX_ADC1:
			smp_cnt++;
			adc_disable();
			rtc_checkSecondsAndRemainder();
			toc();
		break;
		default:
		break;
	}
	
	//I_ADC[smp_cnt] = adc_readUnsigned(ADC_MUX_ADC1);
	// increase sample counter
	//smp_cnt++;
	
	//toc();
}

int main(void){
	
	ADCSRA |=  (1<<ADEN) |  (1<<ADATE) | (1<<ADIE) | (1<<ADPS2)  | (1<<ADPS0);
	// -1.ADC-init
	ADMUX |= (1<<REFS0); 					// 0.MUX setzen, AVCC als Ref., Kanal1 ausgewählt
	SFIOR  |=  (1<<ADTS1) |(1<<ADTS0);  	// 1. Auslösung der AD-Wandlung auf Timer setzen
	
	rtc_initSample();
	/*
	TIMSK = (1<<OCIE0);		    			// Timer 0 Compare Match enable
	OCR0=0x32;	        	    			// Einstellen f_a durch Compare Register, momentan:50
	TCNT0 = 0x00;  			    			// 2.Timer starten:
	TCCR0 = (1<<CS01);  					// Prescaler 8 --> Inkr. mit  500 kHz --> f_a = 500 kHz/OCR0 = 10 kHz
	*/
	sei ();
	
	ADCSRA |= (1<<ADSC);		    		// Start der Konvertierung
	
	while(1);
	/*while(ad_menge<20);		    			// while() --> 20 Werte
	
	cli();									// interrupts ausschalten
	TCCR0 = ((0<<CS02) |  (0<<CS00));   	// 8bit-Timer anhalten
	
	
	ADCSRA &= ~(1<<ADEN); 	*/				//ADC deaktivieren
}	//messung_starten()


ISR(TIMER1_COMPA_vect){						// 3. Timer löst AD-Wandlung aus
	SFIOR  &=  ~((1<<ADTS1) |(1<<ADTS0));  	// ADC auf Freerunning setzen
	ADMUX |= (1<<MUX0);    					// MUX toggeln, Kanal2
	kanal=1;
	TCNT1 = 0x00;  							// Rücksetzen des Timers
}


ISR(ADC_vect){			     		// 4./7. ADC ready INT löst aus.

	if (kanal==1) {	 // Wert von Kanal1 holen
		ad_wert[ad_menge]= ADCW; 		// 5. Wert holen
		ADCSRA &= ~(1<<ADATE);   		// 6. auto-trigger off
		kanal=2;
	}
	
	else {	     	 // Wert von Kanal2 holen
		ad_wert2[ad_menge]= ADCW;		// 8. Wert holen, Kanal2 auslesen
		ADMUX &= ~(1<<MUX0);     		// 9. Fertig, wieder zu 0
		SFIOR |=  (1<<ADTS1) |(1<<ADTS0); 	// 9. Fertig, wieder zu 0
		ADCSRA |= (1<<ADATE);	 		// auto-trigger on --> Comp.-Match
		ad_menge++;
	}
}

/*
int main(void)
{
	debug_init();
	uart_init();
	adc_init(ADC_VREF_2V56, ADC_PRESCALER_DIV128, ADC_AUTOTRIGGER_SOURCE_FREERUNNING);
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
			
			//_delay_ms(1000);
			second = 0;
			debug_ledOff();
			sei();
			smp_reset();
		}
    }
}*/