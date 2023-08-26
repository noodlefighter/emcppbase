#include "SoftwareSPI.h"

SoftwareSPI::SoftwareSPI()
  : SoftwareSPI(PIN_NC, PIN_NC, PIN_NC, PIN_NC)
{
}
SoftwareSPI::SoftwareSPI(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss)
  : _mode(SPI_MODE0), _bitOrder(MSBFIRST)
{
  init(sck, miso, mosi, ss);
}

void SoftwareSPI::init(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss)
{
  _sck = sck;
  _miso = miso;
  _mosi = mosi;
  _ss = ss;
}

void SoftwareSPI::begin()
{
  beginTransaction(SPISettings());
}

void SoftwareSPI::beginTransaction(SPISettings settings)
{
  pinMode(_ss, OUTPUT);
  pinMode(_sck, OUTPUT);
  pinMode(_miso, INPUT);
  pinMode(_mosi, OUTPUT);

  digitalWrite(_ss, LOW);
  digitalWrite(_sck, LOW);
  digitalWrite(_mosi, LOW);
}
void SoftwareSPI::endTransaction(void)
{
  digitalWrite(_ss, HIGH);
}

void SoftwareSPI::end()
{
  endTransaction();
}

void SoftwareSPI::setBitOrder(uint8_t bitOrder)
{
  _bitOrder = bitOrder;
}

void SoftwareSPI::setDataMode(SPIMode mode)
{
  _mode = mode;
}

uint8_t SoftwareSPI::transfer(uint8_t data)
{
  uint8_t out = 0;

  if (_bitOrder == MSBFIRST) {
    data = reverseBits(data);
  }

  digitalWrite(_ss, LOW);

  for (int8_t bit = 7; bit >= 0; --bit) {
    digitalWrite(_mosi, (data >> bit) & 0x01);

    if (_mode == SPI_MODE0 || _mode == SPI_MODE2) {
      digitalWrite(_sck, LOW);
      delayMicroseconds(1);
      digitalWrite(_sck, HIGH);
    } else {
      digitalWrite(_sck, HIGH);
      delayMicroseconds(1);
      digitalWrite(_sck, LOW);
    }

    if (_mode == SPI_MODE0 || _mode == SPI_MODE1) {
      out |= (digitalRead(_miso) << bit);
    } else {
      out |= (digitalRead(_miso) << (7 - bit));
    }
  }

  digitalWrite(_ss, HIGH);

  if (_bitOrder == MSBFIRST) {
    out = reverseBits(out);
  }

  return out;
}

uint16_t SoftwareSPI::transfer16(uint16_t data)
{
  union {
    uint16_t val;
    struct {
      uint8_t lsb;
      uint8_t msb;
    };
  } in, out;

  in.val = data;

  if (_bitOrder == MSBFIRST) {
    out.msb = transfer(in.msb);
    out.lsb = transfer(in.lsb);
  }
  else {
    out.lsb = transfer(in.lsb);
    out.msb = transfer(in.msb);
  }
  return out.val;
}

void SoftwareSPI::transfer(const void *buf, size_t count)
{
  for (size_t i = 0; i < count; ++i) {
    transfer(((uint8_t*)buf)[i]);
  }
}

uint8_t SoftwareSPI::reverseBits(uint8_t data)
{
  uint8_t reversed = 0;

  for (int8_t i = 0; i < 8; ++i) {
    reversed <<= 1;
    reversed |= (data & 0x01);
    data >>= 1;
  }

  return reversed;
}
