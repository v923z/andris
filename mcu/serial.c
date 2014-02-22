// Serial communication functions
// by Zoltán Vörös
// 23 Sep 2011

#include "serial.h"

ISR(USART_UDRE_vect) {
	UDR = data[buffer];
	if(buffer == 0)  {
		UCSRB &= ~_BV(UDRIE);	// buffer is empty, disable interrupt
	}
	else {
		buffer--;
	}
}

ISR(USART_RXC_vect) {
	control_byte = UDR;
	// Disable the USART interrupt. This should be enabled, once the task is finished!!!
	UCSRB &= ~_BV(RXCIE);
}

void USART_Flush(void) {
	uint8_t dummy;
	_delay_ms(2);
	while(UCSRA & _BV(RXC)) {
		_delay_ms(2);
		dummy = UDR;
	}
}

void USART_Init(void) {
	control_byte = 0;
	UBRRH = (BAUD_PRESCALE >> 8);
	UBRRL = BAUD_PRESCALE;

	UCSRB |= _BV(RXEN) | _BV(TXEN);
	UCSRC |= _BV(URSEL) | _BV(UCSZ0) | _BV(UCSZ1);
	UCSRB |= _BV(RXCIE);
}

void USART_SendByte(unsigned char sbyte) {
	while ((UCSRA & _BV(UDRE)) == 0) {};
	UDR = sbyte;
}

void USART_OK(void) {
	while( (UCSRB & UDRIE) ) {} ;
	data[0] = 'K';
	data[1] = 'O';
	buffer = 1;
	UCSRB |= _BV(UDRIE);
}

void USART_SendString(char *string) {
        unsigned int length = 0;
        // In case the transmit buffer hasn't been emptied yet, we wait here
        while( (UCSRB & UDRIE) ) {} ;
	
        while(*string != '\0') {
                data[length++] = *string++;
        }
        buffer = length - 1;
        UCSRB |= _BV(UDRIE);
}

unsigned char USART_ReadByte(void) {
      unsigned char byte;
      while ((UCSRA & _BV(RXC)) == 0) {};	// Wait for data ready to be read from UDR
      byte = UDR;
      return(byte);				// Fetch the recieved byte value
}

void USART_Restore(void) {
	control_byte = 0;
	UCSRB |= _BV(RXCIE);
}

uint16_t USART_ReadInteger(uint8_t delimiter) {
	// This function returns an integer read from the serial port. 
	unsigned int ret = 0;
	unsigned char ss;
	while(1) {
		ss = USART_ReadByte();
		if(ss == delimiter) break;
		ret = ret * 10 + (ss - 0x30);
	}
	return(ret);
}

int16_t USART_ReadSignedInteger(uint8_t delimiter) {
	// This function returns an integer read from the serial port. 
	int16_t ret = 0;
	uint16_t tmp = 0;
	uint8_t ss;
	uint8_t pos_neg = '+';
	
	while(1) {
		ss = USART_ReadByte();
		if(ss == delimiter) break;
		else if(ss == '-') {
			pos_neg = '-';
			//continue;
		}
		else tmp = tmp * 10 + (ss - 0x30);
	}
	ret = (signed short int)(tmp);
	if(pos_neg == '-') ret = 0 - (signed short int)tmp;
	return(ret);
}

void USART_SendInteger(unsigned int num, unsigned char delimiter) {
      unsigned int length = 0;
      unsigned int nn;
      // In case the transmit buffer hasn't been emptied yet, we wait here
      while ( UCSRB & _BV(UDRIE) ) {};

      // When we are done with the number, we terminate the string by a delimiter. Note, however, that the string 
      // should be reversed, for the serial buffer is sent from the end. See USART_UDRE_vect above.
      data[length] = delimiter;
      length++;
     
      while(num > 9) {
	    nn = num - 10 * ( num / 10 ); 
	    data[length++] = ( nn + 0x30 );
	    num = num / 10;
      }
      data[length] = num + 0x30;
      buffer = length;
      // We enable the USART transmit interrupt here. This is disabled in the interrupt handler, once all data has been sent. 
      UCSRB |= _BV(UDRIE);
}

int32_t USART_ReadSignedInteger32(uint8_t delimiter) {
	// This function returns an integer read from the serial port. 
	int32_t ret = 0;
	uint32_t tmp = 0;
	uint8_t ss;
	uint8_t pos_neg = '+';
	
	while(1) {
		ss = USART_ReadByte();
		if(ss == delimiter) break;
		else if(ss == '-') {
			pos_neg = '-';
			//continue;
		}
		else tmp = tmp * 10 + (ss - 0x30);
	}
	ret = (int32_t)(tmp);
	if(pos_neg == '-') ret = 0 - (int32_t)tmp;
	return(ret);
}

void USART_SendSignedInteger32(int32_t num, unsigned char delimiter) {
	uint16_t length = 0;
	unsigned int nn;
	uint8_t posneg = '+';
	// In case the transmit buffer hasn't been emptied yet, we wait here
	while (UCSRB & _BV(UDRIE)) {};

	// When we are done with the number, we terminate the string by a delimiter. Note, however, that the string 
	// should be reversed, for the serial buffer is sent from the end. See USART_UDRE_vect above.
	data[length] = delimiter;
	length++;
	if(num < 0) {
		posneg = '-';
		num = 0 - num;
	}	
	while(num > 9) {
		nn = num - 10 * ( num / 10 ); 
		data[length++] = ( nn + 0x30 );
		num = num / 10;
	}
	data[length] = num + 0x30;
	if(posneg == '-') {
		length++;
		data[length] = '-';
	}
	buffer = length;
	// We enable the USART transmit interrupt here. This is disabled in the interrupt handler, once all data has been sent. 
	UCSRB |= _BV(UDRIE);
}
