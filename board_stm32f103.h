#ifndef BOARD_STM32F103_H_INCLUDED
#define BOARD_STM32F103_H_INCLUDED

//implemented for STM32F103
//v0.10: 12/27/2017
//GPIO: pinMode(), digitalWrite(), digitalRead()
//timing: ticks(), micros(), millis(), delayTicks(), delayMicros()/delayMicroseconds(), delayMillis()/delayMilliseconds()/delay()
//not implemented
//analog: analogRead(), analogWrite()
//serial: serial_begin(), serial_write(), serial_read(), ...

//compiler: IAR-STM8
#include "stm32f10x.h"							//we use stm32f100
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
	D0,  D1,  D2,  D3,  D4,  D5,  D6,  D7,  D8,  D9,  D10, D11, D12, D13, D14, D15,		//map to PA0..15 (PC7 is missing)
	D16, D17, D18, D19, D20, D21, D22, D23,	D24, D25, D26, D27, D28, D29, D30, D31,		//map to PB0..15
	D32, D33, D34, D35, D36, D37, D38, D39,	D40, D41, D42, D43, D44, D45, D46, D47,		//map to PC0..15
	D48, D49, D50, D51, D52, D53, D54, D55,	D56, D57, D58, D59, D60, D61, D62, D63,		//map to PD0..15
#if defined(RCC_APB2ENR_IOPEEN)
	D64, D65, D66, D67, D68, D69, D70, D71,	D72, D73, D74, D75, D76, D77, D78, D79,		//map to PE0..15
#endif
#if defined(RCC_APB2ENR_IOPFEN)
	D80, D81, D82, D83, D84, D85, D86, D87,	D88, D89, D90, D91, D92, D93, D94, D95,		//map to PE0..15
#endif
#if defined(RCC_APB2ENR_IOPGEN)
	D96, D97, D98, D99, D100,D101,D102,D103,D104,D105,D106,D107,D108,D109,D110,D111,	//map to PE0..15
#endif
	DMAX										//boundary check
} PIN_T;

//gpio definitions
//gpio cnf1..0 + mod1..0
#define GPIOMODE_INAN		0x00			//0b0000->analog input
#define GPIOMODE_INFL		0x04			//0b0100->floating input
#define GPIOMODE_INPU		0x08			//0b1000->input, pull-up (odr=1)
#define GPIOMODE_INDN		0x08			//0b1000->input, pull-dn (odr=0)
#define GPIOMODE_OUTPP		0x01			//0b0001->pushpull output @ 10Mhz
#define GPIOMODE_OUTOD		0x09			//0b1001->open drain output @ 10Mhz
#define GPIOMODE_AFPP		0x09			//0b1001->alternative function output, push-pull, 10Mhz
#define GPIOMODE_AFOD		0x0d			//0b1101->alternative function output, open-drain, 10Mhz

//port definitions
//GPIO-based
#define IO_SET(gpio, bits)	gpio->BSRR = (bits)		//gpio->ODR |= (bits)		//set bits on gpio
#define IO_CLR(gpio, bits)	gpio->BRR  = (bits)		//gpio->ODR &=~(bits)		//clear bits on gpio
#define IO_FLP(gpio, bits)	gpio->ODR ^= (bits)		//flip bits on gpio
#define IO_GET(gpio, bits)	((gpio->IDR) & (bits))	//return bits on gpio
#define IO_OUTPP(port, pins)				GPIO_DDR(port, pins, GPIOMODE_OUTPP)	//push-pull mode (CR1 set, CR2 cleared)	//IO_OUTPP(GPIOx, GPIO_Pins).
//#define IO_OUTOD(port, pins)				GPIO_DDR(port, pins, GPIOMODE_OUTOD)	//open drain mode (cr1 + cr2 cleared)	//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_OUT_OD_LOW_FAST)
#define IO_OUT(port, pins)					IO_OUTPP(port, pins)					//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_OUT_PP_LOW_FAST)
#define IO_INFL(port, pins)					GPIO_DDR(port, pins, GPIOMODE_INFL)		//floating input, no interrupt			//IO_INFL(GPIOx, GPIO_Pins)
#define IO_INPU(port, pins)					GPIO_DDR(port, pins, GPIOMODE_INPU)		//pull-up, no interrupt					//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_IN_PU_NO_IT)
#define IO_IN(port, pins)					IO_INFL(port, pins)					//IO_IN(port, pins)				//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_IN_FL_NO_IT)
//#define IO_AFPP(port, pins)					GPIO_DDR(port, pins, GPIOMODE_AFPP)		//configure pin for alternative function output, push-pull, 10Mhz
//#define IO_AFOD(port, pins)					GPIO_DDR(port, pins, GPIOMODE_AFOD)		//configure pin for alternative function output, open-drain, 10Mhz
//#define IO_AN(port, pins)					GPIO_DDR(port, pins, GPIOMODE_INAN)


//struct used to map a pin to GPIO+mask
typedef struct {
	GPIO_TypeDef *gpio;					//gpio for a pin
	uint16_t mask;						//pin position [0..15] - 16bit
} PIN2GPIO;

//pin defs for analog functions
typedef enum {
	A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15,
	AVREFINT,									//AIN16 = Vrefint
	ATEMP,										//AIN17 = temperature sensor
	AMAX										//boundary check
} AIN_T;

#endif // BOARD_ATMEGA328P_H_INCLUDED
