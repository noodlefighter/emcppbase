#include "hw/linux/ScreenFb-linux.h"

#include "embase_log.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>


using namespace embase;

void ScreenFb::_dump_vscreeninfo(struct fb_var_screeninfo *fvsi)
{
	printf("======= FB VAR SCREENINFO =======\n");
	printf("xres: %d\n", fvsi->xres);
	printf("yres: %d\n", fvsi->yres);
	printf("yres_virtual: %d\n", fvsi->yres_virtual);
	printf("buffer number: %d\n", fvsi->yres_virtual / fvsi->yres);
	printf("bpp : %d\n", fvsi->bits_per_pixel);
	printf("red bits    :\n");
	printf("    offset   : %d\n", fvsi->red.offset);
	printf("    length   : %d\n", fvsi->red.length);
	printf("    msb_right: %d\n", fvsi->red.msb_right);
	printf("green bits  :\n");
	printf("    offset   : %d\n", fvsi->green.offset);
	printf("    length   : %d\n", fvsi->green.length);
	printf("    msb_right: %d\n", fvsi->green.msb_right);
	printf("blue bits   :\n");
	printf("    offset   : %d\n", fvsi->blue.offset);
	printf("    length   : %d\n", fvsi->blue.length);
	printf("    msb_right: %d\n", fvsi->blue.msb_right);
	printf("transp bits :\n");
	printf("    offset   : %d\n", fvsi->transp.offset);
	printf("    length   : %d\n", fvsi->transp.length);
	printf("    msb_right: %d\n", fvsi->transp.msb_right);

	printf("=================================\n");
}
void ScreenFb::_dump_fscreeninfo(struct fb_fix_screeninfo *ffsi)
{
	printf("======= FB FIX SCREENINFO =======\n");
	printf("id          : %s\n", ffsi->id);
	printf("smem_start  : 0x%08lX\n", ffsi->smem_start);
	printf("smem_len    : %u\n", ffsi->smem_len);
	printf("line_length : %u\n", ffsi->line_length);
	printf("=================================\n");
}

BOOL ScreenFb::init()
{
  BOOL rc = FALSE;
  int fd = 0;
	int index = 0;
	struct fb_var_screeninfo fvsi;
	struct fb_fix_screeninfo ffsi;

  if ((fd = open("/dev/fb0", O_RDWR)) < 0) {
    _logger.error("open: %s", strerror(errno));
    return FALSE;
  }

  if (ioctl(fd, FBIOGET_VSCREENINFO, &fvsi) < 0) {
    _logger.error("ioctl(FBIOGET_VSCREENINFO): %s", strerror(errno));
    goto error;
  }
  if (ioctl(fd, FBIOGET_FSCREENINFO, &ffsi) < 0) {
    _logger.error("ioctl(FBIOGET_FSCREENINFO): %s", strerror(errno));
    goto error;
  }
  _dump_vscreeninfo(&fvsi);
  _dump_fscreeninfo(&ffsi);

  _fb.fd = fd;
  _fb.width = fvsi.xres;
  _fb.height = fvsi.yres;
  _fb.height_virtual = fvsi.yres_virtual;
  _fb.bpp = fvsi.bits_per_pixel;
  _fb.stride = ffsi.line_length;
  _fb.red_offset = fvsi.red.offset;
  _fb.red_length = fvsi.red.length;
  _fb.green_offset = fvsi.green.offset;
  _fb.green_length = fvsi.green.length;
  _fb.blue_offset = fvsi.blue.offset;
  _fb.blue_length = fvsi.blue.length;
  _fb.transp_offset = fvsi.transp.offset;
  _fb.transp_length = fvsi.transp.length;
  _fb.buffer_num = _fb.height_virtual / _fb.height;

  for (const PixelFormatDesc &i : pixfmt_tb) {
    if ()
  }


  _fb.base = (char *)mmap((caddr_t)NULL, ffsi.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (_fb.base == (char *)-1) {
    _logger.error("mmap error: %s", strerror(errno));
    goto error;
  }
  return TRUE;

error:
  if (fd > 0) {
    close(fd);
  }
  return FALSE;
}

BOOL ScreenFb::drawRegion(const Rectangle_t &region, const IBuffer_t &buff)
{
}
