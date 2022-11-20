#pragma once

#include "hw/Screen.h"

namespace embase
{

class ScreenSsd1283 : public Screen {
public:
  BOOL init(int pixelX, int pixelY);
  BOOL drawRegion(const Rectangle_t &region, const IBuffer_t &buff) override;
protected:
  virtual void _spiWrite(int dc, const UINT8 *data, int size) = 0;
  virtual void _spiWriteFb(const UINT8 *data, int size) = 0;
private:
  void _writeIndex(UINT8 index);
  void _data8(UINT8 data);
  void _reg16(UINT8 index, uint16_t data);
  void _setXY(UINT32 x, UINT32 y);
  void _setRegion(UINT32 x1, UINT32 y1, UINT32 x2, UINT32 y2);
};

} // namespace embase
