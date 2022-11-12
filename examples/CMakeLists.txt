add_executable(example-thread ${CMAKE_CURRENT_LIST_DIR}/example-thread.cpp)
target_link_libraries(example-thread embase)

add_executable(example-string ${CMAKE_CURRENT_LIST_DIR}/example-string.cpp)
target_link_libraries(example-string embase)
