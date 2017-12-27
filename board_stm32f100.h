#ifndef BOARD_STM32F100_H_INCLUDED
#define BOARD_STM32F100_H_INCLUDED

//implemented for STM32F100
//v0.10: 12/26/2017
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
	D64, D65, D66, D67, D68, D69, D70, D71,	D72, D73, D74, D75, D76, D77, D78, D79,		//map to PE0..15
#if defined(RCC_APB2ENR_IOPFEN)
	D80, D81, D82, D83, D84, D85, D86, D87,	D88, D89, D90, D91, D92, D93, D94, D95,		//map to PE0..15
#endif
#if defined(RCC_APB2ENR_IOPGEN)
	D96, D97, D98, D99, D100,D101,D102,D103,D104,D105,D106,D107,D108,D109,D110,D111,	//map to PE0..15
#endif
	DMAX										//boundary check
} PIN_T;

//gpio definitions

//port definitions
//GPIO-based
#define IO_SET(gpio, bits)	gpio->BSRR = (bits)		//gpio->ODR |= (bits)		//set bits on gpio
#define IO_CLR(gpio, bits)	gpio->BRR  = (bits)		//gpio->ODR &=~(bits)		//clear bits on gpio
#define IO_FLP(gpio, bits)	gpio->ODR ^= (bits)		//flip bits on gpio
#define IO_GET(gpio, bits)	((gpio->IDR) & (bits))	//return bits on gpio
//IO handled in pinMode()
//#define IO_IN(gpio, bits)	do {gpio->DDR &=~(bits); gpio->CR1&=~(bits); gpio->CR2&=~(bits);} while (0)		//set bits as input
//#define IO_INPU(gpio, bits)	do {gpio->DDR &=~(bits); gpio->CR1|= (bits); gpio->CR2&=~(bits);} while (0)		//set bits as input
//#define IO_OUT(gpio, bits)	do {gpio->DDR |= (bits); gpio->CR1|= (bits); gpio->CR2&=~(bits);} while (0)		//ddr |= (bits)		//set bits as output

//struct used to map a pin to GPIO+mask
typedef struct {
	GPIO_TypeDef *gpio;					//gpio for a pin
	uint16_t pos;						//pin position [0..15] - 16bit
} PIN2GPIO;

//pin defs for analog functions
typedef enum {
	A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15,
	AVREFINT,									//AIN16 = Vrefint
	ATEMP,										//AIN17 = temperature sensor
	AMAX										//boundary check
} AIN_T;

//interrupt from iostm8.h

/*-------------------------------------------------------------------------
 *      Interrupt vector numbers
 *-----------------------------------------------------------------------*/
#define AWU_vector                           0x03
#define CLK_CSS_vector                       0x04
#define CLK_SWITCH_vector                    0x04
#define beCAN_FMP_vector                     0x0A
#define beCAN_FULL_vector                    0x0A
#define beCAN_FOVR_vector                    0x0A
#define beCAN_EWGF_vector                    0x0B
#define beCAN_EPVF_vector                    0x0B
#define beCAN_BOFF_vector                    0x0B
#define beCAN_LEC0_vector                    0x0B
#define beCAN_LEC1_vector                    0x0B
#define beCAN_LEC2_vector                    0x0B
#define beCAN_RQCP0_vector                   0x0B
#define beCAN_RQCP1_vector                   0x0B
#define beCAN_RQCP2_vector                   0x0B
#define beCAN_WKUI_vector                    0x0B
#define SPI_TXE_vector                       0x0C
#define SPI_RXNE_vector                      0x0C
#define SPI_WKUP_vector                      0x0C
#define SPI_MODF_vector                      0x0C
#define SPI_OVR_vector                       0x0C
#define SPI_CRCERR_vector                    0x0C
#define TIM1_OVR_UIF_vector                  0x0D
#define TIM1_CAPCOM_BIF_vector               0x0D
#define TIM1_CAPCOM_TIF_vector               0x0D
#define TIM1_CAPCOM_CC1IF_vector             0x0E
#define TIM1_CAPCOM_CC2IF_vector             0x0E
#define TIM1_CAPCOM_CC3IF_vector             0x0E
#define TIM1_CAPCOM_CC4IF_vector             0x0E
#define TIM1_CAPCOM_COMIF_vector             0x0E
#define TIM2_OVR_UIF_vector                  0x0F
#define TIM2_CAPCOM_TIF_vector               0x10
#define TIM2_CAPCOM_CC1IF_vector             0x10
#define TIM2_CAPCOM_CC2IF_vector             0x10
#define TIM2_CAPCOM_CC3IF_vector             0x10
#define TIM3_OVR_UIF_vector                  0x11
#define TIM3_CAPCOM_TIF_vector               0x12
#define TIM3_CAPCOM_CC1IF_vector             0x12
#define TIM3_CAPCOM_CC2IF_vector             0x12
#define TIM3_CAPCOM_CC3IF_vector             0x12
#define UART1_T_TXE_vector                   0x13
#define UART1_T_TC_vector                    0x13
#define UART1_R_RXNE_vector                  0x14
#define UART1_R_OR_vector                    0x14
#define UART1_R_IDLE_vector                  0x14
#define UART1_R_PE_vector                    0x14
#define UART1_R_LBDF_vector                  0x14
#define I2C_SB_vector                        0x15
#define I2C_ADDR_vector                      0x15
#define I2C_ADD10_vector                     0x15
#define I2C_STOPF_vector                     0x15
#define I2C_BTF_vector                       0x15
#define I2C_WUFH_vector                      0x15
#define I2C_RXNE_vector                      0x15
#define I2C_TXE_vector                       0x15
#define I2C_BERR_vector                      0x15
#define I2C_ARLO_vector                      0x15
#define I2C_AF_vector                        0x15
#define I2C_OVR_vector                       0x15
#define UART3_T_TXE_vector                   0x16
#define UART3_T_TC_vector                    0x16
#define UART3_R_RXNE_vector                  0x17
#define UART3_R_OR_vector                    0x17
#define UART3_R_IDLE_vector                  0x17
#define UART3_R_PE_vector                    0x17
#define UART3_R_LBDF_vector                  0x17
#define UART3_R_LHDF_vector                  0x17
#define ADC2_AWDG_vector                     0x18
#define ADC2_EOC_vector                      0x18
#define TIM4_OVR_UIF_vector                  0x19
#define FLASH_EOP_vector                     0x1A
#define FLASH_WR_PG_DIS_vector               0x1A

#endif // BOARD_ATMEGA328P_H_INCLUDED
