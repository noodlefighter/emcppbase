#pragma once

#include "SPI.h"

class SoftwareSPI : public SPIClass
{
private:
  uint8_t _sck;
  uint8_t _miso;
  uint8_t _mosi;
  uint8_t _ss;
  SPIMode _mode;
  uint8_t _bitOrder;
public:

  SoftwareSPI();
  SoftwareSPI(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss);

  void init(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss);

  void begin() override;
  void end() override;
  void beginTransaction(SPISettings settings) override;
  void endTransaction(void) override;

  void setBitOrder(uint8_t bitOrder) override;
  void setDataMode(SPIMode mode) override;

  uint8_t transfer(uint8_t data) override;
  uint16_t transfer16(uint16_t data) override;
  void transfer(const void *buf, size_t count) override;

private:
  uint8_t reverseBits(uint8_t data);
};
