#include "xduino.h"						//use xduino generic defs
#include "board_msp430.h"				//we use board-specific defs

//put board specific implementation here

//global defines
//for easy portability
#define TAxCTL				TA2CTL			//timera control
#define TAxR				TA2R			//timer / counter
#define TAxIV				TA2IV			//interrupt flag
#if defined(TA2EX0)
#define TAxEX0				TA2EX0			//expansion register
#endif

#define TAxCCTL0			TA2CCTL0		//timer2 compare control
#define TAxCCTL1			TA2CCTL1		//timer2 c0mpare control
#define TAxCCTL2			TA2CCTL2		//timer2 compare control
#define TAxCCTL3			TA2CCTL3		//timer2 compare control
#define TAxCCTL4			TA2CCTL4		//timer2 c0mpare control
#define TAxCCTL5			TA2CCTL5		//timer2 compare control
#define TAxCCTL6			TA2CCTL6		//timer2 compare control
#define TAxCCR0				TA2CCR0			//timer2 compare register
#define TAxCCR1				TA2CCR1			//timer2 compare register
#define TAxCCR2				TA2CCR2			//timer2 compare register
#define TAxCCR3				TA2CCR3			//timer2 compare register
#define TAxCCR4				TA2CCR4			//timer2 compare register
#define TAxCCR5				TA2CCR5			//timer2 compare register
#define TAxCCR6				TA2CCR6			//timer2 compare register

//global variables
volatile uint32_t timer_ticks=0;		//timer ticks, 32-bit
//gpio pins
PIN2GPIO GPIO_PinDef[]={
	//starting with D0
#if defined(P1IN)
	//P10..7
	{(volatile uint8_t *)&P1OUT, (volatile uint8_t *)&P1IN, (volatile uint8_t *)&P1DIR, 1<<0},						//D0 = P10
	{(volatile uint8_t *)&P1OUT, (volatile uint8_t *)&P1IN, (volatile uint8_t *)&P1DIR, 1<<1},						//D1 = P11
	{(volatile uint8_t *)&P1OUT, (volatile uint8_t *)&P1IN, (volatile uint8_t *)&P1DIR, 1<<2},						//D2 = P12
	{(volatile uint8_t *)&P1OUT, (volatile uint8_t *)&P1IN, (volatile uint8_t *)&P1DIR, 1<<3},						//D3 = P13
	{(volatile uint8_t *)&P1OUT, (volatile uint8_t *)&P1IN, (volatile uint8_t *)&P1DIR, 1<<4},						//D4 = P14
	{(volatile uint8_t *)&P1OUT, (volatile uint8_t *)&P1IN, (volatile uint8_t *)&P1DIR, 1<<5},						//D5 = P15
	{(volatile uint8_t *)&P1OUT, (volatile uint8_t *)&P1IN, (volatile uint8_t *)&P1DIR, 1<<6},						//D6 = P16
	{(volatile uint8_t *)&P1OUT, (volatile uint8_t *)&P1IN, (volatile uint8_t *)&P1DIR, 1<<7},						//D7 = P17
#endif

#if defined(P2IN)
	//P20..7
	{(volatile uint8_t *)&P2OUT, (volatile uint8_t *)&P2IN, (volatile uint8_t *)&P2DIR, 1<<0},						//D0 = P20
	{(volatile uint8_t *)&P2OUT, (volatile uint8_t *)&P2IN, (volatile uint8_t *)&P2DIR, 1<<1},						//D1 = P21
	{(volatile uint8_t *)&P2OUT, (volatile uint8_t *)&P2IN, (volatile uint8_t *)&P2DIR, 1<<2},						//D2 = P22
	{(volatile uint8_t *)&P2OUT, (volatile uint8_t *)&P2IN, (volatile uint8_t *)&P2DIR, 1<<3},						//D3 = P23
	{(volatile uint8_t *)&P2OUT, (volatile uint8_t *)&P2IN, (volatile uint8_t *)&P2DIR, 1<<4},						//D4 = P24
	{(volatile uint8_t *)&P2OUT, (volatile uint8_t *)&P2IN, (volatile uint8_t *)&P2DIR, 1<<5},						//D5 = P25
	{(volatile uint8_t *)&P2OUT, (volatile uint8_t *)&P2IN, (volatile uint8_t *)&P2DIR, 1<<6},						//D6 = P26
	{(volatile uint8_t *)&P2OUT, (volatile uint8_t *)&P2IN, (volatile uint8_t *)&P2DIR, 1<<7},						//D7 = P27
#endif

#if defined(P3IN)
	//P30..7
	{(volatile uint8_t *)&P3OUT, (volatile uint8_t *)&P3IN, (volatile uint8_t *)&P3DIR, 1<<0},						//D0 = P30
	{(volatile uint8_t *)&P3OUT, (volatile uint8_t *)&P3IN, (volatile uint8_t *)&P3DIR, 1<<1},						//D1 = P31
	{(volatile uint8_t *)&P3OUT, (volatile uint8_t *)&P3IN, (volatile uint8_t *)&P3DIR, 1<<2},						//D2 = P32
	{(volatile uint8_t *)&P3OUT, (volatile uint8_t *)&P3IN, (volatile uint8_t *)&P3DIR, 1<<3},						//D3 = P33
	{(volatile uint8_t *)&P3OUT, (volatile uint8_t *)&P3IN, (volatile uint8_t *)&P3DIR, 1<<4},						//D4 = P34
	{(volatile uint8_t *)&P3OUT, (volatile uint8_t *)&P3IN, (volatile uint8_t *)&P3DIR, 1<<5},						//D5 = P35
	{(volatile uint8_t *)&P3OUT, (volatile uint8_t *)&P3IN, (volatile uint8_t *)&P3DIR, 1<<6},						//D6 = P36
	{(volatile uint8_t *)&P3OUT, (volatile uint8_t *)&P3IN, (volatile uint8_t *)&P3DIR, 1<<7},						//D7 = P37
#endif

#if defined(P4IN)
	//P40..7
	{(volatile uint8_t *)&P4OUT, (volatile uint8_t *)&P4IN, (volatile uint8_t *)&P4DIR, 1<<0},						//D0 = P40
	{(volatile uint8_t *)&P4OUT, (volatile uint8_t *)&P4IN, (volatile uint8_t *)&P4DIR, 1<<1},						//D1 = P41
	{(volatile uint8_t *)&P4OUT, (volatile uint8_t *)&P4IN, (volatile uint8_t *)&P4DIR, 1<<2},						//D2 = P42
	{(volatile uint8_t *)&P4OUT, (volatile uint8_t *)&P4IN, (volatile uint8_t *)&P4DIR, 1<<3},						//D3 = P43
	{(volatile uint8_t *)&P4OUT, (volatile uint8_t *)&P4IN, (volatile uint8_t *)&P4DIR, 1<<4},						//D4 = P44
	{(volatile uint8_t *)&P4OUT, (volatile uint8_t *)&P4IN, (volatile uint8_t *)&P4DIR, 1<<5},						//D5 = P45
	{(volatile uint8_t *)&P4OUT, (volatile uint8_t *)&P4IN, (volatile uint8_t *)&P4DIR, 1<<6},						//D6 = P46
	{(volatile uint8_t *)&P4OUT, (volatile uint8_t *)&P4IN, (volatile uint8_t *)&P4DIR, 1<<7},						//D7 = P47
#endif

#if defined(P5IN)
	//P50..7
	{(volatile uint8_t *)&P5OUT, (volatile uint8_t *)&P5IN, (volatile uint8_t *)&P5DIR, 1<<0},						//D0 = P50
	{(volatile uint8_t *)&P5OUT, (volatile uint8_t *)&P5IN, (volatile uint8_t *)&P5DIR, 1<<1},						//D1 = P51
	{(volatile uint8_t *)&P5OUT, (volatile uint8_t *)&P5IN, (volatile uint8_t *)&P5DIR, 1<<2},						//D2 = P52
	{(volatile uint8_t *)&P5OUT, (volatile uint8_t *)&P5IN, (volatile uint8_t *)&P5DIR, 1<<3},						//D3 = P53
	{(volatile uint8_t *)&P5OUT, (volatile uint8_t *)&P5IN, (volatile uint8_t *)&P5DIR, 1<<4},						//D4 = P54
	{(volatile uint8_t *)&P5OUT, (volatile uint8_t *)&P5IN, (volatile uint8_t *)&P5DIR, 1<<5},						//D5 = P55
	{(volatile uint8_t *)&P5OUT, (volatile uint8_t *)&P5IN, (volatile uint8_t *)&P5DIR, 1<<6},						//D6 = P56
	{(volatile uint8_t *)&P5OUT, (volatile uint8_t *)&P5IN, (volatile uint8_t *)&P5DIR, 1<<7},						//D7 = P57
#endif

#if defined(P6IN)
	//P60..7
	{(volatile uint8_t *)&P6OUT, (volatile uint8_t *)&P6IN, (volatile uint8_t *)&P6DIR, 1<<0},						//D0 = P60
	{(volatile uint8_t *)&P6OUT, (volatile uint8_t *)&P6IN, (volatile uint8_t *)&P6DIR, 1<<1},						//D1 = P61
	{(volatile uint8_t *)&P6OUT, (volatile uint8_t *)&P6IN, (volatile uint8_t *)&P6DIR, 1<<2},						//D2 = P62
	{(volatile uint8_t *)&P6OUT, (volatile uint8_t *)&P6IN, (volatile uint8_t *)&P6DIR, 1<<3},						//D3 = P63
	{(volatile uint8_t *)&P6OUT, (volatile uint8_t *)&P6IN, (volatile uint8_t *)&P6DIR, 1<<4},						//D4 = P64
	{(volatile uint8_t *)&P6OUT, (volatile uint8_t *)&P6IN, (volatile uint8_t *)&P6DIR, 1<<5},						//D5 = P65
	{(volatile uint8_t *)&P6OUT, (volatile uint8_t *)&P6IN, (volatile uint8_t *)&P6DIR, 1<<6},						//D6 = P66
	{(volatile uint8_t *)&P6OUT, (volatile uint8_t *)&P6IN, (volatile uint8_t *)&P6DIR, 1<<7},						//D7 = P67
#endif
	
#if defined(P7IN)
	//P70..7
	{(volatile uint8_t *)&P7OUT, (volatile uint8_t *)&P7IN, (volatile uint8_t *)&P7DIR, 1<<0},						//D0 = P70
	{(volatile uint8_t *)&P7OUT, (volatile uint8_t *)&P7IN, (volatile uint8_t *)&P7DIR, 1<<1},						//D1 = P71
	{(volatile uint8_t *)&P7OUT, (volatile uint8_t *)&P7IN, (volatile uint8_t *)&P7DIR, 1<<2},						//D2 = P72
	{(volatile uint8_t *)&P7OUT, (volatile uint8_t *)&P7IN, (volatile uint8_t *)&P7DIR, 1<<3},						//D3 = P73
	{(volatile uint8_t *)&P7OUT, (volatile uint8_t *)&P7IN, (volatile uint8_t *)&P7DIR, 1<<4},						//D4 = P74
	{(volatile uint8_t *)&P7OUT, (volatile uint8_t *)&P7IN, (volatile uint8_t *)&P7DIR, 1<<5},						//D5 = P75
	{(volatile uint8_t *)&P7OUT, (volatile uint8_t *)&P7IN, (volatile uint8_t *)&P7DIR, 1<<6},						//D6 = P76
	{(volatile uint8_t *)&P7OUT, (volatile uint8_t *)&P7IN, (volatile uint8_t *)&P7DIR, 1<<7},						//D7 = P77
#endif

#if defined(P8IN)
	//P80..7
	{(volatile uint8_t *)&P8OUT, (volatile uint8_t *)&P8IN, (volatile uint8_t *)&P8DIR, 1<<0},						//D0 = P80
	{(volatile uint8_t *)&P8OUT, (volatile uint8_t *)&P8IN, (volatile uint8_t *)&P8DIR, 1<<1},						//D1 = P81
	{(volatile uint8_t *)&P8OUT, (volatile uint8_t *)&P8IN, (volatile uint8_t *)&P8DIR, 1<<2},						//D2 = P82
	{(volatile uint8_t *)&P8OUT, (volatile uint8_t *)&P8IN, (volatile uint8_t *)&P8DIR, 1<<3},						//D3 = P83
	{(volatile uint8_t *)&P8OUT, (volatile uint8_t *)&P8IN, (volatile uint8_t *)&P8DIR, 1<<4},						//D4 = P84
	{(volatile uint8_t *)&P8OUT, (volatile uint8_t *)&P8IN, (volatile uint8_t *)&P8DIR, 1<<5},						//D5 = P85
	{(volatile uint8_t *)&P8OUT, (volatile uint8_t *)&P8IN, (volatile uint8_t *)&P8DIR, 1<<6},						//D6 = P86
	{(volatile uint8_t *)&P8OUT, (volatile uint8_t *)&P8IN, (volatile uint8_t *)&P8DIR, 1<<7},						//D7 = P87
#endif

#if defined(P9IN)
	//P90..7
	{(volatile uint8_t *)&P9OUT, (volatile uint8_t *)&P9IN, (volatile uint8_t *)&P9DIR, 1<<0},						//D0 = P90
	{(volatile uint8_t *)&P9OUT, (volatile uint8_t *)&P9IN, (volatile uint8_t *)&P9DIR, 1<<1},						//D1 = P91
	{(volatile uint8_t *)&P9OUT, (volatile uint8_t *)&P9IN, (volatile uint8_t *)&P9DIR, 1<<2},						//D2 = P92
	{(volatile uint8_t *)&P9OUT, (volatile uint8_t *)&P9IN, (volatile uint8_t *)&P9DIR, 1<<3},						//D3 = P93
	{(volatile uint8_t *)&P9OUT, (volatile uint8_t *)&P9IN, (volatile uint8_t *)&P9DIR, 1<<4},						//D4 = P94
	{(volatile uint8_t *)&P9OUT, (volatile uint8_t *)&P9IN, (volatile uint8_t *)&P9DIR, 1<<5},						//D5 = P95
	{(volatile uint8_t *)&P9OUT, (volatile uint8_t *)&P9IN, (volatile uint8_t *)&P9DIR, 1<<6},						//D6 = P96
	{(volatile uint8_t *)&P9OUT, (volatile uint8_t *)&P9IN, (volatile uint8_t *)&P9DIR, 1<<7},						//D7 = P97
#endif

#if defined(P10IN)
	//P100..7
	{(volatile uint8_t *)&P10OUT, (volatile uint8_t *)&P10IN, (volatile uint8_t *)&P10DIR, 1<<0},						//D0 = P100
	{(volatile uint8_t *)&P10OUT, (volatile uint8_t *)&P10IN, (volatile uint8_t *)&P10DIR, 1<<1},						//D1 = P101
	{(volatile uint8_t *)&P10OUT, (volatile uint8_t *)&P10IN, (volatile uint8_t *)&P10DIR, 1<<2},						//D2 = P102
	{(volatile uint8_t *)&P10OUT, (volatile uint8_t *)&P10IN, (volatile uint8_t *)&P10DIR, 1<<3},						//D3 = P103
	{(volatile uint8_t *)&P10OUT, (volatile uint8_t *)&P10IN, (volatile uint8_t *)&P10DIR, 1<<4},						//D4 = P104
	{(volatile uint8_t *)&P10OUT, (volatile uint8_t *)&P10IN, (volatile uint8_t *)&P10DIR, 1<<5},						//D5 = P105
	{(volatile uint8_t *)&P10OUT, (volatile uint8_t *)&P10IN, (volatile uint8_t *)&P10DIR, 1<<6},						//D6 = P106
	{(volatile uint8_t *)&P10OUT, (volatile uint8_t *)&P10IN, (volatile uint8_t *)&P10DIR, 1<<7},						//D7 = P107
#endif

};

// Timer A1 interrupt service routine, ccr1..4, ia
#pragma vector=TIMER2_A1_VECTOR
__interrupt void _ISRTimer2_A1 (void) {
	//TxCTL_bit.TAIFG=0;						//clear tmr1 interrupt flag
	///*_tmr1*/_isr_ptr1();					//execute user tmr1 isr
	switch (TAxIV) {
		//case 0x02: 	TAxCCR1+=_ccr1_pr; TAxCCTL1 &=~CCIFG; _isrptr_ccr1(); break;		//0x02 -> ccr1
		//case 0x04: 	TAxCCR2+=_ccr2_pr; TAxCCTL2 &=~CCIFG; _isrptr_ccr2(); break;		//0x04 -> ccr2
		//case 0x06: 	TAxCCR3+=_ccr3_pr; TAxCCTL3 &=~CCIFG; _isrptr_ccr3(); break;		//0x04 -> ccr2
		//case 0x08: 	TAxCCR4+=_ccr4_pr; TAxCCTL4 &=~CCIFG; _isrptr_ccr4(); break;		//0x04 -> ccr2
		//case 0x0a: 	TAxCCR5+=_ccr5_pr; TAxCCTL5 &=~CCIFG; _isrptr_ccr5(); break;		//0x04 -> ccr2
		//case 0x0c: 	TAxCCR6+=_ccr6_pr; TAxCCTL6 &=~CCIFG; _isrptr_ccr6(); break;		//0x04 -> ccr2
		//overflow interrupt
		case 0x0e:		TAxCTL &=~TAIFG; timer_ticks += 0x10000ul; break;		//0x04 -> ccr2
	default: break;
	}
}

//user must provide the following functions / macro defs
void mcu_init(void) {
  	// Stop watchdog timer to prevent time out reset
  	WDTCTL = WDTPW + WDTHOLD;
  	PM5CTL0 &=~LOCKLPM5;           				// Disable the GPIO power-on default high-impedance mode

   	//initialize the ports to GPIO
#if defined(P1IN)
   	P1SEL0 = P1SEL1 = 0x00;						//all pins digital
#endif
#if defined(P2IN)
   	P2SEL0 = P2SEL1 = 0x00;						//all pins digital
#endif
#if defined(P3IN)
   	P3SEL0 = P3SEL1 = 0x00;						//all pins digital
#endif
#if defined(P4IN)
   	P4SEL0 = P4SEL1 = 0x00;						//all pins digital
#endif
#if defined(P5IN)
   	P5SEL0 = P5SEL1 = 0x00;						//all pins digital
#endif
#if defined(P6IN)
   	P6SEL0 = P6SEL1 = 0x00;						//all pins digital
#endif
#if defined(P7IN)
   	P7SEL0 = P7SEL1 = 0x00;						//all pins digital
#endif
#if defined(P8IN)
   	P8SEL0 = P8SEL1 = 0x00;						//all pins digital
#endif
#if defined(P9IN)
   	P9SEL0 = P9SEL1 = 0x00;						//all pins digital
#endif

	//initialize timera2 (16-bit), 1:1 prescaler, overflow interrupt enabled
	//stop the timer
	//clear the timer control register
	TAxCTL |= TACLR;							//TxCTL_bit.TACLR;						//set to reset timer a

	//stop timer
	//TxCTL &=~MC_0;							//TxCTL_bit.TAMC = 0x00;				//timer mode - 0x00: halted, 0x01: up mode, 0x02: continuous mode (to 0xffff), 0x03: up/down
	//TxCTL |= TASSEL_2;						//TxCTL_bit.TASSEL = 0x02;				//timer source - 0x00: TACLK, 0x01: ACLK, 0x02: SMCLK, 0x03: INCLK
	//TxCTL |= (ps & ID_3);						//TxCTL_bit.TAID = ps & 0x03;			//input divider - 0x00: /1, 0x01: /2, 0x02: /4, 0x03: /8
	//TxCTL |= OUTMOD0;							//set output mode to zero
	TAxR = 0;									//reset the timer counter
	TAxCTL = 	TASSEL_2 |						//0=TACLK, 1=ACLK, 2=SMCLK, and 3=INCLK
				//ID__1 |							//prescaler: ID__1/2/4/8: 1/2/4/8x
				MC_2 |							//0=stop, 1=up to ccr0, 2=continous mode, 3=up and down
				0x00;							//TCIE disabled
#if defined(TAxEX0)
	TAxEX0 = 0x00;								//(ps & TMRA_EX8x);	//set expansion divider
#endif
	TAxCTL &=~TAIFG;								//TxCTL_bit.TAIFG = 0;					//interrupt flag: 0= no interrupt pending; 1=interrupt pending
	TAxCTL |= TAIE;								//TxCTL_bit.TAIE = 0;					//timer a interrupt enable: 0: interrupt disabled; 1: interrupt enabled;
	TAxCTL|= ID__1;								//prescaler: ID__1/2/4/8: 1/2/4/8x
	//timer0 is running now
	ei();										//enable interrupts globally
}

//return ticks
uint32_t ticks(void) {
	uint32_t m;							//hold overflow count
	uint16_t f;							//hold timer counter - TIMER0 is 16-bit wide

	//perform a double read
	do {
		m = timer_ticks;
		f = TAxR;
	} while (m != timer_ticks);			//keep reading until m/f are atomic
	return m | f;						//form the ticks
}

//return time in microseconds
uint32_t micros(void) {
	//return ticks() / (F_CPU / 1000000ul) * 4;		//calculate micro seconds
	return ticks();									//4:1 prescaler @ 4Mhz F_CPU
}

//return time in milliseconds
uint32_t millis(void) {
	return micros() / 1000;
}

//set pin mode
void pinMode(PIN_T pin, uint8_t mode) {
	volatile uint8_t *ddr, *port;
	uint8_t mask;

	if (pin>=DMAX) return;								//invalid pin -> do nothing
	ddr=GPIO_PinDef[pin].DDR;							//get gpio address
	port=GPIO_PinDef[pin].PORT;
	mask=GPIO_PinDef[pin].mask;
	switch (mode) {
		case OUTPUT:		IO_OUT(*ddr, mask); break;
		case INPUT_PULLUP:	IO_IN(*ddr, mask); IO_SET(*port, mask); break;	//not exactly
		case INPUT:
		default:			IO_IN(*ddr, mask); break;
	}
}

//set pin high/low
void digitalWrite(PIN_T pin, uint8_t state) {
	volatile uint8_t *port;
	uint8_t mask;

	if (pin>=DMAX) return;				//invalid pin
	port=GPIO_PinDef[pin].PORT;							//get gpio address
	mask=GPIO_PinDef[pin].mask;
	if (state == LOW) IO_CLR(*port, mask); else IO_SET(*port, mask);
	//if (state) IO_SET(*port, mask); else IO_CLR(*port, mask);
}

//read pin state
int digitalRead(PIN_T pin) {
	volatile uint8_t *port;
	uint8_t mask;

	if (pin>=DMAX) return -1;							//invalid pin
	port=GPIO_PinDef[pin].PIN;						//get gpio address
	mask=GPIO_PinDef[pin].mask;
	return IO_GET(*port, mask)?HIGH:LOW;
}
