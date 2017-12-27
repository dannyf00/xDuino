#include "xduino.h"						//use xduino generic defs
#include "board_stm32f103.h"				//we use board-specific defs

//put board specific implementation here

//global defines

//global variables
volatile uint32_t timer_ticks=0;		//timer ticks, 32-bit
//gpio pins
const PIN2GPIO GPIO_PinDef[]={
	//has to mamtch PIN_T def in boards.h
	//starting with D0
	//PA0..16
	{GPIOA, 1 << 0},						//D0 = PA0
	{GPIOA, 1 << 1},						//D1 = PA1
	{GPIOA, 1 << 2},						//D2 = PA2
	{GPIOA, 1 << 3},						//D3 = PA3
	{GPIOA, 1 << 4},						//D4 = PA4
	{GPIOA, 1 << 5},						//D5 = PA5
	{GPIOA, 1 << 6},						//D6 = PA6
	{GPIOA, 1 << 7},						//D7 = PA7
	{GPIOA, 1 << 8},						//D8 = PB0
	{GPIOA, 1 << 9},						//D9 = PB1
	{GPIOA, 1 <<10},						//D10= PB2
	{GPIOA, 1 <<11},						//D11= PB3
	{GPIOA, 1 <<12},						//D12= PB4
	{GPIOA, 1 <<13},						//D13= PB5
	{GPIOA, 1 <<14},						//D14= PB6
	{GPIOA, 1 <<15},						//D15= PB7

	//PB0..15
	{GPIOB, 1 << 0},						//D16= PC0
	{GPIOB, 1 << 1},						//D17= PC1
	{GPIOB, 1 << 2},						//D18= PC2
	{GPIOB, 1 << 3},						//D19= PC3
	{GPIOB, 1 << 4},						//D20= PC4
	{GPIOB, 1 << 5},						//D21= PC5
	{GPIOB, 1 << 6},						//D22= PC6
	{GPIOB, 1 << 7},						//D23= PC7
	{GPIOB, 1 << 8},						//D24= PD0
	{GPIOB, 1 << 9},						//D25= PD1
	{GPIOB, 1 <<10},						//D26= PD2
	{GPIOB, 1 <<11},						//D27= PD3
	{GPIOB, 1 <<12},						//D28= PD4
	{GPIOB, 1 <<13},						//D29= PD5
	{GPIOB, 1 <<14},						//D30= PD6
	{GPIOB, 1 <<15},						//D31= PD7

	//PC0..7
	{GPIOC, 1 << 0},						//D32= PE0
	{GPIOC, 1 << 1},						//D33= PE1
	{GPIOC, 1 << 2},						//D34= PE2
	{GPIOC, 1 << 3},						//D35= PE3
	{GPIOC, 1 << 4},						//D36= PE4
	{GPIOC, 1 << 5},						//D37= PE5
	{GPIOC, 1 << 6},						//D38= PE6
	{GPIOC, 1 << 7},						//D39= PE7
	{GPIOC, 1 << 8},						//D40= PE0
	{GPIOC, 1 << 9},						//D41= PE1
	{GPIOC, 1 <<10},						//D42= PE2
	{GPIOC, 1 <<11},						//D43= PE3
	{GPIOC, 1 <<12},						//D44= PE4
	{GPIOC, 1 <<13},						//D45= PE5
	{GPIOC, 1 <<14},						//D46= PE6
	{GPIOC, 1 <<15},						//D47= PE7

	//PD0..7
	{GPIOD, 1 << 0},						//D32= PE0
	{GPIOD, 1 << 1},						//D33= PE1
	{GPIOD, 1 << 2},						//D34= PE2
	{GPIOD, 1 << 3},						//D35= PE3
	{GPIOD, 1 << 4},						//D36= PE4
	{GPIOD, 1 << 5},						//D37= PE5
	{GPIOD, 1 << 6},						//D38= PE6
	{GPIOD, 1 << 7},						//D39= PE7
	{GPIOD, 1 << 8},						//D40= PE0
	{GPIOD, 1 << 9},						//D41= PE1
	{GPIOD, 1 <<10},						//D42= PE2
	{GPIOD, 1 <<11},						//D43= PE3
	{GPIOD, 1 <<12},						//D44= PE4
	{GPIOD, 1 <<13},						//D45= PE5
	{GPIOD, 1 <<14},						//D46= PE6
	{GPIOD, 1 <<15},						//D47= PE7

#if defined(RCC_APB2ENR_IOPEEN)
	//PE0..15
	{GPIOE, 1 <<  0},						//ARMduino Pin 32 = PE0
	{GPIOE, 1 <<  1},						//ARMduino Pin 33 = PE1
	{GPIOE, 1 <<  2},						//ARMduino Pin 34 = PE2
	{GPIOE, 1 <<  3},						//ARMduino Pin 35 = PE3
	{GPIOE, 1 <<  4},						//ARMduino Pin 36 = PE4
	{GPIOE, 1 <<  5},						//ARMduino Pin 37 = PE5
	{GPIOE, 1 <<  6},						//ARMduino Pin 38 = PE6
	{GPIOE, 1 <<  7},						//ARMduino Pin 39 = PE7
	{GPIOE, 1 <<  8},						//ARMduino Pin 32 = PE8
	{GPIOE, 1 <<  9},						//ARMduino Pin 33 = PE9
	{GPIOE, 1 << 10},						//ARMduino Pin 34 = PE10
	{GPIOE, 1 << 11},						//ARMduino Pin 35 = PE11
	{GPIOE, 1 << 12},						//ARMduino Pin 36 = PE12
	{GPIOE, 1 << 13},						//ARMduino Pin 37 = PE13
	{GPIOE, 1 << 14},						//ARMduino Pin 38 = PE14
	{GPIOE, 1 << 15},						//ARMduino Pin 39 = PE15
#endif

#if defined(RCC_APB2ENR_IOPFEN)			//GPIOF not present on all chips
	{GPIOF, 1 <<  0},						//ARMduino Pin 40 = PF0
	{GPIOF, 1 <<  1},						//ARMduino Pin 41 = PF1
	{GPIOF, 1 <<  2},						//ARMduino Pin 42 = PF2
	{GPIOF, 1 <<  3},						//ARMduino Pin 43 = PF3
	{GPIOF, 1 <<  4},						//ARMduino Pin 44 = PF4
	{GPIOF, 1 <<  5},						//ARMduino Pin 45 = PF5
	{GPIOF, 1 <<  6},						//ARMduino Pin 46 = PF6
	{GPIOF, 1 <<  7},						//ARMduino Pin 47 = PF7
	{GPIOF, 1 <<  8},						//ARMduino Pin 40 = PF8
	{GPIOF, 1 <<  9},						//ARMduino Pin 41 = PF9
	{GPIOF, 1 << 10},						//ARMduino Pin 42 = PF10
	{GPIOF, 1 << 11},						//ARMduino Pin 43 = PF11
	{GPIOF, 1 << 12},						//ARMduino Pin 44 = PF12
	{GPIOF, 1 << 13},						//ARMduino Pin 45 = PF13
	{GPIOF, 1 << 14},						//ARMduino Pin 46 = PF14
	{GPIOF, 1 << 15},						//ARMduino Pin 47 = PF15
#endif

#if defined(RCC_APB2ENR_IOPGEN)			//GPIOG not present on all chips
	{GPIOG, 1 <<  0},						//ARMduino Pin 48 = PG0
	{GPIOG, 1 <<  1},						//ARMduino Pin 49 = PG1
	{GPIOG, 1 <<  2},						//ARMduino Pin 50 = PG2
	{GPIOG, 1 <<  3},						//ARMduino Pin 51 = PG3
	{GPIOG, 1 <<  4},						//ARMduino Pin 52 = PG4
	{GPIOG, 1 <<  5},						//ARMduino Pin 53 = PG5
	{GPIOG, 1 <<  6},						//ARMduino Pin 54 = PG6
	{GPIOG, 1 <<  7},						//ARMduino Pin 55 = PG7
	{GPIOG, 1 <<  8},						//ARMduino Pin 48 = PG8
	{GPIOG, 1 <<  9},						//ARMduino Pin 49 = PG9
	{GPIOG, 1 << 10},						//ARMduino Pin 50 = PG10
	{GPIOG, 1 << 11},						//ARMduino Pin 51 = PG11
	{GPIOG, 1 << 12},						//ARMduino Pin 52 = PG12
	{GPIOG, 1 << 13},						//ARMduino Pin 53 = PG13
	{GPIOG, 1 << 14},						//ARMduino Pin 54 = PG14
	{GPIOG, 1 << 15},						//ARMduino Pin 55 = PG15
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
#if defined(RCC_APB2ENR_IOPEEN)
			RCC_APB2ENR_IOPEEN |
#endif
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

//configure gpio DDR mode (cnf1..0 + mod1..0 bits)
void GPIO_DDR(GPIO_TypeDef * gpio, uint32_t mask, uint32_t mode) {
	mode = mode & 0x0f;				//lowest 4 bits effective

	//for the lowest 8 bits
	if (mask & (1ul<< 0)) gpio->CRL = (gpio->CRL &~0x0000000ful) | (mode << (0 * 4));
	if (mask & (1ul<< 1)) gpio->CRL = (gpio->CRL &~0x000000f0ul) | (mode << (1 * 4));
	if (mask & (1ul<< 2)) gpio->CRL = (gpio->CRL &~0x00000f00ul) | (mode << (2 * 4));
	if (mask & (1ul<< 3)) gpio->CRL = (gpio->CRL &~0x0000f000ul) | (mode << (3 * 4));
	if (mask & (1ul<< 4)) gpio->CRL = (gpio->CRL &~0x000f0000ul) | (mode << (4 * 4));
	if (mask & (1ul<< 5)) gpio->CRL = (gpio->CRL &~0x00f00000ul) | (mode << (5 * 4));
	if (mask & (1ul<< 6)) gpio->CRL = (gpio->CRL &~0x0f000000ul) | (mode << (6 * 4));
	if (mask & (1ul<< 7)) gpio->CRL = (gpio->CRL &~0xf0000000ul) | (mode << (7 * 4));

	//for the highest 8 bits
	if (mask & (1ul<< 8)) gpio->CRH = (gpio->CRH &~0x0000000ful) | (mode << (0 * 4));
	if (mask & (1ul<< 9)) gpio->CRH = (gpio->CRH &~0x000000f0ul) | (mode << (1 * 4));
	if (mask & (1ul<<10)) gpio->CRH = (gpio->CRH &~0x00000f00ul) | (mode << (2 * 4));
	if (mask & (1ul<<11)) gpio->CRH = (gpio->CRH &~0x0000f000ul) | (mode << (3 * 4));
	if (mask & (1ul<<12)) gpio->CRH = (gpio->CRH &~0x000f0000ul) | (mode << (4 * 4));
	if (mask & (1ul<<13)) gpio->CRH = (gpio->CRH &~0x00f00000ul) | (mode << (5 * 4));
	if (mask & (1ul<<14)) gpio->CRH = (gpio->CRH &~0x0f000000ul) | (mode << (6 * 4));
	if (mask & (1ul<<15)) gpio->CRH = (gpio->CRH &~0xf0000000ul) | (mode << (7 * 4));

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
		case INPUT_PULLUP:	IO_INPU(gpio, mask); break;
		case INPUT:
		default:			IO_INFL(gpio, mask);
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
