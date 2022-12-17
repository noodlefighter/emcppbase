#pragma once

#include "hw/Screen.h"

namespace embase
{

class ScreenSt7525 : public Screen {
public:
  static const int LCD_HIGHT = 192;
  static const int LCD_WIDTH = 64;

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

} // namespace embase
