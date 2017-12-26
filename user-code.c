#include "xduino.h"								//include xduino defs

#define LED		D21								//D21 = RC5

//user setup
void setup(void) {
	pinMode(LED, OUTPUT);
}

void loop(void) {
	digitalWrite(LED, !digitalRead(LED));		//32.6Khz@O0, $90.1Khz@O3
	delay(10);
}
