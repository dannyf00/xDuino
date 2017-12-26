#include "xduino.h"								//we use aruidno port for stm8s

//user-supplied code prototype
//global definitions

//global variables

//delay a number of ticks
void delayTicks(uint32_t tks) {
	uint32_t start_ticks = ticks();

	while (ticks() - start_ticks < tks ) continue;
}

//delay milliseconds
void delay(uint32_t ms) {
	uint32_t start_time = millis();

	while (millis() - start_time < ms) continue;	//wait until desired time runs out
}

//delay micro seconds
void delayMicroseconds(uint32_t us) {
	uint32_t start_time = micros();

	while (micros() - start_time < us) continue;	//wait until desired time runs out
}
//end Time


//Arduino Functions: Advanced IO
//shift in - from arduino code base / not optimized
uint8_t shiftIn(PIN_T dataPin, PIN_T clockPin, uint8_t bitOrder) {
	uint8_t value = 0;
	uint8_t i;

	for (i = 0; i < 8; ++i) {
		digitalWrite(clockPin, HIGH);
		if (bitOrder == LSBFIRST)
			value |= digitalRead(dataPin) << i;
		else
			value |= digitalRead(dataPin) << (7 - i);
		digitalWrite(clockPin, LOW);
	}
	return value;
}

//shift out - from arduino code base / not optimized
void shiftOut(PIN_T dataPin, PIN_T clockPin, uint8_t bitOrder, uint8_t val) {
	uint8_t i;

	for (i = 0; i < 8; i++)  {
		if (bitOrder == LSBFIRST)
			digitalWrite(dataPin, !!(val & (1 << i)));
		else
			digitalWrite(dataPin, !!(val & (1 << (7 - i))));

		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);
	}
}

//wait for a pulse and return timing
uint32_t pulseIn(PIN_T pin, uint8_t state) {
	uint32_t tmp;
	uint8_t state1;
	state = (state == LOW)?LOW:HIGH;
	state1= (state == LOW)?HIGH:LOW;
	while (digitalRead(pin) == state) continue;		//wait for the pin to opposite
	//now pin is _state
	tmp = micros();
	//state = (state == LOW)?HIGH:LOW;				//calculate the state to end the wait
	while (digitalRead(pin) == state1) continue;	//wait for the pin to go back to its original state
	tmp = micros() - tmp;							//calculate the pulse width
	return tmp;
}

//end Advanced IO

//stylized code for main()
int main(void) {
	mcu_init();							//reset the chip
	setup();							//user-set up the code
	while (1) {
		loop();							//user specified loop
	}
	return 0;
}
