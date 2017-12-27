#include "xduino.h"						//use xduino generic defs
#include "board_stm32f030.h"				//we use board-specific defs

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

#if defined(RCC_AHBENR_GPIOEEN)
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

#if defined(RCC_AHBENR_GPIOFEN)			//GPIOF not present on all chips
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

#if defined(RCC_AHBENR_GPIOGEN)			//GPIOG not present on all chips
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
	RCC->AHBENR |=
			RCC_AHBENR_GPIOAEN |
			RCC_AHBENR_GPIOBEN |
			RCC_AHBENR_GPIOCEN |
			RCC_AHBENR_GPIODEN |
#if defined(RCC_AHBENR_GPIOEEN)
			RCC_AHBENR_GPIOEEN |
#endif
#if defined(RCC_AHBENR_GPIOFEN)
			RCC_AHBENR_GPIOFEN |
#endif
#if defined(RCC_AHBENR_GPIOGEN)
			RCC_AHBENR_GPIOGEN |
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
void GPIO_DDR(GPIO_TypeDef * GPIOx, uint32_t mask, uint32_t mode) {
	uint8_t pos;
	//uint32_t pin_mask;

	for (pos=0; pos < 16; pos++) {
		//looking for pin position / mask
		//pin_mask = 1ul << pos;
		if (mask & (1ul << pos)) {
			//we have found the pos / pin_mask
			if ((mode & GPIOMODE_OUTPUT) || (mode & GPIOMODE_AF)) {
				GPIOx->OSPEEDR &=~(0x03ul << (2 * pos));	//clear ospeeder
				GPIOx->OSPEEDR |= (0x01ul << (2 * pos));	//set to medium speed (0x01)

				GPIOx->OTYPER &=~(1ul << pos);				//clear otyper
				GPIOx->OTYPER |= ((mode & GPIOMODE_PP)?0ul:1ul) << pos;	//0->pp, 1->od
			}

			GPIOx->MODER &=~(0x03 << (2 * pos));			//clear moder
			GPIOx->MODER |= (mode & 0x03) << (2 * pos);		//set moder

			GPIOx->PUPDR &=~(0x03 << (2 * pos));			//clear pupdr
			GPIOx->PUPDR |= ((mode >> 4) & 0x03) << (2 * pos);	//set pupdr
		}
	}
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
		default:			IO_INFL(gpio, mask); break;
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
