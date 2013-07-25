
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})


QT4_WRAP_UI(UISrcs mainwindow.ui)
QT4_WRAP_CPP(MOCSrcs mainwindow.h)
set(source MMU.cpp Cartridge.cpp mainwindow.cpp GameBoy.cpp CPU.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_library(GBEmuLib ${source} ${MOCSrcs} ${UISrcs})
add_executable(GBEmu ${source} main.cpp ${MOCSrcs} ${UISrcs})
target_link_libraries(GBEmu ${QT_LIBRARIES})
