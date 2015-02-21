/*
 * debug.h
 *
 * Created: 21.02.2015 16:44:36
 *  Author: Strice
 */ 

#include "BitUtilities.h"
#include <avr/io.h>

#define DB_PORT PORTD
#define DB_LED1	2
#define DB_LED2	3

int processTime;

void tic(void);
int toc(void);