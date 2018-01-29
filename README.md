# xDuino
A generic implementation of Arduino on MCUs

Implementing Arduino on a host of MCUs.

Examples provided as of 12/26/2017:

1. AVR: ATmega8, ATmega328
2. PIC: PIC16F193x and PIC18FxxK20
3. 8051: AT89C51
4. PIC24: PIC24FJ32/64GA102/104
5. STM8S105 - should work with other STM8S chips with TIM4
6. STM8S003
7. STM32F030/100/103/303/407 - should work with others STM32 chips

Note:
Support for PIC24FJ32GA102/104 and PIC24FJ64GA102/104 added (tested). Code should also support PIC24FJ16/32/48/64GA002/002 (untested).
Support for STM8 (STM8S105, STM8S003 and STM8S103) added.
[1/28/2018]Support for analogWrite() added for STM8S105/STM8S003, for 9 channels (STM8S105) or 5 channels (STM8S003) of 16-bit PWM. User adjustable resolution / frequency.
[1/28/2018]Support for STM8S103 added, with support for 16-bit analogWrite() on 5 channels (for TSSOP20 packages). This means those el-cheapo $0.99 eBay STM8S103 boards can be used as Arduinon clones.
Support for STM32F030/100/103 added. Should work with other STM32 chips as well.
[12/28/2017]Support for STM32F303/407 chips added;
[12/28/2017]Support for LPC12xx chips added.
[12/28/2017]Support for MSP432 chips added.
[12/28/2017]Support for PIC32MX1/2/3 family of chips added (untested).
[1/20/2018]Support for LPC13xx chips added.
[1/22/2018]Support for LM4F120/TM4C chips added, under CMSIS framework. Can be easily expanded to LM3S devices. A little note on the porting here;
[1/27/2018]analogWrite() supported, generating up to 24-channels of 16-bit PWM output. Resolution user adjustable.
[1/28/2018]Serial0..3 supported added. Additional support for Serial4..7 has been added.
[1/27/2018]Support for LM3S full-line of CM3 chips added, again using the CMSIS framework. For tighter code size. See notes here for changes needed to the start-up file under CCS. No change needed for Keil.
[1/27/2018]Support for MSP430FR5969 added. Adopting it to other MSP430 requires just minor changes.
[1/27/2018]Support for LPC17xx chips added.

More to come
