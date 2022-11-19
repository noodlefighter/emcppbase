#include "Screen.h"
#include "embase_macros.h"
#include "embase_macros_bits.h"

using namespace embase;

BOOL Screen::init(int sizeX, int sizeY, PixelFormat pixFmt) {
  _sizeX = sizeX;
  _sizeY = sizeY;
  _pixFmt = pixFmt;
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
    uint8_t r = rMax*y/ySize;
    uint8_t g = gMax*y/ySize;
    uint8_t b = bMax*y/ySize;
    for (int x = 0; x < xSize; x++) {
      getPixel(fmt, r, g, b, &buf[ofst++]);
    }
  }
  return TRUE;
}

BOOL Screen::getPixel(PixelFormat fmt, UINT8 r, UINT8 g, UINT8 b, BYTE *buf)
{
  switch (fmt) {
  case PixelFormat::RGB565:
    return (((uint16_t)r >> 3) << 11) | (((uint16_t)g >> 2) << 5 ) | (((uint16_t)b >> 3) << 0);
  case PixelFormat::RGB565_SWAP:
    return SWAP_U16((((uint16_t)r >> 3) << 11) | (((uint16_t)g >> 2) << 5 ) | (((uint16_t)b >> 3) << 0));
  default:
    return FALSE;
  }
}
