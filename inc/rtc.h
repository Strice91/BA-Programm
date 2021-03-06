/*
 * rtc.h
 *
 * Created: 20.02.2015 15:48:56
 *  Author: Strice
 *  Source: http://www.mikrocontroller.net/articles/AVR_-_Die_genaue_Sekunde_/_RTC
 */ 
#ifndef RTC_H
 #define RTC_H

#include "BitUtilities.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "debug.h"

#define XTAL F_CPU
#define SAMPLE_FREQ 500L		// 4kHz

#define uchar unsigned char
#define uint unsigned int

// uchar tc;
// Is not working because SAMPLE_FREQ > 255
// therefore use uint 

uint timerCounter;				// counts timer interrupts
uchar volatile second;          // counts seconds

// Sets up a timer which causes an Interrupt
// Interrupt will occur with the SAMPLE_FREQ
void rtc_initSample(void);

// Check if it is necessary to increase second counter
// and update On Compare Register if sample frequency is no
// factor of CPU Frequency
void rtc_checkSecondsAndRemainder(void);

#endif //RTC_H