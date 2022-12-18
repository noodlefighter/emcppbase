#include "hw/ScreenSt7525.h"
#include "embase_macros_bits.h"
#include "embase_platform.h"

using namespace embase;

ScreenSt7525::ScreenSt7525()
{
}

void ScreenSt7525::_transferCommand(uint8_t data)
{
  _spiWrite(1, &data, 1);
}

void ScreenSt7525::_setRamAddr(uint16_t page, uint16_t column)
{
	_transferCommand(0xb0+page); // page addr
	_transferCommand(((column>>4)&0x0f)+0x10); // col high 4bit
	_transferCommand(column&0x0f); // col low 4bit
}

BOOL ScreenSt7525::init()
{
	// 子类的init()调用该函数前需要实现：
  // 1. 给LCD上电
  // 2. 拉低RST脚100ms，硬件复位
  // 3. 等待100ms确保驱动工作

	_transferCommand(0xe2); // 软复位
	__msleep(200);
	_transferCommand(0x2f); // 打开内部升压
	__msleep(200);
	_transferCommand(0xa0); //
	_transferCommand(0x81); // 微调对比度
	_transferCommand(0x70); // 微调对比度的值0x00-0xFF
	_transferCommand(0xeb); // 1/9偏压比(bias)
	_transferCommand(0xc4); // 行列扫描顺序，从上到下
	_transferCommand(0xaf); // 开显示
}

/*
---------------------------------page_start

  (x,y)           (x_end,y)
  |------ w --------|
  |                 |
  h     dp data     |
---------------------------------page_start+1
  |                 |
  |-----------------|
  (x,y_end)         (x_end,y_end)

---------------------------------page_end

*/
void ScreenSt7525::_setBufferPixel(uint16_t x, uint16_t y, uint8_t val)
{
	int page = y / 8;
	int col = x;
	uint8_t bit_n = y % 8;

	uint8_t dat = _buf[page][col];
	if (val) {
		BIT_SET(dat, bit_n);
	}
	else {
		BIT_CLR(dat, bit_n);
	}
	_buf[page][col] = dat;
}

BOOL ScreenSt7525::drawRegion(const Rectangle_t &region, const IBuffer_t &buff)
{
// void lcd_draw_xy(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *dp)
  uint16_t x = region.a.x;
  uint16_t y = region.a.y;
  uint16_t w = region.b.x - region.a.x + 1;
  uint16_t h = region.b.y - region.b.y + 1;
  const uint8_t *dp = (const uint8_t *) buff.data;

	uint16_t i, j, page, col;

	uint16_t x_end = x + w - 1;
	uint16_t y_end = y + h - 1;
	uint16_t page_start = y / 8;
	uint16_t page_end = y_end / 8;

	// u1_printf("x:%d,y:%d,w:%d,h:%d,x_end:%d,y_end:%d,page_start:%d,page_end:%d\n",
	// 	x, y, w, h, x_end, y_end, page_start, page_end);

	int byte_n = 0;
	int bit_n = 0;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			int target_x = x + i;
			int target_y = y + j;

			_setBufferPixel(target_x, target_y, dp[byte_n] & (1 << bit_n));
			// u1_printf("pixel(%d,%d)=%d", target_x, target_y, dp[byte_n] & (1 << bit_n));

			if (++bit_n >= 8) {
				bit_n = 0;
				byte_n++;
			}
		}
	}
	// u1_printf("%02X %02X %02X %02X", lcd_buf[0][0], lcd_buf[0][1], lcd_buf[0][2], lcd_buf[0][3]);

	for (page = page_start; page <= page_end; page++) {
		_setRamAddr(page, x);
    _spiWrite(0, &_buf[page][x], w);
	}
}

#ifdef EMBASE_HW_USE_ARDUINO

#include "Arduino.h"

ScreenSt7525SoftSpi::ScreenSt7525SoftSpi()
{
}

BOOL ScreenSt7525SoftSpi::init(int pinCS, int pinDC, int pinSCK, int pinSDA, int pinRST)
{
	_pinCS = (uint8_t)pinCS;
	_pinDC = (uint8_t)pinDC;
	_pinSCK = (uint8_t)pinSCK;
	_pinSDA = (uint8_t)pinSDA;
	_pinRST = (uint8_t)pinRST;

	pinMode(_pinCS, OUTPUT);
	pinMode(_pinDC, OUTPUT);
	pinMode(_pinSCK, OUTPUT);
	pinMode(_pinSDA, OUTPUT);
	digitalWrite(_pinCS, HIGH);
	digitalWrite(_pinSCK, HIGH);
	digitalWrite(_pinSDA, LOW);
	if (0 != _pinRST) {
		pinMode(_pinRST, OUTPUT);
		digitalWrite(_pinRST, LOW);
		delay(100);
		digitalWrite(_pinRST, HIGH);
	}
	return ScreenSt7525::init();
}

void ScreenSt7525SoftSpi::_spiWrite(int dc, const UINT8 *data, int size)
{
	char i, j;

	for (i = 0; i < size; i++) {
		UINT8 d = data[i];

		digitalWrite(_pinCS, LOW);
		digitalWrite(_pinDC, HIGH);
		for (j = 0; j < 8; j++) {
			digitalWrite(_pinSCK, LOW);
			if(d & 0x80)
				digitalWrite(_pinSDA, HIGH);
			else
				digitalWrite(_pinSDA, LOW);
			digitalWrite(_pinSCK, HIGH);
			d = (d<<1);
		}
		digitalWrite(_pinCS, HIGH);
	}
}
#endif
