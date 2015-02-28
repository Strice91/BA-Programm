/*
 * Sampling1.h
 *
 * Created: 22.02.2015 17:19:15
 *  Author: Strice
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "../../inc/adc.h"
#include "../../inc/lcd.h"
#include "../../inc/rtc.h"
#include "../../inc/debug.h"
//#include "../../inc/sample.h"

#define U_DC_OFFSET 512
#define I_DC_OFFSET 512
#define Ku 1.0
#define Ki 1.0
#define Betha 1.0
#define A 1.0

void smp_init(void);
void smp_sample(void);
void smp_sampleCalculation(void);
void smp_mainCalculation(void);
void smp_reset(void);

void writeTwoLines(char *name1, char *name2, int32_t V1, int32_t V2);

