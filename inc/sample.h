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
int16_t smp_sampleU(void);
int16_t smp_sampleI(void);
void smp_reset(int *smp_cnt);
void smp_sampleCalculation(uint64_t *UsqSum, uint64_t *IsqSUM, int64_t *Psum, int16_t U_mean, int16_t I_mean, int16_t U, int16_t I);