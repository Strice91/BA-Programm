
// includes
#include <util/delay.h>
#include "BitUtilities.h"

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
			sbi(ADMUX,REFS0);	// REFS0 = 1  
			sbi(ADMUX,REFS1);	// REFS1 = 1
		break;
		case 5: // Referenzspannung AREF = AVcc 
			sbi(ADMUX,REFS0);			// REFS0 = 1,  REFS1 = 0
		break;
		default: // Referenzspannung AREF = AVcc 
			sbi(ADMUX,REFS0);			// REFS0 = 1,  REFS1 = 0
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
	
	// ADC Control and Status Register A
	ADCSRB = 0x00;
	sbi(ADCSRB,ADTS2);
	sbi(ADCSRB,ADTS1);
	sbi(ADCSRB,ADTS0);
	
	// Den ADC initialisieren und einen sog. Dummyreadout machen
	sbi(ADCSRA,ADSC);
	while(ADCSRA & (1<<ADSC));
}

int readADC(void)
{
	sbi(ADCSRA,ADSC);
	while(ADCSRA & (1<<ADSC));
	return ADC;
}