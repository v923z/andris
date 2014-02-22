#include "adc.h"

void ADC_Init(void) {
	// Voltage reference on AV_CC
	ADMUX |= _BV(REFS0);
	// Prescaler 64 - approx. 190 kHz in this case
	// 16 MHz clock; prescaler 32 -> 38 ks/s. See p. 207 for Atmega8
	ADCSRA |= _BV(ADEN) | _BV(ADPS1) | _BV(ADPS2);
	ADMUX &= ~( _BV(0) );
}

uint16_t ADC_Conversion(unsigned char channel) {
	unsigned short HIGH, LOW;

	ADMUX |= channel;
	
	ADCSRA |= _BV(ADSC);
	// Wait till the conversion is complete
	while((ADCSRA & _BV(ADIF))==0);
	// When done, clear the ADC flag 
	ADCSRA |= _BV(ADIF);
	// Getting the 8 lower bits 
	LOW = ADCL;
	// Getting the 8 higher bits
	HIGH = ADCH; 
	return((HIGH << 8) + LOW);
}

uint16_t ADC_BlockMeasure(uint8_t channel, uint8_t block) {
	uint16_t ret = 0;
	while(block > 0) {
		ret += ADC_Conversion(channel);
		block--;
	}
	return(ret);
}
