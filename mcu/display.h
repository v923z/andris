#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <avr/io.h> 
#include <util/delay.h>
#include "hardware.h"
#include "adc.h"
#include "serial.h"

void Digit(uint8_t i) {
	// Clear all LEDs
	CA(); CB(); CC(); CD(); CE(); CF(); CG(); CP();
	
	if(i == 0) { A(); B(); C(); D(); E(); G(); } 
	else if(i == 1) { B(); C(); } 
	else if(i == 2) { A(); B(); D(); E(); G(); }
	else if(i == 3) { A(); B(); C(); D(); G(); }
	else if(i == 4) { B(); C(); F(); G(); } 
	else if(i == 5) { A(); C(); D(); F(); G(); } 
	else if(i == 6) { A(); C(); D(); E(); F(); G(); } 
	else if(i == 7) { A(); B(); C(); } 
	else if(i == 8) { A(); B(); C(); D(); E(); F(); G(); } 
	else if(i == 9) { A(); B(); C(); D(); F(); G(); }
}

void SetDigits(uint8_t number, uint8_t dot1, uint8_t dot2) {
	uint8_t rem;
	rem = number - 10 * (number / 10);
	DIGIT0();
	Digit(rem);
	if(dot1) P();
	_delay_ms(30);
	rem = number / 10;
	DIGIT1();
	Digit(rem);
	if(dot1) P();
	_delay_ms(30);
}
#endif
