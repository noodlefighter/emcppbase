#pragma once

#include "hw/Device.h"

namespace embase {

class Uart : public Device {
public:
  virtual int read(void *buf, size_t bufsize) = 0;
  virtual int write(const void *dat, size_t datsize) = 0;
};

}
