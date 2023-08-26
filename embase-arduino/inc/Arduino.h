#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// #include "embase_arduino_board.h"

#ifdef HIGH
    #undef HIGH
    #warning override HIGH!!
#endif
#define HIGH 0x1

#ifdef LOW
    #undef LOW
    #warning override LOW!!
#endif
#define LOW  0x0

#ifdef PI
    #undef PI
    #warning override PI!!
#endif
#define PI 3.1415926535897932384626433832795

#ifdef HALF_PI
    #undef HALF_PI
    #warning override HALF_PI!!
#endif
#define HALF_PI 1.5707963267948966192313216916398

#ifdef TWO_PI
    #undef TWO_PI
    #warning override TWO_PI!!
#endif
#define TWO_PI 6.283185307179586476925286766559

#ifdef DEG_TO_RAD
    #undef DEG_TO_RAD
    #warning override DEG_TO_RAD!!
#endif
#define DEG_TO_RAD 0.017453292519943295769236907684886

#ifdef RAD_TO_DEG
    #undef RAD_TO_DEG
    #warning override RAD_TO_DEG!!
#endif
#define RAD_TO_DEG 57.295779513082320876798154814105

#ifdef EULER
    #undef EULER
    #warning override EULER!!
#endif
#define EULER 2.718281828459045235360287471352

#ifdef SERIAL
    #undef SERIAL
    #warning override SERIAL!!
#endif
#define SERIAL  0

#ifdef DISPLAY
    #undef DISPLAY
    #warning override DISPLAY!!
#endif
#define DISPLAY 1

#ifdef LSBFIRST
    #undef LSBFIRST
    #warning override LSBFIRST!!
#endif
#define LSBFIRST 0

#ifdef MSBFIRST
    #undef MSBFIRST
    #warning override MSBFIRST!!
#endif
#define MSBFIRST 1

#ifdef CHANGE
    #undef CHANGE
    #warning override CHANGE!!
#endif
#define CHANGE 1

#ifdef FALLING
    #undef FALLING
    #warning override FALLING!!
#endif
#define FALLING 2

#ifdef RISING
    #undef RISING
    #warning override RISING!!
#endif
#define RISING 3

#ifdef HZ
    #undef HZ
    #warning override HZ!!
#endif
#define HZ 1000

// #ifndef min
// #define min(a, b) (((a) < (b)) ? (a) : (b))
// #endif

#ifdef PIN_NC
    #undef PIN_NC
    #warning override PIN_NC!!
#endif
#define PIN_NC 255

typedef bool boolean;

typedef enum WiringPinMode {
    OUTPUT,
    OUTPUT_OPEN_DRAIN,
    INPUT,
    INPUT_ANALOG,
    INPUT_PULLUP,
    INPUT_PULLDOWN,
    INPUT_FLOATING,
    PWM,
    PWM_OPEN_DRAIN,
} WiringPinMode;

extern "C" {

// note: 需要用户在板级实现
void pinMode(uint8_t pin, WiringPinMode mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);

// note: 由embase-arduino实现
uint32_t millis(void);
uint32_t micros(void);
void delay(unsigned long ms);
void delayMicroseconds(unsigned int us);
}

#include <stddef.h>
#include <atomic.h>
#include <stdio.h>
#include <string.h>
