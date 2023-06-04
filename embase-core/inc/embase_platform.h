#pragma once

#include "embase_def.h"

namespace embase {

typedef UINT32 TimeStamp_t;

void __msleep(UINT32 v);

TimeStamp_t __get_sys_timestamp();

};
