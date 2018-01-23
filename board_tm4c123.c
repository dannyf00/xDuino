#include "xduino.h"						//use xduino generic defs
#include "board_tm4c123.h"				//we use board-specific defs

//put board specific implementation here

//global defines

//global variables
volatile uint32_t timer_ticks=0;		//timer ticks, 32-bit
//gpio pins
const PIN2GPIO GPIO_PinDef[]={
	//has to mamtch PIN_T def in boards.h
	//starting with D0
	//PB0..15
	{GPIOA, 1 << 0},						//D16= PC0
	{GPIOA, 1 << 1},						//D17= PC1
	{GPIOA, 1 << 2},						//D18= PC2
	{GPIOA, 1 << 3},						//D19= PC3
	{GPIOA, 1 << 4},						//D20= PC4
	{GPIOA, 1 << 5},						//D21= PC5
	{GPIOA, 1 << 6},						//D22= PC6
	{GPIOA, 1 << 7},						//D23= PC7

	//PC0..7
	{GPIOB, 1 << 0},						//D32= PE0
	{GPIOB, 1 << 1},						//D33= PE1
	{GPIOB, 1 << 2},						//D34= PE2
	{GPIOB, 1 << 3},						//D35= PE3
	{GPIOB, 1 << 4},						//D36= PE4
	{GPIOB, 1 << 5},						//D37= PE5
	{GPIOB, 1 << 6},						//D38= PE6
	{GPIOB, 1 << 7},						//D39= PE7

	//PD0..7
	{GPIOC, 1 << 0},						//D32= PE0
	{GPIOC, 1 << 1},						//D33= PE1
	{GPIOC, 1 << 2},						//D34= PE2
	{GPIOC, 1 << 3},						//D35= PE3
	{GPIOC, 1 << 4},						//D36= PE4
	{GPIOC, 1 << 5},						//D37= PE5
	{GPIOC, 1 << 6},						//D38= PE6
	{GPIOC, 1 << 7},						//D39= PE7

#if defined(GPIOD)
	//PE0..15
	{GPIOD, 1 <<  0},						//ARMduino Pin 32 = PE0
	{GPIOD, 1 <<  1},						//ARMduino Pin 33 = PE1
	{GPIOD, 1 <<  2},						//ARMduino Pin 34 = PE2
	{GPIOD, 1 <<  3},						//ARMduino Pin 35 = PE3
	{GPIOD, 1 <<  4},						//ARMduino Pin 36 = PE4
	{GPIOD, 1 <<  5},						//ARMduino Pin 37 = PE5
	{GPIOD, 1 <<  6},						//ARMduino Pin 38 = PE6
	{GPIOD, 1 <<  7},						//ARMduino Pin 39 = PE7
#endif

#if defined(GPIOE)			//GPIOE not present on all chips
	{GPIOE, 1 <<  0},						//ARMduino Pin 40 = PF0
	{GPIOE, 1 <<  1},						//ARMduino Pin 41 = PF1
	{GPIOE, 1 <<  2},						//ARMduino Pin 42 = PF2
	{GPIOE, 1 <<  3},						//ARMduino Pin 43 = PF3
	{GPIOE, 1 <<  4},						//ARMduino Pin 44 = PF4
	{GPIOE, 1 <<  5},						//ARMduino Pin 45 = PF5
	{GPIOE, 1 <<  6},						//ARMduino Pin 46 = PF6
	{GPIOE, 1 <<  7},						//ARMduino Pin 47 = PF7
#endif

#if defined(GPIOF)			//GPIOF not present on all chips
	{GPIOF, 1 <<  0},						//ARMduino Pin 48 = PG0
	{GPIOF, 1 <<  1},						//ARMduino Pin 49 = PG1
	{GPIOF, 1 <<  2},						//ARMduino Pin 50 = PG2
	{GPIOF, 1 <<  3},						//ARMduino Pin 51 = PG3
	{GPIOF, 1 <<  4},						//ARMduino Pin 52 = PG4
	{GPIOF, 1 <<  5},						//ARMduino Pin 53 = PG5
	{GPIOF, 1 <<  6},						//ARMduino Pin 54 = PG6
	{GPIOF, 1 <<  7},						//ARMduino Pin 55 = PG7
#endif

#if defined(GPIOG)			//GPIOG not present on all chips
	{GPIOG, 1 <<  0},						//ARMduino Pin 48 = PG0
	{GPIOG, 1 <<  1},						//ARMduino Pin 49 = PG1
	{GPIOG, 1 <<  2},						//ARMduino Pin 50 = PG2
	{GPIOG, 1 <<  3},						//ARMduino Pin 51 = PG3
	{GPIOG, 1 <<  4},						//ARMduino Pin 52 = PG4
	{GPIOG, 1 <<  5},						//ARMduino Pin 53 = PG5
	{GPIOG, 1 <<  6},						//ARMduino Pin 54 = PG6
	{GPIOG, 1 <<  7},						//ARMduino Pin 55 = PG7
#endif

#if defined(GPIOH)			//GPIOH not present on all chips
	{GPIOH, 1 <<  0},						//ARMduino Pin 48 = PG0
	{GPIOH, 1 <<  1},						//ARMduino Pin 49 = PG1
	{GPIOH, 1 <<  2},						//ARMduino Pin 50 = PG2
	{GPIOH, 1 <<  3},						//ARMduino Pin 51 = PG3
	{GPIOH, 1 <<  4},						//ARMduino Pin 52 = PG4
	{GPIOH, 1 <<  5},						//ARMduino Pin 53 = PG5
	{GPIOH, 1 <<  6},						//ARMduino Pin 54 = PG6
	{GPIOH, 1 <<  7},						//ARMduino Pin 55 = PG7
#endif

#if defined(GPIOI)			//GPIOI not present on all chips
	{GPIOI, 1 <<  0},						//ARMduino Pin 48 = PG0
	{GPIOI, 1 <<  1},						//ARMduino Pin 49 = PG1
	{GPIOI, 1 <<  2},						//ARMduino Pin 50 = PG2
	{GPIOI, 1 <<  3},						//ARMduino Pin 51 = PG3
	{GPIOI, 1 <<  4},						//ARMduino Pin 52 = PG4
	{GPIOI, 1 <<  5},						//ARMduino Pin 53 = PG5
	{GPIOI, 1 <<  6},						//ARMduino Pin 54 = PG6
	{GPIOI, 1 <<  7},						//ARMduino Pin 55 = PG7
#endif

#if defined(GPIOJ)			//GPIOJ not present on all chips
	{GPIOJ, 1 <<  0},						//ARMduino Pin 48 = PG0
	{GPIOJ, 1 <<  1},						//ARMduino Pin 49 = PG1
	{GPIOJ, 1 <<  2},						//ARMduino Pin 50 = PG2
	{GPIOJ, 1 <<  3},						//ARMduino Pin 51 = PG3
	{GPIOJ, 1 <<  4},						//ARMduino Pin 52 = PG4
	{GPIOJ, 1 <<  5},						//ARMduino Pin 53 = PG5
	{GPIOJ, 1 <<  6},						//ARMduino Pin 54 = PG6
	{GPIOJ, 1 <<  7},						//ARMduino Pin 55 = PG7
#endif
};

//systick handler - to provide time base for millis()/micros()
void SysTick_Handler(void) {
	//clear the flag - done automatically
	timer_ticks += 1ul<<24;						//increment systick counter - 24bit, 1:1 prescaler
}

//user must provide the following functions / macro defs
void mcu_init(void) {
	SystemInit();								//CMSIS reset - optional

	//for debugging purposes
	//delay_ms(1000);							//short delay - in case the jtag / swd pins are locked up
	//MAP_SysCtlDelay(F_CPU / 3);				//instead
	volatile int i = 1000000ul;
	while (i--) continue;						//waste sometime, per Luminary app note

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
	//enable clock to GPIOx
	SYSCTL->RCGCGPIO |= 0xffff;					//GPIOA..
	//check for status - not available on all chips
	//only test for gpioa..gpiof
	//while ((SYSCTL->PRGPIO & 0x3f) != 0x3f) continue;	//1->peripheral ready, 0->peripheral not ready

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
	mask=GPIO_PinDef[pin].mask;
	switch (mode) {
		case OUTPUT:		IO_OUT(gpio, mask); break;
		case INPUT_PULLUP:	IO_INPU(gpio, mask); break;
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
