BUILD_DIR := "./build"

build:
  mkdir -p {{ BUILD_DIR }}
  cd {{ BUILD_DIR }} && cmake -GNinja .. && ninja

clean:
  rm -rf {{ BUILD_DIR }}

test: build
  cd {{ BUILD_DIR }} && ctest -V
