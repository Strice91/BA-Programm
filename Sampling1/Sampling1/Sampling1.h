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

#define LP_ORDER 6
const int16_t lp_coeff[LP_ORDER] ={5252,   5568,   5728,   5728,   5568,   5252};

void smp_init(void);
void smp_sample(float *U, float *I);
void smp_addToSquareSum(float *U_SUM, float *I_SUM, float *P_SUM, float *U, float *I);

