#ifndef _HARDWARE_H_ 
#define _HARDWARE_H_ 

#define PORT_DISPLAY	PORTD
#define DDR_DISPLAY		DDRD

#define a		_BV(PD0)
#define b		_BV(PD1)
#define c		_BV(PD2)
#define d		_BV(PD3)
#define e		_BV(PD4)
#define f		_BV(PD5)
#define g		_BV(PD6)
#define p		_BV(PD7)

#define PORT_DIGIT		PORTC
#define DDR_DIGIT		DDRC

#define NUMBER0			_BV(PC0)
#define NUMBER1			_BV(PC1)

#define	PORT_SENSE		PORTC
#define	DDR_SENSE		DDRC

#define	CLOCK_IN		_BV(PC2)
#define	CLOCK_HIGH		(PINC & CLOCK_IN)

#define SENSE_PIN0		(PINC & _BV(PC3))
#define SENSE_PIN1		(PINC & _BV(PC4))
#define SENSE_PIN2		(PINC & _BV(PC5))
#define SENSE_PIN3		(PINC & _BV(PC6))

#endif
