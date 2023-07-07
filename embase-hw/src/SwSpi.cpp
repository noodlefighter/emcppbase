#include "SwSpi.h"
#include "embase_platform.h"

void SwSpi::init(uint8_t ss, uint8_t sck, uint8_t mosi, uint8_t miso)
{
  _pin_ss = ss;
  _pin_mosi = mosi;
  _pin_miso = miso;
  _pin_sck = sck;
  _delay = 2;
  _cke = 0;
  _ckp = 0;
  _bit_order = MSBFIRST;

  pinMode(_pin_mosi, OUTPUT);
  pinMode(_pin_miso, INPUT_PULLUP);
  pinMode(_pin_sck, OUTPUT);
  pinMode(_pin_ss, OUTPUT);
  // log_output_fn(true,"init",_delay);
}

void SwSpi::setBitOrder(uint8_t order)
{
  _bit_order = order & 1;
}

void SwSpi::setDataMode(SwSpiMode mode)
{
  switch (mode) {
  case SwSpiMode::SPI_MODE0:
    _ckp = 0;
    _cke = 0;
    break;
  case SwSpiMode::SPI_MODE1:
    _ckp = 0;
    _cke = 1;
    break;
  case SwSpiMode::SPI_MODE2:
    _ckp = 1;
    _cke = 0;
    break;
  case SwSpiMode::SPI_MODE3:
    _ckp = 1;
    _cke = 1;
    break;
  }

  digitalWrite(_pin_sck, _ckp ? HIGH : LOW);
}

uint8_t SwSpi::transfer(uint8_t val)
{
  uint8_t out = 0;

  // log_output_fn(true,"spi8:in");
  // uint32_t cpu_stat = enter_critical();

  if (_bit_order == MSBFIRST) {
    uint8_t v2 =
        ((val & 0x01) << 7) |
        ((val & 0x02) << 5) |
        ((val & 0x04) << 3) |
        ((val & 0x08) << 1) |
        ((val & 0x10) >> 1) |
        ((val & 0x20) >> 3) |
        ((val & 0x40) >> 5) |
        ((val & 0x80) >> 7);
    val = v2;
  }

  uint8_t del = _delay >> 1;

  // log_output_fn(true,"spi8:del=%d(%d)",del,_delay);

  uint8_t bval = 0;
  int sck = (_ckp) ? HIGH : LOW;

  for (uint8_t bit = 0u; bit < 8u; bit++) {
    if (_cke) {
      sck ^= 1;
      digitalWrite(_pin_sck, sck);
      embase::__usleep(del);
    }

    // ... Write bit
    digitalWrite(_pin_mosi, ((val & (1 << bit)) ? HIGH : LOW));

    // log_output_fn(true,"spi8:embase::__usleep(%d)1",_delay);
    embase::__usleep(del);
    // log_output_fn(true,"spi8:embase::__usleep(%d)2",_delay);

    sck ^= 1u;
    digitalWrite(_pin_sck, sck);

    // ... Read bit
    {
      bval = digitalRead(_pin_miso);

      if (_bit_order == MSBFIRST) {
        out <<= 1;
        out |= bval;
      }
      else {
        out >>= 1;
        out |= bval << 7;
      }
    }

    embase::__usleep(del);

    if (!_cke) {
      sck ^= 1u;
      digitalWrite(_pin_sck, sck);
    }
  }

  // log_output_fn(true,"transfer(%2x)->%2x\r\n",val,out);
  // exit_critical(cpu_stat);
  // log_output_fn(true,"spi8:out");

  return out;
}

uint16_t SwSpi::transfer16(uint16_t data)
{
  // log_output_fn(true,"spi16:");

  union {
    uint16_t val;
    struct {
      uint8_t lsb;
      uint8_t msb;
    };
  } in, out;

  in.val = data;

  if (_bit_order == MSBFIRST) {
    out.msb = transfer(in.msb);
    out.lsb = transfer(in.lsb);
  }
  else {
    out.lsb = transfer(in.lsb);
    out.msb = transfer(in.msb);
  }

  return out.val;
}
