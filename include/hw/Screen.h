#pragma once

#include "embase_def.h"

namespace embase {

class Screen {
public:

  enum class PixelFormat {
    NONE,
    MIN = 1,
    MONO = MIN,  // 1 bit per pixel
    RGB565,
    RGB565_SWAP,
    RGB888,
    MAX = RGB888,
  };

  BOOL init(int sizeX, int sizeY, PixelFormat pixFmt);

  PixelFormat getPixelFormat();
  int getSizeX();
  int getSizeY();

  virtual BOOL setBacklight(int level);
  virtual BOOL drawRegion(const Rectangle_t &region, const IBuffer_t &buff) = 0;


  static int getPixel(PixelFormat fmt, int r, int g, int b, BYTE *buf);
  static BOOL fillGradient(BYTE *buf, int xSize, int ySize, PixelFormat fmt,
                           int rMax, int gMax, int bMax);

protected:
  int _sizeX, _sizeY;
  PixelFormat _pixFmt;
};

}
