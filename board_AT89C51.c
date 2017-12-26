#include "xduino.h"						//use xduino generic defs
#include "board_at89c51.h"				//we use board-specific defs

//put board specific implementation here

//global defines

//global variables
volatile uint32_t timer_ticks=0;		//timer ticks, 32-bit
//gpio pins - hard-coded due to the use of SFR

//timer0 overflow interrupt handler
void _tmr0_isr(void) interrupt TF0_VECTOR {
	//clear the flag - done automatically
	timer_ticks+= 0x10000ul;			//increment timer ticks, T0 in 16-bit mode
}

//user must provide the following functions / macro defs
void mcu_init(void) {
	//initialize timer0, 1:1 prescaler, 16-bit mode overflow interrupt enabled
	//stop the timer
	TR0 = 0;										//0->stop the timer, 1->start the timer
	TMOD = 	(TMOD &~0x0f) | 
			(0 << 3) |								//0->enable timer when TR0 is set
			(0 << 2) |				  				//0->timer operation, 1->counter operation
			(0x03 & 0x01);							//0x01->mode 1, 16-bit T0	
	TH0 = TL0 = 0;									//reset the counter
	TF0 = 0;										//0->clear the flag
	ET0 = 1;										//1->enable the overflow interrupt, 0->disable the interrupt
	TR0 = 1;										//0x00->stop the timer, 0x01 -> start the timer
	//timer0 is running now
	interrupts();									//enable interrupts globally
}

//return ticks
uint32_t ticks(void) {
	uint32_t m;							//hold overflow count
	uint16_t f;							//hold timer counter - T0 is 16-bit wide
	uint8_t msb, lsb;

	//perform a double read
	//noInterrupts();
	do {
		m = timer_ticks;
		msb = TH0;
		lsb = TL0;
	} while (msb != TH0);				//keep reading until msb/lsf are atomic
	//interrupts();
	f = (msb << 8) | lsb;				//form the atomic t0 value 16-bit
	return m | f;						//form the ticks
}

//return time in microseconds
uint32_t micros(void) {
	//return ticks() / (F_CPU / 1000000ul) * 1;		//calculate micro seconds
	return ticks();									//1:1 prescaler @ 1Mhz F_CPU
}

//return time in milliseconds
uint32_t millis(void) {
	return micros() / 1000;
}

//set pin mode
void pinMode(PIN_T pin, uint8_t mode) {

	switch (pin) {
		//D0..7 on P0
		case D0 : if (mode == OUTPUT) IO_OUT(P0, 1<<0); else IO_IN(P0, 1<<0); break;
		case D1 : if (mode == OUTPUT) IO_OUT(P0, 1<<1); else IO_IN(P0, 1<<1); break;
		case D2 : if (mode == OUTPUT) IO_OUT(P0, 1<<2); else IO_IN(P0, 1<<2); break;
		case D3 : if (mode == OUTPUT) IO_OUT(P0, 1<<3); else IO_IN(P0, 1<<3); break;
		case D4 : if (mode == OUTPUT) IO_OUT(P0, 1<<4); else IO_IN(P0, 1<<4); break;
		case D5 : if (mode == OUTPUT) IO_OUT(P0, 1<<5); else IO_IN(P0, 1<<5); break;
		case D6 : if (mode == OUTPUT) IO_OUT(P0, 1<<6); else IO_IN(P0, 1<<6); break;
		case D7 : if (mode == OUTPUT) IO_OUT(P0, 1<<7); else IO_IN(P0, 1<<7); break;

		//D8..15 on P1
		case D8 : if (mode == OUTPUT) IO_OUT(P1, 1<<0); else IO_IN(P1, 1<<0); break;
		case D9 : if (mode == OUTPUT) IO_OUT(P1, 1<<1); else IO_IN(P1, 1<<1); break;
		case D10: if (mode == OUTPUT) IO_OUT(P1, 1<<2); else IO_IN(P1, 1<<2); break;
		case D11: if (mode == OUTPUT) IO_OUT(P1, 1<<3); else IO_IN(P1, 1<<3); break;
		case D12: if (mode == OUTPUT) IO_OUT(P1, 1<<4); else IO_IN(P1, 1<<4); break;
		case D13: if (mode == OUTPUT) IO_OUT(P1, 1<<5); else IO_IN(P1, 1<<5); break;
		case D14: if (mode == OUTPUT) IO_OUT(P1, 1<<6); else IO_IN(P1, 1<<6); break;
		case D15: if (mode == OUTPUT) IO_OUT(P1, 1<<7); else IO_IN(P1, 1<<7); break;
		
		//D16..23 on P2
		case D16: if (mode == OUTPUT) IO_OUT(P2, 1<<0); else IO_IN(P2, 1<<0); break;
		case D17: if (mode == OUTPUT) IO_OUT(P2, 1<<1); else IO_IN(P2, 1<<1); break;
		case D18: if (mode == OUTPUT) IO_OUT(P2, 1<<2); else IO_IN(P2, 1<<2); break;
		case D19: if (mode == OUTPUT) IO_OUT(P2, 1<<3); else IO_IN(P2, 1<<3); break;
		case D20: if (mode == OUTPUT) IO_OUT(P2, 1<<4); else IO_IN(P2, 1<<4); break;
		case D21: if (mode == OUTPUT) IO_OUT(P2, 1<<5); else IO_IN(P2, 1<<5); break;
		case D22: if (mode == OUTPUT) IO_OUT(P2, 1<<6); else IO_IN(P2, 1<<6); break;
		case D23: if (mode == OUTPUT) IO_OUT(P2, 1<<7); else IO_IN(P2, 1<<7); break;
	}
}

//set pin high/low
void digitalWrite(PIN_T pin, uint8_t state) {
	switch (pin) {
		//D0..7 on P0
		case D0 : if (state == LOW) IO_CLR(P0, 1<<0); else IO_SET(P0, 1<<0); break;
		case D1 : if (state == LOW) IO_CLR(P0, 1<<1); else IO_SET(P0, 1<<1); break;
		case D2 : if (state == LOW) IO_CLR(P0, 1<<2); else IO_SET(P0, 1<<2); break;
		case D3 : if (state == LOW) IO_CLR(P0, 1<<3); else IO_SET(P0, 1<<3); break;
		case D4 : if (state == LOW) IO_CLR(P0, 1<<4); else IO_SET(P0, 1<<4); break;
		case D5 : if (state == LOW) IO_CLR(P0, 1<<5); else IO_SET(P0, 1<<5); break;
		case D6 : if (state == LOW) IO_CLR(P0, 1<<6); else IO_SET(P0, 1<<6); break;
		case D7 : if (state == LOW) IO_CLR(P0, 1<<7); else IO_SET(P0, 1<<7); break;

		//D8..15 on P1
		case D8 : if (state == LOW) IO_CLR(P1, 1<<0); else IO_SET(P1, 1<<0); break;
		case D9 : if (state == LOW) IO_CLR(P1, 1<<1); else IO_SET(P1, 1<<1); break;
		case D10: if (state == LOW) IO_CLR(P1, 1<<2); else IO_SET(P1, 1<<2); break;
		case D11: if (state == LOW) IO_CLR(P1, 1<<3); else IO_SET(P1, 1<<3); break;
		case D12: if (state == LOW) IO_CLR(P1, 1<<4); else IO_SET(P1, 1<<4); break;
		case D13: if (state == LOW) IO_CLR(P1, 1<<5); else IO_SET(P1, 1<<5); break;
		case D14: if (state == LOW) IO_CLR(P1, 1<<6); else IO_SET(P1, 1<<6); break;
		case D15: if (state == LOW) IO_CLR(P1, 1<<7); else IO_SET(P1, 1<<7); break;
		
		//D16..23 on P2
		case D16: if (state == LOW) IO_CLR(P2, 1<<0); else IO_SET(P2, 1<<0); break;
		case D17: if (state == LOW) IO_CLR(P2, 1<<1); else IO_SET(P2, 1<<1); break;
		case D18: if (state == LOW) IO_CLR(P2, 1<<2); else IO_SET(P2, 1<<2); break;
		case D19: if (state == LOW) IO_CLR(P2, 1<<3); else IO_SET(P2, 1<<3); break;
		case D20: if (state == LOW) IO_CLR(P2, 1<<4); else IO_SET(P2, 1<<4); break;
		case D21: if (state == LOW) IO_CLR(P2, 1<<5); else IO_SET(P2, 1<<5); break;
		case D22: if (state == LOW) IO_CLR(P2, 1<<6); else IO_SET(P2, 1<<6); break;
		case D23: if (state == LOW) IO_CLR(P2, 1<<7); else IO_SET(P2, 1<<7); break;
	}
}

//read pin state
int digitalRead(PIN_T pin) {
	switch (pin) {
		//D0..7 on P0
		case D0 : return IO_GET(P0, 1<<0)?HIGH:LOW; break;
		case D1 : return IO_GET(P0, 1<<1)?HIGH:LOW; break;
		case D2 : return IO_GET(P0, 1<<2)?HIGH:LOW; break;
		case D3 : return IO_GET(P0, 1<<3)?HIGH:LOW; break;
		case D4 : return IO_GET(P0, 1<<4)?HIGH:LOW; break;
		case D5 : return IO_GET(P0, 1<<5)?HIGH:LOW; break;
		case D6 : return IO_GET(P0, 1<<6)?HIGH:LOW; break;
		case D7 : return IO_GET(P0, 1<<7)?HIGH:LOW; break;

		//D8..15 on P1
		case D8 : return IO_GET(P1, 1<<0)?HIGH:LOW; break;
		case D9 : return IO_GET(P1, 1<<1)?HIGH:LOW; break;
		case D10: return IO_GET(P1, 1<<2)?HIGH:LOW; break;
		case D11: return IO_GET(P1, 1<<3)?HIGH:LOW; break;
		case D12: return IO_GET(P1, 1<<4)?HIGH:LOW; break;
		case D13: return IO_GET(P1, 1<<5)?HIGH:LOW; break;
		case D14: return IO_GET(P1, 1<<6)?HIGH:LOW; break;
		case D15: return IO_GET(P1, 1<<7)?HIGH:LOW; break;
		
		//D16..23 on P2
		case D16: return IO_GET(P2, 1<<0)?HIGH:LOW; break;
		case D17: return IO_GET(P2, 1<<1)?HIGH:LOW; break;
		case D18: return IO_GET(P2, 1<<2)?HIGH:LOW; break;
		case D19: return IO_GET(P2, 1<<3)?HIGH:LOW; break;
		case D20: return IO_GET(P2, 1<<4)?HIGH:LOW; break;
		case D21: return IO_GET(P2, 1<<5)?HIGH:LOW; break;
		case D22: return IO_GET(P2, 1<<6)?HIGH:LOW; break;
		case D23: return IO_GET(P2, 1<<7)?HIGH:LOW; break;
	}
	return -1;
}
