/*
 * debug.c
 *
 * Created: 21.02.2015 16:44:36
 *  Author: Strice
 */ 
 
#include "debug.h"

void debug_init(void){
	// Declare debug port as output
	DB_DDR = 0xFF;
}

void tic(void){
	// Switch on Debug LED
	sbi(DB_PORT,DB_LED1);

	//----------------------------------//
	// 			Setup Timer				//
	//----------------------------------//
}

int toc(void){
	// Switch off Debug LED
	cbi(DB_PORT,DB_LED1);

	//----------------------------------//
	// 			Read Timer				//
	//----------------------------------//
	
	processTime = 0;
	return processTime;
}

void debug_ledOn(void){
	// Switch on Debug LED
	sbi(DB_PORT,DB_LED2);
}

void debug_ledOff(void){
	// Switch off Debug LED
	cbi(DB_PORT,DB_LED2);
}

void debug_ledToggle(void){
	// Toggle Debug LED
	tgl(DB_PORT,DB_LED2);
}