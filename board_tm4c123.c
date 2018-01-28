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

	//initialize PWM / CCP output for analogWrite()

	//16-bit split timers, up/down counters
#if defined(USE_T0CCP0)					//PF0 is locked by default. be careful using this pin
	//T0CCP0 / PF0 used
	//configure gpio: T0CCP0 on PF0
	SYSCTL->RCGCGPIO |= (1<<5);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure PF0 for alternate function / T0CCP0
	GPIOF->DEN |= (1<<0);				//1=digital enabled, 0=digital disabled
	GPIOF->AFSEL |= (1<<0);				//1=alternate function enabled
	GPIOF->PCTL = (GPIOF->PCTL &~(0x0f << (0*4))) | (0x07<<(0*4));	//mux 7 to route CCP to PF0
	//now PF0 has been configured for T0CCP0

	//route the timer0
	SYSCTL->RCGCTIMER |= (1<<0);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<0)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER0->CTL &=~(1<<0);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER0->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER0->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER0->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	TIMER0->CTL = (TIMER0->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER0->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER0->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER0->TAPMR = TIMER0->TAPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER0->TAILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER0->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER0->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER0->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER0->CTL |= (1<<0);							//0->disable timer, 1->enable timer

#endif

#if defined(USE_T0CCP1)
	//T0CCP1 / PF1 used
	//configure gpio: T0CCP1 on PF1
	SYSCTL->RCGCGPIO |= (1<<5);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure PF1 for alternate function / T0CCP1
	GPIOF->DEN |= (1<<1);				//1=digital enabled, 0=digital disabled
	GPIOF->AFSEL |= (1<<1);				//1=alternate function enabled
	GPIOF->PCTL = (GPIOF->PCTL &~(0x0f << (1*4))) | (0x07<<(1*4));	//mux 7 to route CCP to PF1
	//now PF1 has been configured for T0CCP1

	//route the timer0
	SYSCTL->RCGCTIMER |= (1<<0);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<0)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER0->CTL &=~(1<<8);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER0->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER0->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER0->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	TIMER0->CTL = (TIMER0->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER0->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER0->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER0->TBPMR = TIMER0->TBPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER0->TBILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER0->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER0->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER0->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER0->CTL |= (1<<8);							//0->disable timer, 1->enable timer

#endif

#if defined(USE_T1CCP0)
	//T1CCP0 / PF2 used
	//configure gpio: T1CCP0 on PF2
	SYSCTL->RCGCGPIO |= (1<<5);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure PF2 for alternate function / T1CCP0
	GPIOF->DEN |= (1<<2);				//1=digital enabled, 0=digital disabled
	GPIOF->AFSEL |= (1<<2);				//1=alternate function enabled
	GPIOF->PCTL = (GPIOF->PCTL &~(0x0f << (2*4))) | (0x07<<(2*4));	//mux 7 to route CCP to PF2
	//now PF2 has been configured for T1CCP0

	//route the timer1
	SYSCTL->RCGCTIMER |= (1<<1);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<1)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER1->CTL &=~(1<<0);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER1->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER1->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER1->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	TIMER1->CTL = (TIMER1->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER1->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER1->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER1->TAPMR = TIMER1->TAPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER1->TAILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER1->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER1->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER1->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER1->CTL |= (1<<0);							//0->disable timer, 1->enable timer

#endif

#if defined(USE_T1CCP1)
	//T1CCP1 / PF3 used
	//configure gpio: T1CCP1 on PF3
	SYSCTL->RCGCGPIO |= (1<<5);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure PF1 for alternate function / T0CCP1
	GPIOF->DEN |= (1<<3);				//1=digital enabled, 0=digital disabled
	GPIOF->AFSEL |= (1<<3);				//1=alternate function enabled
	GPIOF->PCTL = (GPIOF->PCTL &~(0x0f << (3*4))) | (0x07<<(3*4));	//mux 7 to route CCP to PF1
	//now PF1 has been configured for T0CCP1

	//route the timer1
	SYSCTL->RCGCTIMER |= (1<<1);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<1)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER1->CTL &=~(1<<8);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER1->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER1->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER1->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	TIMER1->CTL = (TIMER1->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER1->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER1->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER1->TBPMR = TIMER1->TBPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER1->TBILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER1->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER1->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER1->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER1->CTL |= (1<<8);							//0->disable timer, 1->enable timer

#endif

#if defined(USE_T2CCP0)
	//T2CCP0 / PB0 used
	//configure gpio: T2CCP0 on PB0
	SYSCTL->RCGCGPIO |= (1<<1);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<1)) == 0) continue;	//1->ready, 0->not ready
	//configure PB0 for alternate function / T2CCP0
	GPIOB->DEN |= (1<<0);				//1=digital enabled, 0=digital disabled
	GPIOB->AFSEL |= (1<<0);				//1=alternate function enabled
	GPIOB->PCTL = (GPIOB->PCTL &~(0x0f << (0*4))) | (0x07<<(0*4));	//mux 7 to route CCP to PF0
	//now PB0 has been configured for T2CCP0

	//route the timer2
	SYSCTL->RCGCTIMER |= (1<<2);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER2->CTL &=~(1<<0);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER2->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER2->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER2->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	TIMER2->CTL = (TIMER2->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER2->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER2->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER2->TAPMR = TIMER2->TAPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER2->TAILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER2->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER2->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER2->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER2->CTL |= (1<<0);							//0->disable timer, 1->enable timer

#endif

#if defined(USE_T2CCP1)
	//T2CCP1 / PB1 used
	//configure gpio: T2CCP1 on PB1
	SYSCTL->RCGCGPIO |= (1<<1);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<1)) == 0) continue;	//1->ready, 0->not ready
	//configure PB1 for alternate function / T2CCP1
	GPIOB->DEN |= (1<<1);				//1=digital enabled, 0=digital disabled
	GPIOB->AFSEL |= (1<<1);				//1=alternate function enabled
	GPIOB->PCTL = (GPIOB->PCTL &~(0x0f << (1*4))) | (0x07<<(1*4));	//mux 7 to route CCP to PF1
	//now PB1 has been configured for T2CCP1

	//route the timer2
	SYSCTL->RCGCTIMER |= (1<<2);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER2->CTL &=~(1<<8);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER2->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER2->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER2->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	TIMER2->CTL = (TIMER2->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER2->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER2->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER2->TBPMR = TIMER2->TBPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER2->TBILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER2->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER2->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER2->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER2->CTL |= (1<<8);							//0->disable timer, 1->enable timer

#endif

#if defined(USE_T3CCP0)
	//T3CCP0 / PB2 used
	//configure gpio: T3CCP0 on PB2
	SYSCTL->RCGCGPIO |= (1<<1);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<1)) == 0) continue;	//1->ready, 0->not ready
	//configure PF2 for alternate function / T1CCP0
	GPIOB->DEN |= (1<<2);				//1=digital enabled, 0=digital disabled
	GPIOB->AFSEL |= (1<<2);				//1=alternate function enabled
	GPIOB->PCTL = (GPIOB->PCTL &~(0x0f << (2*4))) | (0x07<<(2*4));	//mux 7 to route CCP to PF2
	//now PB2 has been configured for T3CCP0

	//route timer3
	SYSCTL->RCGCTIMER |= (1<<3);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER3->CTL &=~(1<<0);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER3->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER3->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER3->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	TIMER3->CTL = (TIMER3->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER3->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER3->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER3->TAPMR = TIMER3->TAPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER3->TAILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER3->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER3->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER3->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER3->CTL |= (1<<0);							//0->disable timer, 1->enable timer

#endif

#if defined(USE_T3CCP1)
	//T3CCP1 / PB3 used
	//configure gpio: T3CCP1 on PB3
	SYSCTL->RCGCGPIO |= (1<<1);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<1)) == 0) continue;	//1->ready, 0->not ready
	//configure PB3 for alternate function / T3CCP1
	GPIOB->DEN |= (1<<3);				//1=digital enabled, 0=digital disabled
	GPIOB->AFSEL |= (1<<3);				//1=alternate function enabled
	GPIOB->PCTL = (GPIOB->PCTL &~(0x0f << (3*4))) | (0x07<<(3*4));	//mux 7 to route CCP to PF1
	//now PB3 has been configured for T3CCP1

	//route the timer3
	SYSCTL->RCGCTIMER |= (1<<3);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER3->CTL &=~(1<<8);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER3->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER3->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER3->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	TIMER3->CTL = (TIMER3->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER3->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER3->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER3->TBPMR = TIMER3->TBPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER3->TBILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER3->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER3->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER3->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER3->CTL |= (1<<8);							//0->disable timer, 1->enable timer

#endif
//trouble here
#if defined(USE_T4CCP0)
	//T4CCP0 / PC0 used
	//configure gpio: T4CCP0 on PC0
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC0 for alternate function / T4CCP0
	GPIOC->DEN |= (1<<0);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<0);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (0*4))) | (0x07<<(0*4));	//mux 7 to route CCP to PF0
	//now PC0 has been configured for T4CCP0

	//route the timer4
	SYSCTL->RCGCTIMER |= (1<<4);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<4)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER4->CTL &=~(1<<0);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER4->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER4->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER4->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	TIMER4->CTL = (TIMER4->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER4->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER4->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER4->TAPMR = TIMER4->TAPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER4->TAILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER4->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER4->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER4->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER4->CTL |= (1<<0);							//0->disable timer, 1->enable timer

#endif

#if defined(USE_T4CCP1)
	//T4CCP1 / PC1 used
	//configure gpio: T4CCP1 on PC1
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC1 for alternate function / T4CCP1
	GPIOC->DEN |= (1<<1);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<1);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (1*4))) | (0x07<<(1*4));	//mux 7 to route CCP to PF1
	//now PC1 has been configured for T4CCP1

	//route the TIMER4
	SYSCTL->RCGCTIMER |= (1<<4);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<4)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER4->CTL &=~(1<<8);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER4->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER4->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER4->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	TIMER4->CTL = (TIMER4->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER4->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER4->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER4->TBPMR = TIMER4->TBPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER4->TBILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER4->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER4->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER4->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER4->CTL |= (1<<8);							//0->disable timer, 1->enable timer

#endif

#if defined(USE_T5CCP0)
	//T5CCP0 / PC2 used
	//configure gpio: T5CCP0 on PC2
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC2 for alternate function / T5CCP0
	GPIOC->DEN |= (1<<2);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<2);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (2*4))) | (0x07<<(2*4));	//mux 7 to route CCP to PF2
	//now PC2 has been configured for T5CCP0

	//route timer5
	SYSCTL->RCGCTIMER |= (1<<5);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER5->CTL &=~(1<<0);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER5->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER5->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER5->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	TIMER5->CTL = (TIMER5->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER5->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER5->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER5->TAPMR = TIMER5->TAPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER5->TAILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER5->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER5->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER5->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER5->CTL |= (1<<0);							//0->disable timer, 1->enable timer

#endif

#if defined(USE_T5CCP1)
	//T5CCP1 / PC3 used
	//configure gpio: T5CCP1 on PC3
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC3 for alternate function / T5CCP1
	GPIOC->DEN |= (1<<3);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<3);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (3*4))) | (0x07<<(3*4));	//mux 7 to route CCP to PF1
	//now PC3 has been configured for T5CCP1

	//route the TIMER5
	SYSCTL->RCGCTIMER |= (1<<5);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRTIMER & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split timer
	//stop the timer
	TIMER5->CTL &=~(1<<8);							//0->disable timer, 1->enable timer
	//configure the timer, split, upcounter
	TIMER5->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split timers
	TIMER5->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->timer counts right away; 1->timer waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the timer is a down counter
	TIMER5->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	TIMER5->CTL = (TIMER5->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	TIMER5->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	TIMER5->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	TIMER5->TBPMR = TIMER5->TBPR = (TxCCP_PS - 1) & 0xff;							//set the prescaler
	TIMER5->TBILR= (TxCCP_PR - 1) & 0xffff;							//set the top
	//reset counter
	TIMER5->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	TIMER5->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	TIMER5->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the timer
	TIMER5->CTL |= (1<<8);							//0->disable timer, 1->enable timer

#endif


	//32-bit split WTIMERs, up/down counters
#if defined(USE_WT0CCP0)
	//WT0CCP0 / PC4 used
	//configure gpio: WT0CCP0 on PC4
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC4 for alternate function / WT0CCP0
	GPIOC->DEN |= (1<<4);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<4);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (4*4))) | (0x07<<(4*4));	//mux 7 to route CCP to PC4
	//now PC4 has been configured for WT0CCP0

	//route the WTIMER0
	SYSCTL->RCGCWTIMER |= (1<<0);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<0)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER0->CTL &=~(1<<0);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER0->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER0->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER0->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	WTIMER0->CTL = (WTIMER0->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER0->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER0->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER0->TAPMR = WTIMER0->TAPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER0->TAILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER0->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER0->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER0->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER0->CTL |= (1<<0);							//0->disable WTIMER, 1->enable WTIMER

#endif

#if defined(USE_WT0CCP1)
	//WT0CCP1 / PC5 used
	//configure gpio: WT0CCP1 on PC5
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC5 for alternate function / WT0CCP1
	GPIOC->DEN |= (1<<5);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<5);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (5*4))) | (0x07<<(5*4));	//mux 7 to route CCP to PF1
	//now PF1 has been configured for T0CCP1

	//route the WTIMER0
	SYSCTL->RCGCWTIMER |= (1<<0);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<0)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER0->CTL &=~(1<<8);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER0->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER0->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER0->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	WTIMER0->CTL = (WTIMER0->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER0->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER0->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER0->TBPMR = WTIMER0->TBPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER0->TBILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER0->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER0->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER0->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER0->CTL |= (1<<8);							//0->disable WTIMER, 1->enable WTIMER

#endif

#if defined(USE_WT1CCP0)
	//WT1CCP0 / PC6 used
	//configure gpio: WT1CCP0 on PC6
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC6 for alternate function / WT1CCP0
	GPIOC->DEN |= (1<<6);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<6);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (6*4))) | (0x07<<(6*4));	//mux 7 to route CCP to PF2
	//now PC6 has been configured for WT1CCP0

	//route the WTIMER1
	SYSCTL->RCGCWTIMER |= (1<<1);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<1)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER1->CTL &=~(1<<0);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER1->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER1->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER1->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	WTIMER1->CTL = (WTIMER1->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER1->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER1->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER1->TAPMR = WTIMER1->TAPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER1->TAILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER1->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER1->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER1->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER1->CTL |= (1<<0);							//0->disable WTIMER, 1->enable WTIMER

#endif

#if defined(USE_WT1CCP1)
	//WT1CCP1 / PC7 used
	//configure gpio: WT1CCP1 on PC7
	SYSCTL->RCGCGPIO |= (1<<2);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure PC7 for alternate function / WT0CCP1
	GPIOC->DEN |= (1<<7);				//1=digital enabled, 0=digital disabled
	GPIOC->AFSEL |= (1<<7);				//1=alternate function enabled
	GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (7*4))) | (0x07<<(7*4));	//mux 7 to route CCP to PF1
	//now PF1 has been configured for T0CCP1

	//route the WTIMER1
	SYSCTL->RCGCWTIMER |= (1<<1);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<1)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split WTIMER
	//stop the WTIMER
	WTIMER1->CTL &=~(1<<8);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER1->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER1->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER1->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	WTIMER1->CTL = (WTIMER1->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER1->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER1->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER1->TBPMR = WTIMER1->TBPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER1->TBILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER1->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER1->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER1->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER1->CTL |= (1<<8);							//0->disable WTIMER, 1->enable WTIMER

#endif

#if defined(USE_WT2CCP0)
	//WT2CCP0 / PD0 used
	//configure gpio: WT2CCP0 on PD0
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD0 for alternate function / WT2CCP0
	GPIOD->DEN |= (1<<0);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<0);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (0*4))) | (0x07<<(0*4));	//mux 7 to route CCP to PF0
	//now PD0 has been configured for WT2CCP0

	//route the WTIMER2
	SYSCTL->RCGCWTIMER |= (1<<2);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 16-bit split WTIMER
	//stop the WTIMER
	WTIMER2->CTL &=~(1<<0);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER2->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER2->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER2->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	WTIMER2->CTL = (WTIMER2->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER2->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER2->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER2->TAPMR = WTIMER2->TAPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER2->TAILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER2->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER2->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER2->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER2->CTL |= (1<<0);							//0->disable WTIMER, 1->enable WTIMER

#endif

#if defined(USE_WT2CCP1)
	//WT2CCP1 / PD1 used
	//configure gpio: WT2CCP1 on PD1
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD1 for alternate function / WT2CCP1
	GPIOD->DEN |= (1<<1);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<1);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (1*4))) | (0x07<<(1*4));	//mux 7 to route CCP to PF1
	//now PD1 has been configured for WT2CCP1

	//route the WTIMER2
	SYSCTL->RCGCWTIMER |= (1<<2);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<2)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER2->CTL &=~(1<<8);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER2->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER2->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER2->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	WTIMER2->CTL = (WTIMER2->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER2->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER2->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER2->TBPMR = WTIMER2->TBPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER2->TBILR= (TxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER2->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER2->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER2->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER2->CTL |= (1<<8);							//0->disable WTIMER, 1->enable WTIMER

#endif

#if defined(USE_WT3CCP0)
	//WT3CCP0 / PD2 used
	//configure gpio: WT3CCP0 on PD2
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD2 for alternate function / WT1CCP0
	GPIOD->DEN |= (1<<2);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<2);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (2*4))) | (0x07<<(2*4));	//mux 7 to route CCP to PF2
	//now PD2 has been configured for WT3CCP0

	//route WTIMER3
	SYSCTL->RCGCWTIMER |= (1<<3);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER3->CTL &=~(1<<0);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER3->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER3->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER3->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	WTIMER3->CTL = (WTIMER3->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER3->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER3->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER3->TAPMR = WTIMER3->TAPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER3->TAILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER3->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER3->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER3->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER3->CTL |= (1<<0);							//0->disable WTIMER, 1->enable WTIMER

#endif

#if defined(USE_WT3CCP1)
	//WT3CCP1 / PD3 used
	//configure gpio: WT3CCP1 on PD3
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD3 for alternate function / WT3CCP1
	GPIOD->DEN |= (1<<3);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<3);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (3*4))) | (0x07<<(3*4));	//mux 7 to route CCP to PF1
	//now PD3 has been configured for WT3CCP1

	//route the WTIMER3
	SYSCTL->RCGCWTIMER |= (1<<3);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER3->CTL &=~(1<<8);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER3->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER3->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER3->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	WTIMER3->CTL = (WTIMER3->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER3->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER3->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER3->TBPMR = WTIMER3->TBPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER3->TBILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER3->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER3->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER3->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER3->CTL |= (1<<8);							//0->disable WTIMER, 1->enable WTIMER

#endif

#if defined(USE_WT4CCP0)
	//WT4CCP0 / PD4 used
	//configure gpio: WT4CCP0 on PD4
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD4 for alternate function / WT4CCP0
	GPIOD->DEN |= (1<<4);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<4);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (4*4))) | (0x07<<(4*4));	//mux 7 to route CCP to PF0
	//now PD0 has been configured for WT4CCP0

	//route the WTIMER4
	SYSCTL->RCGCWTIMER |= (1<<4);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<4)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER4->CTL &=~(1<<0);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER4->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER4->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER4->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	WTIMER4->CTL = (WTIMER4->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER4->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER4->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER4->TAPMR = WTIMER4->TAPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER4->TAILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER4->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER4->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER4->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER4->CTL |= (1<<0);							//0->disable WTIMER, 1->enable WTIMER

#endif

#if defined(USE_WT4CCP1)
	//WT4CCP1 / PD5 used
	//configure gpio: WT4CCP1 on PD5
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD5 for alternate function / WT4CCP1
	GPIOD->DEN |= (1<<5);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<5);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (5*4))) | (0x07<<(5*4));	//mux 7 to route CCP to PF1
	//now PD5 has been configured for WT4CCP1

	//route the WTIMER4
	SYSCTL->RCGCWTIMER |= (1<<4);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<4)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER4->CTL &=~(1<<8);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER4->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER4->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER4->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	WTIMER4->CTL = (WTIMER4->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER4->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER4->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER4->TBPMR = WTIMER4->TBPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER4->TBILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER4->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER4->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER4->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER4->CTL |= (1<<8);							//0->disable WTIMER, 1->enable WTIMER

#endif

#if defined(USE_WT5CCP0)
	//WT5CCP0 / PD6 used
	//configure gpio: WT5CCP0 on PD6
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD6 for alternate function / WT5CCP0
	GPIOD->DEN |= (1<<6);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<6);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (6*4))) | (0x07<<(6*4));	//mux 7 to route CCP to PF2
	//now PD6 has been configured for WT5CCP0

	//route WTIMER5
	SYSCTL->RCGCWTIMER |= (1<<5);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER5->CTL &=~(1<<0);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER5->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER5->TAMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER5->CTL |= (1<<6);							//0->output not affected, 1->output inverted
	WTIMER5->CTL = (WTIMER5->CTL & ~(0x03 << 2)) | (0x00 << 2);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER5->TAMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER5->TAMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER5->TAPMR = WTIMER5->TAPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER5->TAILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER5->TAR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER5->IMR &=~(0x1f << 0);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER5->ICR |= (0x1f << 0);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER5->CTL |= (1<<0);							//0->disable WTIMER, 1->enable WTIMER

#endif

#if defined(USE_WT5CCP1)
	//WT5CCP1 / PD7 used
	//configure gpio: WT5CCP1 on PD7
	SYSCTL->RCGCGPIO |= (1<<3);			//0->GPIOA, 1->GPIOB, 2=GPIOC, 3=GPIOD, 4=GPIOE, 5=GPIOF, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->ready, 0->not ready
	//configure PD7 for alternate function / WT5CCP1
	GPIOD->DEN |= (1<<7);				//1=digital enabled, 0=digital disabled
	GPIOD->AFSEL |= (1<<7);				//1=alternate function enabled
	GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (7*4))) | (0x07<<(7*4));	//mux 7 to route CCP to PF1
	//now PD7 has been configured for WT5CCP1

	//route the WTIMER5
	SYSCTL->RCGCWTIMER |= (1<<5);		//1->periopheral clock enabled, 0->peripheral clock disabled
	while ((SYSCTL->PRWTIMER & (1<<5)) == 0) continue;	//1->ready, 0->not ready
	//configure timebase for 32-bit split WTIMER
	//stop the WTIMER
	WTIMER5->CTL &=~(1<<8);							//0->disable WTIMER, 1->enable WTIMER
	//configure the WTIMER, split, upcounter
	WTIMER5->CFG  = 0x04;							//0x00->32/64bit, 0x01->rtc, 0x02-0x03->reserved, 0x04->16/32bit split WTIMERs
	WTIMER5->TBMR = 	(0<<11) |						//0->legacy ops
					(0<<10) |						//0->update match register on the next cycle, 1->update match register now
					(0<< 9) |						//0->pwm interrupt disabled, 1->pwm interrupt enabled
					(0<< 8) |						//0->update load register ont he next cycle; 1->update load register now
					(0<< 7) |						//0->disable snap shot, 1->enable snap shot
					(0<< 6) |						//0->WTIMER counts right away; 1->WTIMER waits on trigger before counting
					(0<< 5) |						//0->match interrupt disabled, 1->match interrupt enabled
					(0<< 4) |						//0->counts down, 1->counts up
					(1<< 3) |						//0->capture / compare enabled 1->pwm enabled
					(0<< 2) |						//0->edge count for capture; 1->edge time for capture
					(2<< 0) |						//0x00->reserved, 0x01->one shot, 0x02->periodic, 0x03->capture
					0x00;

	//invert the output as the WTIMER is a down counter
	WTIMER5->CTL |= (1<<14);							//0->output not affected, 1->output inverted
	WTIMER5->CTL = (WTIMER5->CTL & ~(0x03 << 10)) | (0x00 << 10);		//0->positive edge, 1->negative edge, 2->reserved, 3->both edges
	WTIMER5->TBMR &=~(1<<9);							//1->enable PWM interrupt, 0->disable PWM interrupt
	WTIMER5->TBMATCHR = 0;							//for 0% duty cycle
	//set the prescaler
	WTIMER5->TBPMR = WTIMER5->TBPR = (TxCCP_PS - 1) & 0xffff;							//set the prescaler
	WTIMER5->TBILR= (WTxCCP_PR - 1);							//set the top
	//reset counter
	WTIMER5->TBR = 0;

	//clear ISR flags, disable isr
	//disable all interrupt
	WTIMER5->IMR &=~(0x1f << 8);						//0->disable time-out interrupt, 1->enable time-out interrupt
	WTIMER5->ICR |= (0x1f << 8);						//1->clear interrupt flag, 0->no effect

	//start the WTIMER
	WTIMER5->CTL |= (1<<8);							//0->disable WTIMER, 1->enable WTIMER

#endif


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

//16/32-bit PWM output
//PS defined by TxCCP_PS
//PR defined by TxCCP_PR
//valid pin assignment:
//PF0/T0CCP0 - not used / locked by CR
//PF1/T0CCP1
//PF2/T1CCP0
//PF3/T1CCP1
//PF4/T2CCP0 - not used / see PB0
//PB0/T2CCP0
//PB1/T2CCP1
//PB2/T3CCP0
//PB3/T3CCP1
//PB4/T1CCP0 - not used/see PF2
//PB5/T1CCP1 - not used/see PF3
//PB6/T0CCP0 - not used/see PF0
//PB7/T0CCP1 - not used/see PF1
//PC0/T4CCP0 - not used/SWCLK
//PC1/T4CCP1 - not used/SWDIO
//PC2/T5CCP0 - not used/TDI
//PC3/T5CCP1 - not used/TDO
//PC4/WT0CCP0
//PC5/WT0CCP1
//PC6/WT1CCP0
//PC7/WT1CCP1
//PD0/WT2CCP0
//PD1/WT2CCP1
//PD2/WT3CCP0
//PD3/WT3CCP1
//PD4/WT4CCP0
//PD5/WT4CCP1
//PD6/WT5CCP0
//PD7/WT5CCP1
void analogWrite(PIN_T pin, uint16_t dc) {
	switch (pin) {
		//for 16-bit timers
		case PF0: TIMER0->TAMATCHR = dc; break;		//PF0 = T0CCP0
		case PF1: TIMER0->TBMATCHR = dc; break;		//PF1 = T0CCP1
		case PF2: TIMER1->TAMATCHR = dc; break;		//PF2 = T1CCP0
		case PF3: TIMER1->TBMATCHR = dc; break;		//PF3 = T1CCP1
		case PB0: TIMER2->TAMATCHR = dc; break;		//PB0 = T2CCP0
		case PB1: TIMER2->TBMATCHR = dc; break;		//PB1 = T2CCP1
		case PB2: TIMER3->TAMATCHR = dc; break;		//PB2 = T3CCP0
		case PB3: TIMER3->TBMATCHR = dc; break;		//PB3 = T3CCP1
		case PC0: TIMER4->TAMATCHR = dc; break;		//PC0 = T4CCP0
		case PC1: TIMER4->TBMATCHR = dc; break;		//PC1 = T4CCP1
		case PC2: TIMER5->TAMATCHR = dc; break;		//PC2 = T5CCP0
		case PC3: TIMER5->TBMATCHR = dc; break;		//PC3 = T5CCP1

		//for 32-bit timers - ***LIITED TO 16-BIT*** BY THE PROTOTYPE
		case PC4: WTIMER0->TAMATCHR = dc; break;	//PC4 = WT0CCP0
		case PC5: WTIMER0->TBMATCHR = dc; break;	//PC5 = WT0CCP1
		case PC6: WTIMER1->TAMATCHR = dc; break;	//PC6 = WT1CCP0
		case PC7: WTIMER1->TBMATCHR = dc; break;	//PC7 = WT1CCP1
		case PD0: WTIMER2->TAMATCHR = dc; break;	//PD0 = WT2CCP0
		case PD1: WTIMER2->TBMATCHR = dc; break;	//PD1 = WT2CCP1
		case PD2: WTIMER3->TAMATCHR = dc; break;	//PD2 = WT3CCP0
		case PD3: WTIMER3->TBMATCHR = dc; break;	//PD3 = WT3CCP1
		case PD4: WTIMER4->TAMATCHR = dc; break;	//PD4 = WT4CCP0
		case PD5: WTIMER4->TBMATCHR = dc; break;	//PD5 = WT4CCP1
		case PD6: WTIMER5->TAMATCHR = dc; break;	//PD6 = WT5CCP0
		case PD7: WTIMER5->TBMATCHR = dc; break;	//PD7 = WT5CCP1
	}
}

//serial comm
void Serial0_begin(uint32_t baudrate) {
	//UART0: RX on PA0, TX on PA1
	//uart0: tx on PA1, rx on PA0
	//route clock to GPIO
	SYSCTL->RCGCGPIO |= (1<<0);				//0->GPIOA, 1->GPIOB, 2->GPIOC, ...
	while ((SYSCTL->PRGPIO & (1<<0)) == 0) continue;	//1->peripheral ready, 0-> not ready
	//configure PA0 for alternate function / mux group 1
	GPIOA->DEN |= (1<<0); GPIOA->AFSEL |= (1<<0); GPIOA->PCTL = (GPIOA->PCTL &~(0x0f << (0*4))) | (0x01 << (0*4));
	//configure PA1 for alternate function / mux group 1
	GPIOA->DEN |= (1<<1); GPIOA->AFSEL |= (1<<1); GPIOA->PCTL = (GPIOA->PCTL &~(0x0f << (1*4))) | (0x01 << (1*4));

	//route clock to UART
	SYSCTL->RCGCUART |= (1<<0);				//0->UART0, 1->UART1, ...
	while ((SYSCTL->PRUART & (1<<0)) == 0) continue;	//1->peripheral ready, 0-> not ready

	//stop the uart
	UART0->CTL &=~(1<<0);					//1->enable uart, 0->disable uart

	//set HSE for high speed
	UART0->CTL =	(0<<15) |				//0->clear to send disabled, 1->clear to send enabled
					(0<<14) |				//0->request to send disabled, 1->request to send enabled
					(0<<11) |				//1->RTS signal received, 0->RTS not received
					(0<< 9) |				//1->enable uart receive, 0->disable uart receive
					(0<< 8) |				//1->enable uart transmit, 0->disable uart transmit
					(0<< 7) |				//0->normal operation, 1->TX/RX loop back enabled
					(1<< 5) |				//0->HSE disabled, divide by 16, 1->HSE enabled, divide by 8
					(0<< 4) |				//0->set TXRIS when UARTIFLS is met, 1->TXRIS set only after all transmitted data have been sent
					(0<< 3) | 				//0->normal operation, 1->UART in smart card mode
					(0<< 2) |				//0->low level bits transmitted as active high, 1->uart in SIR low-power mode
					(0<< 1) |				//0->normal operation, 1->IrDA SIR enabled
					(0<< 0) |				//0->uart is disabled, 1->uart is enabled
					0x00;
	if (GPIOA->AFSEL & (1<<0)) UART0->CTL |= (1<<9); else UART0->CTL &=~(1<<9);	//enable receiving if PA0 is configured for alternate function
	if (GPIOA->AFSEL & (1<<1)) UART0->CTL |= (1<<8); else UART0->CTL &=~(1<<8);	//enable transmission if PA1 is configured for alternate function

	if (UART0->CTL & (1<<5)) {				//HSE bit set -> divide by 8
		//calculate the integer baud rate
		UART0->IBRD = SystemCoreClock / baudrate / 8;
		//calculate the fractional baud rate = 64*fraction
		UART0->FBRD = (8 * SystemCoreClock / baudrate - UART0->IBRD * 64);
	} else {								//HSE bit cleared -> divide by 16
		//calculate the integer baud rate
		UART0->IBRD = SystemCoreClock / baudrate / 16;
		//calculate the fractional baud rate = 64*fraction
		UART0->FBRD = (4 * SystemCoreClock / baudrate - UART0->IBRD * 64);
	}

	//configure serial parameters in LCRH
	UART0->LCRH = 	(0<<7) |				//0->stick parity disabled, 1->stick parity enabled
					(3<<5) |				//word length. 0->5bit, 1->6bit, 2->7bit, 3->8bit
					(1<<4) |				//0->fifo disabled, 1->fifo enabled
					(0<<3) |				//0->1 stop bit, 1->two stop bits
					(0<<2) |				//0->odd parity, 1->even parity. no effect if parity is disabled (bit 1 cleared)
					(0<<1) |				//0->parity disabled, 1->parity enabled
					(0<<0) | 				//0->normal use, 1->send break
					0x00;

	//configure the uart clock source
	UART0->CC = 0x00;						//0x00->system clock used, 0x05->PIOSC used

	//clear the flags
	UART0->IM = 0x00;						//all interrupt disabled
	UART0->ICR = 0xffff;						//1->clear flags

	//start the uart
	UART0->CTL |= (1<<0);					//1->enable uart, 0->disable uart

}

void Serial0_println(char *str) {
	Serial0_print(str);
	Serial0_print("\n\r");
}

void Serial0_print(char *str) {
	while (*str) {
		//while (UART0->FR & (1<<3)) continue;	//wait for transmision to end - most conservative
		while (UART0->FR & (1<<5)) continue;	//wait for transmision buffer to free up - most aggressive
		UART0->DR = *str++;
	}
}

//only return 1 (indicating data availability), or 0 (no data available)
char Serial0_available(void) {
	return (UART0->FR & (1<<4))?1:0;
}

char Serial0_read(void) {
	return UART0->DR;
}

void Serial1_begin(uint32_t baudrate) {
	//uart1: tx on PB1, rx on PB0
	//route clock to GPIO
	SYSCTL->RCGCGPIO |= (1<<1);				//0->GPIOA, 1->GPIOB, 2->GPIOC, ...
	while ((SYSCTL->PRGPIO & (1<<1)) == 0) continue;	//1->peripheral ready, 0-> not ready
	//configure PB0 for alternate function / mux group 1
	GPIOB->DEN |= (1<<0); GPIOB->AFSEL |= (1<<0); GPIOB->PCTL = (GPIOB->PCTL &~(0x0f << (0*4))) | (0x01 << (0*4));
	//configure PB1 for alternate function / mux group 1
	GPIOB->DEN |= (1<<1); GPIOB->AFSEL |= (1<<1); GPIOB->PCTL = (GPIOB->PCTL &~(0x0f << (1*4))) | (0x01 << (1*4));

	//route clock to UART
	SYSCTL->RCGCUART |= (1<<1);				//0->UART0, 1->UART1, ...
	while ((SYSCTL->PRUART & (1<<1)) == 0) continue;	//1->peripheral ready, 0-> not ready

	//stop the uart
	UART1->CTL &=~(1<<0);					//1->enable uart, 0->disable uart

	//set HSE for high speed
	UART1->CTL =	(0<<15) |				//0->clear to send disabled, 1->clear to send enabled
					(0<<14) |				//0->request to send disabled, 1->request to send enabled
					(0<<11) |				//1->RTS signal received, 0->RTS not received
					(0<< 9) |				//1->enable uart receive, 0->disable uart receive
					(0<< 8) |				//1->enable uart transmit, 0->disable uart transmit
					(0<< 7) |				//0->normal operation, 1->TX/RX loop back enabled
					(1<< 5) |				//0->HSE disabled, divide by 16, 1->HSE enabled, divide by 8
					(0<< 4) |				//0->set TXRIS when UARTIFLS is met, 1->TXRIS set only after all transmitted data have been sent
					(0<< 3) | 				//0->normal operation, 1->UART in smart card mode
					(0<< 2) |				//0->low level bits transmitted as active high, 1->uart in SIR low-power mode
					(0<< 1) |				//0->normal operation, 1->IrDA SIR enabled
					(0<< 0) |				//0->uart is disabled, 1->uart is enabled
					0x00;
	if (GPIOB->AFSEL & (1<<0)) UART1->CTL |= (1<<9); else UART1->CTL &=~(1<<9);	//enable receiving if PB0 is configured for alternate function
	if (GPIOB->AFSEL & (1<<1)) UART1->CTL |= (1<<8); else UART1->CTL &=~(1<<8);	//enable transmission if PB1 is configured for alternate function

	if (UART1->CTL & (1<<5)) {				//HSE bit set -> divide by 8
		//calculate the integer baud rate
		UART1->IBRD = SystemCoreClock / baudrate / 8;
		//calculate the fractional baud rate = 64*fraction
		UART1->FBRD = (8 * SystemCoreClock / baudrate - UART1->IBRD * 64);
	} else {								//HSE bit cleared -> divide by 16
		//calculate the integer baud rate
		UART1->IBRD = SystemCoreClock / baudrate / 16;
		//calculate the fractional baud rate = 64*fraction
		UART1->FBRD = (4 * SystemCoreClock / baudrate - UART1->IBRD * 64);
	}

	//configure serial parameters in LCRH
	UART1->LCRH = 	(0<<7) |				//0->stick parity disabled, 1->stick parity enabled
					(3<<5) |				//word length. 0->5bit, 1->6bit, 2->7bit, 3->8bit
					(1<<4) |				//0->fifo disabled, 1->fifo enabled
					(0<<3) |				//0->1 stop bit, 1->two stop bits
					(0<<2) |				//0->odd parity, 1->even parity. no effect if parity is disabled (bit 1 cleared)
					(0<<1) |				//0->parity disabled, 1->parity enabled
					(0<<0) | 				//0->normal use, 1->send break
					0x00;

	//configure the uart clock source
	UART1->CC = 0x00;						//0x00->system clock used, 0x05->PIOSC used

	//clear the flags
	UART1->IM = 0x00;						//all interrupt disabled
	UART1->ICR = 0xffff;						//1->clear flags

	//start the uart
	UART1->CTL |= (1<<0);					//1->enable uart, 0->disable uart

}

void Serial1_println(char *str) {
	Serial1_print(str);
	Serial1_print("\n\r");
}

void Serial1_print(char *str) {
	while (*str) {
		//while (UART1->FR & (1<<3)) continue;	//wait for transmision to end - most conservative
		while (UART1->FR & (1<<5)) continue;	//wait for transmision buffer to free up - most aggressive
		UART1->DR = *str++;
	}
}

//only return 1 (indicating data availability), or 0 (no data available)
char Serial1_available(void) {
	return (UART1->FR & (1<<4))?1:0;
}

char Serial1_read(void) {
	return UART1->DR;
}

void Serial2_begin(uint32_t baudrate) {
	//uart2: tx on PD7, rx on PD6
	//route clock to GPIO
	SYSCTL->RCGCGPIO |= (1<<3);				//0->GPIOA, 1->GPIOB, 2->GPIOC, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->peripheral ready, 0-> not ready
	//configure PD6 for alternate function / mux group 1
	GPIOD->DEN |= (1<<6); GPIOD->AFSEL |= (1<<6); GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (6*4))) | (0x01 << (6*4));
	//configure PD7 for alternate function / mux group 1
	GPIOD->DEN |= (1<<7); GPIOD->AFSEL |= (1<<7); GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (7*4))) | (0x01 << (7*4));

	//route clock to UART
	SYSCTL->RCGCUART |= (1<<2);				//0->UART0, 1->UART1, ...
	while ((SYSCTL->PRUART & (1<<2)) == 0) continue;	//1->peripheral ready, 0-> not ready

	//stop the uart
	UART2->CTL &=~(1<<0);					//1->enable uart, 0->disable uart

	//set HSE for high speed
	UART2->CTL =	(0<<15) |				//0->clear to send disabled, 1->clear to send enabled
					(0<<14) |				//0->request to send disabled, 1->request to send enabled
					(0<<11) |				//1->RTS signal received, 0->RTS not received
					(0<< 9) |				//1->enable uart receive, 0->disable uart receive
					(0<< 8) |				//1->enable uart transmit, 0->disable uart transmit
					(0<< 7) |				//0->normal operation, 1->TX/RX loop back enabled
					(1<< 5) |				//0->HSE disabled, divide by 16, 1->HSE enabled, divide by 8
					(0<< 4) |				//0->set TXRIS when UARTIFLS is met, 1->TXRIS set only after all transmitted data have been sent
					(0<< 3) | 				//0->normal operation, 1->UART in smart card mode
					(0<< 2) |				//0->low level bits transmitted as active high, 1->uart in SIR low-power mode
					(0<< 1) |				//0->normal operation, 1->IrDA SIR enabled
					(0<< 0) |				//0->uart is disabled, 1->uart is enabled
					0x00;
	if (GPIOD->AFSEL & (1<<6)) UART2->CTL |= (1<<9); else UART2->CTL &=~(1<<9);	//enable receiving if PD6 is configured for alternate function
	if (GPIOD->AFSEL & (1<<7)) UART2->CTL |= (1<<8); else UART2->CTL &=~(1<<8);	//enable transmission if PD7 is configured for alternate function

	if (UART2->CTL & (1<<5)) {				//HSE bit set -> divide by 8
		//calculate the integer baud rate
		UART2->IBRD = SystemCoreClock / baudrate / 8;
		//calculate the fractional baud rate = 64*fraction
		UART2->FBRD = (8 * SystemCoreClock / baudrate - UART2->IBRD * 64);
	} else {								//HSE bit cleared -> divide by 16
		//calculate the integer baud rate
		UART2->IBRD = SystemCoreClock / baudrate / 16;
		//calculate the fractional baud rate = 64*fraction
		UART2->FBRD = (4 * SystemCoreClock / baudrate - UART2->IBRD * 64);
	}

	//configure serial parameters in LCRH
	UART2->LCRH = 	(0<<7) |				//0->stick parity disabled, 1->stick parity enabled
					(3<<5) |				//word length. 0->5bit, 1->6bit, 2->7bit, 3->8bit
					(1<<4) |				//0->fifo disabled, 1->fifo enabled
					(0<<3) |				//0->1 stop bit, 1->two stop bits
					(0<<2) |				//0->odd parity, 1->even parity. no effect if parity is disabled (bit 1 cleared)
					(0<<1) |				//0->parity disabled, 1->parity enabled
					(0<<0) | 				//0->normal use, 1->send break
					0x00;

	//configure the uart clock source
	UART2->CC = 0x00;						//0x00->system clock used, 0x05->PIOSC used

	//clear the flags
	UART2->IM = 0x00;						//all interrupt disabled
	UART2->ICR = 0xffff;						//1->clear flags

	//start the uart
	UART2->CTL |= (1<<0);					//1->enable uart, 0->disable uart

}


void Serial2_println(char *str) {
	Serial2_print(str);
	Serial2_print("\n\r");
}

void Serial2_print(char *str) {
	while (*str) {
		//while (UART2->FR & (1<<3)) continue;	//wait for transmision to end - most conservative
		while (UART2->FR & (1<<5)) continue;	//wait for transmision buffer to free up - most aggressive
		UART2->DR = *str++;
	}
}

//only return 1 (indicating data availability), or 0 (no data available)
char Serial2_available(void) {
	return (UART2->FR & (1<<4))?1:0;
}

char Serial2_read(void) {
	return UART2->DR;
}

void Serial3_begin(uint32_t baudrate) {
	//uart3: tx on PC7, rx on PC6
	//route clock to GPIO
	SYSCTL->RCGCGPIO |= (1<<2);				//0->GPIOA, 1->GPIOB, 2->GPIOC, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->peripheral ready, 0-> not ready
	//configure PC6 for alternate function / mux group 1
	GPIOC->DEN |= (1<<6); GPIOC->AFSEL |= (1<<6); GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (6*4))) | (0x01 << (6*4));
	//configure PC7 for alternate function / mux group 1
	GPIOC->DEN |= (1<<7); GPIOC->AFSEL |= (1<<7); GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (7*4))) | (0x01 << (7*4));

	//route clock to UART
	SYSCTL->RCGCUART |= (1<<3);				//0->UART0, 1->UART1, ...
	while ((SYSCTL->PRUART & (1<<3)) == 0) continue;	//1->peripheral ready, 0-> not ready

	//stop the uart
	UART3->CTL &=~(1<<0);					//1->enable uart, 0->disable uart

	//set HSE for high speed
	UART3->CTL =	(0<<15) |				//0->clear to send disabled, 1->clear to send enabled
					(0<<14) |				//0->request to send disabled, 1->request to send enabled
					(0<<11) |				//1->RTS signal received, 0->RTS not received
					(0<< 9) |				//1->enable uart receive, 0->disable uart receive
					(0<< 8) |				//1->enable uart transmit, 0->disable uart transmit
					(0<< 7) |				//0->normal operation, 1->TX/RX loop back enabled
					(1<< 5) |				//0->HSE disabled, divide by 16, 1->HSE enabled, divide by 8
					(0<< 4) |				//0->set TXRIS when UARTIFLS is met, 1->TXRIS set only after all transmitted data have been sent
					(0<< 3) | 				//0->normal operation, 1->UART in smart card mode
					(0<< 2) |				//0->low level bits transmitted as active high, 1->uart in SIR low-power mode
					(0<< 1) |				//0->normal operation, 1->IrDA SIR enabled
					(0<< 0) |				//0->uart is disabled, 1->uart is enabled
					0x00;
	if (GPIOC->AFSEL & (1<<6)) UART3->CTL |= (1<<9); else UART3->CTL &=~(1<<9);	//enable receiving if PC6 is configured for alternate function
	if (GPIOC->AFSEL & (1<<7)) UART3->CTL |= (1<<8); else UART3->CTL &=~(1<<8);	//enable transmission if PC7 is configured for alternate function

	if (UART3->CTL & (1<<5)) {				//HSE bit set -> divide by 8
		//calculate the integer baud rate
		UART3->IBRD = SystemCoreClock / baudrate / 8;
		//calculate the fractional baud rate = 64*fraction
		UART3->FBRD = (8 * SystemCoreClock / baudrate - UART3->IBRD * 64);
	} else {								//HSE bit cleared -> divide by 16
		//calculate the integer baud rate
		UART3->IBRD = SystemCoreClock / baudrate / 16;
		//calculate the fractional baud rate = 64*fraction
		UART3->FBRD = (4 * SystemCoreClock / baudrate - UART3->IBRD * 64);
	}

	//configure serial parameters in LCRH
	UART3->LCRH = 	(0<<7) |				//0->stick parity disabled, 1->stick parity enabled
					(3<<5) |				//word length. 0->5bit, 1->6bit, 2->7bit, 3->8bit
					(1<<4) |				//0->fifo disabled, 1->fifo enabled
					(0<<3) |				//0->1 stop bit, 1->two stop bits
					(0<<2) |				//0->odd parity, 1->even parity. no effect if parity is disabled (bit 1 cleared)
					(0<<1) |				//0->parity disabled, 1->parity enabled
					(0<<0) | 				//0->normal use, 1->send break
					0x00;

	//configure the uart clock source
	UART3->CC = 0x00;						//0x00->system clock used, 0x05->PIOSC used

	//clear the flags
	UART3->IM = 0x00;						//all interrupt disabled
	UART3->ICR = 0xffff;						//1->clear flags

	//start the uart
	UART3->CTL |= (1<<0);					//1->enable uart, 0->disable uart

}


void Serial3_println(char *str) {
	Serial3_print(str);
	Serial3_print("\n\r");
}

void Serial3_print(char *str) {
	while (*str) {
		//while (UART3->FR & (1<<3)) continue;	//wait for transmision to end - most conservative
		while (UART3->FR & (1<<5)) continue;	//wait for transmision buffer to free up - most aggressive
		UART3->DR = *str++;
	}
}

//only return 1 (indicating data availability), or 0 (no data available)
char Serial3_available(void) {
	return (UART3->FR & (1<<4))?1:0;
}

char Serial3_read(void) {
	return UART3->DR;
}

