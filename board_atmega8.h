#ifndef BOARD_ATMEGA8_H_INCLUDED
#define BOARD_ATMEGA8_H_INCLUDED

//implemented for ATmega8/8L
//v0.10: 12/25/2017
//GPIO: pinMode(), digitalWrite(), digitalRead()
//timing: ticks(), micros(), millis(), delayTicks(), delayMicros()/delayMicroseconds(), delayMillis()/delayMilliseconds()/delay()
//not implemented
//analog: analogRead(), analogWrite()
//serial: serial_begin(), serial_write(), serial_read(), ...

//compiler: GCC-AVR
#include <avr/io.h>								//we use avr
#include <avr/interrupt.h>						//we use interrupts
#include <stdint.h>								//we use uintx types - if not available, use the alternatives below
/*
typedef unsigned char 	uint8_t;
typedef unsigned short 	uint16_t;
typedef unsigned long 	uint32_t;
typedef   signed char 	 int8_t;
typedef   signed short 	 int16_t;
typedef   signed long 	 int32_t;
*/

//put board specific defs here
//user must provide the following macros
#define F_CPU				16000000ul			//CPU frequency, in Hz
#define NOP()				asm("nop")			//nop op
#define interrupts()		sei()				//enable interrupts
#define noInterrupts()		cli()				//disable interrupts

//pin defs for gpio functions
typedef enum {
	D0,  D1,  D2,  D3,  D4,  D5,  D6,  D7,		//maps to PB0..7
	D8,  D9,  D10, D11, D12, D13, D14, D15,		//maps to PC0..7 (PC7 is missing)
	D16, D17, D18, D19, D20, D21, D22, D23, 	//maps to PD0..7
	//D24, D25, D26, D27, D28, D29, D30, D31	//maps to PE0..7
	DMAX										//boundary check
} PIN_T;

//gpio definitions
typedef struct {
	volatile unsigned char PIN;	//input data register
	volatile unsigned char DDR;	//data direction register
	volatile unsigned char PORT;	//output data register
} GPIO_TypeDef;				//gpio data registers

#define GPIOA				((GPIO_TypeDef *) &PINA)
#define GPIOB				((GPIO_TypeDef *) &PINB)
#define GPIOC				((GPIO_TypeDef *) &PINC)
#define GPIOD				((GPIO_TypeDef *) &PIND)
#define GPIOE				((GPIO_TypeDef *) &PINE)
#define GPIOF				((GPIO_TypeDef *) &PINF)
#define GPIOG				((GPIO_TypeDef *) &PING)
#define GPIOH				((GPIO_TypeDef *) &PINH)

//port definitions
#define IO_SET(port, bits)	port |= (bits)		//set bits on port
#define IO_CLR(port, bits)	port &=~(bits)		//clear bits on port
#define IO_FLP(port, bits)	port ^= (bits)		//flip bits on port
#define IO_GET(port, bits)	((port) & (bits))	//return bits on port
#define IO_IN(ddr, bits)	ddr &=~(bits)		//set bits as input
#define IO_OUT(ddr, bits)	ddr |= (bits)		//ddr |= (bits)		//set bits as output

//struct used to map a pin to GPIO+mask
typedef struct {
	GPIO_TypeDef *gpio;					//gpio for a pin
	uint8_t mask;						//pin mask - 16bit
} PIN2GPIO;

//pin defs for analog functions
typedef enum {
	A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15,
	AVREFINT,									//AIN16 = Vrefint
	ATEMP,										//AIN17 = temperature sensor
	AMAX										//boundary check
} AIN_T;


#endif // BOARD_ATMEGA328P_H_INCLUDED
