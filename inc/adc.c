
// includes
#include "adc.h"

unsigned int analog_int;
double analog_double;

void adc_init(enum adc_vref vref, enum adc_prescaler prescaler, enum adc_auto_trigger_source triggerSource)
{
	// Perform ADC initialization methods
	adc_setReferenceVoltage(vref);
	adc_initPrescaler(prescaler);
	adc_setAutoTriggerSource(triggerSource);
}

void adc_initPrescaler(enum adc_prescaler prescaler){
	// Choose the prescaler and set the Enable Bit
	ADCSRA = (uint8_t)prescaler | (1 << ADEN);
}

void adc_setReferenceVoltage(enum adc_vref vref){
	uint8_t temp;
	// Fetch current configuration of ADMUX
	temp = (ADMUX & ~(ADC_VREF_MASK));
	// Overwrite bits for VREF
	temp |= (uint8_t)vref;
	// Store old configuration and new bits in ADMUX
	ADMUX = temp;
}

void adc_setAutoTriggerSource(enum adc_auto_trigger_source triggerSource){
	uint8_t temp;
	// Fetch current configuration of ADTS Register
	temp = (ADC_ADTS_REG & ~(ADC_ADTS_SOURCE_MASK));
	// Overwrite bits for Trigger Source
	temp |= (uint8_t)triggerSource;
	// Store old configuration and new bits in ADTS Register
	ADC_ADTS_REG = temp;
}

void adc_setMux(enum adc_mux_setting input){
	uint8_t temp;

	temp = (ADMUX & ~(ADC_MUX_MASK));

	#if defined(MUX5)
		/* if bit 6 (MUX5) is set: */
		if (input & (1 << 5)) {
			ADCSRB = (1 << MUX5);
		} else {
			ADCSRB &= ~(1 << MUX5);
		}

		/* mask out MUX5 for ADMUX. */
		temp |= ((uint8_t)input & ADC_MUX_MASK);
	#else
		temp |= (uint8_t)input;
	#endif
	ADMUX = temp;
}

void adc_endable(void){
	// Set ADC Enable Bit
	sbi(ADCSRA,ADEN);
}

void adc_disable(void){
	// Clear ADC Enable Bit
	cbi(ADCSRA,ADEN);
}

void adc_endableInterrupt(void){
	// Set Interrupt Enable Bit
	sbi(ADCSRA,ADIE);
}

void adc_disableInterrupt(void){
	// Clear Interrupt Enable Bit
	cbi(ADCSRA,ADIE);
}

void adc_endableAutoTrigger(void){
	// Set Auto Trigger Enable Bit
	sbi(ADCSRA,ADATE);
}

void adc_disableAutoTrigger(void){
	// Clear Auto Trigger Enable Bit
	cbi(ADCSRA,ADATE);
}

int adc_readUnsigned(enum adc_mux_setting mux){
	//adc_setReferenceVoltage(vref);		// Choose Reference Voltage
	adc_setMux(mux);					// Choose Channel
	adc_startConversion();				// Start AD Conversion
	adc_ConversionCompleteAndClear();	// Wait and Clear
	return ADC;
}

double adc_readDouble(enum adc_mux_setting mux){
	adc_setMux(mux);					// Choose Channel
	adc_startConversion();				// Start AD Conversion
	adc_ConversionCompleteAndClear();	// Wait and Clear
	analog_int = ADC;
	analog_double = analog_int / 1023.0;
	return analog_double;
}

void adc_ConversionCompleteAndClear(void){
	//while(ADCSRA & (1<<ADSC));
	while(!(ADCSRA & (1<<ADIF)));	// Wait for the ADC Interrupt Fag
	ADCSRA|=(1<<ADIF);				// Clear Flag
}

void adc_startConversion(void){
	// Set Start Conversion Bit
	sbi(ADCSRA,ADSC);
}


