#pragma once

#include "hw/Screen.h"
#include "embase_log.h"

#include <linux/fb.h>

namespace embase {


struct FbContext_t
{
	int fd;
	int width;
	int height;
	int height_virtual;
	int bpp;
	int stride;
	int red_offset;
	int red_length;
	int green_offset;
	int green_length;
	int blue_offset;
	int blue_length;
	int transp_offset;
	int transp_length;
	int buffer_num;
	char *data;
	char *base;
};

class ScreenFb : public Screen {
public:
  ScreenFb() : _logger("ScreenFb") {}
  BOOL init();

  BOOL drawRegion(const Rectangle_t &region, const IBuffer_t &buff) override;
private:
  Logger _logger;
  FbContext_t _fb;
  void _dump_vscreeninfo(struct fb_var_screeninfo *fvsi);
  void _dump_fscreeninfo(struct fb_fix_screeninfo *ffsi);
};

};
