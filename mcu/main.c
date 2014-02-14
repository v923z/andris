#include "display.h"

uint8_t counter;
uint16_t adc;

void SetDigits(uint8_t number, uint8_t dot1, uint8_t dot2) {
	uint8_t rem;
	rem = number - 10 * (number / 10);
	PORT_DIGIT &= (~NUMBER0 & ~NUMBER1);
	PORT_DIGIT |= NUMBER0;
	PORT_DISPLAY = ~digits[rem];
	if(dot1) PORT_DISPLAY |= p;
	_delay_ms(30);
	rem = number / 10;
	PORT_DIGIT &= (~NUMBER0 & ~NUMBER1);
	PORT_DIGIT |= NUMBER1;
	PORT_DISPLAY = ~digits[rem];
	if(dot2) PORT_DISPLAY |= p;
	_delay_ms(30);
}

int main (void) {
	DDR_DISPLAY |= 0xff;
	DDR_DIGIT |= (NUMBER0 | NUMBER1);
	ADC_Init();
	USART_Init();
	
	for(;;) {
		if(SENSE_PIN0) {	// We are counting UP
			if(CLOCK_HIGH) counter++;
			if(counter == 100) counter = 0;
			SetDigits(counter, 0, 0);
		}
		if(SENSE_PIN1) {	// We are counting DOWN
			if(CLOCK_HIGH) counter--;
			SetDigits(counter, 0, 0);
			if(counter == 0) counter = 100;			
		}
		if(SENSE_PIN2) {	// Voltmeter
			adc = ADC_BlockMeasure(0, 50);
			SetDigits((adc >> 10), 1, 0);
		}		
	}
	return(0);
}
