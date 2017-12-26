#include "xduino.h"						//use xduino generic defs
#include "board_pic18fxxk20.h"			//we use board-specific defs

//put board specific implementation here
//config bits
//18fxxk20
#if	defined(_18F23K20) || defined(_18F24K20) || defined(_18F25K20) || defined(_18F26K20) || \
    defined(_18F43K20) || defined(_18F44K20) || defined(_18F45K20) || defined(_18F46K20) || \
	defined(_18LF23K20) || defined(_18LF24K20) || defined(_18LF25K20) || defined(_18LF26K20) || \
    defined(_18LF43K20) || defined(_18LF44K20) || defined(_18LF45K20) || defined(_18LF46K20)

#pragma config IESO = OFF
#pragma config FOSC = HS			//INTIO67
#pragma config FCMEN = OFF

/*
Register: CONFIG1H @ 0x300001

IESO =	Internal/External Oscillator Switchover bit
OFF	Oscillator Switchover mode disabled
ON	Oscillator Switchover mode enabled
FOSC =	Oscillator Selection bits
RCIO6	External RC oscillator, port function on RA6
RC	External RC oscillator, CLKOUT function on RA6
INTIO7	Internal oscillator block, CLKOUT function on RA6, port function on RA7
XT	XT oscillator
LP	LP oscillator
HSPLL	HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1)
ECIO6	EC oscillator, port function on RA6
EC	EC oscillator, CLKOUT function on RA6
INTIO67	Internal oscillator block, port function on RA6 and RA7
HS	HS oscillator
FCMEN =	Fail-Safe Clock Monitor Enable bit
OFF	Fail-Safe Clock Monitor disabled
ON	Fail-Safe Clock Monitor enabled
*/
#pragma config BOREN = OFF
#pragma config BORV = 18
#pragma config PWRT = ON
#pragma config WDTPS = 32768
#pragma config WDTEN = OFF
/*
Register: CONFIG2L @ 0x300002

BOREN =	Brown-out Reset Enable bits
NOSLP	Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled)
OFF	Brown-out Reset disabled in hardware and software
ON	Brown-out Reset enabled and controlled by software (SBOREN is enabled)
SBORDIS	Brown-out Reset enabled in hardware only (SBOREN is disabled)
BORV =	Brown Out Reset Voltage bits
18	VBOR set to 1.8 V nominal
27	VBOR set to 2.7 V nominal
22	VBOR set to 2.2 V nominal
30	VBOR set to 3.0 V nominal
PWRT =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
Register: CONFIG2H @ 0x300003

WDTPS =	Watchdog Timer Postscale Select bits
8	1:8
1	1:1
32768	1:32768
1024	1:1024
2	1:2
32	1:32
16	1:16
16384	1:16384
128	1:128
4096	1:4096
64	1:64
8192	1:8192
2048	1:2048
512	1:512
256	1:256
4	1:4
WDTEN =	Watchdog Timer Enable bit
OFF	WDT is controlled by SWDTEN bit of the WDTCON register
ON	WDT is always enabled. SWDTEN bit has no effect
*/
#pragma config CCP2MX = PORTC
#pragma config PBADEN = OFF
#pragma config LPT1OSC = OFF
#pragma config MCLRE = OFF
#pragma config HFOFST = OFF
/*
Register: CONFIG3H @ 0x300005

CCP2MX =	CCP2 MUX bit
PORTC	CCP2 input/output is multiplexed with RC1
PORTBE	CCP2 input/output is multiplexed with RB3
PBADEN =	PORTB A/D Enable bit
OFF	PORTB<4:0> pins are configured as digital I/O on Reset
ON	PORTB<4:0> pins are configured as analog input channels on Reset
LPT1OSC =	Low-Power Timer1 Oscillator Enable bit
OFF	Timer1 configured for higher power operation
ON	Timer1 configured for low-power operation
MCLRE =	MCLR Pin Enable bit
OFF	RE3 input pin enabled; MCLR disabled
ON	MCLR pin enabled; RE3 input pin disabled
HFOFST =	HFINTOSC Fast Start-up
OFF	The system clock is held off until the HFINTOSC is stable.
ON	HFINTOSC starts clocking the CPU without waiting for the oscillator to stablize.
*/
#pragma config DEBUG = OFF
#pragma config STVREN = OFF
#pragma config XINST = OFF
#pragma config LVP = OFF
/*
Register: CONFIG4L @ 0x300006

DEBUG =	Background Debugger Enable bit
OFF	Background debugger disabled, RB6 and RB7 configured as general purpose I/O pins
ON	Background debugger enabled, RB6 and RB7 are dedicated to In-Circuit Debug
STVREN =	Stack Full/Underflow Reset Enable bit
OFF	Stack full/underflow will not cause Reset
ON	Stack full/underflow will cause Reset
XINST =	Extended Instruction Set Enable bit
OFF	Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
ON	Instruction set extension and Indexed Addressing mode enabled
LVP =	Single-Supply ICSP Enable bit
OFF	Single-Supply ICSP disabled
ON	Single-Supply ICSP enabled
*/
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#if		defined(_18F25K20) || defined(_18F26K20) || defined(_18F45K20) || defined(_18F46K20) || \
		defined(_18LF25K20) || defined(_18LF26K20) || defined(_18LF45K20) || defined(_18LF46K20)
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#endif
#pragma config CPD = OFF
#pragma config CPB = OFF
/*
Register: CONFIG5L @ 0x300008

CP0 =	Code Protection Block 0
OFF	Block 0 (000800-003FFFh) not code-protected
ON	Block 0 (000800-003FFFh) code-protected
CP1 =	Code Protection Block 1
OFF	Block 1 (004000-007FFFh) not code-protected
ON	Block 1 (004000-007FFFh) code-protected
CP2 =	Code Protection Block 2
OFF	Block 2 (008000-00BFFFh) not code-protected
ON	Block 2 (008000-00BFFFh) code-protected
CP3 =	Code Protection Block 3
OFF	Block 3 (00C000-00FFFFh) not code-protected
ON	Block 3 (00C000-00FFFFh) code-protected
Register: CONFIG5H @ 0x300009

CPD =	Data EEPROM Code Protection bit
OFF	Data EEPROM not code-protected
ON	Data EEPROM code-protected
CPB =	Boot Block Code Protection bit
OFF	Boot block (000000-0007FFh) not code-protected
ON	Boot block (000000-0007FFh) code-protected
*/
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#if		defined(_18F25K20) || defined(_18F26K20) || defined(_18F45K20) || defined(_18F46K20) || \
		defined(_18LF25K20) || defined(_18LF26K20) || defined(_18LF45K20) || defined(_18LF46K20)
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#endif
#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTD = OFF
/*
Register: CONFIG6L @ 0x30000A

WRT0 =	Write Protection Block 0
OFF	Block 0 (000800-003FFFh) not write-protected
ON	Block 0 (000800-003FFFh) write-protected
WRT1 =	Write Protection Block 1
OFF	Block 1 (004000-007FFFh) not write-protected
ON	Block 1 (004000-007FFFh) write-protected
WRT2 =	Write Protection Block 2
OFF	Block 2 (008000-00BFFFh) not write-protected
ON	Block 2 (008000-00BFFFh) write-protected
WRT3 =	Write Protection Block 3
OFF	Block 3 (00C000h-00FFFFh) not write-protected
ON	Block 3 (00C000h-00FFFFh) write-protected
Register: CONFIG6H @ 0x30000B

WRTB =	Boot Block Write Protection bit
OFF	Boot Block (000000-0007FFh) not write-protected
ON	Boot Block (000000-0007FFh) write-protected
WRTC =	Configuration Register Write Protection bit
OFF	Configuration registers (300000-3000FFh) not write-protected
ON	Configuration registers (300000-3000FFh) write-protected
WRTD =	Data EEPROM Write Protection bit
OFF	Data EEPROM not write-protected
ON	Data EEPROM write-protected
*/
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#if		defined(_18F25K20) || defined(_18F26K20) || defined(_18F45K20) || defined(_18F46K20) || \
		defined(_18LF25K20) || defined(_18LF26K20) || defined(_18LF45K20) || defined(_18LF46K20)
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#endif
#pragma config EBTRB = OFF
/*
Register: CONFIG7L @ 0x30000C

EBTR0 =	Table Read Protection Block 0
OFF	Block 0 (000800-003FFFh) not protected from table reads executed in other blocks
ON	Block 0 (000800-003FFFh) protected from table reads executed in other blocks
EBTR1 =	Table Read Protection Block 1
OFF	Block 1 (004000-007FFFh) not protected from table reads executed in other blocks
ON	Block 1 (004000-007FFFh) protected from table reads executed in other blocks
EBTR2 =	Table Read Protection Block 2
OFF	Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks
ON	Block 2 (008000-00BFFFh) protected from table reads executed in other blocks
EBTR3 =	Table Read Protection Block 3
OFF	Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks
ON	Block 3 (00C000-00FFFFh) protected from table reads executed in other blocks
Register: CONFIG7H @ 0x30000D

EBTRB =	Boot Block Table Read Protection bit
OFF	Boot Block (000000-0007FFh) not protected from table reads executed in other blocks
ON	Boot Block (000000-0007FFh) protected from table reads executed in other blocks
*/

#else
#warning "wrong chip. not yet supported!"
#endif

//global defines

//global variables
volatile uint32_t timer_ticks=0;		//timer ticks, 32-bit
//gpio pins
const PIN2GPIO GPIO_PinDef[]={
	//starting with D0
	//PA0..7
	{&LATA, &PORTA, &TRISA, 1<<0},						//D0 = PA0
	{&LATA, &PORTA, &TRISA, 1<<1},						//D1 = PA1
	{&LATA, &PORTA, &TRISA, 1<<2},						//D2 = PA2
	{&LATA, &PORTA, &TRISA, 1<<3},						//D3 = PA3
	{&LATA, &PORTA, &TRISA, 1<<4},						//D4 = PA4
	{&LATA, &PORTA, &TRISA, 1<<5},						//D5 = PA5
	{&LATA, &PORTA, &TRISA, 1<<6},						//D6 = PA6
	{&LATA, &PORTA, &TRISA, 1<<7},						//D7 = PA7

	//PB0..7
	{&LATB, &PORTB, &TRISB, 1<<0},						//D8 = PB0
	{&LATB, &PORTB, &TRISB, 1<<1},						//D9 = PB1
	{&LATB, &PORTB, &TRISB, 1<<2},						//D10= PB2
	{&LATB, &PORTB, &TRISB, 1<<3},						//D11= PB3
	{&LATB, &PORTB, &TRISB, 1<<4},						//D12= PB4
	{&LATB, &PORTB, &TRISB, 1<<5},						//D13= PB5
	{&LATB, &PORTB, &TRISB, 1<<6},						//D14= PB6
	{&LATB, &PORTB, &TRISB, 1<<7},						//D15= PB7

	//PC0..7
	{&LATC, &PORTC, &TRISC, 1<<0},						//D16= PC0
	{&LATC, &PORTC, &TRISC, 1<<1},						//D17= PC1
	{&LATC, &PORTC, &TRISC, 1<<2},						//D18= PC2
	{&LATC, &PORTC, &TRISC, 1<<3},						//D19= PC3
	{&LATC, &PORTC, &TRISC, 1<<4},						//D20= PC4
	{&LATC, &PORTC, &TRISC, 1<<5},						//D21= PC5
	{&LATC, &PORTC, &TRISC, 1<<6},						//D22= PC6
	{&LATC, &PORTC, &TRISC, 1<<7},						//D23= PC7

#if	defined(_18F43K20) || defined(_18F44K20) || defined(_18F45K20) || defined(_18F46K20) || \
	defined(_18LF43K20) || defined(_18LF44K20) || defined(_18LF45K20) || defined(_18LF46K20)
	//PD0..7 - not available on 23/24/25/26k20
	{&LATD, &PORTD, &TRISD, 1<<0},						//D24= PD0
	{&LATD, &PORTD, &TRISD, 1<<1},						//D25= PD1
	{&LATD, &PORTD, &TRISD, 1<<2},						//D26= PD2
	{&LATD, &PORTD, &TRISD, 1<<3},						//D27= PD3
	{&LATD, &PORTD, &TRISD, 1<<4},						//D28= PD4
	{&LATD, &PORTD, &TRISD, 1<<5},						//D29= PD5
	{&LATD, &PORTD, &TRISD, 1<<6},						//D30= PD6
	{&LATD, &PORTD, &TRISD, 1<<7},						//D31= PD7
	
	//PE0..7
	{&LATE, &PORTE, &TRISE, 1<<0},						//D32= PE0
	{&LATE, &PORTE, &TRISE, 1<<1},						//D33= PE1
	{&LATE, &PORTE, &TRISE, 1<<2},						//D34= PE2
	{&LATE, &PORTE, &TRISE, 1<<3},						//D35= PE3
	{&LATE, &PORTE, &TRISE, 1<<4},						//D36= PE4
	{&LATE, &PORTE, &TRISE, 1<<5},						//D37= PE5
	{&LATE, &PORTE, &TRISE, 1<<6},						//D38= PE6
	{&LATE, &PORTE, &TRISE, 1<<7},						//D23= PE7
#endif
};

//timer0 overflow interrupt handler
void interrupt isr(void) {
	if (T0IF) {
		T0IF = 0;										//clear the flag
		timer_ticks+= 0x10000ul;						//increment timer ticks - TMR0 in 16-bit mode
	}	
}

//user must provide the following functions / macro defs
void mcu_init(void) {
	//initialize the ports to GPIO
	ANSEL = 0x00;						//all pins digital
	ANSELH= 0x00;
	CM1CON0 = 0x00;						//analog comparators off
	CM2CON0 = 0x00;
	IRCF2 = 1, IRCF1 = 1, IRCF0 = 1;	//0b111->16Mhz, 0b101->4Mhz, ircf2..0=0b011 -> 1Mhz

	//initialize timer0, 64:1 prescaler, overflow interrupt enabled
	//stop the timer
	TMR0ON = 0;
	T08BIT = 0;										//0->TMR0 runs in 16-bit mode, 1-8-bit mode
	T0CS = 0;										//count on F_OSC/4
	PSA = 0;										//0->prescaler assigned to tmr0
	T0PS2=0, T0PS1=0, T0PS0=1;						//0b000->prescaler = 1:1, 0b001->prescaler = 4:1, 0b101->prescaler = 64:1
	TMR0 = 0;										//reset the counter
	T0IF = 0;										//0->clear the flag
	T0IE = 1;										//1->enable the overflow interrupt, 0->disable the interrupt
	TMR0ON = 1;
	//timer0 is running now
	ei();											//enable interrupts globally
}

//return ticks
uint32_t ticks(void) {
	uint32_t m;							//hold overflow count
	uint16_t f;							//hold timer counter - TIMER0 is 16-bit wide

	//perform a double read
	do {
		m = timer_ticks;
		f = TMR0;
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
	port=GPIO_PinDef[pin].LAT;							//get gpio address
	mask=GPIO_PinDef[pin].mask;
	if (state == LOW) IO_CLR(*port, mask); else IO_SET(*port, mask);
	//if (state) IO_SET(*port, mask); else IO_CLR(*port, mask);
}

//read pin state
int digitalRead(PIN_T pin) {
	volatile uint8_t *port;
	uint8_t mask;

	if (pin>=DMAX) return -1;							//invalid pin
	port=GPIO_PinDef[pin].PORT;						//get gpio address
	mask=GPIO_PinDef[pin].mask;
	return IO_GET(*port, mask)?HIGH:LOW;
}
