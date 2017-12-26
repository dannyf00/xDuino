#include "xduino.h"						//use xduino generic defs
#include "board_atmega8.h"				//we use board-specific defs

//put board specific implementation here

//global defines

//global variables
volatile uint32_t timer_ticks=0;		//timer ticks, 32-bit
//gpio pins
const PIN2GPIO GPIO_PinDef[]={
	//has to mamtch PIN_T def in boards.h
	//starting with D0
	//PB0..7
	{GPIOB, 1<<0},						//D0 = PB0
	{GPIOB, 1<<1},						//D1 = PB1
	{GPIOB, 1<<2},						//D2 = PB2
	{GPIOB, 1<<3},						//D3 = PB3
	{GPIOB, 1<<4},						//D4 = PB4
	{GPIOB, 1<<5},						//D5 = PB5
	{GPIOB, 1<<6},						//D6 = PB6
	{GPIOB, 1<<7},						//D7 = PB7

	//PC0..7
	{GPIOC, 1<<0},						//D8 = PC0
	{GPIOC, 1<<1},						//D9 = PC1
	{GPIOC, 1<<2},						//D10= PC2
	{GPIOC, 1<<3},						//D11= PC3
	{GPIOC, 1<<4},						//D12= PC4
	{GPIOC, 1<<5},						//D13= PC5
	{GPIOC, 1<<6},						//D14= PC6
	{GPIOC, 1<<7},						//D15= PC7

	//PD0..7
	{GPIOD, 1<<0},						//D16= PD0
	{GPIOD, 1<<1},						//D17= PD1
	{GPIOD, 1<<2},						//D18= PD2
	{GPIOD, 1<<3},						//D19= PD3
	{GPIOD, 1<<4},						//D20= PD4
	{GPIOD, 1<<5},						//D21= PD5
	{GPIOD, 1<<6},						//D22= PD6
	{GPIOD, 1<<7},						//D23= PD7
};

//timer0 overflow interrupt handler
ISR(TIMER0_OVF_vect) {
	//clear the flag - done automatically
	timer_ticks+= 0x100;				//increment timer ticks
}

//user must provide the following functions / macro defs
void mcu_init(void) {
	//initialize timer0, 64:1 prescaler, overflow interrupt enabled
	//stop the timer
	TCCR0 = (TCCR0 &~0x07) | (0x07 & 0x00);		//0x00->stop the timer, 0x03 -> prescaler to 64x:1
	TCNT0 = 0;										//reset the counter
	TIFR |= (1<<TOV0);								//1->clear the flag
	TIMSK |= (1<<TOIE0);							//1->enable the overflow interrupt, 0->disable the interrupt
	TCCR0 = (TCCR0 &~0x07) | (0x07 & 0x03);		//0x00->stop the timer, 0x03 -> prescaler to 64x:1
	//timer0 is running now
	sei();											//enable interrupts globally
}

//return ticks
uint32_t ticks(void) {
	uint32_t m;							//hold overflow count
	uint8_t f;							//hold timer counter - TIMER0 is 8-bit wide

	//perform a double read
	do {
		m = timer_ticks;
		f = TCNT0;
	} while (m != timer_ticks);			//keep reading until m/f are atomic
	return m | f;						//form the ticks
}

//return time in microseconds
uint32_t micros(void) {
	//return ticks() / (F_CPU / 1000000ul) * 64;		//calculate micro seconds
	return ticks() << 2;								//64:1 prescaler @ 16Mhz F_CPU
}

//return time in milliseconds
uint32_t millis(void) {
	return micros() / 1000;
}

//set pin mode
void pinMode(PIN_T pin, uint8_t mode) {
	GPIO_TypeDef *gpio;
	uint8_t mask;

	if (pin>=DMAX) return;								//invalid pin -> do nothing
	gpio=GPIO_PinDef[pin].gpio;							//get gpio address
	mask=GPIO_PinDef[pin].mask;
	switch (mode) {
		case OUTPUT:		IO_OUT(gpio->DDR, mask); break;
		case INPUT_PULLUP:	IO_IN(gpio->DDR, mask); IO_SET(gpio->PORT, mask); break;
		case INPUT:
		default:			IO_IN(gpio->DDR, mask); break;
	}
}

//set pin high/low
void digitalWrite(PIN_T pin, uint8_t state) {
	GPIO_TypeDef *gpio;
	uint8_t mask;

	if (pin>=DMAX) return;				//invalid pin
	gpio=GPIO_PinDef[pin].gpio;							//get gpio address
	mask=GPIO_PinDef[pin].mask;
	if (state == LOW) IO_CLR(gpio->PORT, mask); else IO_SET(gpio->PORT, mask);
	//if (state) IO_SET(gpio->PORT, mask); else IO_CLR(gpio->PORT, mask);
}

//read pin state
int digitalRead(PIN_T pin) {
	GPIO_TypeDef *gpio;
	uint8_t mask;

	if (pin>=DMAX) return -1;							//invalid pin
	gpio=GPIO_PinDef[pin].gpio;							//get gpio address
	mask=GPIO_PinDef[pin].mask;
	return IO_GET(gpio->PIN, mask)?HIGH:LOW;
}
