cmake_minimum_required(VERSION 3.6)
project(embase VERSION 1.0.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -fvisibility=hidden")


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()
set(EMBASE_ROOT ${CMAKE_CURRENT_LIST_DIR})

option(EMBASE_EXAMPLES "Configure CMake to build examples (or not)" ON)

if(NOT DEFINED EMBASE_TARGET_LOGGER)
message("Set EMBASE_TARGET_LOGGER info default[1]")
set(EMBASE_TARGET_LOGGER 1)
endif()


configure_file(${EMBASE_ROOT}/include/embase_config.h.in ${EMBASE_ROOT}/include/embase_config.h)

include_directories(${EMBASE_ROOT}/include ${EMBASE_ROOT}/src)

add_subdirectory(${EMBASE_ROOT}/libs/etl EXCLUDE_FROM_ALL)

add_subdirectory(${EMBASE_ROOT}/src EXCLUDE_FROM_ALL)
get_directory_property(_parent PARENT_DIRECTORY)
if(_parent)
  set(EMBASE_TARGET_PLATFORM ${EMBASE_TARGET_PLATFORM} PARENT_SCOPE)
endif()

if(EMBASE_EXAMPLES)
  add_subdirectory(${EMBASE_ROOT}/examples)
endif()




