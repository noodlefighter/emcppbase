#pragma once

#include "embase_config.h"
#include "embase_types.h"
#include "etl/string.h"


#define EMBASE_PLATFORM_UNKOWN               0
#define EMBASE_PLATFORM_LINUX                1
#define EMBASE_PLATFORM_MAC                  2
#define EMBASE_PLATFORM_WIN32                3
#define EMBASE_PLATFORM_BAREMETAL            4

#define EMBASE_ARCH_UNKOWN                   0
#define EMBASE_ARCH_X86_64                   1
#define EMBASE_ARCH_ARM                      2
#define EMBASE_ARCH_ARM64                    3

namespace embase {

class Object {
public :
  Object(){}
  etl::string<EMBASE_OBJECT_NAME_MAXSIZE> name;
};

struct IBuffer_t {
  size_t size;
  void *data;
};

template <typename type_, const int dimension_>
struct Coord_t {
  etl::array<type_, dimension_> v;
};

struct Rectangle_t {
  typedef Coord_t<UINT32, 2> Point_t;
  Point_t a;
  Point_t b;
};

}

