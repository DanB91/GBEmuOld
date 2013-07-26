SET(CMAKE_FIND_LIBRARY_PREFIXES "")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")


# It was noticed that when using MinGW gcc it is essential that 'core' is mentioned before 'base'.
find_package(wxWidgets COMPONENTS core base REQUIRED)
 
 
# wxWidgets include (this will do all the magic to configure everything)
include( "${wxWidgets_USE_FILE}" )
add_subdirectory(GUI)

set(source MMU.cpp Cartridge.cpp GameBoy.cpp CPU.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_library(GBEmuLib ${source})
add_executable(GBEmu ${source} main.cpp )
target_link_libraries(GBEmu ${wxWidgets_LIBRARIES} GBEmuGUI)
