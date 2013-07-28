
set(source MMU.cpp Cartridge.cpp GameBoy.cpp CPU.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ..)
add_library(GB ${source})
