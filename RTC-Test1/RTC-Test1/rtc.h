/*
 * rtc.h
 *
 * Created: 20.02.2015 15:48:56
 *  Author: Strice
 */ 
#include "../../inc/BitUtilities.h"
#include <avr/io.h>

#define XTAL F_CPU
#define SAMPLE_FREQ 4000L	// 4kHz

#define uchar unsigned char
#define uint unsigned int

//ISR(TIMER1_COMPA_vect);
void rtc_init(void);