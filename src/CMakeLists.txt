
file(GLOB EMBASE_SRCS ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

# posix
if((${EMBASE_CONFIG_OS} MATCHES "linux") OR (${EMBASE_CONFIG_OS} MATCHES "macos"))
  file(GLOB POSIX_SRCS ${CMAKE_CURRENT_LIST_DIR}/platform/posix/*.cpp)
  set(EMBASE_SRCS ${EMBASE_SRCS} ${POSIX_SRCS})
endif()

if (${EMBASE_CONFIG_OS} MATCHES "freertos")
  file(GLOB FREERTOS_SRCS ${CMAKE_CURRENT_LIST_DIR}/platform/freertos/*.cpp)
  set(EMBASE_SRCS ${EMBASE_SRCS} ${FREERTOS_SRCS})
endif()

set(EMBASE_LINKS ${EMBASE_LINKS} etl::etl)


# if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
# target_compile_definitions(embase PRIVATE _DEBUG)
# endif()


file(GLOB HW_SRCS ${CMAKE_CURRENT_LIST_DIR}/hw/*.cpp)
set(EMBASE_SRCS ${EMBASE_SRCS} ${HW_SRCS})


add_library(embase ${EMBASE_SRCS})
target_include_directories(embase PUBLIC ${EMBASE_ROOT}/include ${EMBASE_ROOT}/src)
target_link_libraries(embase PUBLIC ${EMBASE_LINKS})
