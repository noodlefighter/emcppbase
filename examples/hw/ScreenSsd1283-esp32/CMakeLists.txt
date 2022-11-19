cmake_minimum_required(VERSION 3.0.0)
project(spi_master)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../.. embase_root)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(spi_master) # 如果没有这个，ESP-IDF无法正常构建

