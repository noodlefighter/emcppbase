add_executable(test-task test-task.cpp)
target_link_libraries(test-task embase-core)
add_test(NAME test-task COMMAND test-task)

add_executable(test-buffer test-buffer.cpp)
target_link_libraries(test-buffer embase-core)
add_test(NAME test-buffer COMMAND test-buffer)
