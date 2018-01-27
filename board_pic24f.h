#ifndef BOARD_PIC24FJ64GA102_H_INCLUDED
#define BOARD_PIC24FJ64GA102_H_INCLUDED

//implemented for PIC24FJ32GA102/104, and PIC24FJ64GA102/104
//v0.10: 12/26/2017
//GPIO: pinMode(), digitalWrite(), digitalRead()
//timing: ticks(), micros(), millis(), delayTicks(), delayMicros()/delayMicroseconds(), delayMillis()/delayMilliseconds()/delay()
//not implemented
//analog: analogRead(), analogWrite()
//serial: serial_begin(), serial_write(), serial_read(), ...

//compiler: XC16
#include <xc.h>									//we use xc
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
#define F_CPU				(16000000ul/2)		//CPU frequency, in Hz
#define NOP()				Nop()				//nop op
#define interrupts()		sei()				//enable interrupts
#define noInterrupts()		cli()				//disable interrupts

//pin defs for gpio functions
typedef enum {
	PA0,  PA1,  PA2,  PA3,  PA4,  PA5,  PA6,  PA7,  PA8,  PA9,  PA10, PA11, PA12, PA13, PA14, PA15,		//maps to PA0..15
	PB0,  PB1,  PB2,  PB3,  PB4,  PB5,  PB6,  PB7,  PB8,  PB9,  PB10, PB11, PB12, PB13, PB14, PB15,		//maps to PB0..15
	//PC0,  PC1,  PC2,  PC3,  PC4,  PC5,  PC6,  PC7,  PC8,  PC9,  PC10, PC11, PC12, PC13, PC14, PC15,		//maps to PC0..15
	DMAX										//boundary check
} PIN_T;

//gpio definitions
typedef struct {
	volatile unsigned short TRIS;	//direction register - offset 0x0000
	volatile unsigned short PORT;	//input data register
	volatile unsigned short LAT;		//output data register
	volatile unsigned short ODC;		//open drain register
} GPIO_TypeDef;				//gpio data registers

#define GPIOA				((GPIO_TypeDef *) &TRISA)
#define GPIOB				((GPIO_TypeDef *) &TRISB)
#define GPIOC            	((GPIO_TypeDef *) &TRISC)
#define GPIOD				((GPIO_TypeDef *) &TRISD)
#define GPIOE				((GPIO_TypeDef *) &TRISE)
#define GPIOF				((GPIO_TypeDef *) &TRISF)
#define GPIOG				((GPIO_TypeDef *) &TRISG)

//port definitions
#define IO_SET(port, bits)	port |= (bits)		//set bits on port
#define IO_CLR(port, bits)	port &=~(bits)		//clear bits on port
#define IO_FLP(port, bits)	port ^= (bits)		//flip bits on port
#define IO_GET(port, bits)	((port) & (bits))	//return bits on port
#define IO_IN(ddr, bits)	IO_SET(ddr,bits)		//set bits as input
#define IO_OUT(ddr, bits)	IO_CLR(ddr,bits)		//ddr |= (bits)		//set bits as output

//struct used to map a pin to GPIO+mask
typedef struct {
	GPIO_TypeDef *gpio;					//gpio for a pin
	uint16_t mask;						//pin mask - 16bit
} PIN2GPIO;

//pin defs for analog functions
typedef enum {
	A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15,
	AVREFINT,									//AIN16 = Vrefint
	ATEMP,										//AIN17 = temperature sensor
	AMAX										//boundary check
} AIN_T;


#endif // BOARD_ATMEGA328P_H_INCLUDED
