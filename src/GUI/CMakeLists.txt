
set(source MainWindow.cpp GBEmuGUIMainWindow.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_library(GBEmuGUI ${source})
