cmake_minimum_required (VERSION 2.6)
PROJECT(GBEmu)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")
list( APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -Wall")
enable_testing()
add_subdirectory(src)
add_subdirectory(tests)





