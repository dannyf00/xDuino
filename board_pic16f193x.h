#ifndef BOARD_PIC16F193X_H_INCLUDED
#define BOARD_PIC16F193X_H_INCLUDED

//implemented for PIC16F193x/PIC16LF193x
//v0.10: 12/26/2017
//GPIO: pinMode(), digitalWrite(), digitalRead()
//timing: ticks(), micros(), millis(), delayTicks(), delayMicros()/delayMicroseconds(), delayMillis()/delayMilliseconds()/delay()
//not implemented
//analog: analogRead(), analogWrite()
//serial: serial_begin(), serial_write(), serial_read(), ...

//compiler: XC8
#include <xc.h>									//we use xc
#include <stdint.h>							//we use uintx types - if not available, use the alternatives below
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
#define F_CPU				(16000000ul/4)		//CPU frequency, in Hz. 16Mhz crystal or INTRC (see fuse settings in .c file
#ifndef NOP
	#define NOP()			asm("nop")			//nop()
#endif
#define interrupts()		ei()				//enable interrupts
#define noInterrupts()		di()				//disable interrupts

//pin defs for gpio functions
typedef enum {
	D0,  D1,  D2,  D3,  D4,  D5,  D6,  D7,		//maps to PA0..7
	D8,  D9,  D10, D11, D12, D13, D14, D15,		//maps to PB0..7
	D16, D17, D18, D19, D20, D21, D22, D23, 	//maps to PC0..7
	//D24, D25, D26, D27, D28, D29, D30, D31	//maps to PD0..7
	DMAX										//boundary check
} PIN_T;

//gpio definitions
//port definitions
#define IO_SET(port, bits)	port |= (bits)		//set bits on port
#define IO_CLR(port, bits)	port &=~(bits)		//clear bits on port
#define IO_FLP(port, bits)	port ^= (bits)		//flip bits on port
#define IO_GET(port, bits)	((port) & (bits))	//return bits on port
#define IO_IN(ddr, bits)	ddr |= (bits)		//set bits as input
#define IO_OUT(ddr, bits)	ddr &=~(bits)		//ddr |= (bits)		//set bits as output

//struct used to map a pin to GPIO+mask
typedef struct {
	volatile uint8_t *PORT;						//port data register
	//volatile uint8_t *PIN;					//input data register
	volatile uint8_t *DDR;						//port direction register
	uint8_t mask;								//pin mask - 8-bit
} PIN2GPIO;

//pin defs for analog functions
typedef enum {
	A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15,
	AVREFINT,									//AIN16 = Vrefint
	ATEMP,										//AIN17 = temperature sensor
	AMAX										//boundary check
} AIN_T;


#endif // BOARD_ATMEGA328P_H_INCLUDED
