#pragma once

#include "embase_def.h"
#include "etl/string.h"
#include "etl/multi_vector.h"
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

// 错误时返回空的vector
template<const size_t N_>
etl::vector<etl::string_view, N_> __string_split(const etl::string_view &string, const char *delim)
{
  etl::vector<etl::string_view, N_> res;
  size_t from = 0, to = 0;
  size_t delim_len = strlen(delim);
  size_t cnt = 0;
  while (etl::istring::npos != (to = string.find(delim, from))) {
    if (++cnt + 1 > N_) {
      goto error;
    }
    res.push_back(string.substr(from, to-from));
    from = to + delim_len;
  }
  res.push_back(string.substr(from, to-from));
  return res;
error:
  res.clear();
  return res;
}
template<const size_t N_>
etl::vector<etl::string_view, N_> __string_split(const etl::istring &string, const char *delim)
{
  const etl::string_view view(string);
  return __string_split(view, delim);
}

}
