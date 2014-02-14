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

void USART_Init(void) {
	control_byte = 0;
	UBRRH = (BAUD_PRESCALE >> 8);
	UBRRL = BAUD_PRESCALE;

	UCSRB |= _BV(RXEN) | _BV(TXEN);   // Turn on the transmission and reception circuitry
	UCSRC |= _BV(URSEL) | _BV(UCSZ0) | _BV(UCSZ1); // Use 8-bit character sizes

	UCSRB |= _BV(RXCIE); // Enable the USART Recieve Complete interrupt (USART_RXC) 
}

void USART_SendByte(unsigned char sbyte) {
	while ((UCSRA & _BV(UDRE)) == 0) {};
	UDR = sbyte;
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

unsigned int Read_Integer(unsigned char delimiter) {
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
