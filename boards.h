#ifndef BOARDS_H_INCLUDED
#define BOARDS_H_INCLUDED

//#include <stdint.h>						//for intx_t types - if not available, use the following defs

typedef unsigned char 	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned long	uint32_t;
typedef signed char 	int8_t;
typedef signed short	int16_t;
typedef signed long		int32_t;

//put board specific header here
#if 	defined(BOARD_AT89C51)			//for AT89C51
  #include "board_at89c51.h"
#elif 	defined(BOARD_ATMEGA328P)		//for ATMEGA328P
  #include "board_atmega328p.h"
#elif 	defined(BOARD_ATMEGA8)			//for ATMEGA8/8L
  #include "board_atmega8.h"
#elif 	defined(BOARD_PIC16F193X)		//for PIC16F193x/PIC16LF193x
  #include "board_pic16f193x.h"
#elif 	defined(BOARD_PIC18FXXK20)		//for PIC18FxxK20
  #include "board_pic18fxxk20.h"
#else
#warning "no board defined!"
#endif

//user must provide the following routines
//reset the mcu
void mcu_init(void);

#endif // BOARDS_H_INCLUDED
