#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)

volatile unsigned char control_byte;
volatile unsigned char data[32], buffer, num;

void USART_Init(void);
unsigned char USART_ReadByte(void);
void USART_SendByte(unsigned char );
void USART_SendString(char *);
void USART_Restore(void);
unsigned int Read_Integer(unsigned char );
void USART_SendInteger(unsigned int, unsigned char );
#endif
