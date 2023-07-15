#include "embase_platform.h"

using namespace embase;

extern "C" {

void __embase_msleep(UINT32 v)
{
  embase::__msleep(v);
}

void __embase_usleep(UINT32 v)
{
  embase::__usleep(v);
}

} // extern "C"
