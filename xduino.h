//xduino port for generic mcus
//version: v0.10 @ 12/25/2017 on ATmega
//Supported functions:
//GPIO: pinMode(), digitalWrite(), digitalRead(), via chip-specific files
//Time: ticks(), millis(), micros(), delayTicks(), delay()/delayMillis()/delayMilliseconds(), delayMicros()/delayMicroseconds()
//Math: min(), max(), abs(), constrain(), map(), pow(), sqrt()
//Trigonometry: sin(), cos(), tan()
//Characters: isAlphaNumeric(), isAlpha(), isAscii(), isWhitespace(), isControl(), isDigit(), isGraph(), isLowerCase(), isPrintable, isPunct(), isSpace(), isUpperCase(), isHexadecimalDigit()
//Random Numbers: randomSeed(), random(max). random(min, max) ported to random2(min, max)
//Bits and Bytes: lowByte(), highByte(), bitRead(), bitWrite(), bitSet(), bitClear(), bit()

#ifndef _xduino_H
#define _xduino_H

#include <stdlib.h>							//we use rand()
#include <stdint.h>							//we use uint types
#include "boards.h"							//we use board-specific definitions

//global defines
//F_CPU defined in boards.h
//NOP() defined in boards.h
#define NOP2()					{NOP(); NOP();}
#define NOP4()					{NOP2(); NOP2();}
#define NOP8()					{NOP4(); NOP4();}
#define NOP16()					{NOP8(); NOP8();}
#define NOP16()					{NOP8(); NOP8();}
#define NOP24()					{NOP16(); NOP8();}
#define NOP32()					{NOP16(); NOP16();}
#define NOP40()					{NOP32(); NOP8();}
#define NOP64()					{NOP32(); NOP32();}

//arduino-specific defs
#define INPUT				0									//gpio input, floating
#define OUTPUT				1									//gpio output, pushpull
#define INPUT_PULLUP		2									//input with pull-up
//additional defs in device specific file

#define LOW					0
#define HIGH				1									//(!LOW)

#define PI 					3.1415926535897932384626433832795
#define HALF_PI 			(PI / 2)							//1.5707963267948966192313216916398
#define TWO_PI 				(PI + PI)							//6.283185307179586476925286766559
#define DEG_TO_RAD 			(TWO_PI / 360)						//0.017453292519943295769236907684886
#define RAD_TO_DEG 			(360 / TWO_PI)						//57.295779513082320876798154814105
#define EULER 				2.718281828459045235360287471352	//Euler's number

#define LSBFIRST 			0
#define MSBFIRST 			1									//(!LSBFIRST)							//1

#define CHANGE 				0x01
#define FALLING 			0x02
#define RISING 				0x03

#ifndef min
  #define min(a,b) 			((a)<(b)?(a):(b))
#endif
#ifndef max
#define max(a,b) 			((a)>(b)?(a):(b))
#endif
#ifndef abs
#define abs(x) 				((x)>0?(x):-(x))
#endif
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     		((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) 		((deg)*DEG_TO_RAD)
#define degrees(rad) 		((rad)*RAD_TO_DEG)
#define sq(x) 				((x)*(x))

//interrupts()/noInterrupts() defined in boards.h
//#define interrupts() 		ei()
//#define noInterrupts() 		di()

#define clockCyclesPerMicrosecond() 	( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) 	( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) 	( (a) * clockCyclesPerMicrosecond() )

#define lowByte(w) 			((uint8_t) ((w) & 0xff))
#define highByte(w) 		((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) 	((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bit(n)				(1ul<<(n))

#define false				0
#define true				(!false)

//characters
#define isAlphaNumeric(c)	isalnum(c)
#define isAlpha(c)			isalpha(c)
#define isAscii(c)			isascii(c)
#define isWhitespace(c)		isblank(c)
#define isControl(c)		iscntrl(c)
#define isDigit(c)			isdigit(c)
#define isGraph(c)			isgraph(c)
#define isLowerCase(c)		islower(c)
#define isPrintable(c)		isprint(c)
#define isPunct(c)			ispunct(c)
#define isSpace(c)			isspace(c)
#define isUpperCase(c)		isupper(c)
#define isHexadecimalDigit(c)	isxdigit(c)

//random number
#define randomSeed(seed)	srand(seed)
#define random(max)			random2(0, max)
#define random2(min, max)	((min) + (int32_t) ((max) - (min)) * rand() / 32768)

//random() will need manual porting

//global variables

//external setup/loop - defined by user
extern void setup(void);
extern void loop(void);

//time base
uint32_t millis(void);
uint32_t micros(void);
uint32_t ticks(void);
//delay a number of ticks
void delayTicks(uint32_t tks);
#define delayMillis(ms)			delayMilliseconds(ms)
#define delayMicros(us)			delayMicroseconds(us)
void delay(uint32_t ms);
void delayMicroseconds(uint32_t us);
#define delayMilliseconds(ms)	delay(ms)

//advanced io
//shiftin/out: bitOrder = MSBFIRST or LSBFIRST
uint8_t shiftIn(PIN_T dataPin, PIN_T clockPin, uint8_t bitOrder);
void shiftOut(PIN_T dataPin, PIN_T clockPin, uint8_t bitOrder, uint8_t val);
//wait for a pulse and return timing
uint32_t pulseIn(PIN_T pin, uint8_t state);

//================chip-specific functions, user-implemented for target chip
//gpio functions - chip-specific
void pinMode(PIN_T pin, uint8_t mode);
void digitalWrite(PIN_T pin, uint8_t mode);
int digitalRead(PIN_T pin);

//analogWrite()/pwm output - chip-specific
void analogWrite(PIN_T pin, uint16_t dc);

//analogRead() - chip-specific
uint16_t analogRead(AIN_T ain);

//Serial IO

//Serial comm
void Serial0_begin(uint32_t baudrate);
void Serial0_println(char *str);
void Serial0_print(char *str);
char Serial0_available(void);
char Serial0_read(void);

void Serial1_begin(uint32_t baudrate);
void Serial1_println(char *str);
void Serial1_print(char *str);
char Serial1_available(void);
char Serial1_read(void);

void Serial2_begin(uint32_t baudrate);
void Serial2_println(char *str);
void Serial2_print(char *str);
char Serial2_available(void);
char Serial2_read(void);

void Serial3_begin(uint32_t baudrate);
void Serial3_println(char *str);
void Serial3_print(char *str);
char Serial3_available(void);
char Serial3_read(void);

//Advanced IO
//tone()
//noTone()

//External Interrupts
void attachInterrupt(PIN_T pin, void (*isrptr)(void), uint8_t mode);
void detachInterrupt(PIN_T pin);

//================end chip-specific functions
#endif
