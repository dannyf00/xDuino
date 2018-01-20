#ifndef BOARD_LPC13XX_H_INCLUDED
#define BOARD_LPC13XX_H_INCLUDED

//implemented for LPC13xx
//v0.10: 12/28/2017
//GPIO: pinMode(), digitalWrite(), digitalRead()
//timing: ticks(), micros(), millis(), delayTicks(), delayMicros()/delayMicroseconds(), delayMillis()/delayMilliseconds()/delay()
//not implemented
//analog: analogRead(), analogWrite()
//serial: serial_begin(), serial_write(), serial_read(), ...

//compiler: LPCXpresso
#include "lpc13xx.h"							//we use lpc13xx
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
#define F_CPU				(SystemCoreClock)	//CPU frequency, in Hz
#define NOP()				__NOP()				//nop op
#define interrupts()		//enableInterrupts()	//enable interrupts - always
#define noInterrupts()		//disableInterrupts()	//disable interrupts- always

//pin defs for gpio functions
typedef enum {
	//GPIO0
	D0,  D1,  D2,  D3,  D4,  D5,  D6,  D7,  D8,  D9,  D10, D11, D12, D13, D14, D15,		//map to P00..15 (PC7 is missing)
	D16, D17, D18, D19, D20, D21, D22, D23,	D24, D25, D26, D27, D28, D29, D30, D31,		//map to P016..31
	//GPIO1
	D32, D33, D34, D35, D36, D37, D38, D39,	D40, D41, D42, D43, D44, D45, D46, D47,		//map to P10..15
	D48, D49, D50, D51, D52, D53, D54, D55,	D56, D57, D58, D59, D60, D61, D62, D63,		//map to P116..31
#if defined(LPC_GPIO2)
	//GPIO2
	D64, D65, D66, D67, D68, D69, D70, D71,	D72, D73, D74, D75, D76, D77, D78, D79,		//map to P20..15
	D80, D81, D82, D83, D84, D85, D86, D87,	D88, D89, D90, D91, D92, D93, D94, D95,		//map to P216..31
#endif
#if defined(LPC_GPIO3)
	//GPIO3
	D96, D97, D98, D99, D100,D101,D102,D103,D104,D105,D106,D107,D108,D109,D110,D111,	//map to P30..15
	D112,D113,D114,D115,D116,D117,D118,D119,D120,D121,D122,D123,D124,D125,D126,D127,	//map to P316..31
#endif
#if defined(LPC_GPIO4)
	//GPIO4
	D128,D129,D130,D131,D132,D133,D134,D135,D136,D137,D138,D139,D141,D142,D143,D144,	//map to P40..15
	D145,D146,D147,D148,D149,D150,D151,D152,D153,D154,D155,D156,D157,D158,D159,D160,	//map to P416..31
#endif
	DMAX										//boundary check
} PIN_T;

//gpio definitions
//port macros
#define IO_SET(port, pins) 	port->DATA |= (pins)	//port->ODR |= (pins)		//port->BSRR = (pins)
#define IO_CLR(port, pins)	port->DATA &=~(pins)		//port->BRR = (pins)
#define IO_FLP(port, pins)	port->DATA ^= (pins)
#define IO_GET(port, pins)	((port->DATA) & (pins))	//return gpio pins

//fast gpio routines
#define FIO_SET(port, pins)	IO_SET(port, pins)		//port->BSRR = (pins)
#define FIO_CLR(port, pins)	IO_CLR(port, pins)		//port->BRR = (pins)
#define FIO_FLP(port, pins)	IO_FLP(port, pins)		//no fast io routine for pin flipping
#define FIO_GET(port, pins) IO_GET(port, pins)		// no fast io routines

//set pins to output
//void IO_OUT(GPIO_TypeDef* port, uint16_t pins);
#define IO_OUT(port, pins)	port->DIR |= (pins)		//GPIO_SetDir(port, pins, 1)

//set pins as floating input
//void IO_IN(GPIO_TypeDef* port, uint16_t pins);
#define IO_IN(port, pins)	port->DIR &=~(pins)		//GPIO_SetDir(port, pins, 0)

typedef LPC_GPIO_TypeDef 	GPIO_TypeDef;
#define GPIO0				LPC_GPIO0
#define GPIO1				LPC_GPIO1
#define GPIO2				LPC_GPIO2
#define GPIO3				LPC_GPIO3
#define GPIO4				LPC_GPIO4
#define GPIO5				LPC_GPIO5

//struct used to map a pin to GPIO+mask
typedef struct {
	GPIO_TypeDef *gpio;					//gpio for a pin
	uint32_t mask;						//pin position [0..31] - 32bit
} PIN2GPIO;

//pin defs for analog functions
typedef enum {
	A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15,
	AVREFINT,									//AIN16 = Vrefint
	ATEMP,										//AIN17 = temperature sensor
	AMAX										//boundary check
} AIN_T;

#endif // BOARD_ATMEGA328P_H_INCLUDED
