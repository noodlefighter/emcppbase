#include "embase_platform.h"

namespace embase {

TimeMs_t __get_systick_ms()
{
  struct timespec times = {0, 0};
  clock_gettime(CLOCK_MONOTONIC, &times);
  return (TimeMs_t)times.tv_sec*1e3 + (TimeMs_t)times.tv_nsec/1e6;
}

}
