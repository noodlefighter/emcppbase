#pragma once

#include "embase_config.h"
#include "embase_def.h"
#include "etl/string.h"
#include <stdarg.h>

namespace embase {

class Logger {
public:
  Logger(const char *name);
  Logger(const char *name, int lv);

  void setName(const char *name);
  const etl::istring &getName();

  void setLv(int lv);
  int getLv();

  void logPrint(int lv, const char *fmt, ...);
  void logPrint(int lv, const char *fmt, va_list a_args);

  void error(const char *fmt, ...) {
  #if EMBASE_LOG_LV_ERROR <= EMBASE_LOG_BUILD_TIME_LV
    va_list args;
    va_start(args, fmt);
    logPrint(EMBASE_LOG_LV_ERROR, fmt, args);
    va_end(args);
  #endif
  }

  void warn(const char *fmt, ...) {
  #if EMBASE_LOG_LV_WARN <= EMBASE_LOG_BUILD_TIME_LV
    va_list args;
    va_start(args, fmt);
    logPrint(EMBASE_LOG_LV_WARN, fmt, args);
    va_end(args);
  #endif
  }

  void info(const char *fmt, ...) {
  #if  EMBASE_LOG_LV_INFO <= EMBASE_LOG_BUILD_TIME_LV
    va_list args;
    va_start(args, fmt);
    logPrint(EMBASE_LOG_LV_INFO, fmt, args);
    va_end(args);
  #endif
  }

  void debug(const char *fmt, ...) {
  #if EMBASE_LOG_LV_DEBUG <= EMBASE_LOG_BUILD_TIME_LV
    va_list args;
    va_start(args, fmt);
    logPrint(EMBASE_LOG_LV_DEBUG, fmt, args);
    va_end(args);
  #endif
  }

  void trace(const char *fmt, ...) {
  #if EMBASE_LOG_LV_TRACE <= EMBASE_LOG_BUILD_TIME_LV
    va_list args;
    va_start(args, fmt);
    logPrint(EMBASE_LOG_LV_TRACE, fmt, args);
    va_end(args);
  #endif
  }

private:
  etl::string<EMBASE_LOGGER_NAME_MAXSIZE> _name;
  int _lv;

  // weak symbol, override by link-time
  static void _output(const BYTE *buff);
};

};

extern embase::Logger g_default_logger;
