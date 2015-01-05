
// includes
#include "BitUtilities.h"

// Config ADC
#define ADCPORT = ADCSRA;

// 

void initADC(int AREF)
{
	// Lösche alle Bits
	ADMUX = 0x00;
	
	// Auswahl der Referenzspannung
	switch(AREF) {
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
	//sbi(ADCSRA,ADFR);	// Free Running Mode
	sbi(ADCSRA,ADIE);	// ADC Interrupt wird freigegeben: Interrupt Enable
	

}