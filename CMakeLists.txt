cmake_minimum_required(VERSION 3.6)
project(embase VERSION 1.0.0)

option(EMBASE_EXAMPLES "Configure CMake to build examples (or not)" OFF)
option(EMBASE_ARDUINO "Use the arduino compatibility layer provided by Embase (or not)" ON)
option(EMBASE_HW_USE_ARDUINO "some" ON)
configure_file(
  ${CMAKE_CURRENT_LIST_DIR}/embase-core/inc/embase_config.h.in
  ${CMAKE_CURRENT_LIST_DIR}/embase-core/inc/embase_config.h
  @ONLY
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -fvisibility=hidden")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()
set(EMBASE_ROOT ${CMAKE_CURRENT_LIST_DIR})


if(NOT DEFINED EMBASE_TARGET_LOGGER)
message("Set EMBASE_TARGET_LOGGER info default[1]")
set(EMBASE_TARGET_LOGGER 1)
endif()

message("CMAKE_HOST_SYSTEM_NAME is: ${CMAKE_HOST_SYSTEM_NAME}")

# default
if(NOT EMBASE_CONFIG_OS)
  if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    set(EMBASE_CONFIG_OS "linux")
  elseif(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
    set(EMBASE_CONFIG_OS "macos")
  elseif(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
    set(EMBASE_CONFIG_OS "win32")
  else()
    set(EMBASE_CONFIG_OS "unkown")
  endif()
endif()

message("EMBASE_CONFIG_OS is: ${EMBASE_CONFIG_OS}")

if (${EMBASE_CONFIG_OS} MATCHES "unkown")
  set(EMBASE_OS 0)
elseif (${EMBASE_CONFIG_OS} MATCHES "linux")
  set(EMBASE_OS 1)
elseif (${EMBASE_CONFIG_OS} MATCHES "macos")
  set(EMBASE_OS 2)
elseif (${EMBASE_CONFIG_OS} MATCHES "win32")
  set(EMBASE_OS 3)
elseif (${EMBASE_CONFIG_OS} MATCHES "freertos")
  set(EMBASE_OS 4)
endif()

include_directories(
  ${EMBASE_ROOT}/include
  ${EMBASE_ROOT}/src
  ${EMBASE_ROOT}/libs/better-enums
)

set(GIT_DIR_LOOKUP_POLICY ALLOW_LOOKING_ABOVE_CMAKE_SOURCE_DIR)
add_subdirectory(${EMBASE_ROOT}/libs/etl etl EXCLUDE_FROM_ALL)

add_subdirectory(${EMBASE_ROOT}/embase-core)
add_subdirectory(${EMBASE_ROOT}/embase-hw)
if (EMBASE_ARDUINO)
  add_subdirectory(${EMBASE_ROOT}/embase-arduino)
endif()

if(EMBASE_EXAMPLES)
  add_subdirectory(${EMBASE_ROOT}/examples)
endif()




