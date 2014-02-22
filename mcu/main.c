#include "display.h"

uint16_t counter = 0;
uint8_t prev = 0;
uint16_t adc;
extern volatile uint8_t control_byte;


int main (void) {
	DISPLAY_INIT();
	ADC_Init();
	//USART_Init();
	//sei();
	//USART_Restore();
	
	for(;;) {
		if(SENSE_PINS() == 3) {	// Voltmeter
			adc = ADC_BlockMeasure(0, 50);
			SetDigits((adc >> 10), 0, 1);
		}
		else if(SENSE_PINS() == 1) {	// We are counting UP
			if(CLOCK_HIGH) {
				if(prev == 0) {
					prev = 1;
					counter++;
				}
			} else { prev = 0; }
			if(counter == 100) counter = 0;
			SetDigits(counter, 0, 0);
		}
		//if(SENSE_PINS() == 2) {	// We are counting DOWN
		else {
			if(CLOCK_HIGH) {
				if(prev == 0) {
					prev = 1;
					if(counter == 0) counter = 100;
					counter--;
				}
			} else { prev = 0; }
			SetDigits(counter, 0, 0);
		}
	}
	
	//for(;;) {
		//SetDigits(counter, 0, 0);
		//switch(control_byte) {
			//case 'D':
				//counter = USART_ReadInteger('N');
				//USART_Restore();
				//break;
				
			//case 'P':
				//counter = USART_ReadInteger('N');
				//ClearDisplay();	
				//if(counter == 1) { DIGIT0(); P();}
				//else if(counter == 2) { DIGIT1(); P();}
				//USART_Restore();
				//break;

			//case 'E':
				//counter = USART_ReadInteger('N');
				//USART_SendInteger(counter, 'N');
				//USART_Restore();
				//break;
		//}
	//}
	return(0);
}
