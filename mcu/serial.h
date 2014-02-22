#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)

volatile unsigned char control_byte;
volatile unsigned char data[32], buffer, num;

void USART_Flush(void);
void USART_Init(void);
unsigned char USART_ReadByte(void);
void USART_SendByte(unsigned char );
void USART_SendString(char *);
void USART_OK(void);
void USART_Restore(void);
uint16_t USART_ReadInteger(uint8_t );
int16_t USART_ReadSignedInteger(uint8_t );
void USART_SendInteger(unsigned int, unsigned char );
void USART_SendRedundantBytes(uint8_t , uint8_t );
int32_t USART_ReadSignedInteger32(uint8_t );
void USART_SendSignedInteger32(int32_t , unsigned char );

#endif
