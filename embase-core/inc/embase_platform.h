#pragma once

#include "embase_def.h"

#ifdef __cplusplus

namespace embase {

typedef UINT32 TimeStamp_t;

void __msleep(UINT32 v);
void __usleep(UINT32 v);

TimeStamp_t __get_sys_timestamp();

};

#else // C兼容接口

void __embase_msleep(uint32_t v);
void __embase_usleep(uint32_t v);

#endif // __cplusplus
