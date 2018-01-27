#include "xduino.h"						//use xduino generic defs
#include "board_lpc17xx.h"				//we use board-specific defs

//put board specific implementation here

//global defines

//global variables
volatile uint32_t timer_ticks=0;		//timer ticks, 32-bit
//gpio pins
const PIN2GPIO GPIO_PinDef[]={
	//has to mamtch PIN_T def in boards.h
	//starting with D0
#if defined(LPC_GPIO0)
	//P10..31
	{GPIO0, 1 << 0},						//D0 = PA0
	{GPIO0, 1 << 1},						//D1 = PA1
	{GPIO0, 1 << 2},						//D2 = PA2
	{GPIO0, 1 << 3},						//D3 = PA3
	{GPIO0, 1 << 4},						//D4 = PA4
	{GPIO0, 1 << 5},						//D5 = PA5
	{GPIO0, 1 << 6},						//D6 = PA6
	{GPIO0, 1 << 7},						//D7 = PA7
	{GPIO0, 1 << 8},						//D8 = PB0
	{GPIO0, 1 << 9},						//D9 = PB1
	{GPIO0, 1 <<10},						//D10= PB2
	{GPIO0, 1 <<11},						//D11= PB3
	{GPIO0, 1 <<12},						//D12= PB4
	{GPIO0, 1 <<13},						//D13= PB5
	{GPIO0, 1 <<14},						//D14= PB6
	{GPIO0, 1 <<15},						//D15= PB7
	{GPIO0, 1 <<16},						//D16= PC0
	{GPIO0, 1 <<16},						//D17= PC1
	{GPIO0, 1 <<18},						//D18= PC2
	{GPIO0, 1 <<19},						//D19= PC3
	{GPIO0, 1 <<20},						//D20= PC4
	{GPIO0, 1 <<21},						//D21= PC5
	{GPIO0, 1 <<22},						//D22= PC6
	{GPIO0, 1 <<23},						//D23= PC7
	{GPIO0, 1 <<24},						//D24= PD0
	{GPIO0, 1 <<25},						//D25= PD1
	{GPIO0, 1 <<26},						//D26= PD2
	{GPIO0, 1 <<27},						//D27= PD3
	{GPIO0, 1 <<28},						//D28= PD4
	{GPIO0, 1 <<29},						//D29= PD5
	{GPIO0, 1 <<30},						//D30= PD6
	{GPIO0, 1 <<31},						//D31= PD7
#endif
#if defined(LPC_GPIO2)
	//P10..31
	{GPIO1, 1 << 0},						//D32= PE0
	{GPIO1, 1 << 1},						//D33= PE1
	{GPIO1, 1 << 2},						//D34= PE2
	{GPIO1, 1 << 3},						//D35= PE3
	{GPIO1, 1 << 4},						//D36= PE4
	{GPIO1, 1 << 5},						//D37= PE5
	{GPIO1, 1 << 6},						//D38= PE6
	{GPIO1, 1 << 7},						//D39= PE7
	{GPIO1, 1 << 8},						//D40= PE0
	{GPIO1, 1 << 9},						//D41= PE1
	{GPIO1, 1 <<10},						//D42= PE2
	{GPIO1, 1 <<11},						//D43= PE3
	{GPIO1, 1 <<12},						//D44= PE4
	{GPIO1, 1 <<13},						//D45= PE5
	{GPIO1, 1 <<14},						//D46= PE6
	{GPIO1, 1 <<15},						//D47= PE7
	{GPIO1, 1 <<16},						//D32= PE0
	{GPIO1, 1 <<17},						//D33= PE1
	{GPIO1, 1 <<18},						//D34= PE2
	{GPIO1, 1 <<19},						//D35= PE3
	{GPIO1, 1 <<20},						//D36= PE4
	{GPIO1, 1 <<21},						//D37= PE5
	{GPIO1, 1 <<22},						//D38= PE6
	{GPIO1, 1 <<23},						//D39= PE7
	{GPIO1, 1 <<24},						//D40= PE0
	{GPIO1, 1 <<25},						//D41= PE1
	{GPIO1, 1 <<26},						//D42= PE2
	{GPIO1, 1 <<27},						//D43= PE3
	{GPIO1, 1 <<28},						//D44= PE4
	{GPIO1, 1 <<29},						//D45= PE5
	{GPIO1, 1 <<30},						//D46= PE6
	{GPIO1, 1 <<31},						//D47= PE7
#endif
#if defined(LPC_GPIO2)
	//P20..31
	{GPIO2, 1 << 0},						//ARMduino Pin 32 = PE0
	{GPIO2, 1 << 1},						//ARMduino Pin 33 = PE1
	{GPIO2, 1 << 2},						//ARMduino Pin 34 = PE2
	{GPIO2, 1 << 3},						//ARMduino Pin 35 = PE3
	{GPIO2, 1 << 4},						//ARMduino Pin 36 = PE4
	{GPIO2, 1 << 5},						//ARMduino Pin 37 = PE5
	{GPIO2, 1 << 6},						//ARMduino Pin 38 = PE6
	{GPIO2, 1 << 7},						//ARMduino Pin 39 = PE7
	{GPIO2, 1 << 8},						//ARMduino Pin 32 = PE8
	{GPIO2, 1 << 9},						//ARMduino Pin 33 = PE9
	{GPIO2, 1 <<10},						//ARMduino Pin 34 = PE10
	{GPIO2, 1 <<11},						//ARMduino Pin 35 = PE11
	{GPIO2, 1 <<12},						//ARMduino Pin 36 = PE12
	{GPIO2, 1 <<13},						//ARMduino Pin 37 = PE13
	{GPIO2, 1 <<14},						//ARMduino Pin 38 = PE14
	{GPIO2, 1 <<15},						//ARMduino Pin 39 = PE15
	{GPIO2, 1 <<16},						//D32= PE0
	{GPIO2, 1 <<17},						//D33= PE1
	{GPIO2, 1 <<18},						//D34= PE2
	{GPIO2, 1 <<19},						//D35= PE3
	{GPIO2, 1 <<20},						//D36= PE4
	{GPIO2, 1 <<21},						//D37= PE5
	{GPIO2, 1 <<22},						//D38= PE6
	{GPIO2, 1 <<23},						//D39= PE7
	{GPIO2, 1 <<24},						//D40= PE0
	{GPIO2, 1 <<25},						//D41= PE1
	{GPIO2, 1 <<26},						//D42= PE2
	{GPIO2, 1 <<27},						//D43= PE3
	{GPIO2, 1 <<28},						//D44= PE4
	{GPIO2, 1 <<29},						//D45= PE5
	{GPIO2, 1 <<30},						//D46= PE6
	{GPIO2, 1 <<31},						//D47= PE7
#endif

#if defined(LPC_GPIO3)
	//P20..31
	{GPIO3, 1 << 0},						//ARMduino Pin 32 = PE0
	{GPIO3, 1 << 1},						//ARMduino Pin 33 = PE1
	{GPIO3, 1 << 2},						//ARMduino Pin 34 = PE2
	{GPIO3, 1 << 3},						//ARMduino Pin 35 = PE3
	{GPIO3, 1 << 4},						//ARMduino Pin 36 = PE4
	{GPIO3, 1 << 5},						//ARMduino Pin 37 = PE5
	{GPIO3, 1 << 6},						//ARMduino Pin 38 = PE6
	{GPIO3, 1 << 7},						//ARMduino Pin 39 = PE7
	{GPIO3, 1 << 8},						//ARMduino Pin 32 = PE8
	{GPIO3, 1 << 9},						//ARMduino Pin 33 = PE9
	{GPIO3, 1 <<10},						//ARMduino Pin 34 = PE10
	{GPIO3, 1 <<11},						//ARMduino Pin 35 = PE11
	{GPIO3, 1 <<12},						//ARMduino Pin 36 = PE12
	{GPIO3, 1 <<13},						//ARMduino Pin 37 = PE13
	{GPIO3, 1 <<14},						//ARMduino Pin 38 = PE14
	{GPIO3, 1 <<15},						//ARMduino Pin 39 = PE15
	{GPIO3, 1 <<16},						//D32= PE0
	{GPIO3, 1 <<17},						//D33= PE1
	{GPIO3, 1 <<18},						//D34= PE2
	{GPIO3, 1 <<19},						//D35= PE3
	{GPIO3, 1 <<20},						//D36= PE4
	{GPIO3, 1 <<21},						//D37= PE5
	{GPIO3, 1 <<22},						//D38= PE6
	{GPIO3, 1 <<23},						//D39= PE7
	{GPIO3, 1 <<24},						//D40= PE0
	{GPIO3, 1 <<25},						//D41= PE1
	{GPIO3, 1 <<26},						//D42= PE2
	{GPIO3, 1 <<27},						//D43= PE3
	{GPIO3, 1 <<28},						//D44= PE4
	{GPIO3, 1 <<29},						//D45= PE5
	{GPIO3, 1 <<30},						//D46= PE6
	{GPIO3, 1 <<31},						//D47= PE7
#endif

#if defined(LPC_GPIO4)
	//P20..31
	{GPIO4, 1 << 0},						//ARMduino Pin 32 = PE0
	{GPIO4, 1 << 1},						//ARMduino Pin 33 = PE1
	{GPIO4, 1 << 2},						//ARMduino Pin 34 = PE2
	{GPIO4, 1 << 3},						//ARMduino Pin 35 = PE3
	{GPIO4, 1 << 4},						//ARMduino Pin 36 = PE4
	{GPIO4, 1 << 5},						//ARMduino Pin 37 = PE5
	{GPIO4, 1 << 6},						//ARMduino Pin 38 = PE6
	{GPIO4, 1 << 7},						//ARMduino Pin 39 = PE7
	{GPIO4, 1 << 8},						//ARMduino Pin 32 = PE8
	{GPIO4, 1 << 9},						//ARMduino Pin 33 = PE9
	{GPIO4, 1 <<10},						//ARMduino Pin 34 = PE10
	{GPIO4, 1 <<11},						//ARMduino Pin 35 = PE11
	{GPIO4, 1 <<12},						//ARMduino Pin 36 = PE12
	{GPIO4, 1 <<13},						//ARMduino Pin 37 = PE13
	{GPIO4, 1 <<14},						//ARMduino Pin 38 = PE14
	{GPIO4, 1 <<15},						//ARMduino Pin 39 = PE15
	{GPIO4, 1 <<16},						//D32= PE0
	{GPIO4, 1 <<17},						//D33= PE1
	{GPIO4, 1 <<18},						//D34= PE2
	{GPIO4, 1 <<19},						//D35= PE3
	{GPIO4, 1 <<20},						//D36= PE4
	{GPIO4, 1 <<21},						//D37= PE5
	{GPIO4, 1 <<22},						//D38= PE6
	{GPIO4, 1 <<23},						//D39= PE7
	{GPIO4, 1 <<24},						//D40= PE0
	{GPIO4, 1 <<25},						//D41= PE1
	{GPIO4, 1 <<26},						//D42= PE2
	{GPIO4, 1 <<27},						//D43= PE3
	{GPIO4, 1 <<28},						//D44= PE4
	{GPIO4, 1 <<29},						//D45= PE5
	{GPIO4, 1 <<30},						//D46= PE6
	{GPIO4, 1 <<31},						//D47= PE7
#endif

#if defined(LPC_GPIO5)
	//P20..31
	{GPIO5, 1 << 0},						//ARMduino Pin 32 = PE0
	{GPIO5, 1 << 1},						//ARMduino Pin 33 = PE1
	{GPIO5, 1 << 2},						//ARMduino Pin 34 = PE2
	{GPIO5, 1 << 3},						//ARMduino Pin 35 = PE3
	{GPIO5, 1 << 4},						//ARMduino Pin 36 = PE4
	{GPIO5, 1 << 5},						//ARMduino Pin 37 = PE5
	{GPIO5, 1 << 6},						//ARMduino Pin 38 = PE6
	{GPIO5, 1 << 7},						//ARMduino Pin 39 = PE7
	{GPIO5, 1 << 8},						//ARMduino Pin 32 = PE8
	{GPIO5, 1 << 9},						//ARMduino Pin 33 = PE9
	{GPIO5, 1 <<10},						//ARMduino Pin 34 = PE10
	{GPIO5, 1 <<11},						//ARMduino Pin 35 = PE11
	{GPIO5, 1 <<12},						//ARMduino Pin 36 = PE12
	{GPIO5, 1 <<13},						//ARMduino Pin 37 = PE13
	{GPIO5, 1 <<14},						//ARMduino Pin 38 = PE14
	{GPIO5, 1 <<15},						//ARMduino Pin 39 = PE15
	{GPIO5, 1 <<16},						//D32= PE0
	{GPIO5, 1 <<17},						//D33= PE1
	{GPIO5, 1 <<18},						//D34= PE2
	{GPIO5, 1 <<19},						//D35= PE3
	{GPIO5, 1 <<20},						//D36= PE4
	{GPIO5, 1 <<21},						//D37= PE5
	{GPIO5, 1 <<22},						//D38= PE6
	{GPIO5, 1 <<23},						//D39= PE7
	{GPIO5, 1 <<24},						//D40= PE0
	{GPIO5, 1 <<25},						//D41= PE1
	{GPIO5, 1 <<26},						//D42= PE2
	{GPIO5, 1 <<27},						//D43= PE3
	{GPIO5, 1 <<28},						//D44= PE4
	{GPIO5, 1 <<29},						//D45= PE5
	{GPIO5, 1 <<30},						//D46= PE6
	{GPIO5, 1 <<31},						//D47= PE7
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
	/* Enable AHB clock to the GPIO domain. */
	LPC_SC->PCONP |= 1<<15;			//15: enable clock to gpio
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
		case INPUT_PULLUP:	IO_IN(gpio, mask); break;	//pull-up not implemented
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
