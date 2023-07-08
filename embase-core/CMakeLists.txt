
file(GLOB EMBASE_SRCS ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

# posix
if((${EMBASE_CONFIG_OS} MATCHES "linux") OR (${EMBASE_CONFIG_OS} MATCHES "macos"))
  file(GLOB POSIX_SRCS ${CMAKE_CURRENT_LIST_DIR}/src/platform/posix/*.cpp)
  set(EMBASE_SRCS ${EMBASE_SRCS} ${POSIX_SRCS})
endif()

if (${EMBASE_CONFIG_OS} MATCHES "freertos")
  file(GLOB FREERTOS_SRCS ${CMAKE_CURRENT_LIST_DIR}/src/platform/freertos/*.cpp)
  set(EMBASE_SRCS ${EMBASE_SRCS} ${FREERTOS_SRCS})
endif()

set(EMBASE_LINKS ${EMBASE_LINKS} etl::etl)


# if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
# target_compile_definitions(embase PRIVATE _DEBUG)
# endif()


# file(GLOB HW_SRCS ${CMAKE_CURRENT_LIST_DIR}/hw/*.cpp)
# set(EMBASE_SRCS ${EMBASE_SRCS} ${HW_SRCS})


add_library(embase-core ${EMBASE_SRCS})
target_include_directories(embase-core PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/inc
  ${EMBASE_ROOT}/libs/async.h
  ${EMBASE_ROOT}/libs/better-enums
)
# target_include_directories(embase-core PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(embase-core PUBLIC ${EMBASE_LINKS})
add_library(embase::core ALIAS embase-core)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test)
