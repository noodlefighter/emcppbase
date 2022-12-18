#ifndef _Arduino_H_INCLUDED
#define _Arduino_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// #include "embase_arduino_board.h"

extern "C" {

/**
 * Specifies a GPIO pin behavior.
 * @see pinMode()
 */
typedef enum WiringPinMode {
    OUTPUT, /**< Basic digital output: when the pin is HIGH, the
               voltage is held at +3.3v (Vcc) and when it is LOW, it
               is pulled down to ground. */

    OUTPUT_OPEN_DRAIN, /**< In open drain mode, the pin indicates
                          "low" by accepting current flow to ground
                          and "high" by providing increased
                          impedance. An example use would be to
                          connect a pin to a bus line (which is pulled
                          up to a positive voltage by a separate
                          supply through a large resistor). When the
                          pin is high, not much current flows through
                          to ground and the line stays at positive
                          voltage; when the pin is low, the bus
                          "drains" to ground with a small amount of
                          current constantly flowing through the large
                          resistor from the external supply. In this
                          mode, no current is ever actually sourced
                          from the pin. */

    INPUT, /**< Basic digital input. The pin voltage is sampled; when
              it is closer to 3.3v (Vcc) the pin status is high, and
              when it is closer to 0v (ground) it is low. If no
              external circuit is pulling the pin voltage to high or
              low, it will tend to randomly oscillate and be very
              sensitive to noise (e.g., a breath of air across the pin
              might cause the state to flip). */

    INPUT_ANALOG, /**< This is a special mode for when the pin will be
                     used for analog (not digital) reads.  Enables ADC
                     conversion to be performed on the voltage at the
                     pin. */

    INPUT_PULLUP, /**< The state of the pin in this mode is reported
                     the same way as with INPUT, but the pin voltage
                     is gently "pulled up" towards +3.3v. This means
                     the state will be high unless an external device
                     is specifically pulling the pin down to ground,
                     in which case the "gentle" pull up will not
                     affect the state of the input. */

    INPUT_PULLDOWN, /**< The state of the pin in this mode is reported
                       the same way as with INPUT, but the pin voltage
                       is gently "pulled down" towards 0v. This means
                       the state will be low unless an external device
                       is specifically pulling the pin up to 3.3v, in
                       which case the "gentle" pull down will not
                       affect the state of the input. */

    INPUT_FLOATING, /**< Synonym for INPUT. */

    // PWM, /**< This is a special mode for when the pin will be used for
    //         PWM output (a special case of digital output). */

    // PWM_OPEN_DRAIN, /**< Like PWM, except that instead of alternating
    //                    cycles of LOW and HIGH, the voltage on the pin
    //                    consists of alternating cycles of LOW and
    //                    floating (disconnected). */
} WiringPinMode;

/**
 * Configure behavior of a GPIO pin.
 *
 * @param pin Number of pin to configure.
 * @param mode Mode corresponding to desired pin behavior.
 * @see WiringPinMode
 */
void pinMode(uint8_t pin, WiringPinMode mode);

void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);

uint32_t millis(void);
uint32_t micros(void);

void delay(unsigned long ms);
void delayMicroseconds(unsigned int us);

} // extern "C"

#define HIGH 0x1
#define LOW  0x0

// #define INPUT 0x0
// #define OUTPUT 0x1
// #define INPUT_PULLUP 0x2

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3



#include <atomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define SPI_MODE_MASTER 0
#define HZ 1000

// #define min(a, b) (((a) < (b)) ? (a) : (b))
typedef bool boolean;

#endif
