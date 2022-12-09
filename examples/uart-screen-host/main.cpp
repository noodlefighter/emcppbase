#include "embase_log.h"
#include "embase_types.h"

extern "C" {
  #include "nypack.h"
}

using namespace embase;

#define FB_MAXSIZE    (130*130/8)

int main(void)
{
  BYTE buff[1024];

  BYTE fb[FB_MAXSIZE];

  memset(fb, 0xff, sizeof(fb));

  size_t packlen = 0;
  nypack_generate(fb, sizeof(fb), buff, sizeof(buff), 1, &packlen);
  return 0;
}
