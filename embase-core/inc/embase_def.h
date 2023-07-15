#pragma once

#include "embase_config.h"
#include "embase_types.h"

#ifdef __cplusplus // C++ only
#include "etl/string.h"

namespace embase {

class Object {
public :
  Object(){}
  etl::string<EMBASE_OBJECT_NAME_MAXSIZE> name;
};

struct IBuffer_t {
  size_t size;
  void *data;
  IBuffer_t(void *data, size_t size) : size(size), data(data) {}
};

template <typename type_, const int dimension_>
struct Coord_t {
  etl::array<type_, dimension_> v;
};

struct Point2D_t {
  Point2D_t() : x(0), y(0) {}
  Point2D_t(UINT32 x, UINT32 y) : x(x), y(y) {}
  UINT32 x;
  UINT32 y;
};

struct Rectangle_t {
  Rectangle_t() {}
  Rectangle_t(Point2D_t p1, Point2D_t p2) : a(p1), b(p2) {}
  Rectangle_t(UINT32 x1, UINT32 y1, UINT32 x2, UINT32 y2) : a(x1,y1), b(x2,y2) {}
  Point2D_t a;
  Point2D_t b;
};

} // namespace embase

#endif // __cplusplus

