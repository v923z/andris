#ifndef ADC_H
#define	ADC_H

#include <avr/io.h>

void ADC_Init(void);
uint16_t ADC_Conversion(unsigned char );
uint16_t ADC_BlockMeasure(uint8_t , uint8_t );
#endif
