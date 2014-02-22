#ifndef _HARDWARE_H_ 
#define _HARDWARE_H_ 

// Atmega88 definitions

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
#define	DNUM0()		DDRB |= NUM0
#define	DNUM1()		DDRB |= NUM1

#define DIGIT0()	{ PORTB &= ~NUM0; PORTB &= ~NUM1; PORTB |= NUM0; }
#define DIGIT1()	{ PORTB &= ~NUM0; PORTB &= ~NUM1; PORTB |= NUM1; }

#define DISPLAY_INIT() 	{ DA(); DB(); DC(); DD(); DE(); DF(); DG(); DP(); DNUM0(); DNUM1(); }

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
#define	PIN_SENSE		PINC
#define	DDR_SENSE		DDRC

#define	CLOCK_IN		_BV(PC1)
#define	CLOCK_HIGH		(PINC & CLOCK_IN)

#define SENSE_PIN0		(PIN_SENSE & _BV(PC2))
#define SENSE_PIN1		(PIN_SENSE & _BV(PC3))
#define SENSE_PIN2		(PIN_SENSE & _BV(PC4))
#define SENSE_PIN3		(PIN_SENSE & _BV(PC5))

#define	SENSE_PINS()		((SENSE_PIN0 | SENSE_PIN1 | SENSE_PIN2 | SENSE_PIN3) >> 2)

//// Attiny44 definitions
//#define a		_BV(PA2)
//#define b		_BV(PA3)
//#define c		_BV(PA4)
//#define d		_BV(PA5)
//#define e		_BV(PA6)
//#define f		_BV(PA7)
//#define g		_BV(PA0)
//#define p		_BV(PA1)

//#define DA()	DDRA |= a
//#define DB()	DDRA |= b
//#define DC()	DDRA |= c
//#define DD()	DDRA |= d
//#define DE()	DDRA |= e
//#define DF()	DDRA |= f
//#define DG()	DDRA |= g
//#define DP()	DDRA |= p

//#define NUM0		_BV(PB0)
//#define NUM1		_BV(PB1)
//#define	DNUM0()		DDRB |= NUM0
//#define	DNUM1()		DDRB |= NUM1

//#define DIGIT0()	{ PORTB &= ~NUM0; PORTB &= ~NUM1; PORTB |= NUM0; }
//#define DIGIT1()	{ PORTB &= ~NUM0; PORTB &= ~NUM1; PORTB |= NUM1; }

//#define DISPLAY_INIT() 	{ DA(); DB(); DC(); DD(); DE(); DF(); DG(); DP(); DNUM0(); DNUM1(); }

//#define CA()	PORTA |= a
//#define CB()	PORTA |= b
//#define CC()	PORTA |= c
//#define CD()	PORTA |= d
//#define CE()	PORTA |= e
//#define CF()	PORTA |= f
//#define CG()	PORTA |= g
//#define CP()	PORTA |= p

//#define A()		PORTA &= ~a
//#define B()		PORTA &= ~b
//#define C()		PORTA &= ~c
//#define D()		PORTA &= ~d
//#define E()		PORTA &= ~e
//#define F()		PORTA &= ~f
//#define G()		PORTA &= ~g
//#define P()		PORTA &= ~p

//#define	PORT_SENSE		PORTB
//#define	DDR_SENSE		DDRB

//#define	CLOCK_IN		_BV(PB2)
//#define	CLOCK_HIGH		(PINB & CLOCK_IN)

//#define SENSE_PIN0		(PINA & _BV(PA1))
//#define SENSE_PIN1		(PINC & _BV(PC4))
//#define SENSE_PIN2		(PINC & _BV(PC5))
//#define SENSE_PIN3		(PINC & _BV(PC6))

#endif
