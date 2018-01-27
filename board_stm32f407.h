#ifndef BOARD_STM32F407_H_INCLUDED
#define BOARD_STM32F407_H_INCLUDED

//implemented for STM32F407
//v0.10: 12/28/2017
//GPIO: pinMode(), digitalWrite(), digitalRead()
//timing: ticks(), micros(), millis(), delayTicks(), delayMicros()/delayMicroseconds(), delayMillis()/delayMilliseconds()/delay()
//not implemented
//analog: analogRead(), analogWrite()
//serial: serial_begin(), serial_write(), serial_read(), ...

//compiler: GCC-ARM
#include "stm32f4xx.h"							//we use stm32f407
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
	PA0,  PA1,  PA2,  PA3,  PA4,  PA5,  PA6,  PA7,  PA8,  PA9,  PA10, PA11, PA12, PA13, PA14, PA15,		//map to PA0..15 (PC7 is missing)
	PB0,  PB1,  PB2,  PB3,  PB4,  PB5,  PB6,  PB7,  PB8,  PB9,  PB10, PB11, PB12, PB13, PB14, PB15,		//map to PB0..15 (PC7 is missing)
	PC0,  PC1,  PC2,  PC3,  PC4,  PC5,  PC6,  PC7,  PC8,  PC9,  PC10, PC11, PC12, PC13, PC14, PC15,		//map to PC0..15 (PC7 is missing)
	PD0,  PD1,  PD2,  PD3,  PD4,  PD5,  PD6,  PD7,  PD8,  PD9,  PD10, PD11, PD12, PD13, PD14, PD15,		//map to PD0..15 (PC7 is missing)
#if defined(RCC_AHB1ENR_GPIOEEN)
	PE0,  PE1,  PE2,  PE3,  PE4,  PE5,  PE6,  PE7,  PE8,  PE9,  PE10, PE11, PE12, PE13, PE14, PE15,		//map to PE0..15 (PC7 is missing)
#endif
#if defined(RCC_AHB1ENR_GPIOFEN)
	PF0,  PF1,  PF2,  PF3,  PF4,  PF5,  PF6,  PF7,  PF8,  PF9,  PF10, PF11, PF12, PF13, PF14, PF15,		//map to PF0..15 (PC7 is missing)
#endif
#if defined(RCC_AHB1ENR_GPIOGEN)
	PG0,  PG1,  PG2,  PG3,  PG4,  PG5,  PG6,  PG7,  PG8,  PG9,  PG10, PG11, PG12, PG13, PG14, PG15,		//map to PG0..15 (PC7 is missing)
#endif
#if defined(RCC_AHB1ENR_GPIOHEN)
	PH0,  PH1,  PH2,  PH3,  PH4,  PH5,  PH6,  PH7,  PH8,  PH9,  PH10, PH11, PH12, PH13, PH14, PH15,		//map to PH0..15 (PC7 is missing)
#endif
#if defined(RCC_AHB1ENR_GPIOIEN)
	PI0,  PI1,  PI2,  PI3,  PI4,  PI5,  PI6,  PI7,  PI8,  PI9,  PI10, PI11, PI12, PI13, PI14, PI15,		//map to PI0..15 (PC7 is missing)
#endif
	DMAX										//boundary check
} PIN_T;

//gpio definitions
//MODE:
//Output modes: GPIOMODE_OUTPP, GPIOMODE_OUTOD
//Input mode: GPIOMODE_INPUT, GPIOMODE_INPUTPD, GPIOMODE_INPUTPU
//Alternate function: GPIOMODE_AFPP, GPIOMODE_AFOD
//for moder
#define GPIOMODE_INPUT		(0<<0)		//(0<<0)
#define GPIOMODE_OUTPUT		(1<<0)		//(1<<0)
#define GPIOMODE_AF			(2<<0)
#define GPIOMODE_AN			(3<<0)
//for otyper
#define GPIOMODE_PP			(1<<3)
#define GPIOMODE_OD			(0<<3)
//for pupdr
#define GPIOMODE_FL			(0<<4)
#define GPIOMODE_PU			(1<<4)
#define GPIOMODE_PD			(2<<4)

#define GPIOMODE_OUTPP		(GPIOMODE_OUTPUT | GPIOMODE_PP)		//gpio, output, push-pull
#define GPIOMODE_OUTOD		(GPIOMODE_OUTPUT | GPIOMODE_OD)		//gpio, output, od
#define GPIOMODE_INFL		(GPIOMODE_INPUT)
#define GPIOMODE_INPU		(GPIOMODE_INPUT | GPIOMODE_PU)
#define GPIOMODE_INPD		(GPIOMODE_INPUT | GPIOMODE_PD)
#define GPIOMODE_AFPP		(GPIOMODE_AF | GPIOMODE_PP)
#define GPIOMODE_AFOD		(GPIOMODE_AF | GPIOMODE_OD)
#define GPIOMODE_INAN		(GPIOMODE_AN)

//port definitions
//GPIO-based
#define IO_SET(gpio, bits)	gpio->ODR |= (bits)		//set bits on gpio
#define IO_CLR(gpio, bits)	gpio->ODR &=~(bits)		//clear bits on gpio
#define IO_FLP(gpio, bits)	gpio->ODR ^= (bits)		//flip bits on gpio
#define IO_GET(gpio, bits)	((gpio->IDR) & (bits))	//return bits on gpio
#define IO_OUTPP(port, pins)				GPIO_DDR(port, pins, GPIOMODE_OUTPP)	//push-pull mode (CR1 set, CR2 cleared)	//IO_OUTPP(GPIOx, GPIO_Pins).
//#define IO_OUTOD(port, pins)				GPIO_DDR(port, pins, GPIOMODE_OUTOD)	//open drain mode (cr1 + cr2 cleared)	//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_OUT_OD_LOW_FAST)
#define IO_OUT(port, pins)					IO_OUTPP(port, pins)					//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_OUT_PP_LOW_FAST)
#define IO_INFL(port, pins)					GPIO_DDR(port, pins, GPIOMODE_INFL)		//floating input, no interrupt			//IO_INFL(GPIOx, GPIO_Pins)
#define IO_INPU(port, pins)					GPIO_DDR(port, pins, GPIOMODE_INPU)		//pull-up, no interrupt					//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_IN_PU_NO_IT)
//#define IO_INPD(port, pins)					GPIO_DDR(port, pins, GPIOMODE_INPD)		//pull-up, no interrupt					//_GPIO_Init(GPIOx, GPIO_Pins, GPIO_MODE_IN_PU_NO_IT)
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
