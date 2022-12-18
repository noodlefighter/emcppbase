file(GLOB SRCS ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
add_library(embase-arduino ${SRCS})
target_include_directories(embase-arduino PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)
target_link_libraries(embase-arduino PUBLIC embase-core)
