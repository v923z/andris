#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <avr/io.h> 
#include <util/delay.h>
#include "hardware.h"
#include "adc.h"
#include "serial.h"

uint8_t digits[10] = {(a | b | c | d | e | g), // 0
	(b | c), // 1
	(a | b | g | d | e), // 2
	(a | b | c | d | g), // 3
	(b | c | g | f ), // 4
	(a | c | d | f | g), // 5
	(a | c | d | f | g), // 6
	(a | b | c), // 7
	(a | b | c | d | e | f | g), // 8
	(a | b | c | d | f | g), // 9
	};

#endif
