


enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR} . ../src)
set(LIBS gtest gtest_main GBEmuLib)

macro(createTest nameOfTest testExe testFile)
    add_executable(${nameOfTest} ${testFile})
    target_link_libraries(${nameOfTest} ${LIBS})
    add_test(${nameOfTest}  ${CMAKE_CURRENT_BINARY_DIR}/${testExe})
endmacro(createTest)

createTest(MMUTest test_mmu MMUTest.cpp)
createTest(CartridgeTest test_cartridge CartridgeTest.cpp)
