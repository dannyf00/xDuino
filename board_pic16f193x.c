#include "xduino.h"						//use xduino generic defs
#include "board_pic16f193x.h"			//we use board-specific defs

//put board specific implementation here
//config bits
//16F1936 for 9.65pro - 16Mhz crystal, or INTOSC
#if 	defined(_16F1933) || defined(_16LF1933) || \
 	defined(_16F1934) || defined(_16LF1934) || \
 	defined(_16F1936) || defined(_16LF1936) || \
 	defined(_16F1937) || defined(_16LF1937) || \
 	defined(_16F1938) || defined(_16LF1938) || \
 	defined(_16F1939) || defined(_16LF1939)

#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FOSC = HS			//INTOSC, HS, XT, LP, ECH/ECM/ECL
#pragma config FCMEN = OFF
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config PWRTE = ON
#pragma config CLKOUTEN = OFF

#pragma config PLLEN = OFF, WRT = OFF, STVREN = OFF, BORV = LO, LVP = OFF

#if 	defined(_16F1936) || defined(_16LF1936) //vcapen applies to 1936 only
#pragma config VCAPEN = OFF
#endif

/*
Register: CONFIG1 @ 0x8007

CPD =	Data Memory Code Protection
OFF	Data memory code protection is disabled
ON	Data memory code protection is enabled
BOREN =	Brown-out Reset Enable
OFF	Brown-out Reset disabled
ON	Brown-out Reset enabled
NSLEEP	Brown-out Reset enabled while running and disabled in Sleep
SBODEN	Brown-out Reset controlled by the SBOREN bit in the BORCON register
IESO =	Internal/External Switchover
OFF	Internal/External Switchover mode is disabled
ON	Internal/External Switchover mode is enabled
FOSC =	Oscillator Selection
ECM	ECM, External Clock, Medium Power Mode (0.5-4 MHz): device clock supplied to CLKIN pin
XT	XT Oscillator, Crystal/resonator connected between OSC1 and OSC2 pins
LP	LP Oscillator, Low-power crystal connected between OSC1 and OSC2 pins
EXTRC	EXTRC oscillator: External RC circuit connected to CLKIN pin
ECH	ECH, External Clock, High Power Mode (4-32 MHz): device clock supplied to CLKIN pin
ECL	ECL, External Clock, Low Power Mode (0-0.5 MHz): device clock supplied to CLKIN pin
INTOSC	INTOSC oscillator: I/O function on CLKIN pin
HS	HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins
FCMEN =	Fail-Safe Clock Monitor Enable
OFF	Fail-Safe Clock Monitor is disabled
ON	Fail-Safe Clock Monitor is enabled
MCLRE =	MCLR Pin Function Select
OFF	MCLR/VPP pin function is digital input
ON	MCLR/VPP pin function is MCLR
WDTE =	Watchdog Timer Enable
OFF	WDT disabled
ON	WDT enabled
NSLEEP	WDT enabled while running and disabled in Sleep
SWDTEN	WDT controlled by the SWDTEN bit in the WDTCON register
CP =	Flash Program Memory Code Protection
OFF	Program memory code protection is disabled
ON	Program memory code protection is enabled
PWRTE =	Power-up Timer Enable
OFF	PWRT disabled
ON	PWRT enabled
CLKOUTEN =	Clock Out Enable
OFF	CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin
ON	CLKOUT function is enabled on the CLKOUT pin
*/


/*
Register: CONFIG2 @ 0x8008

PLLEN =	PLL Enable
OFF	4x PLL disabled
ON	4x PLL enabled
WRT =	Flash Memory Self-Write Protection
OFF	Write protection off
BOOT	000h to 1FFh write protected, 200h to 1FFFh may be modified by EECON control
HALF	000h to FFFh write protected, 1000h to 1FFFh may be modified by EECON control
ALL	000h to 1FFFh write protected, no addresses may be modified by EECON control
STVREN =	Stack Overflow/Underflow Reset Enable
OFF	Stack Overflow or Underflow will not cause a Reset
ON	Stack Overflow or Underflow will cause a Reset
BORV =	Brown-out Reset Voltage Selection
LO	Brown-out Reset Voltage (Vbor), low trip point selected.
HI	Brown-out Reset Voltage (Vbor), high trip point selected.
VCAPEN =	Voltage Regulator Capacitor Enable
RA5	VCAP functionality is enabled on RA5
OFF	All VCAP pin functionality is disabled
RA6	VCAP functionality is enabled on RA6
RA0	VCAP functionality is enabled on RA0
LVP =	Low-Voltage Programming Enable
OFF	High-voltage on MCLR/VPP must be used for programming
ON	Low-voltage programming enabled
*/

//16f1937 for 9.65pro
#elif defined(_16F1937) || defined(_16LF1937)

#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FOSC = INTOSC
#pragma config FCMEN = OFF
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config PWRTE = ON
#pragma config CLKOUTEN = OFF
/*
CPD =	Data Memory Code Protection
OFF	Data memory code protection is disabled
ON	Data memory code protection is enabled
BOREN =	Brown-out Reset Enable
OFF	Brown-out Reset disabled
ON	Brown-out Reset enabled
NSLEEP	Brown-out Reset enabled while running and disabled in Sleep
SBODEN	Brown-out Reset controlled by the SBOREN bit in the BORCON register
IESO =	Internal/External Switchover
OFF	Internal/External Switchover mode is disabled
ON	Internal/External Switchover mode is enabled
FOSC =	Oscillator Selection
ECM	ECM, External Clock, Medium Power Mode (0.5-4 MHz): device clock supplied to CLKIN pin
XT	XT Oscillator, Crystal/resonator connected between OSC1 and OSC2 pins
LP	LP Oscillator, Low-power crystal connected between OSC1 and OSC2 pins
EXTRC	EXTRC oscillator: External RC circuit connected to CLKIN pin
ECH	ECH, External Clock, High Power Mode (4-32 MHz): device clock supplied to CLKIN pin
ECL	ECL, External Clock, Low Power Mode (0-0.5 MHz): device clock supplied to CLKIN pin
INTOSC	INTOSC oscillator: I/O function on CLKIN pin
HS	HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins
FCMEN =	Fail-Safe Clock Monitor Enable
OFF	Fail-Safe Clock Monitor is disabled
ON	Fail-Safe Clock Monitor is enabled
MCLRE =	MCLR Pin Function Select
OFF	MCLR/VPP pin function is digital input
ON	MCLR/VPP pin function is MCLR
WDTE =	Watchdog Timer Enable
OFF	WDT disabled
ON	WDT enabled
NSLEEP	WDT enabled while running and disabled in Sleep
SWDTEN	WDT controlled by the SWDTEN bit in the WDTCON register
CP =	Flash Program Memory Code Protection
OFF	Program memory code protection is disabled
ON	Program memory code protection is enabled
PWRTE =	Power-up Timer Enable
OFF	PWRT disabled
ON	PWRT enabled
CLKOUTEN =	Clock Out Enable
OFF	CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin
ON	CLKOUT function is enabled on the CLKOUT pin
*/
#pragma config PLLEN = OFF, WRT = OFF, STVREN = OFF, BORV = LO, VCAPEN = OFF, LVP = OFF

/*
Register: CONFIG2 @ 0x8008

PLLEN =	PLL Enable
OFF	4x PLL disabled
ON	4x PLL enabled
WRT =	Flash Memory Self-Write Protection
OFF	Write protection off
BOOT	000h to 1FFh write protected, 200h to 1FFFh may be modified by EECON control
HALF	000h to FFFh write protected, 1000h to 1FFFh may be modified by EECON control
ALL	000h to 1FFFh write protected, no addresses may be modified by EECON control
STVREN =	Stack Overflow/Underflow Reset Enable
OFF	Stack Overflow or Underflow will not cause a Reset
ON	Stack Overflow or Underflow will cause a Reset
BORV =	Brown-out Reset Voltage Selection
LO	Brown-out Reset Voltage (Vbor), low trip point selected.
HI	Brown-out Reset Voltage (Vbor), high trip point selected.
VCAPEN =	Voltage Regulator Capacitor Enable
RA5	VCAP functionality is enabled on RA5
OFF	All VCAP pin functionality is disabled
RA6	VCAP functionality is enabled on RA6
RA0	VCAP functionality is enabled on RA0
LVP =	Low-Voltage Programming Enable
OFF	High-voltage on MCLR/VPP must be used for programming
ON	Low-voltage programming enabled
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
	{&PORTA, &TRISA, 1<<0},						//D0 = PA0
	{&PORTA, &TRISA, 1<<1},						//D1 = PA1
	{&PORTA, &TRISA, 1<<2},						//D2 = PA2
	{&PORTA, &TRISA, 1<<3},						//D3 = PA3
	{&PORTA, &TRISA, 1<<4},						//D4 = PA4
	{&PORTA, &TRISA, 1<<5},						//D5 = PA5
	{&PORTA, &TRISA, 1<<6},						//D6 = PA6
	{&PORTA, &TRISA, 1<<7},						//D7 = PA7

	//PB0..7
	{&PORTB, &TRISB, 1<<0},						//D8 = PB0
	{&PORTB, &TRISB, 1<<1},						//D9 = PB1
	{&PORTB, &TRISB, 1<<2},						//D10= PB2
	{&PORTB, &TRISB, 1<<3},						//D11= PB3
	{&PORTB, &TRISB, 1<<4},						//D12= PB4
	{&PORTB, &TRISB, 1<<5},						//D13= PB5
	{&PORTB, &TRISB, 1<<6},						//D14= PB6
	{&PORTB, &TRISB, 1<<7},						//D15= PB7

	//PC0..7
	{&PORTC, &TRISC, 1<<0},						//D16= PC0
	{&PORTC, &TRISC, 1<<1},						//D17= PC1
	{&PORTC, &TRISC, 1<<2},						//D18= PC2
	{&PORTC, &TRISC, 1<<3},						//D19= PC3
	{&PORTC, &TRISC, 1<<4},						//D20= PC4
	{&PORTC, &TRISC, 1<<5},						//D21= PC5
	{&PORTC, &TRISC, 1<<6},						//D22= PC6
	{&PORTC, &TRISC, 1<<7},						//D23= PC7
};

//timer0 overflow interrupt handler
void interrupt isr(void) {
	if (T0IF) {
		T0IF = 0;									//clear the flag
		timer_ticks+= 0x100;						//increment timer ticks
	}	
}

//user must provide the following functions / macro defs
void mcu_init(void) {
	//initialize the ports to GPIO
	ANSELA = 0x00;						//all pins gpio
	ANSELB = 0x00;
	CM1CON0 = 0x00;						//turn off analog comparators
	CM2CON0 = 0x00;
	APFCON = 0x00;                      //choose default functions

	//initialize the rc oscillator
	IRCF3=1, IRCF2=1, IRCF1=1, IRCF0=1;	//0b1111->16Mhz, 0b1110->8Mhz, 0b1101->4Mhz

	//initialize timer0, 64:1 prescaler, overflow interrupt enabled
	//stop the timer - cannot be done on this chip
	T0CS = 0;										//count on F_OSC/4
	PSA = 0;										//0->prescaler assigned to tmr0
	PS2=1, PS1=0, PS0=1;							//0b101->prescaler = 64:1
	TMR0 = 0;										//reset the counter
	T0IF = 0;										//0->clear the flag
	T0IE = 1;										//1->enable the overflow interrupt, 0->disable the interrupt
	//timer0 is running now
	ei();											//enable interrupts globally
}

//return ticks
uint32_t ticks(void) {
	uint32_t m;							//hold overflow count
	uint8_t f;							//hold timer counter - TIMER0 is 8-bit wide

	//perform a double read
	do {
		m = timer_ticks;
		f = TMR0;
	} while (m != timer_ticks);			//keep reading until m/f are atomic
	return m | f;						//form the ticks
}

//return time in microseconds
uint32_t micros(void) {
	//return ticks() / (F_CPU / 1000000ul) * 64;		//calculate micro seconds
	return ticks() << 4;								//64:1 prescaler @ 4Mhz F_CPU
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
	port=GPIO_PinDef[pin].PORT;						//get gpio address
	mask=GPIO_PinDef[pin].mask;
	return IO_GET(*port, mask)?HIGH:LOW;
}
