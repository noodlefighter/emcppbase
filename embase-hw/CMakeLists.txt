file(GLOB HW_SRCS ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(embase-hw ${HW_SRCS})
target_include_directories(embase-hw PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)
# target_include_directories(embase-hw PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(embase-hw PUBLIC embase-core)

if(EMBASE_HW_USE_ARDUINO)
  target_link_libraries(embase-hw PUBLIC embase-arduino)
endif()
