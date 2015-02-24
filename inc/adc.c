
// includes
#include "adc.h"

void adc_init(enum adc_vref vref, enum adc_prescaler prescaler, enum adc_auto_trigger_source triggerSource)
{
	
	adc_setReferenceVoltage(vref);
	adc_initPrescaler(prescaler);
	adc_setAutoTriggerSource(triggerSource);
	adc_setMux(ADC_MUX_ADC0);
	
	/*
	// Lösche alle Bits
	ADMUX = 0x00;
	
	// Auswahl der Referenzspannung
	switch(AREF) 
	{
		
		case 1: // Referenzspannung AREF = 1.1V 
			sbi(ADMUX,REFS1);	// REFS0 = 0,  REFS1 = 1
		break;
		case 2: // Referenzspannung AREF = 2.56V 
			//ADMUX = (1<<REFS0) | (1<<REFS1);
			sbi(ADMUX,REFS0);	// REFS0 = 1  
			_delay_ms(2);
			sbi(ADMUX,REFS1);	// REFS1 = 1
		break;
		case 5: // Referenzspannung AREF = AVcc 
			sbi(ADMUX,REFS0);	// REFS0 = 1,  REFS1 = 0
		break;
		default: // Referenzspannung AREF = AVcc 
			sbi(ADMUX,REFS0);	// REFS0 = 1,  REFS1 = 0
		break;
	}

	// ADC Control and Status Register A
	ADCSRA = 0x00;			// Lösche alle Bits
	sbi(ADCSRA,ADEN);		// Enable ADC startet den Konversionsvorgang
	//sbi(ADCSRA,ADATE);	// Free Running Mode
	sbi(ADCSRA,ADIE);		// ADC Interrupt wird freigegeben: Interrupt Enable
	// ADC Takt sollte zwischen 50kHz und 200kHz liegen
	// 20MHz / 128 = 156kHz
	sbi(ADCSRA,ADPS2);		// PreSkaler Bit 2
	sbi(ADCSRA,ADPS1);		// PreSkaler Bit 1
	sbi(ADCSRA,ADPS0);		// PreSkaler Bit 0
	
	// ADC Control and Status Register B
	ADCSRB = 0x00;
	sbi(ADCSRB,ADTS2);
	sbi(ADCSRB,ADTS1);
	sbi(ADCSRB,ADTS0);
	*/
	// Den ADC initialisieren und einen sog. Dummyreadout machen
	//adc_startConversion();
	//adc_ConversionCompleteAndClear();
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

int adc_readUnsigned(void){
	adc_startConversion();
	adc_ConversionCompleteAndClear();
	return ADC;
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


