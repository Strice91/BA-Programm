/*
 * BitUtillities.h
 *
 * Created: 03.01.2015 10:35:49
 *  Author: Strice
 *	Source: Dr. Günter Spanner | AVR-Mikrocontroller in C programmieren (S 158)
 */

#ifndef BITUTILLITIES_H
	#define BITUTILLITIES_H

	#include <inttypes.h>

	// General bit utilities
	#define sbi(PORT, bit) 		(PORT|=(1<<bit)) 	// set bit in PORT
	#define cbi(PORT, bit) 		(PORT&=~(1<<bit))	// clear bit in PORT
	#define tgl(PORT, bit) 		(PORT^=(1<<bit))	// toggle bit in PORT

	/*
	void setbits1(volatile uint8_t *PORT, int bits[], int amountOfBits){
		//int mask 
		//for
	}
	*/
#endif //BITUTILLITIES_H