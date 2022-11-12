#pragma once

#include "embase_def.h"
#include "etl/string.h"
#include <cstdarg>
#include <stdio.h>

namespace Embase {

template<const size_t MAX_SIZE_>
etl::string<MAX_SIZE_> __string_format(const char* format, ...)
{
  va_list args;
  etl::string<MAX_SIZE_> buffer(MAX_SIZE_, '\0');
  va_start(args, format);
  int s = ::vsnprintf(&buffer.front(), buffer.length() + 1, format, args); //note: 替换libc里的实现
  va_end(args);
  buffer.resize(s);
  return buffer;
}

static inline
BOOL __string_startswith(etl::istring& src, etl::istring& val) {
  return etl::string_view(src).starts_with(val) ? TRUE : FALSE;
}
static inline
BOOL __string_startswith(etl::istring& src, const char *val) {
  return etl::string_view(src).starts_with(val) ? TRUE : FALSE;
}
static inline
BOOL __string_endwith(etl::istring& src, etl::istring& val) {
  return etl::string_view(src).ends_with(val) ? TRUE : FALSE;
}
static inline
BOOL __string_endwith(etl::istring& src, const char *val) {
  return etl::string_view(src).ends_with(val) ? TRUE : FALSE;
}



// std::vector<std::string> __string_split(const std::string &string, const std::string &delim);

}
