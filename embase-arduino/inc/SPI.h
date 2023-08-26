#pragma once
#include <Arduino.h>

typedef enum
{
  SPI_MODE0 = 0,
  SPI_MODE1,
  SPI_MODE2,
  SPI_MODE3
} SPIMode;

class SPISettings
{
public:
  SPISettings(uint32_t speedMaximum, uint8_t bitOrder, uint8_t dataMode)
  {
    //todo:
  }
  SPISettings()
  {
    SPISettings(4000000, MSBFIRST, SPI_MODE0);
  }
private:
  friend class SPIClass;
};

class SPIClass
{
public:
  virtual void begin() = 0;
  virtual void beginTransaction(SPISettings settings) = 0;
  virtual void endTransaction(void) = 0;
  virtual void end() = 0;

  // deprecated, beginTransaction() instead
  virtual void setBitOrder(uint8_t bitOrder)
  {
    (void) bitOrder;
  }
  // deprecated, beginTransaction() instead
  virtual void setClockDivider(uint8_t clockDiv)
  {
    (void) clockDiv;
  }
  // deprecated, beginTransaction() instead
  virtual void setDataMode(SPIMode dataMode)
  {
    (void) dataMode;
  }

  // Write to the SPI bus (MOSI pin) and also receive (MISO pin)
  virtual uint8_t transfer(uint8_t data) = 0;
  virtual uint16_t transfer16(uint16_t data) = 0;
  virtual void transfer(const void *buf, size_t count) = 0;

  virtual void usingInterrupt(uint8_t interruptNumber)
  {
    (void)interruptNumber;
  }
  virtual void notUsingInterrupt(uint8_t interruptNumber)
  {
    (void)interruptNumber;
  }
};
