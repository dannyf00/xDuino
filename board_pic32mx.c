#include "xduino.h"						//use xduino generic defs
#include "board_pic32mx.h"				//we use board-specific defs

//put board specific implementation here
//config bits here
#include "config_xc32.h"				//config bits for PIC32MX chips

//global defines
#define _TxIP				IPC1bits.T1IP		//t1 interrupt priority
#define _TxIS				IPC1bits.T1IS		//t1 interrupt sub-priority
#define _TxIPL				IPL2				//default isr priority levels
#define TxIP_DEFAULT		2					//default interrupt priority - lowest
#define TxIS_DEFAULT		0					//default interrupt subpriority

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

//timer1 overflow interrupt handler
void __ISR(_TIMER_1_VECTOR/*, _TxIPL*/) _T1Interrupt(void) {
//void __ISR(_TIMER_1_VECTOR, IPL2SOFT) Timer1Handler(void) {
	IFS0bits.T1IF=0;					//clear tmr1 interrupt flag
	timer_ticks+= 0x10000UL;			//increment timer ticks - 16BIT Timer1
}

//user must provide the following functions / macro defs
void mcu_init(void) {
	/* Set the system and peripheral bus speeds and enable the program cache*/
	
	//SYSTEMConfigPerformance( F_CPU );
	
	//mOSCSetPBDIV( OSC_PB_DIV_2 );

	//clock defaults to FRC
	//set PBDIV to 1:1
	//unlock sequency
	SYSKEY = 0x0; 									// ensure OSCCON is locked
	SYSKEY = 0xAA996655; 							// Write Key1 to SYSKEY
	SYSKEY = 0x556699AA; 							// Write Key2 to SYSKEY
	// OSCCON is now unlocked
	// make the desired change
	OSCCON = (OSCCON &~0x00180000ul) | (0x00 & 0x00180000ul);	//or to set through config bits
	//lock sequency
	SYSKEY = 0x00;									//write any value to lock
	
	
	//turn off all peripherals
#if defined(PMD1)	
	PMD1=0xffff; 
#endif
#if defined(PMD2)
	PMD2=0xffff;
#endif
#if defined(PMD3)
	PMD3=0xffff;
#endif
#if defined(PMD4)
	PMD4=0xffff;
#endif
#if defined(PMD5)
	PMD5=0xffff;
#endif
#if defined(PMD6)
	PMD6=0xffff;
#endif

	//all pins digital
//#if defined(ANSELA)
    ANSELA = 0x0000;
//#endif
//#if defined(ANSELB)
    ANSELB = 0x0000;
//#endif
//#if defined(ANSELC)
    //ANSELC = 0x0000;
//#endif

//#if defined(AD1PCFG)
    //AD1PCFG = 0xffff;
//#endif

	//disable interrupts
	//__builtin_disable_interrupts();		//disable interrupts
	//INTDisableInterrupts();
	//enable multivector mode
	//INTCONbits.MVEC = 1;					//1=enable multiple vector
	//__builtin_enable_interrupts();		//enable interrupts
	//INTEnableInterrupts();					
	//INTEnableSystemMultiVectoredInt();
	INTCONbits.MVEC = 1;					//1=enable multi-vectored interrupts, 0=disable
	
	//enable global interrupts
	ei();									//testing


	//initialize timer1, 1:1 prescaler, overflow interrupt enabled
	//_T1MD = 0;								//enable power to tmr
	T1CONbits.TON = 0;							//turn off rtc1
	PR1=-1;										//minimum rtc resolution is 1ms
	T1CONbits.TCS = 0;							//use internal clock = Fosc
	//T1CON = (T1CON & 0xcf) | ((TMR1_PS_1x & 0x03) << 4);	//set the prescaler
	T1CONbits.TCKPS=0x00;						//0x00->set prescaler to 1:1
	//T1CONbits.T32 = 0;						//0->running in 16-bit mode
	T1CONbits.TGATE = 0;							//rtc1 gate disabled
	IFS0bits.T1IF = 0;							//reset the flag
	IEC0bits.T1IE = 0;							//rtc1 interrupt off
	//PEIE=1;									//peripheral interrupt on. no PEIE for PIC24 mcus
	TMR1 = 0;									//reset the timer/counter
	//TMR1L = 0;
	T1CONbits.TON = 1;							//turn on rtc1
	//timer1 is running now
	//ei();										//enable interrupts globally - always enabled by default
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
	return ticks() / (F_CPU / 1000000ul) * 1;	//calculate micro seconds
	//return ticks();								//1:1 prescaler @ 8Mhz F_CPU
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
		case OUTPUT:		IO_OUT(gpio, mask); break;
		case INPUT_PULLUP:	IO_IN(gpio, mask); IO_SET(gpio, mask); break;
		case INPUT:
		default:			IO_IN(gpio, mask); break;
	}
}

//set pin high/low
void digitalWrite(PIN_T pin, uint8_t state) {
	GPIO_TypeDef *gpio;
	uint16_t mask;

	if (pin>=DMAX) return;				//invalid pin
	gpio=GPIO_PinDef[pin].gpio;							//get gpio address
	mask=GPIO_PinDef[pin].mask;
	if (state == LOW) IO_CLR(gpio, mask); else IO_SET(gpio, mask);
	//if (state) IO_SET(gpio, mask); else IO_CLR(gpio, mask);
}

//read pin state
int digitalRead(PIN_T pin) {
	GPIO_TypeDef *gpio;
	uint16_t mask;

	if (pin>=DMAX) return -1;							//invalid pin
	gpio=GPIO_PinDef[pin].gpio;							//get gpio address
	mask=GPIO_PinDef[pin].mask;
	return IO_GET(gpio, mask)?HIGH:LOW;
}
