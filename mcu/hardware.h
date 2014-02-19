#ifndef _HARDWARE_H_ 
#define _HARDWARE_H_ 

#define GLUE(a, b)     a##b
#define PORT(x)        GLUE(PORT, x)
#define PIN(x)         GLUE(PIN, x)
#define DDR(x)         GLUE(DDR, x)

#define a		_BV(PD0)
#define b		_BV(PD1)
#define c		_BV(PD2)
#define d		_BV(PD3)
#define e		_BV(PD4)
#define f		_BV(PD5)
#define g		_BV(PD6)
#define p		_BV(PD7)

#define DA()	DDRD |= a
#define DB()	DDRD |= b
#define DC()	DDRD |= c
#define DD()	DDRD |= d
#define DE()	DDRD |= e
#define DF()	DDRD |= f
#define DG()	DDRD |= g
#define DP()	DDRD |= p

#define NUM0		_BV(PB0)
#define NUM1		_BV(PB1)
#define DIGIT0()	{ PORTB &= ~NUM0; PORTB &= ~NUM1; PORTB |= NUM0; }
#define DIGIT1()	{ PORTB &= ~NUM0; PORTB &= ~NUM1; PORTB |= NUM1; }

#define DISPLAY_INIT() 	{ DA(); DB(); DC(); DD(); DE(); DF(); DG(); DP(); }

#define CA()	PORTD |= a
#define CB()	PORTD |= b
#define CC()	PORTD |= c
#define CD()	PORTD |= d
#define CE()	PORTD |= e
#define CF()	PORTD |= f
#define CG()	PORTD |= g
#define CP()	PORTD |= p

#define A()		PORTD &= ~a
#define B()		PORTD &= ~b
#define C()		PORTD &= ~c
#define D()		PORTD &= ~d
#define E()		PORTD &= ~e
#define F()		PORTD &= ~f
#define G()		PORTD &= ~g
#define P()		PORTD &= ~p

#define	PORT_SENSE		PORTC
#define	DDR_SENSE		DDRC

#define	CLOCK_IN		_BV(PC2)
#define	CLOCK_HIGH		(PINC & CLOCK_IN)

#define SENSE_PIN0		(PINC & _BV(PC3))
#define SENSE_PIN1		(PINC & _BV(PC4))
#define SENSE_PIN2		(PINC & _BV(PC5))
#define SENSE_PIN3		(PINC & _BV(PC6))

#endif
