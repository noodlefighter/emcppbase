#include "embase_platform.h"

namespace embase {

TimeStamp_t __get_sys_timestamp()
{
  struct timespec times = {0, 0};
  clock_gettime(CLOCK_MONOTONIC, &times);
  return (TimeStamp_t)times.tv_sec*1e3 + (TimeStamp_t)times.tv_nsec/1e6;
}

}
