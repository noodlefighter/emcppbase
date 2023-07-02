add_executable(test-task test-task.cpp)
target_link_libraries(test-task embase-core)
add_test(NAME test-task COMMAND test-task)
