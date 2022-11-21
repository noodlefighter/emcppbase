#pragma once

#include "embase_config.h"
#include "embase_types.h"
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

struct Rectangle_t {
  typedef Coord_t<UINT32, 2> Point_t;
  Point_t a;
  Point_t b;

  Rectangle_t() {
    a.v[0] = 0;
    a.v[1] = 0;
    b.v[0] = 0;
    b.v[1] = 0;
  }
  Rectangle_t(Point_t p1, Point_t p2) : a(p1), b(p2) { }
  Rectangle_t(UINT32 x1, UINT32 y1, UINT32 x2, UINT32 y2) {
    Point_t p1 = { {x1, y1} };
    Point_t p2 = { {x2, y2} };
    Rectangle_t(p1, p2);
  }
};

}

