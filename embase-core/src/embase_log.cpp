#include "embase_def.h"
#include "embase_log.h"
#include "embase_macros.h"

using namespace embase;

Logger g_default_logger("default");

Logger::Logger() : Logger("", EMBASE_LOG_LV_INFO)
{
}
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
  BYTE buffer[EMBASE_LOGGER_FMT_BUFFSIZE];

  if (lv <= _lv) {
    // header
    offset = snprintf((char*)buffer, sizeof(buffer), "%s: ", _name.c_str());

    // body
    int body_maxlen = sizeof(buffer) - offset - 2;
    int body_len = vsnprintf((char*)buffer + offset, body_maxlen, fmt, a_args);
    offset += (body_len > body_maxlen) ? body_maxlen : body_len;

    // end: CRLF, 2 bytes
    buffer[offset++] = '\r';
    buffer[offset++] = '\n';
    buffer[offset++] = '\0';
    _output(buffer);
  }
}

EM_WEAK void Logger::_output(const BYTE *buff)
{
  printf("%s", (const char*)buff);
}
