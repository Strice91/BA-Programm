/*
 * debug.h
 *
 * Created: 21.02.2015 16:44:36
 *  Author: Strice
 */ 

#ifndef DEBUG_H
	#define DEBUG_H

	#include "BitUtilities.h"
	#include <avr/io.h>

	#define DB_PORT PORTD
	#define DB_DDR DDRD
	#define DB_LED1	2
	#define DB_LED2	3

	int processTime;

	void debug_init();

	void tic(void);
	int toc(void);

	void debug_ledOn(void);
	void debug_ledOff(void);
	void debug_ledToggle(void);

#endif //DEBUG_H