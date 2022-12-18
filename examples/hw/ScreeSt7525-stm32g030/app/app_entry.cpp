#include "hw/ScreenSt7525.h"

using namespace embase;
ScreenSt7525SoftSpi g_screen;

extern "C"
int app_entry(int argc, char const **argv)
{
  // g_screen.init(1,2,3,4,5);

  // UINT8 buf[4*4/8];
  // g_screen.drawRegion(Rectangle_t(0,0,4,4), IBuffer_t(buf,sizeof(buf)));
  // return 0;
}
