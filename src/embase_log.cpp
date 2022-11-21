#include "embase_def.h"
#include "embase_log.h"
#include "embase_macros.h"

using namespace embase;

Logger g_default_logger("default");

Logger::Logger(const char *name) : Logger(name, EMBASE_LOG_LV_INFO)
{
}
Logger::Logger(const char *name, int lv)
{
  _lv = lv;
  _name.assign(name);
}

void Logger::setName(const char *name)
{
  _name.assign(name);
}
const etl::istring &Logger::getName()
{
  return _name;
}

void Logger::setLv(int lv)
{
  _lv = lv;
}
int Logger::getLv()
{
  return _lv;
}

void Logger::logPrint(int lv, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  logPrint(lv, fmt, args);
  va_end(args);
}

void Logger::logPrint(int lv, const char *fmt, va_list a_args)
{
  ssize_t offset;
  BYTE buffer[EMBASE_LOGGER_FMT_BUFFSIZE+2];

  if (lv <= _lv) {
    offset = snprintf((char*)buffer, EMBASE_LOGGER_FMT_BUFFSIZE, "%s: ", _name.c_str());
    offset += vsnprintf((char*)buffer + offset, EMBASE_LOGGER_FMT_BUFFSIZE - offset, fmt, a_args);
    buffer[offset++] = '\n';
    buffer[offset++] = '\0';
    _output(buffer);
  }
}

EM_WEAK void Logger::_output(const BYTE *buff)
{
  printf((const char*)buff);
}
