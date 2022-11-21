#pragma once

#include "embase_log.h"
#include <functional>
#include <assert.h>

#if EMBASE_DEBUG > 0
#define EM_ASSERT(cond, msg) if(!(cond)){__log("Assert failed: %s", msg);assert(cond);}
#else
#define EM_ASSERT(cond, msg)
#endif

#define EM_GOTO_IF(cond,too)                        if(cond) goto too;
#define EM_BREAK_IF(cond)					                  if(cond) break

#define EM_ABS(v)  (((v) < 0) ? (-(v)) : (v))

#define EM_WEAK  __attribute__((weak))
