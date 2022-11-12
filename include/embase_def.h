#pragma once

#include "embase_config.h"

#include <cstdint>
#include "etl/string.h"

#ifndef INTERFACES
#define INTERFACES struct
#endif


#define EMBASE_PLATFORM_UNKOWN               0
#define EMBASE_PLATFORM_LINUX                1
#define EMBASE_PLATFORM_MAC                  2
#define EMBASE_PLATFORM_WIN32                3
#define EMBASE_PLATFORM_BAREMETAL            4

#define EMBASE_ARCH_UNKOWN                   0
#define EMBASE_ARCH_X86_64                   1
#define EMBASE_ARCH_ARM                      2
#define EMBASE_ARCH_ARM64                    3

namespace Embase {

typedef bool BOOL;
#define FALSE    0
#define TRUE     (!FALSE)

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

class Object {
public :
  Object(){}
  etl::string<EMBASE_OBJECT_NAME_MAXSIZE> name;
};

}

