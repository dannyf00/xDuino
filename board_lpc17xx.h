#ifndef BOARD_LPC17XX_H_INCLUDED
#define BOARD_LPC17XX_H_INCLUDED

//implemented for LPC13xx
//v0.10: 12/28/2017
//GPIO: pinMode(), digitalWrite(), digitalRead()
//timing: ticks(), micros(), millis(), delayTicks(), delayMicros()/delayMicroseconds(), delayMillis()/delayMilliseconds()/delay()
//not implemented
//analog: analogRead(), analogWrite()
//serial: serial_begin(), serial_write(), serial_read(), ...

//compiler: LPCXpresso
#include "lpc17xx.h"							//we use lpc17xx
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
#if defined(LPC_GPIO0)
	//GPIO0
	P0_0,  P0_1,  P0_2,  P0_3,  P0_4,  P0_5,  P0_6,  P0_7,  P0_8,  P0_9,  P0_10, P0_11, P0_12, P0_13, P0_14, P0_15,	P0_16, P0_17, P0_18, P0_19, P0_20, P0_21, P0_22, P0_23,	P0_24, P0_25, P0_26, P0_27, P0_28, P0_29, P0_30, P0_31,		//map to P0_16..31
#endif
#if defined(LPC_GPIO1)
	//GPIO1
	P1_0,  P1_1,  P1_2,  P1_3,  P1_4,  P1_5,  P1_6,  P1_7,  P1_8,  P1_9,  P1_10, P1_11, P1_12, P1_13, P1_14, P1_15,	P1_16, P1_17, P1_18, P1_19, P1_20, P1_21, P1_22, P1_23,	P1_24, P1_25, P1_26, P1_27, P1_28, P1_29, P1_30, P1_31,		//map to P1_16..31
#endif
#if defined(LPC_GPIO2)
	P2_0,  P2_1,  P2_2,  P2_3,  P2_4,  P2_5,  P2_6,  P2_7,  P2_8,  P2_9,  P2_10, P2_11, P2_12, P2_13, P2_14, P2_15,	P2_16, P2_17, P2_18, P2_19, P2_20, P2_21, P2_22, P2_23,	P2_24, P2_25, P2_26, P2_27, P2_28, P2_29, P2_30, P2_31,		//map to P2_16..31
#endif
#if defined(LPC_GPIO3)
	P3_0,  P3_1,  P3_2,  P3_3,  P3_4,  P3_5,  P3_6,  P3_7,  P3_8,  P3_9,  P3_10, P3_11, P3_12, P3_13, P3_14, P3_15,	P3_16, P3_17, P3_18, P3_19, P3_20, P3_21, P3_22, P3_23,	P3_24, P3_25, P3_26, P3_27, P3_28, P3_29, P3_30, P3_31,		//map to P3_16..31
#endif
#if defined(LPC_GPIO4)
	P4_0,  P4_1,  P4_2,  P4_3,  P4_4,  P4_5,  P4_6,  P4_7,  P4_8,  P4_9,  P4_10, P4_11, P4_12, P4_13, P4_14, P4_15,	P4_16, P4_17, P4_18, P4_19, P4_20, P4_21, P4_22, P4_23,	P4_24, P4_25, P4_26, P4_27, P4_28, P4_29, P4_30, P4_31,		//map to P4_16..31
#endif
#if defined(LPC_GPIO5)
	P5_0,  P5_1,  P5_2,  P5_3,  P5_4,  P5_5,  P5_6,  P5_7,  P5_8,  P5_9,  P5_10, P5_11, P5_12, P5_13, P5_14, P5_15,	P5_16, P5_17, P5_18, P5_19, P5_20, P5_21, P5_22, P5_23,	P5_24, P5_25, P5_26, P5_27, P5_28, P5_29, P5_30, P5_31,		//map to P5_16..31
#endif

	DMAX										//boundary check
} PIN_T;

//gpio definitions
//port macros
#define IO_SET(port, pins) 	port->FIOPIN |= (pins)	//port->ODR |= (pins)		//port->BSRR = (pins)
#define IO_CLR(port, pins)	port->FIOPIN &=~(pins)		//port->BRR = (pins)
#define IO_FLP(port, pins)	port->FIOPIN ^= (pins)
#define IO_GET(port, pins)	((port->FIOPIN) & (pins))	//return gpio pins

//fast gpio routines
#define FIO_SET(port, pins)	IO_SET(port, pins)		//port->BSRR = (pins)
#define FIO_CLR(port, pins)	IO_CLR(port, pins)		//port->BRR = (pins)
#define FIO_FLP(port, pins)	IO_FLP(port, pins)		//no fast io routine for pin flipping
#define FIO_GET(port, pins) IO_GET(port, pins)		// no fast io routines

//set pins to output
//void IO_OUT(GPIO_TypeDef* port, uint16_t pins);
#define IO_OUT(port, pins)	port->FIODIR |= (pins)		//GPIO_SetDir(port, pins, 1)

//set pins as floating input
//void IO_IN(GPIO_TypeDef* port, uint16_t pins);
#define IO_IN(port, pins)	port->FIODIR &=~(pins)		//GPIO_SetDir(port, pins, 0)

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
