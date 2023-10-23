#pragma once

#include "embase_def.h"

#ifdef __cplusplus

namespace embase {

typedef UINT32 TimeMs_t;
typedef UINT32 TimeUs_t;

void __msleep(UINT32 v);
void __usleep(UINT32 v);

TimeMs_t __get_systick_ms();
TimeUs_t __get_systick_us();

};

#else // C兼容接口

void __embase_msleep(uint32_t v);
void __embase_usleep(uint32_t v);

#endif // __cplusplus
