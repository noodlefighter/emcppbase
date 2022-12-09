if((${EMBASE_CONFIG_OS} MATCHES "linux") OR (${EMBASE_CONFIG_OS} MATCHES "macos"))
  add_executable(example-thread ${CMAKE_CURRENT_LIST_DIR}/example-thread.cpp)
  target_link_libraries(example-thread embase)
endif()

add_executable(example-string ${CMAKE_CURRENT_LIST_DIR}/example-string.cpp)
target_link_libraries(example-string embase)

add_executable(example-log ${CMAKE_CURRENT_LIST_DIR}/example-log.cpp)
target_link_libraries(example-log embase)

add_executable(example-enum ${CMAKE_CURRENT_LIST_DIR}/example-enum.cpp)
target_link_libraries(example-enum embase)


file(GLOB uart-screen-host-srcs
  ${CMAKE_CURRENT_LIST_DIR}/uart-screen-host/*.c
  ${CMAKE_CURRENT_LIST_DIR}/uart-screen-host/*.cpp
)
add_executable(uart-screen-host ${uart-screen-host-srcs})
target_link_libraries(uart-screen-host embase)
