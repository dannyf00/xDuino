#ifndef BOARD_STM8S003_H_INCLUDED
#define BOARD_STM8S003_H_INCLUDED

//implemented for STM8S003
//v0.10: 12/26/2017
//GPIO: pinMode(), digitalWrite(), digitalRead()
//timing: ticks(), micros(), millis(), delayTicks(), delayMicros()/delayMicroseconds(), delayMillis()/delayMilliseconds()/delay()
//not implemented
//analog: analogRead(), analogWrite()
//serial: serial_begin(), serial_write(), serial_read(), ...

//compiler: IAR-STM8
#include "stm8s.h"								//we use stm8s
//#include <stdint.h>								//we use uintx types - if not available, use the alternatives below
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
#define F_CPU				(16000000ul/1)		//CPU frequency, in Hz
#define NOP()				nop()				//nop op
#define interrupts()		enableInterrupts()	//enable interrupts
#define noInterrupts()		disableInterrupts()	//disable interrupts

#define CLK_PRESCALER_CPUDIV1			0x00					//cpu / 1
#define CLK_PRESCALER_CPUDIV2			0x01					//cpu / 2
#define CLK_PRESCALER_CPUDIV4			0x02					//cpu / 4
#define CLK_PRESCALER_CPUDIV8			0x03					//cpu / 8
#define CLK_PRESCALER_CPUDIV16			0x04					//cpu / 16
#define CLK_PRESCALER_CPUDIV32			0x05					//cpu / 32
#define CLK_PRESCALER_CPUDIV64			0x06					//cpu / 64
#define CLK_PRESCALER_CPUDIV128			0x07					//cpu / 128
#define CLK_PRESCALER_HSIDIV1			(0<<3)					//hsi divider 1:1
#define CLK_PRESCALER_HSIDIV2			(1<<3)					//hsi divider 2:1
#define CLK_PRESCALER_HSIDIV4			(2<<3)					//hsi divider 4:1
#define CLK_PRESCALER_HSIDIV8			(3<<3)					//hsi divider 8:1

//use hsi oscillator
void SystemCoreClockHSI(uint8_t CLK_HSIDIV);

//oscillator macros for HSI + dividers
//void SystemCoreClockHSE(/*CLK_Prescaler_TypeDef CLK_CPUDIV*/);		//running on external crystal / oscillator, specified in HSE_VALUE
//void SystemCoreClockHSI(CLK_Prescaler_TypeDef CLK_Prescaler);		//running on external crystal / oscillator, specified in HSE_VALUE
//void SystemCoreClockLSI(/*CLK_Prescaler_TypeDef CLK_CPUDIV*/);		//running on internal low speed oscillator, specified in LSI_VALUE(=128Khz)
#define SystemCoreClockHSI_16MHz()	SystemCoreClockHSI(CLK_PRESCALER_HSIDIV1)
#define SystemCoreClockHSI_8MHz()	SystemCoreClockHSI(CLK_PRESCALER_HSIDIV2)
#define SystemCoreClockHSI_4MHz()	SystemCoreClockHSI(CLK_PRESCALER_HSIDIV4)
#define SystemCoreClockHSI_2MHz()	SystemCoreClockHSI(CLK_PRESCALER_HSIDIV8)

//pin defs for gpio functions
typedef enum {
	D0,  D1,  D2,  D3,  D4,  D5,  D6,  D7,		//maps to PA0..7
	D8,  D9,  D10, D11, D12, D13, D14, D15,		//maps to PB0..7 (PC7 is missing)
	D16, D17, D18, D19, D20, D21, D22, D23, 	//maps to PC0..7
	D24, D25, D26, D27, D28, D29, D30, D31,		//maps to PD0..7
	D32, D33, D34, D35, D36, D37, D38, D39,		//maps to PE0..7
	DMAX										//boundary check
} PIN_T;

//gpio definitions

//port definitions
#define IO_SET(gpio, bits)	gpio->ODR |= (bits)		//set bits on gpio
#define IO_CLR(gpio, bits)	gpio->ODR &=~(bits)		//clear bits on gpio
#define IO_FLP(gpio, bits)	gpio->ODR ^= (bits)		//flip bits on gpio
#define IO_GET(gpio, bits)	((gpio->IDR) & (bits))	//return bits on gpio
#define IO_IN(gpio, bits)	do {gpio->DDR &=~(bits); gpio->CR1&=~(bits); gpio->CR2&=~(bits);} while (0)		//set bits as input
#define IO_INPU(gpio, bits)	do {gpio->DDR &=~(bits); gpio->CR1|= (bits); gpio->CR2&=~(bits);} while (0)		//set bits as input
#define IO_OUT(gpio, bits)	do {gpio->DDR |= (bits); gpio->CR1|= (bits); gpio->CR2&=~(bits);} while (0)		//ddr |= (bits)		//set bits as output

//struct used to map a pin to GPIO+mask
typedef struct {
	GPIO_TypeDef *gpio;					//gpio for a pin
	uint8_t mask;						//pin mask - 16bit
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
