#include "display.h"

uint8_t counter;
uint16_t adc;

int main (void) {
	DISPLAY_INIT();
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
