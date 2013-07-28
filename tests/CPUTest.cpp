#include <gtest/gtest.h>
#include <fstream>
#include <array>
#include <stdlib.h>
#include "GB/CPU.h"
#include "GBEmuExceptions.h"

using namespace GBEmu;

class CPUTest : public ::testing::Test{
    protected:
        virtual void SetUp(){
           cpu = CPUPtr(new CPU(MMUPtr(new MMU(CartridgePtr(new Cartridge("/home/dan/Downloads/Tetris.gb"))))));
        }


        CPUPtr cpu;
};


//see if the initial values of the state are zero
TEST_F(CPUTest, readState){

    char cpuStateBytes[sizeof(CPU::State)] = {1};
    memcpy(cpuStateBytes, &cpu->getState(), sizeof(CPU::State)); // a bit lazy here

    for(unsigned int i = 0; i < sizeof(CPU::State); i++){
        ASSERT_EQ(cpuStateBytes[i] , 0);
    }

    
    
}

