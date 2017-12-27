#include "xduino.h"						//use xduino generic defs
#include "board_stm32f100.h"				//we use board-specific defs

//put board specific implementation here

//global defines

//global variables
volatile uint32_t timer_ticks=0;		//timer ticks, 32-bit
//gpio pins
const PIN2GPIO GPIO_PinDef[]={
	//has to mamtch PIN_T def in boards.h
	//starting with D0
	//PA0..16
	{GPIOA, 0},						//D0 = PA0
	{GPIOA, 1},						//D1 = PA1
	{GPIOA, 2},						//D2 = PA2
	{GPIOA, 3},						//D3 = PA3
	{GPIOA, 4},						//D4 = PA4
	{GPIOA, 5},						//D5 = PA5
	{GPIOA, 6},						//D6 = PA6
	{GPIOA, 7},						//D7 = PA7
	{GPIOA, 8},						//D8 = PB0
	{GPIOA, 9},						//D9 = PB1
	{GPIOA,10},						//D10= PB2
	{GPIOA,11},						//D11= PB3
	{GPIOA,12},						//D12= PB4
	{GPIOA,13},						//D13= PB5
	{GPIOA,14},						//D14= PB6
	{GPIOA,15},						//D15= PB7

	//PB0..15
	{GPIOB, 0},						//D16= PC0
	{GPIOB, 1},						//D17= PC1
	{GPIOB, 2},						//D18= PC2
	{GPIOB, 3},						//D19= PC3
	{GPIOB, 4},						//D20= PC4
	{GPIOB, 5},						//D21= PC5
	{GPIOB, 6},						//D22= PC6
	{GPIOB, 7},						//D23= PC7
	{GPIOB, 8},						//D24= PD0
	{GPIOB, 9},						//D25= PD1
	{GPIOB,10},						//D26= PD2
	{GPIOB,11},						//D27= PD3
	{GPIOB,12},						//D28= PD4
	{GPIOB,13},						//D29= PD5
	{GPIOB,14},						//D30= PD6
	{GPIOB,15},						//D31= PD7

	//PC0..7
	{GPIOC, 0},						//D32= PE0
	{GPIOC, 1},						//D33= PE1
	{GPIOC, 2},						//D34= PE2
	{GPIOC, 3},						//D35= PE3
	{GPIOC, 4},						//D36= PE4
	{GPIOC, 5},						//D37= PE5
	{GPIOC, 6},						//D38= PE6
	{GPIOC, 7},						//D39= PE7
	{GPIOC, 8},						//D40= PE0
	{GPIOC, 9},						//D41= PE1
	{GPIOC,10},						//D42= PE2
	{GPIOC,11},						//D43= PE3
	{GPIOC,12},						//D44= PE4
	{GPIOC,13},						//D45= PE5
	{GPIOC,14},						//D46= PE6
	{GPIOC,15},						//D47= PE7

	//PD0..7
	{GPIOD, 0},						//D32= PE0
	{GPIOD, 1},						//D33= PE1
	{GPIOD, 2},						//D34= PE2
	{GPIOD, 3},						//D35= PE3
	{GPIOD, 4},						//D36= PE4
	{GPIOD, 5},						//D37= PE5
	{GPIOD, 6},						//D38= PE6
	{GPIOD, 7},						//D39= PE7
	{GPIOD, 8},						//D40= PE0
	{GPIOD, 9},						//D41= PE1
	{GPIOD,10},						//D42= PE2
	{GPIOD,11},						//D43= PE3
	{GPIOD,12},						//D44= PE4
	{GPIOD,13},						//D45= PE5
	{GPIOD,14},						//D46= PE6
	{GPIOD,15},						//D47= PE7

	//PE0..15
	{GPIOE,  0},						//ARMduino Pin 32 = PE0
	{GPIOE,  1},						//ARMduino Pin 33 = PE1
	{GPIOE,  2},						//ARMduino Pin 34 = PE2
	{GPIOE,  3},						//ARMduino Pin 35 = PE3
	{GPIOE,  4},						//ARMduino Pin 36 = PE4
	{GPIOE,  5},						//ARMduino Pin 37 = PE5
	{GPIOE,  6},						//ARMduino Pin 38 = PE6
	{GPIOE,  7},						//ARMduino Pin 39 = PE7
	{GPIOE,  8},						//ARMduino Pin 32 = PE8
	{GPIOE,  9},						//ARMduino Pin 33 = PE9
	{GPIOE, 10},						//ARMduino Pin 34 = PE10
	{GPIOE, 11},						//ARMduino Pin 35 = PE11
	{GPIOE, 12},						//ARMduino Pin 36 = PE12
	{GPIOE, 13},						//ARMduino Pin 37 = PE13
	{GPIOE, 14},						//ARMduino Pin 38 = PE14
	{GPIOE, 15},						//ARMduino Pin 39 = PE15

#if defined(RCC_APB2ENR_IOPFEN)			//GPIOF not present on all chips
	{GPIOF,  0},						//ARMduino Pin 40 = PF0
	{GPIOF,  1},						//ARMduino Pin 41 = PF1
	{GPIOF,  2},						//ARMduino Pin 42 = PF2
	{GPIOF,  3},						//ARMduino Pin 43 = PF3
	{GPIOF,  4},						//ARMduino Pin 44 = PF4
	{GPIOF,  5},						//ARMduino Pin 45 = PF5
	{GPIOF,  6},						//ARMduino Pin 46 = PF6
	{GPIOF,  7},						//ARMduino Pin 47 = PF7
	{GPIOF,  8},						//ARMduino Pin 40 = PF8
	{GPIOF,  9},						//ARMduino Pin 41 = PF9
	{GPIOF, 10},						//ARMduino Pin 42 = PF10
	{GPIOF, 11},						//ARMduino Pin 43 = PF11
	{GPIOF, 12},						//ARMduino Pin 44 = PF12
	{GPIOF, 13},						//ARMduino Pin 45 = PF13
	{GPIOF, 14},						//ARMduino Pin 46 = PF14
	{GPIOF, 15},						//ARMduino Pin 47 = PF15
#endif

#if defined(RCC_APB2ENR_IOPGEN)			//GPIOG not present on all chips
	{GPIOG,  0},						//ARMduino Pin 48 = PG0
	{GPIOG,  1},						//ARMduino Pin 49 = PG1
	{GPIOG,  2},						//ARMduino Pin 50 = PG2
	{GPIOG,  3},						//ARMduino Pin 51 = PG3
	{GPIOG,  4},						//ARMduino Pin 52 = PG4
	{GPIOG,  5},						//ARMduino Pin 53 = PG5
	{GPIOG,  6},						//ARMduino Pin 54 = PG6
	{GPIOG,  7},						//ARMduino Pin 55 = PG7
	{GPIOG,  8},						//ARMduino Pin 48 = PG8
	{GPIOG,  9},						//ARMduino Pin 49 = PG9
	{GPIOG, 10},						//ARMduino Pin 50 = PG10
	{GPIOG, 11},						//ARMduino Pin 51 = PG11
	{GPIOG, 12},						//ARMduino Pin 52 = PG12
	{GPIOG, 13},						//ARMduino Pin 53 = PG13
	{GPIOG, 14},						//ARMduino Pin 54 = PG14
	{GPIOG, 15},						//ARMduino Pin 55 = PG15
#endif
};

//systick handler - to provide time base for millis()/micros()
void SysTick_Handler(void) {
	//clear the flag - done automatically
	timer_ticks += 1ul<<24;						//increment systick counter - 24bit, 1:1 prescaler
}

//user must provide the following functions / macro defs
void mcu_init(void) {
	//manage the clock
	//configure Systick as the time base for millis()/micros()
	timer_ticks = 1ul<<24;											//SysTick is a 24-bit downcounter
	//for chips where SysTick_Config() is not defined in cmsis
	SysTick->LOAD  = 	(timer_ticks - 1)/*ticks*/ & SysTick_LOAD_RELOAD_Msk;      /* set reload register */
	NVIC_SetPriority 	(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Systick Interrupt */
	SysTick->VAL   = 	0;                                          /* Load the SysTick Counter Value */
	SysTick->CTRL  = 	SysTick_CTRL_CLKSOURCE_Msk |
						SysTick_CTRL_TICKINT_Msk   |
						SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
	//alternative - for CMSIS-equip'd chips
	//SysTick_Config(SysTick_LOAD_RELOAD_Msk);			//reload all 24 bits

	//enable interrupts
	interrupts();

	//chip initialization
	//chip_init();										//defined in chip-specific files

	//Update SystemCoreClock
	SystemCoreClockUpdate();

	//route clock to gpio
	//enable clock to GPIO
	RCC->APB2ENR |=
			RCC_APB2ENR_IOPAEN |
			RCC_APB2ENR_IOPBEN |
			RCC_APB2ENR_IOPCEN |
			RCC_APB2ENR_IOPDEN |
			RCC_APB2ENR_IOPEEN |
#if defined(RCC_APB2ENR_IOPFEN)
			RCC_APB2ENR_IOPFEN |
#endif
#if defined(RCC_APB2ENR_IOPGEN)
			RCC_APB2ENR_IOPGEN |
#endif
			0x00;
}

//return ticks
uint32_t ticks(void) {
	uint32_t m;							//hold overflow count
	uint32_t f;							//hold timer counter - Systick is 24-bit wide

	//perform a double read
	do {
		m = timer_ticks;
		f = SysTick->VAL;				//24-bit only
	} while (m != timer_ticks);			//keep reading until m/f are atomic
	return m - f;						//form the ticks
}

//return time in microseconds
uint32_t micros(void) {
	return ticks() / (F_CPU / 1000000ul) * 1;			//calculate micro seconds
	//return ticks() << 0;								//1:1 prescaler @ 16Mhz F_CPU
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
	mask=GPIO_PinDef[pin].pos;
	switch (mode) {
		case OUTPUT:		if (mask > 7) gpio->CRH = (gpio->CRH &~(0x0f << (4*(mask - 8)))) | ((0x00 | 0x03) << (4*(mask - 8))); else gpio->CRL = (gpio->CRL &~(0x0f << (4*mask))) | ((0x00 | 0x03) << (4*mask)); break;	//0x00->pushpull output, 0x03->output @ 50Mhz
		case INPUT_PULLUP:	if (mask > 7) gpio->CRH = (gpio->CRH &~(0x0f << (4*(mask - 8)))) | ((0x08 | 0x00) << (4*(mask - 8))); else gpio->CRL = (gpio->CRL &~(0x0f << (4*mask))) | ((0x08 | 0x00) << (4*mask)); gpio->ODR |= (1ul<<mask); break;	//0x08->input with PU/PD, 0x00->input
		case INPUT:
		default:			if (mask > 7) gpio->CRH = (gpio->CRH &~(0x0f << (mask - 8))) | ((0x04 | 0x00) << (mask - 8)); else gpio->CRL = (gpio->CRL &~(0x0f << mask)) | ((0x04 | 0x00) << mask); break;	//0x04->floating, 0x00->input
	}
}

//set pin high/low
void digitalWrite(PIN_T pin, uint8_t state) {
	GPIO_TypeDef *gpio;
	uint16_t mask;

	if (pin>=DMAX) return;				//invalid pin
	gpio=GPIO_PinDef[pin].gpio;							//get gpio address
	mask=GPIO_PinDef[pin].pos;
	if (state == LOW) IO_CLR(gpio, 1ul << mask); else IO_SET(gpio, 1ul << mask);
	//if (state) IO_SET(gpio, mask); else IO_CLR(gpio, mask);
}

//read pin state
int digitalRead(PIN_T pin) {
	GPIO_TypeDef *gpio;
	uint16_t mask;

	if (pin>=DMAX) return -1;							//invalid pin
	gpio=GPIO_PinDef[pin].gpio;							//get gpio address
	mask=GPIO_PinDef[pin].pos;
	return IO_GET(gpio, 1ul << mask)?HIGH:LOW;
}
