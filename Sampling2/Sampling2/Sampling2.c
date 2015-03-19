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
int64_t watts_sum = 0, watts_sum_calib = 0;

uint16_t Vrms[5] = {0}, Irms[5] = {0};
uint16_t active_power[5] = {0},apparent_power = 0;
int32_t volt_temp, shunt_temp;
int32_t active_energy_signed = 0;
int16_t power_factor;

int cnt = 0;
int sample_cnt;

char str[4];
char str2[4];

ISR(TIMER1_COMPA_vect){
	tic();
	smp_sample();
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
		if(cnt > 9999){
			cnt = 0;
		}
		if(second == 1){
			debug_ledToggle();
			cli();
			smp_calculate();
			sei();
			cnt++;
			second = 0;
		}

    }
}

void smp_init(void){
	adc_init(ADC_VREF_AREF, ADC_PRESCALER_DIV128, ADC_AUTOTRIGGER_SOURCE_FREERUNNING);
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
	
	//i_temp = Ki * (int32_t)phase_read;
	//v_temp = Ku * (int32_t)volt_read;
	
	i_temp = (int32_t)phase_read;
	v_temp = (int32_t)volt_read;
	
	lp_power[0] = ((int64_t)i_temp * (int64_t)v_temp)>>32;
	lp_powerout = lp_filter(lp_power);
	watts_sum  = watts_sum + lp_powerout;
	
	sample_cnt++;
	
}

void smp_calculate(void){
	float kwh_temp=0;
	
	
	
	for(int8_t avg_count = 1; avg_count <4; avg_count++)
	{
		Irms[avg_count]          =  Irms[avg_count+1];
		Vrms[avg_count]          =  Vrms[avg_count+1];
		active_power[avg_count]  = active_power[avg_count+1];
	}
	
	shunt_temp =    (int32_t)((phase_sum/sample_cnt));
	if (shunt_temp < 5){ 
		shunt_temp = 0;
	}
	Irms[4]  = ((int32_t)(sqrt(shunt_temp)*1000))>>16;
	Irms[0]  = ((int32_t)Irms[1] + (int32_t)Irms[2] + (int32_t)Irms[3] + (int32_t)Irms[4])>>2;
	Irms[2]  = Irms[0];
	
	writeTwoLines((int)Irms[0],(int)Irms[1]);
	
	volt_temp =  (int32_t)(volt_sum/sample_cnt);
	if(volt_temp < 5)
	volt_temp = 0;
	Vrms[4]  = (((int32_t)(sqrt(volt_temp)*100))>>16);
	//for smoothing the Vrms
	Vrms[0]  = ((int32_t)Vrms[1] + (int32_t)Vrms[2] + (int32_t)Vrms[3] + (int32_t)Vrms[4])>>2;
	Vrms[2]  = Vrms[0];
	
	apparent_power = ((uint64_t)Vrms[0] * (uint64_t)Irms[0])/100000;
	
	active_energy_signed =  ((watts_sum)  / sample_cnt);
	watts_sum_calib = watts_sum;
	watts_sum = 0;
	
	//for smoothing the active power
	active_power[4] = (uint16_t)(abs(active_energy_signed));
	active_power[0] = ( (uint16_t)(active_power[1]) + (uint16_t)(active_power[2]) + (uint16_t)(active_power[3]) + (uint16_t)(active_power[4]) )>>2;   ////for smoothing the kW
	active_power[2] = active_power[0];
	
	if(active_energy_signed < 3 && active_energy_signed > -3)
	{
		active_power[0] = 0;
		Irms[0] = 0;
		apparent_power = 0;
	}
	if (Irms[0] < 10)
	{
		Irms[0] = 0;
		active_power[0] = 0;
		apparent_power = 0;
	}
	
	//power factor calculation
	power_factor = (int16_t)(1000 * (float)active_power[0]/(float)apparent_power);
	if(power_factor >1000)
	{
		apparent_power = active_power[0];
		power_factor = 1000;
	}
	else if(power_factor < 0)
	{
		power_factor = 0;
	}
	
	kwh_temp = ((float)(active_power[0])/3600000);
	
	//Dc offset voltage calculation
	Vmean  = (int16_t)(volt_mean/sample_cnt);
	p_mean = (int16_t)(phase_mean/sample_cnt);
	phase_mean = 0;
	volt_mean = 0;

	sample_cnt = 0;
	volt_sum = 0;
	phase_sum = 0;
	watts_sum = 0;
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

void writeTwoLines(int V1, int V2){
	char line1[15];
	char line2[15];
	
	sprintf(line1,"V1: %04i",V1);
	sprintf(line2,"V2: %04i",V2);
	
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts(line1);
	lcd_gotoxy(0,1);
	lcd_puts(line2);
}


