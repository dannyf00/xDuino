#ifndef BOARDS_H_INCLUDED
#define BOARDS_H_INCLUDED

#include <stdint.h>						//for intx_t types - if not available, use the following defs
/*
typedef unsigned char 	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned long	uint32_t;
typedef signed char 	int8_t;
typedef signed short	int16_t;
typedef signed long		int32_t;
*/
//put board specific header here
#if 	defined(BOARD_AT89C51)			//for AT89C51
  #include "board_at89c51.h"
#elif 	defined(BOARD_ATMEGA328P)		//for ATMEGA328P
  #include "board_atmega328p.h"
#elif 	defined(BOARD_ATMEGA8)			//for ATMEGA8/8L
  #include "board_atmega8.h"
#elif 	defined(BOARD_PIC16F193X)		//for PIC16F1933/4/6/7/8/9 and PIC16LF1933/4/6/7/8/9
  #include "board_pic16f193x.h"
#elif 	defined(BOARD_PIC18FXXK20)		//for PIC18F23/23/25/26K20 and PIC18F43/44/45/46K20
  #include "board_pic18fxxk20.h"
#elif 	defined(BOARD_PIC24FJ64GA102)		//for PIC24FJ32GA102/104 and PIC24FJ64GA102/104
  #include "board_pic24fj64ga102.h"
#elif 	defined(BOARD_STM8S105)			//for STM8S105
  #include "board_stm8s105.h"
#elif 	defined(BOARD_STM8S003)			//for STM8S003
  #include "board_stm8s003.h"
#elif 	defined(BOARD_STM32F100)		//for STM32F100
  #include "board_stm32f100.h"
#elif 	defined(BOARD_STM32F103)		//for STM32F103
  #include "board_stm32f103.h"
#elif 	defined(BOARD_STM32F030)		//for STM32F030
  #include "board_stm32f030.h"
#elif 	defined(BOARD_STM32F303)		//for STM32F303
  #include "board_stm32f303.h"
#elif 	defined(BOARD_STM32F407)		//for STM32F407
  #include "board_stm32f407.h"
#elif 	defined(BOARD_MSP432)			//for MSP432
  #include "board_msp432.h"
#elif 	defined(BOARD_LPC12XX)			//for LPC12XX
  #include "board_lpc12xx.h"
#else
#warning "no board defined!"
#endif

//user must provide the following routines
//reset the mcu
void mcu_init(void);

#endif // BOARDS_H_INCLUDED
