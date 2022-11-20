#!/bin/bash

set -e
set -u

SHELL_DIR=$(cd "$(dirname "$0")";pwd)
cd "$SHELL_DIR"

CMAKE_ARGS=-GNinja
CMAKE_ARGS="${CMAKE_ARGS} -DCMAKE_VERBOSE_MAKEFILE=on"

# CMAKE_ARGS="${CMAKE_ARGS} -DCMAKE_BUILD_TYPE=Release"
# CMAKE_ARGS="${CMAKE_ARGS} -DCMAKE_BUILD_TYPE=Debug"

BUILDDIR=./build/
cmake -S. -B${BUILDDIR} ${CMAKE_ARGS} -DCMAKE_TOOLCHAIN_FILE=${IDF_PATH}/tools/cmake/toolchain-esp32.cmake
cd ${BUILDDIR} && ninja
