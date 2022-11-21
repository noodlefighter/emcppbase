#include "hw/ScreenSsd1283.h"

#include "embase_platform.h"
#include "embase_macros.h"

using namespace embase;

void ScreenSsd1283::_writeIndex(UINT8 index)
{
  _spiWrite(0, &index, 1);
}

void ScreenSsd1283::_data8(UINT8 data)
{
  _spiWrite(1, &data, 1);
}

void ScreenSsd1283::_reg16(UINT8 index, uint16_t data)
{
  _writeIndex(index);
  data = ((data >> 8) & 0xFF) | ((data << 8) & 0xFF00);
  _spiWrite(1, (const UINT8 *)&data, 2);
}

void ScreenSsd1283::_setXY(UINT32 x, UINT32 y)
{
  _writeIndex(0x21);
  _data8(y + 2);
  _data8(x + 2);
  _writeIndex(0x22);
}

void ScreenSsd1283::_setRegion(UINT32 x1, UINT32 y1, UINT32 x2, UINT32 y2)
{
  _writeIndex(0x44);
  _data8(x2 + 2);
  _data8(x1 + 2);
  _writeIndex(0x45);
  _data8(y2 + 2);
  _data8(y1 + 2);

  _setXY(x1, y1);
}

BOOL ScreenSsd1283::init(int pixelX, int pixelY)
{
  do
  {
    _reg16(0x10, 0x2F8E); /* power control 1 */
    _reg16(0x11, 0x000C); /* power control 2 */
    _reg16(0x07, 0x0021); /* display control */
    _reg16(0x28, 0x0006); /* vcom OTP */
    _reg16(0x28, 0x0005);
    _reg16(0x27, 0x057F); /* further bias current setting */
    _reg16(0x29, 0x89A1); /* vcom OTP */
    _reg16(0x00, 0x0001); /* OSC en */
    __msleep(100);
    _reg16(0x29, 0x80B0); /* vcom OTP */
    __msleep(30);
    _reg16(0x29, 0xFFFE); /* vcom OTP */
    _reg16(0x07, 0x0023); /* display control */
    __msleep(30);
    _reg16(0x07, 0x0033); /* display control */
    _reg16(0x01, 0x2183); /* driver output control, REV, TB, RGB */
    _reg16(0x03, 0x6830); /* entry mode, 65K, ram, ID0 */
    _reg16(0x2F, 0xFFFF); /* 2A ~ 2F, test */
    _reg16(0x2C, 0x8000);
    _reg16(0x27, 0x0570);
    _reg16(0x02, 0x0300); /* driving wave form control */
    _reg16(0x0B, 0x580C); /* frame cycle control */
    _reg16(0x12, 0x0609); /* power control 3 */
    _reg16(0x13, 0x3100); /* power control 4 */

    return Screen::init(pixelX, pixelY, PixelFormat::RGB565_SWAP);
  } while (1);
  return FALSE;
}

BOOL ScreenSsd1283::drawRegion(const Rectangle_t &region, const IBuffer_t &buff)
{
  UINT32 x1 = region.a.x;
  UINT32 y1 = region.a.y;
  UINT32 x2 = region.b.x;
  UINT32 y2 = region.b.y;
  if ((x1 >= _sizeX) || (x2 >= _sizeX) || (y1 >= _sizeY) || (y2 >= _sizeY))
  {
    return FALSE;
  }
  _setRegion(x1, y1, x2, y2);
  _spiWriteFb((const UINT8 *)buff.data, buff.size);
  return TRUE;
}
