#pragma once

#include "etl/string.h"

class Device {
public:
  virtual const etl::istring &getDeviceName();
};
