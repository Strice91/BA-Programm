/*
 * rtc.h
 *
 * Created: 20.02.2015 15:48:56
 *  Author: Strice
 */ 
#include "BitUtilities.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define XTAL F_CPU
#define SAMPLE_FREQ 4000L	// 4kHz

#define uchar unsigned char
#define uint unsigned int

uchar prescaler;
uchar volatile second;          // count seconds

void rtc_initSample(void);
void rtc_initSecond(void);