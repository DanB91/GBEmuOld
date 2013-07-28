#include <gtest/gtest.h>
#include <fstream>
#include "GB/MMU.h"
#include "GBEmuExceptions.h"

using namespace GBEmu;

class MMUTest : public ::testing::Test{
    protected:
        virtual void SetUp(){
            mmu = MMUPtr(new MMU(CartridgePtr(new Cartridge("/home/dan/Downloads/Tetris.gb"))));
        }


        MMUPtr mmu;
};


TEST_F(MMUTest, readByte){

    
    ASSERT_EQ(mmu->readByte(0), 0x31); //BIOS

    mmu->leaveBIOS();

    ASSERT_EQ(mmu->readByte(0), 0xC3); //ROM

    ASSERT_EQ(mmu->readByte(0xC044), 0); //internal RAM

    ASSERT_THROW(mmu->readByte(0xA445), GBEmuException ); //external RAM

}


TEST_F(MMUTest, readWord){

    
    ASSERT_EQ(mmu->readWord(0), 0xFE31); //BIOS

    mmu->leaveBIOS();

    ASSERT_EQ(mmu->readWord(0), 0x0cC3); //ROM

    ASSERT_EQ(mmu->readWord(0xC044), 0); //internal RAM

    ASSERT_THROW(mmu->readWord(0xA445), GBEmuException ); //external RAM

}




TEST_F(MMUTest, writeByte){

    
    ASSERT_THROW(mmu->writeByte(0, 0), GBEmuException); //BIOS

    mmu->leaveBIOS();

    ASSERT_THROW(mmu->writeByte(0, 0), GBEmuException); //ROM

    //internal RAM
    for(int i = 0xC000; i < 0xFDFF; i++){
        mmu->writeByte(i%20, i);
        ASSERT_EQ(mmu->readByte(i), i%20);
    }

    ASSERT_THROW(mmu->writeByte(0, 0xA000), GBEmuException); //ext ram

}
