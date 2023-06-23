// base types
#pragma once

#include <cstdint>

#ifndef INTERFACES
#define INTERFACES struct
#endif

namespace embase {

typedef bool BOOL;
#ifndef FALSE
#define FALSE    0
#endif
#ifndef TRUE
#define TRUE     (!FALSE)
#endif

typedef std::int8_t INT8;
typedef std::int16_t INT16;
typedef std::int32_t INT32;
typedef std::int64_t INT64;

typedef std::uint8_t UINT8;
typedef std::uint16_t UINT16;
typedef std::uint32_t UINT32;
typedef std::uint64_t UINT64;

typedef UINT8 BYTE;
typedef float FLOAT;

typedef unsigned int mseconds_t;
}
