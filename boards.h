#ifndef BOARDS_H_INCLUDED
#define BOARDS_H_INCLUDED

//put board specific header here
#if 	defined(BOARD_ATMEGA328P)		//for ATMEGA328P
  #include "board_atmega328p.h"
#elif 	defined(BOARD_ATMEGA8)			//for ATMEGA8/8L
  #include "board_atmega8.h"
#elif 	defined(BOARD_PIC16F193X)		//for PIC16F193x/PIC16LF193x
  #include "board_pic16f193x.h"
#elif 	defined(BOARD_PIC18FXXK20)		//for PIC18FxxK20
  #include "board_pic18fxxK20.h"
#else
#warning "no board defined!"
#endif

//user must provide the following routines
//reset the mcu
void mcu_init(void);

#endif // BOARDS_H_INCLUDED
