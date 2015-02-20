
// includes
#include "BitUtilities.h"
#include <avr/io.h>
#include <util/delay.h>

void adc_init(int AREF);
int adc_readUnsigned(void);
void adc_ConversionCompleteAndClear(void);
void adc_startConversion(void);