/*
 * Sampling2.c
 *
 * Created: 26.02.2015 11:11:58
 *  Author: Strice
 */ 

#include "Sampling2.h"

volatile int16_t adc_read_ch0, adc_read_ch1;
int32_t phase_mean = 0, volt_mean=0;
int16_t lp_phase[LP_ORDER] = {0}, lp_volt[LP_ORDER] = {0}, lp_power[LP_ORDER] = {0};
int16_t p_mean = 0, Vmean = 0;
uint64_t phase_sum = 0, volt_sum = 0;
int64_t watts_sum = 0;

int cnt = 0;
int sample_cnt;

char str[4];
char str2[4];

ISR(TIMER1_COMPA_vect){
	smp_sample();
	sample_cnt++;
	rtc_checkSecondsAndRemainder();
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
		if(cnt > 9999){
			cnt = 0;
		}
		if(second == 1){
			//_delay_ms(100);
			lcd_gotoxy(0,0);
			debug_ledToggle();
			cli();
			sprintf(str,"W %04i", (int)lp_phase[1]);
			lcd_puts(str);
			lcd_gotoxy(0,1);
			sprintf(str2,"SMPs %d",sample_cnt);
			lcd_puts(str2);
			sei();
			sample_cnt = 0;
			cnt++;
			second = 0;
		}

    }
}

void smp_init(void){
	adc_init(ADC_VREF_2V56, ADC_PRESCALER_DIV128, ADC_AUTOTRIGGER_SOURCE_FREERUNNING);
}

void smp_sample(){	
	
	int32_t i_temp, v_temp;
	int16_t phase_read, volt_read, volt_read_filt1;
	static int16_t volt_read_filt2 = 0;
	int16_t lp_powerout = 0;
	
	adc_read_ch0 = adc_readUnsigned(ADC_MUX_ADC0);
	adc_read_ch1 = adc_readUnsigned(ADC_MUX_ADC1);
	
	phase_mean += (int32_t)adc_read_ch0;	
	lp_phase[0] = adc_read_ch0 - p_mean;	
	phase_read = lp_filter(lp_phase);		// low pass filtering of the input signal
	
	volt_mean += (int32_t)adc_read_ch1;
	lp_volt[0] = adc_read_ch1 - Vmean;
	
	volt_read_filt1 = lp_filter(lp_volt);
	volt_read = (int16_t)(A * (volt_read_filt1 + Betha * (float)volt_read_filt2 ));
	volt_read_filt2 = volt_read_filt1;
	
	phase_sum += (uint64_t)((int32_t)phase_read * (int32_t)phase_read);
	volt_sum += (uint64_t)((int32_t)volt_read * (int32_t)volt_read); 
	
	i_temp = Ki * (int32_t)phase_read;
	v_temp = Ku * (int32_t)volt_read;
	
	lp_power[0] = ((int64_t)i_temp * (int64_t)v_temp)>>32;
	lp_powerout = lp_filter(lp_power);
	watts_sum  = watts_sum + lp_powerout;
	
}


int16_t lp_filter(int16_t *inp_array){
	uint8_t i;
	int16_t lp_out = 0;
	//y(n)=h[0]*x[n]+..+h[N-1]x[n-(N-1)]
	for (i=0; i<LP_ORDER; i++){
		lp_out += ((int32_t)lp_coeff[i] * (int32_t)*inp_array++)>>15;
	}
	for(i=LP_ORDER-1;i>0;i--){
		*inp_array--;
		*inp_array = *(inp_array-1);
	}
	return(lp_out);
}


