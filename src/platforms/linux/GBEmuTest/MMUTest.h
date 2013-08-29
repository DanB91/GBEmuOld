#ifndef MMUTEST_H
#define MMUTEST_H
#include "AutoTest.h"
#include "MMU.h"
#include "GBEmuExceptions.h"
#include <QDebug>

using namespace GBEmu;

class MMUTest : public QObject
{
    Q_OBJECT

public:
    MMUTest();

private Q_SLOTS:
    void readByte();
    void writeWord();
    void writeByte();



private:
    MMU mmu;
    void mmuReset(){

        mmu = MMU();
        mmu.loadROM("Tetris.gb");
    }

};


MMUTest::MMUTest(){

}

void MMUTest::readByte(){


    mmuReset();

    QVERIFY(mmu.readByte(0) == 0x31); //BIOS

    mmu.leaveBIOS(); //should leave bios

    QVERIFY(mmu.readByte(0) == 0xC3); //ROM

    QVERIFY(mmu.readByte(0xC044) == 0); //internal RAM

    QVERIFY_THROW(mmu.readByte(0xA445), GBEmuException ); //external RAM


}

void MMUTest::writeWord(){

    mmuReset();

    QVERIFY(mmu.readWord(0) == 0xFE31); //BIOS

    mmu.leaveBIOS(); //should leave bios

    QVERIFY(mmu.readWord(0) == 0x0cC3); //ROM

    QVERIFY(mmu.readWord(0xC044) == 0); //internal RAM

    QVERIFY_THROW(mmu.readWord(0xA445), GBEmuException ); //external RAM
}


void MMUTest::writeByte(){
    mmuReset();

    QVERIFY_THROW(mmu.writeByte(0, 0), GBEmuException); //BIOS

    mmu.leaveBIOS(); //should leave bios

    QVERIFY_THROW(mmu.writeByte(0, 0), GBEmuException); //ROM

    //internal RAM
    for(int i = 0xC000; i < 0xFDFF; i++){
        mmu.writeByte(i%20, i);
        QVERIFY(mmu.readByte(i) == i%20);
    }

    QVERIFY_THROW(mmu.writeByte(0, 0xA000), GBEmuException); //ext ram
}

DECLARE_TEST(MMUTest)

#endif // MMUTEST_H
