#ifndef BOARD_TM4C123_H_INCLUDED
#define BOARD_TM4C123_H_INCLUDED

//implemented for TM4C123
//v0.10: 12/28/2017
//GPIO: pinMode(), digitalWrite(), digitalRead()
//timing: ticks(), micros(), millis(), delayTicks(), delayMicros()/delayMicroseconds(), delayMillis()/delayMilliseconds()/delay()
//not implemented
//analog: analogRead(), analogWrite()
//serial: serial_begin(), serial_write(), serial_read(), ...

//compiler: TI CCS (requires CMSIS start-up files)
#include "tm4c123.h"								//we use tm4c123
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
#define NOP()				__nop()				//nop op
#define interrupts()		__enable_irq()		//enable interrupts - always
#define noInterrupts()		__disable_irq()		//disable interrupts- always

//pin defs for gpio functions
typedef enum {
	PA0,  PA1,  PA2,  PA3,  PA4,  PA5,  PA6,  PA7,  	//map to GPIOA
	PB0,  PB1,  PB2,  PB3,  PB4,  PB5,  PB6,  PB7,  	//map to GPIOB
	PC0,  PC1,  PC2,  PC3,  PC4,  PC5,  PC6,  PC7,  	//map to GPIOC
#if defined(GPIOD)
	PD0,  PD1,  PD2,  PD3,  PD4,  PD5,  PD6,  PD7,  	//map to GPIOD
#endif
#if defined(GPIOE)
	PE0,  PE1,  PE2,  PE3,  PE4,  PE5,  PE6,  PE7,  	//map to GPIOE
#endif
#if defined(GPIOF)
	PF0,  PF1,  PF2,  PF3,  PF4,  PF5,  PF6,  PF7,  	//map to GPIOF
#endif
#if defined(GPIOG)
	PG0,  PG1,  PG2,  PG3,  PG4,  PG5,  PG6,  PG7,  	//map to GPIOG
#endif
#if defined(GPIOH)
	PH0,  PH1,  PH2,  PH3,  PH4,  PH5,  PH6,  PH7,  	//map to GPIOH
#endif
#if defined(GPIOI)
	PI0,  PI1,  PI2,  PI3,  PI4,  PI5,  PI6,  PI7,  	//map to GPIOI
#endif
#if defined(GPIOJ)
	PJ0,  PJ1,  PJ2,  PJ3,  PJ4,  PJ5,  PJ6,  PJ7,  	//map to GPIOJ
#endif
	DMAX										//boundary check
} PIN_T;

//gpio definitions

//port definitions
//GPIO-based
//gpio macros
#define IO_SET(port, pins)		port->DATA |= (pins)
#define IO_CLR(port, pins)		port->DATA &=~(pins)
#define IO_FLP(port, pins)		port->DATA ^= (pins)
#define IO_GET(port, pins)		((port->DATA) & (pins))
#define IO_IN(port, pins)		do {port->DEN |= (pins); port->PUR &=~(pins); port->PDR &=~(pins); port->DIR &=~(pins);} while (0)
#define IO_INPU(port, pins)		do {port->DEN |= (pins); port->PUR |= (pins); port->PDR &=~(pins); port->DIR &=~(pins);} while (0)
#define IO_OUT(port, pins)		do {port->DEN |= (pins); port->ODR &=~(pins); port->DIR |= (pins);} while (0)

#define GPIO_TypeDef			GPIOA_Type			//for compatability

//struct used to map a pin to GPIO+mask
typedef struct {
	GPIO_TypeDef *gpio;					//gpio for a pin
	uint16_t mask;									//pin position [0..15] - 16bit
} PIN2GPIO;

//pin defs for analog functions
typedef enum {
	A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15,
	AVREFINT,									//AIN16 = Vrefint
	ATEMP,										//AIN17 = temperature sensor
	AMAX										//boundary check
} AIN_T;

#endif // BOARD_ATMEGA328P_H_INCLUDED
