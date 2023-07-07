#pragma once

#include <Arduino.h>

#define HIGH 0x1
#define LOW 0x0

#define SPI_MODE0 SPI_MODE_0
#define SPI_MODE1 SPI_MODE_1
#define SPI_MODE2 SPI_MODE_2
#define SPI_MODE3 SPI_MODE_3

enum class SwSpiMode {
  //* Clock idles low, data captured on rising edge (first transition)
  SPI_MODE_LOW_RISING = 0,
  //* Clock idles low, data captured on falling edge (second transition)
  SPI_MODE_LOW_FALLING = 1,
  //* Clock idles high, data captured on falling edge (first transition)
  SPI_MODE_HIGH_FALLING = 2,
  //* Clock idles high, data captured on rising edge (second transition)
  SPI_MODE_HIGH_RISING = 3,

  SPI_MODE_0 = SPI_MODE_LOW_RISING,   //*< Same as SPI_MODE_LOW_RISING
  SPI_MODE_1 = SPI_MODE_LOW_FALLING,  //*< Same as SPI_MODE_LOW_FALLING
  SPI_MODE_2 = SPI_MODE_HIGH_FALLING, //*< Same as SPI_MODE_HIGH_FALLING
  SPI_MODE_3 = SPI_MODE_HIGH_RISING,  //*< Same as SPI_MODE_HIGH_RISING
};


class SwSpi {
public:
  void init(uint8_t ss, uint8_t sck, uint8_t mosi, uint8_t miso);

  void setBitOrder(uint8_t order); // LSBFIRST or MSBFIRST
  void setDataMode(SwSpiMode mode);
  uint8_t transfer(uint8_t val);
  uint16_t transfer16(uint16_t data);

private:
  uint8_t _cke;
  uint8_t _ckp;
  uint8_t _delay;
  uint8_t _pin_ss;
  uint8_t _pin_sck;
  uint8_t _pin_miso;
  uint8_t _pin_mosi;
  uint8_t _bit_order = MSBFIRST;
};

