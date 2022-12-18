#pragma once

#include "hw/Screen.h"

namespace embase
{

class ScreenSt7525 : public Screen {
public:
  static const int LCD_HIGHT = 192;
  static const int LCD_WIDTH = 64;

  ScreenSt7525();
  BOOL init();
  BOOL drawRegion(const Rectangle_t &region, const IBuffer_t &buff) override;
protected:
  virtual void _spiWrite(int dc, const UINT8 *data, int size) = 0;
private:
  uint8_t _buf[LCD_HIGHT/8][LCD_WIDTH]; // lcd_buf[page][col]
  void _transferCommand(uint8_t data);
  void _setRamAddr(uint16_t page, uint16_t column);
  void _setBufferPixel(uint16_t x, uint16_t y, uint8_t val);
};

#ifdef EMBASE_HW_USE_ARDUINO
// implement with Arduino GPIO interface
class ScreenSt7525SoftSpi : public ScreenSt7525 {
public:
  ScreenSt7525SoftSpi();
  BOOL init(int pinCS, int pinDC, int pinSCK, int pinSDA, int pinRST = 0);
protected:
  void _spiWrite(int dc, const UINT8 *data, int size) override;
private:
  uint8_t _pinCS;
  uint8_t _pinDC;
  uint8_t _pinSCK;
  uint8_t _pinSDA;
  uint8_t _pinRST;
};
#endif

} // namespace embase
