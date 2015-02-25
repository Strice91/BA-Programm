/*
 * sample.h
 *
 * Created: 25.02.2015 14:05:42
 *  Author: Strice
 */ 
 
#include "adc.h"

#define U_DC_OFFSET 512
#define I_DC_OFFSET 512
#define Ku 1.0
#define Ki 1.0
#define Betha 5.0
#define A 0.5

void smp_init(void);
void smp_sample(float *U, float *I);