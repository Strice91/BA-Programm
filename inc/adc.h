
// includes
#include <util/delay.h>
#include "BitUtilities.h"

// Config ADC
#define ADCPORT = ADCSRA;
float voltage;
// 
void initADC(int AREF)
{
	// Lösche alle Bits
	ADMUX = 0x00;
	
	// Auswahl der Referenzspannung
	switch(AREF) 
	{
		case 1: // Referenzspannung AREF = 1.1V 
			sbi(ADMUX,REFS1);			// REFS0 = 0,  REFS1 = 1
		break;
		case 2: // Referenzspannung AREF = 2.56V 
			sbi(ADMUX,(REFS1|REFS0));	// REFS0 = 1,  REFS1 = 1
		break;
		case 5: // Referenzspannung AREF = AVcc 
			sbi(ADMUX,REFS0);			// REFS0 = 1,  REFS1 = 0
		break;
		default: // Referenzspannung AREF = AVcc 
			sbi(ADMUX,REFS0);			// REFS0 = 1,  REFS1 = 0
		break;
	}
	
	// Resultat linksbündig ausgeben
	sbi(ADMUX,ADLAR);	// AD Left Adjust Result Bit = 1
	
	// Lösche alle Bits
	ADCSRA = 0x00;
	// ADC Control and Status Register A
	sbi(ADCSRA,ADEN);	// Enable ADC startet den Konversionsvorgang
	sbi(ADCSRA,ADATE);	// Free Running Mode
	sbi(ADCSRA,ADIE);	// ADC Interrupt wird freigegeben: Interrupt Enable
	// ADC Takt sollte zwischen 50kHz und 200kHz liegen
	// 20MHz / 128 = 156kHz
	ADCSRA = (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); //Takt PreSkaler teilen durch 128
	ADCSRB = (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);
	
	// Den ADC initialisieren und einen sog. Dummyreadout machen
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	voltage = ADCW;
	voltage = 0;
	
}

int readADC(void)
{
	sbi(ADCSRA,ADSC);
	while(ADCSRA & (1<<ADSC));
	voltage = ADCW;
	return voltage;
}