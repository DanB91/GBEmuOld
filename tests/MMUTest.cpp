#include <gtest/gtest.h>
#include <fstream>
#include "MMU.h"

class MMUTest : public ::testing::Test{
    protected:
        virtual void SetUp(){
        }


        GBEmu::MMU mmu;
};

TEST_F(MMUTest, loadrom){
    const char *fn = "/home/dan/Downloads/Pokemon Red.gb";
    mmu.loadROM(fn);
    std::ifstream f(fn, std::ios::in | std::ios::binary);
    unsigned char byte;
    int i = 0;

    if(!f.is_open()){
        FAIL();
    }

    while(f.good()){
        f.read((char*)&byte, 1);

        ASSERT_EQ(mmu.ROM[i], byte) << "Index: "<< i;

        i++;
    }

    f.close();

}

TEST_F(MMUTest, readByte){
    mmu.loadROM("/home/dan/Downloads/Pokemon Red.gb");
    ASSERT_EQ(mmu.readByte(0), 0x31);


    mmu.inBIOS = false;

    ASSERT_EQ(mmu.readByte(0), 0xFF);

}

