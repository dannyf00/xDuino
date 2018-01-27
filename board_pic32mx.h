#ifndef BOARD_PIC32MX_H_INCLUDED
#define BOARD_PIC32MX_H_INCLUDED

//implemented for PIC32MX1/2/3
//v0.10: 12/28/2017
//GPIO: pinMode(), digitalWrite(), digitalRead()
//timing: ticks(), micros(), millis(), delayTicks(), delayMicros()/delayMicroseconds(), delayMillis()/delayMilliseconds()/delay()
//not implemented
//analog: analogRead(), analogWrite()
//serial: serial_begin(), serial_write(), serial_read(), ...

//compiler: XC32
#include <xc.h>									//we use xc
#include <sys/attribs.h>										//attributes for interrupts
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
#define interrupts()		ei()				//enable interrupts
#define noInterrupts()		di()				//disable interrupts

#ifndef ei
#define ei()				__builtin_enable_interrupts()	//do {INTEnableInterrupts();	INTEnableSystemMultiVectoredInt();} while (0)	//__builtin_enable_interrupts()

#endif

#ifndef di
#define di()				__builtin_enable_interrupts()	//INTDisableInterrupts()			//__builtin_disable_interrupts()	//
#endif

//unlock IOLOCK
#define IO_UNLOCK()	{asm volatile ( "MOV #OSCCON, w1 \n" \
					"MOV #0x46, w2 \n" \
					"MOV #0x57, w3 \n" \
					"MOV.b w2, [w1] \n" \
					"MOV.b w3, [w1] \n" \
					"BCLR OSCCON,#6"); \
					}

//lock IOLOCK
#define IO_LOCK()	{asm volatile ( "MOV #OSCCON, w1 \n" \
					"MOV #0x46, w2 \n" \
					"MOV #0x57, w3 \n" \
					"MOV.b w2, [w1] \n" \
					"MOV.b w3, [w1] \n" \
					"BSET OSCCON, #6" ); \
					}


//pin defs for gpio functions
typedef enum {
	PA0,  PA1,  PA2,  PA3,  PA4,  PA5,  PA6,  PA7,  PA8,  PA9,  PA10, PA11, PA12, PA13, PA14, PA15,		//maps to PA0..15
	PB0,  PB1,  PB2,  PB3,  PB4,  PB5,  PB6,  PB7,  PB8,  PB9,  PB10, PB11, PB12, PB13, PB14, PB15,		//maps to PB0..15
	//PC0,  PC1,  PC2,  PC3,  PC4,  PC5,  PC6,  PC7,  PC8,  PC9,  PC10, PC11, PC12, PC13, PC14, PC15,		//maps to PC0..15
	DMAX										//boundary check
} PIN_T;

//gpio definitions
typedef struct {
    volatile uint32_t TRIS;             //data direction register -> 0ffset 0x0000, little endian
    //volatile uint32_t RESERVED0[3];     //fill the space
    volatile uint32_t TRISCLR;          //set to clear
    volatile uint32_t TRISSET;          //set to set
    volatile uint32_t TRISINV;          //set to flip
    volatile uint32_t PORT;             //input data register
    volatile uint32_t RESERVED1[3];     //fill the space
    volatile uint32_t LAT;              //output data register
    //volatile uint32_t RESERVED2[3];     //fill the space
    volatile uint32_t LATCLR;          //set to clear
    volatile uint32_t LATSET;          //set to set
    volatile uint32_t LATINV;          //set to flip
    volatile uint32_t ODC;              //open drain configuration register. set to activate open drain
    //volatile uint32_t RESERVED3[3];     //fill the space

} GPIO_TypeDef;                          //port definition registers

#define GPIOA                           ((GPIO_TypeDef *) &TRISA)
#define GPIOB                           ((GPIO_TypeDef *) &TRISB)
#define GPIOC                           ((GPIO_TypeDef *) &TRISC)
#define GPIOD                           ((GPIO_TypeDef *) &TRISD)
#define GPIOE                           ((GPIO_TypeDef *) &TRISE)
#define GPIOF                           ((GPIO_TypeDef *) &TRISF)
#define GPIOG                           ((GPIO_TypeDef *) &TRISG)

//port definitions
//if gpio_typedef is used
#define IO_SET(port, bits)              FIO_SET(port, bits)				//port->LAT |= (bits)			//set bits on port
#define IO_CLR(port, bits)              FIO_CLR(port, bits)				//port->LAT &=~(bits)			//clear bits on port
#define IO_FLP(port, bits)              FIO_FLP(port, bits)				//port->LAT ^= (bits)			//flip bits on port
#define IO_GET(port, bits)              ((port->PORT) & (bits))			//return bits on port
#define IO_OUT(port, bits)              port->TRIS &=~(bits)			//set bits as output
#define IO_IN(port, bits)               port->TRIS |= (bits)			//set bits as input

//fast port operations
#define FIO_SET(port, bits)              port->LATSET = (bits)			//set bits on port
#define FIO_CLR(port, bits)              port->LATCLR = (bits)			//clear bits on port
#define FIO_FLP(port, bits)              port->LATINV = (bits)			//flip bits on port
#define FIO_GET(port, bits)              ((port->PORT) & (bits))		//return bits on port
#define FIO_OUT(port, bits)              port->TRISCLR = (bits)			//set bits as output
#define FIO_IN(port, bits)               port->TRISSET = (bits)			//set bits as input

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
