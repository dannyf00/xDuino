#include "xduino.h"						//use xduino generic defs
#include "board_pic24fj64ga102.h"		//we use board-specific defs

//put board specific implementation here
//config bits here
#if 	defined(__PIC24FJ64GA102__) | defined (__PIC24FJ64GA104__) | \
		defined(__PIC24FJ32GA102__) | defined (__PIC24FJ32GA104__)

//config fues settings for 24fj64ga102
///config fues settings
//CONFIG1
#pragma config JTAGEN = OFF
#pragma config GCP = OFF
#pragma config GWRP = OFF
#pragma config ICS = PGx2
#pragma config FWDTEN = OFF
#pragma config WINDIS = OFF
#pragma config FWPSA = PR128
#pragma config WDTPS = PS32768

//CONFIG2
#pragma config IESO = OFF
#pragma config FNOSC = PRI
#pragma config FCKSM = CSDCMD
#pragma config OSCIOFNC = OFF
#pragma config IOL1WAY = OFF
#pragma config POSCMOD = HS
#pragma config I2C1SEL = PRI

//CONFIG3
#pragma config WPFP = WPFP0
#pragma config SOSCSEL = IO
#pragma config WUTSEL = LEG
#pragma config WPDIS = WPDIS
#pragma config WPCFG = WPCFGDIS
#pragma config WPEND = WPENDMEM

//CONFIG4
#pragma config DSWDTPS = DSWDTPSF
#pragma config DSWDTOSC = LPRC
#pragma config RTCOSC = LPRC
#pragma config DSBOREN = OFF
#pragma config DSWDTEN = OFF


/*
 DSWDT Postscale Select
DSWDTPS = DSWDTPS0	 1 : 2 (2.1 ms)
DSWDTPS = DSWDTPS1	 1 : 8 (8.3 ms)
DSWDTPS = DSWDTPS2	 1 : 32 (33 ms)
DSWDTPS = DSWDTPS3	 1 : 128 (132 ms)
DSWDTPS = DSWDTPS4	 1 : 512 (528 ms)
DSWDTPS = DSWDTPS5	 1 : 2,048 (2.1 seconds)
DSWDTPS = DSWDTPS6	 1 : 8,192 (8.5 seconds)
DSWDTPS = DSWDTPS7	 1 : 32,768 (34 seconds)
DSWDTPS = DSWDTPS8	 1 : 131,072 (135 seconds)
DSWDTPS = DSWDTPS9	 1 : 524,288 (9 minutes)
DSWDTPS = DSWDTPSA	 1 : 2,097,152 (36 minutes)
DSWDTPS = DSWDTPSB	 1 : 8,388,608 (2.4 hours)
DSWDTPS = DSWDTPSC	 1 : 33,554,432 (9.6 hours)
DSWDTPS = DSWDTPSD	 1 : 134,217,728 (38.5 hours)
DSWDTPS = DSWDTPSE	 1 : 536,870,912 (6.4 days)
DSWDTPS = DSWDTPSF	 1 : 2,147,483,648 (25.7 days)

Deep Sleep Watchdog Timer Oscillator Select
DSWDTOSC = SOSC	 DSWDT uses Secondary Oscillator (SOSC)
DSWDTOSC = LPRC	 DSWDT uses Low Power RC Oscillator (LPRC)

RTCC Reference Oscillator Select
RTCOSC = LPRC	 RTCC uses Low Power RC Oscillator (LPRC)
RTCOSC = SOSC	 RTCC uses Secondary Oscillator (SOSC)

Deep Sleep BOR Enable bit
DSBOREN = OFF	 BOR disabled in Deep Sleep
DSBOREN = ON	 BOR enabled in Deep Sleep

Deep Sleep Watchdog Timer
DSWDTEN = OFF	 DSWDT disabled
DSWDTEN = ON	 DSWDT enabled

Write Protection Flash Page Segment Boundary
WPFP = WPFP0	 Page 0 (0x0)
WPFP = WPFP1	 Page 1 (0x400)
WPFP = WPFP2	 Page 2 (0x800)
WPFP = WPFP3	 Page 3 (0xC00)
WPFP = WPFP4	 Page 4 (0x1000)
WPFP = WPFP5	 Page 5 (0x1400)
WPFP = WPFP6	 Page 6 (0x1800)
WPFP = WPFP7	 Page 7 (0x1C00)
WPFP = WPFP8	 Page 8 (0x2000)
WPFP = WPFP9	 Page 9 (0x2400)
WPFP = WPFP10	 Page 10 (0x2800)
WPFP = WPFP11	 Page 11 (0x2C00)
WPFP = WPFP12	 Page 12 (0x3000)
WPFP = WPFP13	 Page 13 (0x3400)
WPFP = WPFP14	 Page 14 (0x3800)
WPFP = WPFP15	 Page 15 (0x3C00)
WPFP = WPFP16	 Page 16 (0x4000)
WPFP = WPFP17	 Page 17 (0x4400)
WPFP = WPFP18	 Page 18 (0x4800)
WPFP = WPFP19	 Page 19 (0x4C00)
WPFP = WPFP20	 Page 20 (0x5000)
WPFP = WPFP21	 Page 21 (0x5400)
WPFP = WPFP22	 Page 22 (0x5800)
WPFP = WPFP23	 Page 23 (0x5C00)
WPFP = WPFP24	 Page 24 (0x6000)
WPFP = WPFP25	 Page 25 (0x6400)
WPFP = WPFP26	 Page 26 (0x6800)
WPFP = WPFP27	 Page 27 (0x6C00)
WPFP = WPFP28	 Page 28 (0x7000)
WPFP = WPFP29	 Page 29 (0x7400)
WPFP = WPFP30	 Page 30 (0x7800)
WPFP = WPFP31	 Page 31 (0x7C00)
WPFP = WPFP32	 Page 32 (0x8000)
WPFP = WPFP33	 Page 33 (0x8400)
WPFP = WPFP34	 Page 34 (0x8800)
WPFP = WPFP35	 Page 35 (0x8C00)
WPFP = WPFP36	 Page 36 (0x9000)
WPFP = WPFP37	 Page 37 (0x9400)
WPFP = WPFP38	 Page 38 (0x9800)
WPFP = WPFP39	 Page 39 (0x9C00)
WPFP = WPFP40	 Page 40 (0xA000)
WPFP = WPFP41	 Page 41 (0xA400)
WPFP = WPFP42	 Page 42 (0xA800)
WPFP = WPFP63	 Highest Page (same as page 42)

 * Secondary Oscillator Pin Mode Select
SOSCSEL = IO	 SOSC pins have digital I/O functions (RA4, RB4)
SOSCSEL = LPSOSC	 SOSC pins in Low-Power (low drive-strength) Oscillator Mode
SOSCSEL = SOSC	 SOSC pins in Default (high drive-strength) Oscillator Mode

Voltage Regulator Wake-up Time Select
WUTSEL = FST	 Fast regulator start-up time used
WUTSEL = LEG	 Default regulator start-up time used

Segment Write Protection Disable
WPDIS = WPEN	 Segmented code protection enabled
WPDIS = WPDIS	 Segmented code protection disabled

Write Protect Configuration Page Select
WPCFG = WPCFGEN	 Last page and Flash Configuration words are code-protected
WPCFG = WPCFGDIS	 Last page and Flash Configuration words are unprotected

Segment Write Protection End Page Select
WPEND = WPSTARTMEM	 Write Protect from page 0 to WPFP
WPEND = WPENDMEM	 Write Protect from WPFP to the last page of memory

Primary Oscillator Select
POSCMOD = EC	 EC Oscillator mode selected
POSCMOD = XT	 XT Oscillator mode selected
POSCMOD = HS	 HS Oscillator mode selected
POSCMOD = NONE	 Primary Oscillator disabled

I2C1 Pin Select bit
I2C1SEL = SEC	 Use alternate SCL1/SDA1 pins for I2C1
I2C1SEL = PRI	 Use default SCL1/SDA1 pins for I2C1

IOLOCK One-Way Set Enable
IOL1WAY = OFF	 The IOLOCK bit can be set and cleared using the unlock sequence
IOL1WAY = ON	 Once set, the IOLOCK bit cannot be cleared

 * OSCO Pin Configuration
OSCIOFNC = ON	 OSCO pin functions as port I/O (RA3)
OSCIOFNC = OFF	 OSCO pin functions as clock output (CLKO)

Clock Switching and Fail-Safe Clock Monitor
FCKSM = CSECME	 Sw Enabled, Mon Enabled
FCKSM = CSECMD	 Sw Enabled, Mon Disabled
FCKSM = CSDCMD	 Sw Disabled, Mon Disabled

Initial Oscillator Select
FNOSC = FRC	 Fast RC Oscillator (FRC)
FNOSC = FRCPLL	 Fast RC Oscillator with Postscaler and PLL module (FRCPLL)
FNOSC = PRI	 Primary Oscillator (XT, HS, EC)
FNOSC = PRIPLL	 Primary Oscillator with PLL module (XTPLL, HSPLL, ECPLL)
FNOSC = SOSC	 Secondary Oscillator (SOSC)
FNOSC = LPRC	 Low-Power RC Oscillator (LPRC)
FNOSC = FRCDIV	 Fast RC Oscillator with Postscaler (FRCDIV)

Internal External Switchover
IESO = OFF	 IESO mode (Two-Speed Start-up) disabled
IESO = ON	 IESO mode (Two-Speed Start-up) enabled

Watchdog Timer Postscaler
WDTPS = PS1	 1 : 1
WDTPS = PS2	 1 : 2
WDTPS = PS4	 1 : 4
WDTPS = PS8	 1 : 8
WDTPS = PS16	 1 : 16
WDTPS = PS32	 1 : 32
WDTPS = PS64	 1 : 64
WDTPS = PS128	 1 : 128
WDTPS = PS256	 1 : 256
WDTPS = PS512	 1 : 512
WDTPS = PS1024	 1 : 1,024
WDTPS = PS2048	 1 : 2,048
WDTPS = PS4096	 1 : 4,096
WDTPS = PS8192	 1 : 8,192
WDTPS = PS16384	 1 : 16,384
WDTPS = PS32768	 1 : 32,768

WDT Prescaler
FWPSA = PR32	 Prescaler ratio of 1 : 32
FWPSA = PR128	 Prescaler ratio of 1 : 128

Windowed WDT
WINDIS = ON	 Windowed Watchdog Timer enabled; FWDTEN must be 1
WINDIS = OFF	 Standard Watchdog Timer enabled,(Windowed-mode is disabled)

Watchdog Timer
FWDTEN = OFF	 Watchdog Timer is disabled
FWDTEN = ON	 Watchdog Timer is enabled

Emulator Pin Placement Select bits
ICS = PGx3	 Emulator functions are shared with PGEC3/PGED3
ICS = PGx2	 Emulator functions are shared with PGEC2/PGED2
ICS = PGx1	 Emulator functions are shared with PGEC1/PGED1

General Segment Write Protect
GWRP = ON	 Writes to program memory are disabled
GWRP = OFF	 Writes to program memory are allowed

General Segment Code Protect
GCP = ON	 Code protection is enabled for the entire program memory space
GCP = OFF	 Code protection is disabled

JTAG Port Enable
JTAGEN = OFF	 JTAG port is disabled
JTAGEN = ON	 JTAG port is enabled
 */
 
#elif 	defined(__PIC24FJ64GA002__) | defined (__PIC24FJ64GA004__) | \
		defined(__PIC24FJ48GA002__) | defined (__PIC24FJ48GA004__) | \
		defined(__PIC24FJ32GA002__) | defined (__PIC24FJ32GA004__) | \
		defined(__PIC24FJ16GA002__) | defined (__PIC24FJ16GA004__)

/*config fues settings for everything else - need customization*/
//CONFIG1
#pragma config JTAGEN = OFF
#pragma config GCP = OFF
#pragma config GWRP = OFF
#pragma config BKBUG = OFF
#pragma config COE = OFF
#pragma config ICS = PGx2
#pragma config FWDTEN = OFF
#pragma config WINDIS = OFF
#pragma config FWPSA = PR128
#pragma config WDTPS = PS32768

//CONFIG2
#pragma config IESO = OFF
#pragma config SOSCSEL = SOSC
#pragma config WUTSEL = LEG
#pragma config FCKSM = CSDCMD
#pragma config OSCIOFNC = OFF
#pragma config IOL1WAY = OFF
#pragma config I2C1SEL = PRI
#pragma config POSCMOD = HS
/*
 Primary Oscillator Select
POSCMOD = EC	 EC Oscillator mode selected
POSCMOD = XT	 XT Oscillator mode selected
POSCMOD = HS	 HS Oscillator mode selected
POSCMOD = NONE	 Primary oscillator disabled

I2C1 Pin Location Select
I2C1SEL = SEC	 Use alternate SCL1/SDA1 pins
I2C1SEL = PRI	 Use default SCL1/SDA1 pins

IOLOCK Protection
IOL1WAY = OFF	 IOLOCK may be changed via unlocking seq
IOL1WAY = ON	 Once IOLOCK is set, cannot be changed

Primary Oscillator Output Function
OSCIOFNC = ON	 OSC2/CLKO/RC15 functions as port I/O (RC15)
OSCIOFNC = OFF	 OSC2/CLKO/RC15 functions as CLKO (FOSC/2)

Clock Switching and Monitor
FCKSM = CSECME	 Clock switching is enabled, Fail-Safe Clock Monitor is enabled
FCKSM = CSECMD	 Clock switching is enabled, Fail-Safe Clock Monitor is disabled
FCKSM = CSDCMD	 Clock switching and Fail-Safe Clock Monitor are disabled

Oscillator Select
FNOSC = FRC	 Fast RC Oscillator (FRC)
FNOSC = FRCPLL	 Fast RC Oscillator with PLL module (FRCPLL)
FNOSC = PRI	 Primary Oscillator (XT, HS, EC)
FNOSC = PRIPLL	 Primary Oscillator with PLL module (HSPLL, ECPLL)
FNOSC = SOSC	 Secondary Oscillator (SOSC)
FNOSC = LPRC	 Low-Power RC Oscillator (LPRC)
FNOSC = FRCDIV	 Fast RC Oscillator with Postscaler (FRCDIV)

Sec Oscillator Select
SOSCSEL = LPSOSC	 Low Power Secondary Oscillator (LPSOSC)
SOSCSEL = SOSC	 Default Secondary Oscillator (SOSC)

Wake-up timer Select
WUTSEL = FST	 Fast Wake-up Timer
WUTSEL = LEG	 Legacy Wake-up Timer

Internal External Switch Over Mode
IESO = OFF	 IESO mode (Two-Speed Start-up) disabled
IESO = ON	 IESO mode (Two-Speed Start-up) enabled

Watchdog Timer Postscaler
WDTPS = PS1	 1 : 1
WDTPS = PS2	 1 : 2
WDTPS = PS4	 1 : 4
WDTPS = PS8	 1 : 8
WDTPS = PS16	 1 : 16
WDTPS = PS32	 1 : 32
WDTPS = PS64	 1 : 64
WDTPS = PS128	 1 : 128
WDTPS = PS256	 1 : 256
WDTPS = PS512	 1 : 512
WDTPS = PS1024	 1 : 1,024
WDTPS = PS2048	 1 : 2,048
WDTPS = PS4096	 1 : 4,096
WDTPS = PS8192	 1 : 8,192
WDTPS = PS16384	 1 : 16,384
WDTPS = PS32768	 1 : 32,768

WDT Prescaler
FWPSA = PR32	 Prescaler ratio of 1 : 32
FWPSA = PR128	 Prescaler ratio of 1 : 128

Watchdog Timer Window
WINDIS = OFF	 Windowed Watchdog Timer enabled; FWDTEN must be 1
WINDIS = ON	 Standard Watchdog Timer enabled,(Windowed-mode is disabled)

Watchdog Timer Enable
FWDTEN = OFF	 Watchdog Timer is disabled
FWDTEN = ON	 Watchdog Timer is enabled

Comm Channel Select
ICS = PGx3	 Emulator EMUC3/EMUD3 pins are shared with PGC3/PGD3
ICS = PGx2	 Emulator EMUC2/EMUD2 pins are shared with PGC2/PGD2
ICS = PGx1	 Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1

Set Clip On Emulation Mode
COE = ON	 Reset Into Clip On Emulation Mode
COE = OFF	 Reset Into Operational Mode

Background Debug
BKBUG = ON	 Device resets into Debug mode
BKBUG = OFF	 Device resets into Operational mode

General Code Segment Write Protect
GWRP = ON	 Writes to program memory are disabled
GWRP = OFF	 Writes to program memory are allowed

General Code Segment Code Protect
GCP = ON	 Code protection is enabled for the entire program memory space
GCP = OFF	 Code protection is disabled

JTAG Port Enable
JTAGEN = OFF	 JTAG port is disabled
JTAGEN = ON	 JTAG port is enabled
 */
#else
#warning "chip not yet supported!"
#endif

//global defines

//global variables
volatile uint32_t timer_ticks=0;		//timer ticks, 32-bit
//gpio pins
const PIN2GPIO GPIO_PinDef[]={
	//has to mamtch PIN_T def in boards.h
	//starting with D0
	//PA0..14
	{GPIOA, 1<<0},						//D0 = PA0
	{GPIOA, 1<<1},						//D1 = PA1
	{GPIOA, 1<<2},						//D2 = PA2
	{GPIOA, 1<<3},						//D3 = PA3
	{GPIOA, 1<<4},						//D4 = PA4
	{GPIOA, 1<<5},						//D5 = PA5
	{GPIOA, 1<<6},						//D6 = PA6
	{GPIOA, 1<<7},						//D7 = PA7
	{GPIOA, 1<<8},						//D8 = PA8
	{GPIOA, 1<<9},						//D9 = PA9
	{GPIOA, 1<<10},						//D10= PA10
	{GPIOA, 1<<11},						//D11= PA11
	{GPIOA, 1<<12},						//D12= PA12
	{GPIOA, 1<<13},						//D13= PA13
	{GPIOA, 1<<14},						//D14= PA14
	{GPIOA, 1<<15},						//D15= PA15

	//PB0..14
	{GPIOB, 1<<0},						//D16= PB0
	{GPIOB, 1<<1},						//D17= PB1
	{GPIOB, 1<<2},						//D18= PB2
	{GPIOB, 1<<3},						//D19= PB3
	{GPIOB, 1<<4},						//D20= PB4
	{GPIOB, 1<<5},						//D21= PB5
	{GPIOB, 1<<6},						//D22= PB6
	{GPIOB, 1<<7},						//D23= PB7
	{GPIOB, 1<<8},						//D24= PB8
	{GPIOB, 1<<9},						//D25= PB9
	{GPIOB, 1<<10},						//D26= PB10
	{GPIOB, 1<<11},						//D27= PB11
	{GPIOB, 1<<12},						//D28= PB12
	{GPIOB, 1<<13},						//D29= PB13
	{GPIOB, 1<<14},						//D30= PB14
	{GPIOB, 1<<15},						//D31= PB15
};

//timer0 overflow interrupt handler
void _ISR _T1Interrupt(void) {
	//clear the flag
	IFS0bits.T1IF = 0;
	timer_ticks+= 0x10000UL;			//increment timer ticks - 16BIT Timer1
}

//user must provide the following functions / macro defs
void mcu_init(void) {
	//turn off all peripherals
	PMD1=0xffff;
	PMD2=0xffff;
	PMD3=0xffff;
	PMD4=0xffff;

	//all pins digital
	AD1PCFG = 0xffff;					//all pins digital
	//or AD1PCFGH
	//AD1PCFGH = 0xffff;					//all pins digital
	//or AD1PCFGL
	//AD1PCFGL = 0xffff;					//all pins digital

	//initialize timer1, 1:1 prescaler, overflow interrupt enabled
	_T1MD = 0;							//enable power to tmr
	T1CONbits.TON = 0;					//turn off rtc1
	PR1=/*period*/-1;					//minimum rtc resolution is 1ms
	T1CONbits.TCS = 0;					//use internal clock = Fosc / 4
	T1CONbits.TCKPS = 1;				//0->prescaler to 1:1, 1->8:1
	T1CONbits.TGATE = 0;				//rtc1 gate disabled
	IFS0bits.T1IF = 0;					//reset the flag
	IEC0bits.T1IE=1;					//rtc1 interrupt on
	TMR1 = 0;							//reset the timer/counter
	T1CONbits.TON = 1;					//turn on rtc1
	//timer0 is running now
	//ei();								//enable interrupts globally - always enabled by default
}

//return ticks
uint32_t ticks(void) {
	uint32_t m;							//hold overflow count
	uint16_t f;							//hold timer counter - TIMER1 is 16-bit wide

	//perform a double read
	do {
		m = timer_ticks;
		f = TMR1;
	} while (m != timer_ticks);			//keep reading until m/f are atomic
	return m | f;						//form the ticks
}

//return time in microseconds
uint32_t micros(void) {
	//return ticks() / (F_CPU / 1000000ul) * 8;	//calculate micro seconds
	return ticks();								//8:1 prescaler @ 8Mhz F_CPU
}

//return time in milliseconds
uint32_t millis(void) {
	return micros() / 1000;
}

//set pin mode
void pinMode(PIN_T pin, uint8_t mode) {
	GPIO_TypeDef *gpio;
	uint16_t mask;

	if (pin>=DMAX) return;								//invalid pin -> do nothing
	gpio=GPIO_PinDef[pin].gpio;							//get gpio address
	mask=GPIO_PinDef[pin].mask;
	switch (mode) {
		case OUTPUT:		IO_OUT(gpio->TRIS, mask); break;
		case INPUT_PULLUP:	IO_IN(gpio->TRIS, mask); IO_SET(gpio->PORT, mask); break;
		case INPUT:
		default:			IO_IN(gpio->TRIS, mask); break;
	}
}

//set pin high/low
void digitalWrite(PIN_T pin, uint8_t state) {
	GPIO_TypeDef *gpio;
	uint16_t mask;

	if (pin>=DMAX) return;				//invalid pin
	gpio=GPIO_PinDef[pin].gpio;							//get gpio address
	mask=GPIO_PinDef[pin].mask;
	if (state == LOW) IO_CLR(gpio->LAT, mask); else IO_SET(gpio->LAT, mask);
	//if (state) IO_SET(gpio->LAT, mask); else IO_CLR(gpio->LAT, mask);
}

//read pin state
int digitalRead(PIN_T pin) {
	GPIO_TypeDef *gpio;
	uint16_t mask;

	if (pin>=DMAX) return -1;							//invalid pin
	gpio=GPIO_PinDef[pin].gpio;							//get gpio address
	mask=GPIO_PinDef[pin].mask;
	return IO_GET(gpio->PORT, mask)?HIGH:LOW;
}
