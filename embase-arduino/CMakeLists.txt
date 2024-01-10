add_library(
  embase-arduino
  src/Arduino.cpp
  src/Stream.cpp
  src/Print.cpp
)
target_include_directories(embase-arduino PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)
target_link_libraries(embase-arduino PUBLIC embase-core)

add_library(embase::arduino ALIAS embase-arduino)
