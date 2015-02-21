/*
 * debug.c
 *
 * Created: 21.02.2015 16:44:36
 *  Author: Strice
 */ 
#include "debug.h"

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