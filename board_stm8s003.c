#include "xduino.h"						//use xduino generic defs
#include "board_stm8s003.h"				//we use board-specific defs

//put board specific implementation here

//global defines

//global variables
volatile uint32_t SystemCoreClock=16000000ul/8;				//systemcoreclock. defaults to HSI (@16Mhz) / 8
volatile uint32_t timer_ticks=0;		//timer ticks, 32-bit
//gpio pins
const PIN2GPIO GPIO_PinDef[]={
	//has to mamtch PIN_T def in boards.h
	//starting with D0
	//PA0..7
	{GPIOA, 1<<0},						//D0 = PA0
	{GPIOA, 1<<1},						//D1 = PA1
	{GPIOA, 1<<2},						//D2 = PA2
	{GPIOA, 1<<3},						//D3 = PA3
	{GPIOA, 1<<4},						//D4 = PA4
	{GPIOA, 1<<5},						//D5 = PA5
	{GPIOA, 1<<6},						//D6 = PA6
	{GPIOA, 1<<7},						//D7 = PA7

	//PB0..7
	{GPIOB, 1<<0},						//D8 = PB0
	{GPIOB, 1<<1},						//D9 = PB1
	{GPIOB, 1<<2},						//D10= PB2
	{GPIOB, 1<<3},						//D11= PB3
	{GPIOB, 1<<4},						//D12= PB4
	{GPIOB, 1<<5},						//D13= PB5
	{GPIOB, 1<<6},						//D14= PB6
	{GPIOB, 1<<7},						//D15= PB7

	//PC0..7
	{GPIOC, 1<<0},						//D16= PC0
	{GPIOC, 1<<1},						//D17= PC1
	{GPIOC, 1<<2},						//D18= PC2
	{GPIOC, 1<<3},						//D19= PC3
	{GPIOC, 1<<4},						//D20= PC4
	{GPIOC, 1<<5},						//D21= PC5
	{GPIOC, 1<<6},						//D22= PC6
	{GPIOC, 1<<7},						//D23= PC7

	//PD0..7
	{GPIOD, 1<<0},						//D24= PD0
	{GPIOD, 1<<1},						//D25= PD1
	{GPIOD, 1<<2},						//D26= PD2
	{GPIOD, 1<<3},						//D27= PD3
	{GPIOD, 1<<4},						//D28= PD4
	{GPIOD, 1<<5},						//D29= PD5
	{GPIOD, 1<<6},						//D30= PD6
	{GPIOD, 1<<7},						//D31= PD7

	//PE0..7
	{GPIOE, 1<<0},						//D32= PE0
	{GPIOE, 1<<1},						//D33= PE1
	{GPIOE, 1<<2},						//D34= PE2
	{GPIOE, 1<<3},						//D35= PE3
	{GPIOE, 1<<4},						//D36= PE4
	{GPIOE, 1<<5},						//D37= PE5
	{GPIOE, 1<<6},						//D38= PE6
	{GPIOE, 1<<7},						//D39= PE7

#if defined(GPIOF)
	//PF0..7
	{GPIOF, 1<<0},						//D32= PE0
	{GPIOF, 1<<1},						//D33= PE1
	{GPIOF, 1<<2},						//D34= PE2
	{GPIOF, 1<<3},						//D35= PE3
	{GPIOF, 1<<4},						//D36= PE4
	{GPIOF, 1<<5},						//D37= PE5
	{GPIOF, 1<<6},						//D38= PE6
	{GPIOF, 1<<7},						//D39= PE7
#endif
	
#if defined(GPIOG)
	//PG0..7
	{GPIOG, 1<<0},						//D32= PE0
	{GPIOG, 1<<1},						//D33= PE1
	{GPIOG, 1<<2},						//D34= PE2
	{GPIOG, 1<<3},						//D35= PE3
	{GPIOG, 1<<4},						//D36= PE4
	{GPIOG, 1<<5},						//D37= PE5
	{GPIOG, 1<<6},						//D38= PE6
	{GPIOG, 1<<7},						//D39= PE7
#endif
	
#if defined(GPIOH)
	//PH0..7
	{GPIOH, 1<<0},						//D32= PE0
	{GPIOH, 1<<1},						//D33= PE1
	{GPIOH, 1<<2},						//D34= PE2
	{GPIOH, 1<<3},						//D35= PE3
	{GPIOH, 1<<4},						//D36= PE4
	{GPIOH, 1<<5},						//D37= PE5
	{GPIOH, 1<<6},						//D38= PE6
	{GPIOH, 1<<7},						//D39= PE7
#endif
	
#if defined(GPIOI)
	//PI0..7
	{GPIOI, 1<<0},						//D32= PE0
	{GPIOI, 1<<1},						//D33= PE1
	{GPIOI, 1<<2},						//D34= PE2
	{GPIOI, 1<<3},						//D35= PE3
	{GPIOI, 1<<4},						//D36= PE4
	{GPIOI, 1<<5},						//D37= PE5
	{GPIOI, 1<<6},						//D38= PE6
	{GPIOI, 1<<7},						//D39= PE7
#endif
};

//timer4 overflow interrupt handler
//tim4 isr handler
#pragma vector = TIM4_OVR_UIF_vector			//tim4 overflow interrupt
__interrupt void tim4_ovr_isr(void) {
	//clear the flag - done automatically
	TIM4->SR1 &=~(1<<0);						//TIM4_SR_UIF=0;							//clear the flag
	timer_ticks+= 0x100;						//increment timer ticks - tim4 is 8-bit wide
}

//use hsi oscillator
void SystemCoreClockHSI(uint8_t CLK_HSIDIV) {
   /* check the parameters */
    //assert_param(IS_CLK_PRESCALER_OK(CLK_HSIDIV));
	
	//CLK_DeInit();
	CLK->ICKR |= CLK_ICKR_HSIEN;					//enable HSI
	while ((CLK->ICKR & CLK_ICKR_HSIRDY) == 0) continue;	//wait until HSI is ready
	CLK->SWCR|= CLK_SWCR_SWEN;						//start the switch
	CLK->SWR = 0xe1;								//0xe1->HSI, 0xd2->LSI, 0xb4->HSE	//CLK_HSICmd(ENABLE);
	while ((CLK->SWCR & CLK_SWCR_SWBSY) == 1) continue;	//wait until the busy signal is no more	//while(SET != CLK_GetFlagStatus(CLK_FLAG_HSIRDY)) continue;	//make sure hsi is ready
	CLK->CKDIVR = (CLK->CKDIVR &~CLK_CKDIVR_HSIDIV) | (CLK_HSIDIV & CLK_CKDIVR_HSIDIV);	//set hsi divider
	CLK->CKDIVR = (CLK->CKDIVR &~CLK_CKDIVR_CPUDIV) | (CLK_PRESCALER_CPUDIV1 & CLK_CKDIVR_CPUDIV);	//set cpu divier -> default to 1:1
	//update SystemCoreClock
	switch (CLK_HSIDIV) {
		case CLK_PRESCALER_HSIDIV1: SystemCoreClock = HSI_VALUE / 1; break;
		case CLK_PRESCALER_HSIDIV2: SystemCoreClock = HSI_VALUE / 2; break;
		case CLK_PRESCALER_HSIDIV4: SystemCoreClock = HSI_VALUE / 4; break;
		case CLK_PRESCALER_HSIDIV8: SystemCoreClock = HSI_VALUE / 8; break;
		default: SystemCoreClock = HSI_VALUE / 8; break;
	}
}

//use hse oscillator
void SystemCoreClockHSE(void) {
   /* check the parameters */
    //assert_param(IS_CLK_PRESCALER_OK(CLK_HSIDIV));
	
	//CLK_DeInit();
	CLK->ECKR |= CLK_ECKR_HSEEN;					//enable HSE
	while ((CLK->ECKR & CLK_ECKR_HSERDY) == 0) continue;	//wait until HSE is ready
	CLK->SWCR|= CLK_SWCR_SWEN;						//start the switch
	CLK->SWR = 0xb4;								//0xe1->HSI, 0xd2->LSI, 0xb4->HSE	//CLK_HSICmd(ENABLE);
	while ((CLK->SWCR & CLK_SWCR_SWBSY) == 1) continue;	//wait until the busy signal is no more	//while(SET != CLK_GetFlagStatus(CLK_FLAG_HSIRDY)) continue;	//make sure hsi is ready
	//update SystemCoreClock
	SystemCoreClock = HSE_VALUE;
}

//user must provide the following functions / macro defs
void mcu_init(void) {
	SystemCoreClockHSI_16MHz();					//set clock to hsi, _2MHz, _4MHz, _8MHz, _16MHz
	//SystemCoreClockHSE();							//set clock to hse, @ HSE_VALUE
	//SystemCoreClockHSI_2MHz();					//set clock to hsi, _2MHz, _4MHz, _8MHz, _16MHz
	//SystemCoreClockLSI();							//running at LSI (=128Khz)
	//CLK->PCKENR1=CLK->PCKENR2=0x00;				//disable all peripheral clocks
	//CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE);	//enable clock to tim2

	//initialize timer0, 64:1 prescaler, overflow interrupt enabled
	//stop the timer
	//enable the clock to peripheral
	CLK->PCKENR1 |= CLK_PCKENR1_TIM4;			//'1'=clock enabled, '0'=clock disabled


	//stop the timer
	TIM4->CR1 &=~(1<<0);					//stop the timer
	
	//set up the timer
	TIM4->CR1 = (1<<7) |					//'1'->enable auto reload buffer
	  			(0<<5) |					//'0'->edge aligned. 1..3->center aligned
				(0<<4) |					//'0'->up counter, '1' downcounter
				(0<<3) |					//'0'->continuous mode, '1'->one pulse mode
				(0<<2) |					//'0'-> update enable source
				(0<<1) |					//'0'-> update enabled
				(0<<0);						//counter disabled
	//TIMx->CR2 = 0;							//default value
	//TIMx->SMCR = 0;							//default value
	//TIMx->ETR = 0;							//'0'->external trigger not inverted
	
	TIM4->PSCR = TIM4_PSCR_PSC & 0x04;		//set up the prescaler - 0x07->128:1, 0x06->64:1, 0x04->16:1
	TIM4->CNTR = 0; 						//TIMx->CNTRL = 0;			//reset the counter
	TIM4->ARR = -1;							//load up the auto reload register - msb first
	
	TIM4->SR1&=~(1<<0);						//clear UIF
	TIM4->IER|= (1<<0);						//'1'->enable overflow interrupt, '0'->disable interrupt

	//re-enable the counter
	TIM4->CR1 |= (1<<0);	

//configure TIM1/CCP1..4
#if defined(USE_T1CCP1) || defined(USE_T1CCP2) || defined(USE_T1CCP3) || defined(USE_T1CCP4)
	//configure the time base: as counter, top at CxCCP_PR-1
	//enable the clock to peripheral
	CLK->PCKENR1 |= CLK_PCKENR1_TIM1;			//'1'=clock enabled, '0'=clock disabled

	//stop the timer
	TIM1->CR1 &=~(1<<0);					//stop the timer
	
	//set up the timer
	TIM1->CR1 = (1<<7) |					//'1'->enable auto reload buffer
	  			(0<<5) |					//'0'->edge aligned. 1..3->center aligned
				(0<<4) |					//'0'->up counter, '1' downcounter
				(0<<3) |					//'0'->continuous mode, '1'->one pulse mode
				(0<<2) |					//'0'-> update enable source
				(0<<1) |					//'0'-> update enabled
				(0<<0);						//'0'->counter disabled
	TIM1->CR2 = 0;							//default value
	TIM1->SMCR = 0;							//default value
	TIM1->ETR = 0;							//'0'->external trigger not inverted
	
	TIM1->PSCRH = (TxCCP_PS-1) >> 8; TIM1->PSCRL = (TxCCP_PS-1);	//set up the prescaler - msb first
	TIM1->ARRH  = (TxCCP_PR-1) >> 8; TIM1->ARRL  = (TxCCP_PR-1);	//load up the auto reload register - msb first
	TIM1->CNTRH = 0; TIM1->CNTRL = 0;			//reset the counter
	
	TIM1->SR1&=~(0xff);						//clear UIF
	TIM1->IER&=~(0xff);						//'1'->enable overflow interrupt, '0'->disable interrupt

	//configure output compare
#if defined(USE_T1CCP1) && defined(TIM1_CCMR1_RESET_VALUE)
	TIM1->CCMR1 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(7<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM1->CCER1 = 	(TIM1->CCER1 &~0x0f) |
					(0<<3) |				//1->CC1N active high, 0->CC1N active low
					(0<<2) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<1) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<0) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM1->CCR1H = TIM1->CCR1L = 0;			//0%duty cycle
#endif
	
#if defined(USE_T1CCP2) && defined(TIM1_CCMR2_RESET_VALUE)
	TIM1->CCMR2 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(7<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM1->CCER1 = 	(TIM1->CCER1 &~0xf0) |
					(0<<7) |				//1->CC1N active high, 0->CC1N active low
					(0<<6) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<5) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<4) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM1->CCR2H = TIM1->CCR2L = 0;			//0%duty cycle
#endif
	
#if defined(USE_T1CCP3) && defined(TIM1_CCMR3_RESET_VALUE)
	TIM1->CCMR3 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(7<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM1->CCER2 = 	(TIM1->CCER2 &~0x0f) |
					(0<<3) |				//1->CC1N active high, 0->CC1N active low
					(0<<2) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<1) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<0) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM1->CCR3H = TIM1->CCR3L = 0;			//0%duty cycle
#endif
	
#if defined(USE_T1CCP4)  && defined(TIM1_CCMR4_RESET_VALUE)
	TIM1->CCMR4 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(7<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM1->CCER2 = 	(TIM1->CCER2 &~0xf0) |
					(0<<7) |				//1->CC1N active high, 0->CC1N active low
					(0<<6) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<5) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<4) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM1->CCR4H = TIM1->CCR4L = 0;			//0%duty cycle
#endif
	
	TIM1->BKR |= (1<<7);					//1->set main-output-enable bit, 0->reset MOE (main-output-enable) bit
	//re-enable the counter
	TIM1->CR1 |= (1<<0);	

#endif
	
//configure TIM2/CCP1..4
#if defined(USE_T2CCP1) || defined(USE_T2CCP2) || defined(USE_T2CCP3) || defined(USE_T2CCP4)
	//configure the time base: as counter, top at CxCCP_PR-1
	//enable the clock to peripheral
	CLK->PCKENR1 |= CLK_PCKENR1_TIM2;			//'1'=clock enabled, '0'=clock disabled

	//stop the timer
	TIM2->CR1 &=~(1<<0);					//stop the timer
	
	//set up the timer
	TIM2->CR1 = (1<<7) |					//'1'->enable auto reload buffer
	  			(0<<5) |					//'0'->edge aligned. 1..3->center aligned
				(0<<4) |					//'0'->up counter, '1' downcounter
				(0<<3) |					//'0'->continuous mode, '1'->one pulse mode
				(0<<2) |					//'0'-> update enable source
				(0<<1) |					//'0'-> update enabled
				(0<<0);						//'0'->counter disabled
	//TIM2->CR2 = 0;							//default value
	//TIM2->SMCR = 0;							//default value
	//TIM2->ETR = 0;							//'0'->external trigger not inverted
	
	/*TIM2->PSCRH = (TxCCP_PS-1) >> 8; */TIM2->PSCR/*L*/ = (TxCCP_PS-1);	//set up the prescaler - msb first
	TIM2->ARRH  = (TxCCP_PR-1) >> 8; TIM2->ARRL  = (TxCCP_PR-1);	//load up the auto reload register - msb first
	TIM2->CNTRH = 0; TIM2->CNTRL = 0;			//reset the counter
	
	TIM2->SR1&=~(0xff);						//clear UIF
	TIM2->IER&=~(0xff);						//'1'->enable overflow interrupt, '0'->disable interrupt

	//configure output compare
#if defined(USE_T2CCP1) && defined(TIM2_CCMR1_RESET_VALUE)
	TIM2->CCMR1 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM2->CCER1 = 	(TIM2->CCER1 &~0x0f) |
					(0<<3) |				//1->CC1N active high, 0->CC1N active low
					(0<<2) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<1) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<0) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM2->CCR1H = TIM2->CCR1L = 0;			//0%duty cycle
#endif
	
#if defined(USE_T2CCP2) && defined(TIM2_CCMR2_RESET_VALUE)
	TIM2->CCMR2 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM2->CCER1 = 	(TIM2->CCER1 &~0xf0) |
					(0<<7) |				//1->CC1N active high, 0->CC1N active low
					(0<<6) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<5) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<4) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM2->CCR2H = TIM2->CCR2L = 0;			//0%duty cycle
#endif
	
#if defined(USE_T2CCP3) && defined(TIM2_CCMR3_RESET_VALUE)
	TIM2->CCMR3 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM2->CCER2 = 	(TIM2->CCER2 &~0x0f) |
					(0<<3) |				//1->CC1N active high, 0->CC1N active low
					(0<<2) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<1) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<0) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM2->CCR3H = TIM2->CCR3L = 0;			//0%duty cycle
#endif
	
#if defined(USE_T2CCP4) && defined(TIM2_CCMR4_RESET_VALUE)
	TIM2->CCMR4 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM2->CCER2 = 	(TIM2->CCER2 &~0xf0) |
					(0<<7) |				//1->CC1N active high, 0->CC1N active low
					(0<<6) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<5) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<4) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM2->CCR4H = TIM2->CCR4L = 0;			//0%duty cycle
#endif
	//TIM2->BKR |= (1<<7);					//1->set main-output-enable bit, 0->reset MOE (main-output-enable) bit
	//re-enable the counter
	TIM2->CR1 |= (1<<0);	

#endif
	
//configure TIM3/CCP1..4
#if defined(USE_T3CCP1) || defined(USE_T3CCP2) || defined(USE_T3CCP3) || defined(USE_T3CCP4)
	//configure the time base: as counter, top at CxCCP_PR-1
	//enable the clock to peripheral
	CLK->PCKENR1 |= CLK_PCKENR1_TIM3;			//'1'=clock enabled, '0'=clock disabled

	//stop the timer
	TIM3->CR1 &=~(1<<0);					//stop the timer
	
	//set up the timer
	TIM3->CR1 = (1<<7) |					//'1'->enable auto reload buffer
	  			(0<<5) |					//'0'->edge aligned. 1..3->center aligned
				(0<<4) |					//'0'->up counter, '1' downcounter
				(0<<3) |					//'0'->continuous mode, '1'->one pulse mode
				(0<<2) |					//'0'-> update enable source
				(0<<1) |					//'0'-> update enabled
				(0<<0);						//'0'->counter disabled
	//TIM3->CR2 = 0;							//default value
	//TIM3->SMCR = 0;							//default value
	//TIM3->ETR = 0;							//'0'->external trigger not inverted
	
	/*TIM3->PSCRH = (TxCCP_PS-1) >> 8;*/ TIM3->PSCR/*L*/ = (TxCCP_PS-1);	//set up the prescaler - msb first
	TIM3->ARRH  = (TxCCP_PR-1) >> 8; TIM3->ARRL  = (TxCCP_PR-1);	//load up the auto reload register - msb first
	TIM3->CNTRH = 0; TIM3->CNTRL = 0;			//reset the counter
	
	TIM3->SR1&=~(0xff);						//clear UIF
	TIM3->IER&=~(0xff);						//'1'->enable overflow interrupt, '0'->disable interrupt

	//configure output compare
#if defined(USE_T3CCP1) && defined(TIM3_CCMR1_RESET_VALUE)
	TIM3->CCMR1 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM3->CCER1 = 	(TIM3->CCER1 &~0x0f) |
					(0<<3) |				//1->CC1N active high, 0->CC1N active low
					(0<<2) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<1) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<0) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM3->CCR1H = TIM3->CCR1L = 0;			//0%duty cycle
#endif
	
#if defined(USE_T3CCP2) && defined(TIM3_CCMR2_RESET_VALUE)
	TIM3->CCMR2 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM3->CCER1 = 	(TIM3->CCER1 &~0xf0) |
					(0<<7) |				//1->CC1N active high, 0->CC1N active low
					(0<<6) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<5) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<4) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM3->CCR2H = TIM3->CCR2L = 0;			//0%duty cycle
#endif
	
#if defined(USE_T3CCP3) && defined(TIM3_CCMR3_RESET_VALUE)
	TIM3->CCMR3 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM3->CCER2 = 	(TIM3->CCER2 &~0x0f) |
					(0<<3) |				//1->CC1N active high, 0->CC1N active low
					(0<<2) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<1) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<0) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM3->CCR3H = TIM3->CCR3L = 0;			//0%duty cycle
#endif
	
#if defined(USE_T3CCP4) && defined(TIM3_CCMR4_RESET_VALUE)
	TIM3->CCMR4 = 	(0<<7) |				//1->clear enabled; 0->clear not enabled
					(6<<4) |				//6->pwm mode 1, 7->pwm mode 2
					(1<<3) |				//0->output preload disabled, 1->output preload enabled
					(0<<2) |				//0->normal operation, 1->enabled output compare fast
					(0<<0) |				//0->output compare as output pin, 1->CC1 as input, 2->CC! as input, 3->CC1 as input
					0x00;
	TIM3->CCER2 = 	(TIM3->CCER2 &~0xf0) |
					(0<<7) |				//1->CC1N active high, 0->CC1N active low
					(0<<6) |				//1->CC1N enabled, 0->CC1N disabled
					(1<<5) |				//0->CC1 normal polarity, 1->CC1 reverse polarity
					(1<<4) |				//1->enable CC1, 0->disable CC1
					0x00;
	TIM3->CCR4H = TIM3->CCR4L = 0;			//0%duty cycle
#endif
	//TIM3->BKR |= (1<<7);					//1->set main-output-enable bit, 0->reset MOE (main-output-enable) bit
	//re-enable the counter
	TIM3->CR1 |= (1<<0);	

#endif
	
	//timer0 is running now
	enableInterrupts();						//enable interrupts globally
}

//return ticks
uint32_t ticks(void) {
	uint32_t m;							//hold overflow count
	uint8_t f;							//hold timer counter - TIMER0 is 8-bit wide

	//perform a double read
	do {
		m = timer_ticks;
		f = TIM4->CNTR;
	} while (m != timer_ticks);			//keep reading until m/f are atomic
	return m | f;						//form the ticks
}

//return time in microseconds
uint32_t micros(void) {
	//return ticks() / (F_CPU / 1000000ul) * 16;		//calculate micro seconds
	return ticks() << 0;								//16:1 prescaler @ 16Mhz F_CPU
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
		case OUTPUT:		IO_OUT(gpio, mask); break;
		case INPUT_PULLUP:	IO_INPU(gpio, mask); break;
		case INPUT:
		default:			IO_IN(gpio, mask); break;
	}
}

//set pin high/low
void digitalWrite(PIN_T pin, uint8_t state) {
	GPIO_TypeDef *gpio;
	uint8_t mask;

	if (pin>=DMAX) return;				//invalid pin
	gpio=GPIO_PinDef[pin].gpio;							//get gpio address
	mask=GPIO_PinDef[pin].mask;
	if (state == LOW) IO_CLR(gpio, mask); else IO_SET(gpio, mask);
	//if (state) IO_SET(gpio, mask); else IO_CLR(gpio, mask);
}

//read pin state
int digitalRead(PIN_T pin) {
	GPIO_TypeDef *gpio;
	uint8_t mask;

	if (pin>=DMAX) return -1;							//invalid pin
	gpio=GPIO_PinDef[pin].gpio;							//get gpio address
	mask=GPIO_PinDef[pin].mask;
	return IO_GET(gpio, mask)?HIGH:LOW;
}

//analogWrite / pwm output
void analogWrite(PIN_T pin, uint16_t dc) {
	switch (pin) {
	//T1CCP1..4
#if defined(USE_T1CCP1)
	case PC1: pinMode(pin, OUTPUT); TIM1->CCR1H = dc >> 8; TIM1->CCR1L = dc; break;	//PC1=T1CC1
#endif
#if defined(USE_T1CCP2)
	case PC2: pinMode(pin, OUTPUT); TIM1->CCR2H = dc >> 8; TIM1->CCR2L = dc; break;	//PC2=T1CC2
#endif
#if defined(USE_T1CCP3)
	case PC3: pinMode(pin, OUTPUT); TIM1->CCR3H = dc >> 8; TIM1->CCR3L = dc; break;	//PC3=T1CC3
#endif
#if defined(USE_T1CCP4)
	case PC4: pinMode(pin, OUTPUT); TIM1->CCR4H = dc >> 8; TIM1->CCR4L = dc; break;	//PC4=T1CC4
#endif

	//T2CCP1..4
#if defined(USE_T2CCP1)
	case PD4: pinMode(pin, OUTPUT); TIM2->CCR1H = dc >> 8; TIM2->CCR1L = dc; break;	//PD4=T2CC1
#endif
#if defined(USE_T2CCP2)
	case PD3: pinMode(pin, OUTPUT); TIM2->CCR2H = dc >> 8; TIM2->CCR2L = dc; break;	//PD3=T2CC2
#endif
#if defined(USE_T2CCP3)
	case PA3: pinMode(pin, OUTPUT); TIM2->CCR3H = dc >> 8; TIM2->CCR3L = dc; break;	//PA3=T2CC3
#endif
#if defined(USE_T2CCP4)
	//case PC4: pinMode(pin, OUTPUT); TIM2->CCR4H = dc >> 8; TIM2->CCR4L = dc; break;	//PC4=T2CC4
#endif
	
	//T3CCP1..4
#if defined(USE_T3CCP1)
	case PD2: pinMode(pin, OUTPUT); TIM3->CCR1H = dc >> 8; TIM3->CCR1L = dc; break;	//PD2=T3CC1
#endif
#if defined(USE_T3CCP2)
	case PD0: pinMode(pin, OUTPUT); TIM3->CCR2H = dc >> 8; TIM3->CCR2L = dc; break;	//PD0=T3CC2
#endif
#if defined(USE_T3CCP3)
	//case PA3: pinMode(pin, OUTPUT); TIM3->CCR3H = dc >> 8; TIM3->CCR3L = dc; break;	//PA3=T3CC3
#endif
#if defined(USE_T3CCP4)
	//case PC4: pinMode(pin, OUTPUT); TIM3->CCR4H = dc >> 8; TIM3->CCR4L = dc; break;	//PC4=T3CC4
#endif
	
	//T5CCP1..4, if available
	
	}
}
