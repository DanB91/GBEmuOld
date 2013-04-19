


enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR} . ../src)
set(LIBS gtest gtest_main GBEmuLib)



add_executable(test_mmu MMUTest.cpp)
target_link_libraries(test_mmu ${LIBS})
