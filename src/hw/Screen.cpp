#include "hw/Screen.h"
#include "embase_macros.h"
#include "embase_macros_bits.h"

using namespace embase;

BOOL Screen::init(int sizeX, int sizeY, PixelFormat pixFmt) {
  _sizeX = sizeX;
  _sizeY = sizeY;
  _pixFmt = pixFmt;
  return TRUE;
}

BOOL Screen::setBacklight(int level)
{
  return FALSE;
}

Screen::PixelFormat Screen::getPixelFormat()
{
  return _pixFmt;
}
int Screen::getSizeX()
{
  return _sizeX;
}
int Screen::getSizeY()
{
  return _sizeY;
}

BOOL Screen::fillGradient(BYTE *buf, int xSize, int ySize, PixelFormat fmt, int rMax, int gMax, int bMax)
{
  int ofst = 0;
  for (int y = 0; y < ySize; y++) {
    int r = rMax*y/ySize;
    int g = gMax*y/ySize;
    int b = bMax*y/ySize;
    for (int x = 0; x < xSize; x++) {
      ofst += getPixel(fmt, r, g, b, &buf[ofst]);
    }
  }
  return TRUE;
}

int Screen::getPixel(PixelFormat fmt, int r, int g, int b, BYTE *buf)
{
  switch (fmt) {
  case PixelFormat::RGB565:
    SET_U16_LSBFIRST(buf, (((uint16_t)r >> 3) << 11) | (((uint16_t)g >> 2) << 5 ) | (((uint16_t)b >> 3) << 0));
    return 2;
  case PixelFormat::RGB565_SWAP:
    SET_U16_LSBFIRST(buf, SWAP_U16((((uint16_t)r >> 3) << 11) | (((uint16_t)g >> 2) << 5 ) | (((uint16_t)b >> 3) << 0)));
    return 2;
  default:
    return 0;
  }
}
