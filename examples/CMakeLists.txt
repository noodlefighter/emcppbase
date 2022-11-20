if((${EMBASE_CONFIG_OS} MATCHES "linux") OR (${EMBASE_CONFIG_OS} MATCHES "macos"))
  add_executable(example-thread ${CMAKE_CURRENT_LIST_DIR}/example-thread.cpp)
  target_link_libraries(example-thread embase)
endif()

add_executable(example-string ${CMAKE_CURRENT_LIST_DIR}/example-string.cpp)
target_link_libraries(example-string embase)

# add_executable(example-enum ${CMAKE_CURRENT_LIST_DIR}/example-enum.cpp)
# target_link_libraries(example-enum embase)
