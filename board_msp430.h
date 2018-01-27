#ifndef BOARD_MSP430_H_INCLUDED
#define BOARD_MSP430_H_INCLUDED

//implemented for MSP430FR5969
//v0.10: 12/26/2017
//GPIO: pinMode(), digitalWrite(), digitalRead()
//timing: ticks(), micros(), millis(), delayTicks(), delayMicros()/delayMicroseconds(), delayMillis()/delayMilliseconds()/delay()
//not implemented
//analog: analogRead(), analogWrite()
//serial: serial_begin(), serial_write(), serial_read(), ...

//compiler: IAR/TI CCS/MSP430
#include <msp430.h>							//we use IAR / CCS/MSP430
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
	#define NOP()			__no_operation()	//nop()
#endif
#define interrupts()		ei()				//enable interrupts
#define noInterrupts()		di()				//disable interrupts
#define ei()				__enable_interrupt()
#define di()				__disable_interrupt()

//pin defs for gpio functions
typedef enum {
#if defined(P1IN)
	P10,  P11,  P12,  P13,  P14,  P15,  P16,  P17,		//maps to P10..7
#endif
#if defined(P2IN)
	P20,  P21,  P22,  P23,  P24,  P25,  P26,  P27,		//maps to P20..7
#endif
#if defined(P3IN)
	P30,  P31,  P32,  P33,  P34,  P35,  P36,  P37,		//maps to P30..7
#endif
#if defined(P4IN)
	P40,  P41,  P42,  P43,  P44,  P45,  P46,  P47,		//maps to P40..7
#endif
#if defined(P5IN)
	P50,  P51,  P52,  P53,  P54,  P55,  P56,  P57,		//maps to P50..7
#endif
#if defined(P6IN)
	P60,  P61,  P62,  P63,  P64,  P65,  P66,  P67,		//maps to P60..7
#endif
#if defined(P7IN)
	P70,  P71,  P72,  P73,  P74,  P75,  P76,  P77,		//maps to P70..7
#endif
#if defined(P8IN)
	P80,  P81,  P82,  P83,  P84,  P85,  P86,  P87,		//maps to P80..7
#endif
#if defined(P9IN)
	P90,  P91,  P92,  P93,  P94,  P95,  P96,  P97,		//maps to P90..7
#endif
#if defined(P10IN)
	P100,  P101,  P102,  P103,  P104,  P105,  P106,  P107,		//maps to P100..7
#endif
	DMAX										//boundary check
} PIN_T;

//gpio definitions
//port definitions
#define IO_SET(port, bits)	port |= (bits)		//set bits on port
#define IO_CLR(port, bits)	port &=~(bits)		//clear bits on port
#define IO_FLP(port, bits)	port ^= (bits)		//flip bits on port
#define IO_GET(port, bits)	((port) & (bits))	//return bits on port
#define IO_IN(ddr, bits)	ddr &=~(bits)		//set bits as input
#define IO_OUT(ddr, bits)	ddr |= (bits)		//ddr |= (bits)		//set bits as output

//struct used to map a pin to GPIO+mask
typedef struct {
	volatile uint8_t *PORT;						//port data register
	volatile uint8_t *PIN;						//input data register
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
