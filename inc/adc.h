/*
 * adc.h
 *
 * Created: 28.01.2015 09:55:24
 *  Author: Strice
 *	Source: Atmel-Studio standard Lib ADC
 */ 

#ifndef ADC_H
	#define ADC_H

	// includes
	#include "BitUtilities.h"
	#include <avr/io.h>
	#include <util/delay.h>

	//  ADC prescaler mask
	#define ADC_PRESCALER_MASK		(1 << ADPS2 | 1 << ADPS1 | 1 << ADPS0)
	//  ADC voltage reference mask
	#define ADC_VREF_MASK			(1 << REFS1 | 1 << REFS0)
	//  ADC MUX mask
	#define ADC_MUX_MASK			(1 << MUX3 | 1 << MUX2 | 1 << MUX1 | 1 << MUX0)
	//  ADC Auto Trigger mask
	#define ADC_ADTS_SOURCE_MASK	(1 << ADTS2 | 1 << ADTS1 | 1 << ADTS0)
	//  ADC Trigger Source Register
	#define ADC_ADTS_REG ADCSRB

	// ADC prescaler settings
	enum adc_prescaler {
		ADC_PRESCALER_DIV2 =	(0x1 << ADPS0),	//  Divide system clock by 2
		ADC_PRESCALER_DIV4 =	(0x2 << ADPS0),	//  Divide system clock by 4
		ADC_PRESCALER_DIV8 =	(0x3 << ADPS0),	//  Divide system clock by 8
		ADC_PRESCALER_DIV16 =	(0x4 << ADPS0),	//  Divide system clock by 16
		ADC_PRESCALER_DIV32 =	(0x5 << ADPS0),	//  Divide system clock by 32
		ADC_PRESCALER_DIV64 =	(0x6 << ADPS0),	//  Divide system clock by 64
		ADC_PRESCALER_DIV128 =	(0x7 << ADPS0),	//  Divide system clock by 128
	};

	// ADC voltage references
	enum adc_vref {
		ADC_VREF_1V1 =	(1<<REFS1),				// Set reference voltage to 1.1V 
		ADC_VREF_2V56 = (1<<REFS0)|(1<<REFS1),	// Set reference voltage to 2.56V 
		ADC_VREF_AVCC = (1<<REFS0),				// Set reference voltage to AVCC
		ADC_VREF_AREF = 0x00,					// Set reference voltage to external AREF
	};

	// ADC input MUX settings
	enum adc_mux_setting {
		// Gains of x10 and x200 should only be used with 2.56V
		ADC_MUX_ADC0 = (0x0<<MUX0),	//  Select Channel 0
		ADC_MUX_ADC1 = (0x1<<MUX0), //  Select Channel 1
		ADC_MUX_ADC2 = (0x2<<MUX0),	//  Select Channel 2
		ADC_MUX_ADC3 = (0x3<<MUX0),	//  Select Channel 3
		ADC_MUX_ADC4 = (0x4<<MUX0),	//  Select Channel 4
		ADC_MUX_ADC5 = (0x5<<MUX0),	//  Select Channel 5
		ADC_MUX_ADC6 = (0x6<<MUX0),	//  Select Channel 6
		ADC_MUX_ADC7 = (0x7<<MUX0),	//  Select Channel 7
		
		// Differential mode MUX settings are missing
	};

	// ADC Auto Trigger sources
	enum adc_auto_trigger_source {
		ADC_AUTOTRIGGER_SOURCE_FREERUNNING = (0x0<<ADTS0),		//  Free Running mode
		ADC_AUTOTRIGGER_SOURCE_ANALOG_COMPARATOR = (0x1<<ADTS0),//  Analog Comparator
		ADC_AUTOTRIGGER_SOURCE_EIR0 = (0x2 << ADTS0),			//  External Interrupt Request 0
		ADC_AUTOTRIGGER_SOURCE_TC0_COMPARE = (0x3 <<  ADTS0),	//  Timer/Counter0 Compare Match
		ADC_AUTOTRIGGER_SOURCE_TC0_OVERFLOW = (0x4 << ADTS0),	//  Timer/Counter0 Overflow
		ADC_AUTOTRIGGER_SOURCE_TC1_COMPARE_B = (0x5 << ADTS0),	//  Timer/Counter1 Compare Match B
		ADC_AUTOTRIGGER_SOURCE_TC1_OVERFLOW = (0x6 << ADTS0),	//  Timer/Counter1 Overflow
		ADC_AUTOTRIGGER_SOURCE_TC1_CAPTURE = (0x7 << ADTS0),	//  Timer/Counter1 Capture Event
	};

	// Initialization
	void adc_init(enum adc_vref vref, enum adc_prescaler prescaler, enum adc_auto_trigger_source triggerSource);
	void adc_initPrescaler(enum adc_prescaler prescaler);
	void adc_setReferenceVoltage(enum adc_vref vref);
	void adc_setAutoTriggerSource(enum adc_auto_trigger_source triggerSource);
	void adc_setMux(enum adc_mux_setting input);

	// Enable / Disable Functions
	void adc_endable(void);
	void adc_disable(void);
	void adc_endableInterrupt(void);
	void adc_disableInterrupt(void);
	void adc_endableAutoTrigger(void);
	void adc_disableAutoTrigger(void);

	// Read ADC
	int adc_readUnsigned(enum adc_mux_setting mux);
	double adc_readDouble(enum adc_mux_setting mux);
	void adc_startConversion(void);
	void adc_ConversionCompleteAndClear(void);

#endif //ADC_H
