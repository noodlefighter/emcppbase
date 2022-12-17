#pragma once

#include "embase_def.h"

namespace embase {

class Screen {
public:

  enum class PixelFormat {
    NONE,
    MIN = 1,
    MONO = MIN,  // 1 bit per pixel
    GRAY_2BIT,
    GRAY_4BIT,
    GRAY_8BIT,
    GRAY_16BIT,
    RGB565,
    RGB565_SWAP,
    RGB888,
    MAX = RGB888,
  };
  static int getPixel(PixelFormat fmt, int r, int g, int b, BYTE *buf);
  static BOOL fillGradient(BYTE *buf, int xSize, int ySize, PixelFormat fmt,
                           int rMax, int gMax, int bMax);

  struct PixelFormatDesc {
    int bits_per_pixel;
    int grayscale;
    int red_offset;
    int red_length;
    int green_offset;
    int green_length;
    int blue_offset;
    int blue_length;
  };
  static PixelFormat pixelFormatFromDesc(PixelFormatDesc &desc);
  static PixelFormatDesc& pixelFormatToDesc(PixelFormat pixFmt);

  BOOL init(int sizeX, int sizeY, PixelFormat pixFmt);

  PixelFormat getPixelFormat();
  int getSizeX();
  int getSizeY();

  virtual BOOL setBacklight(int level);
  virtual BOOL drawRegion(const Rectangle_t &region, const IBuffer_t &buff) = 0;

protected:
  int _sizeX, _sizeY;
  PixelFormat _pixFmt;

private:
  static const PixelFormatDesc _pixFmtDescTable[(long)PixelFormat::MAX + 1];
};

}
