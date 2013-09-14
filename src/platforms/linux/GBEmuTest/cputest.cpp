#include "cputest.h"
#include <QDebug>

CPUTest::CPUTest()
    :cpu(MMU::UPtr(new FakeMMU))
{

}

void CPUTest::op01(){ //LD BC d16

    cpu.mmu->writeByte(1, 0);
    cpu.mmu->writeWord(0x300, 1);
    cpu.step();

    QVERIFY(cpu.BC == 0x300);
    cpu.PC = 0;
    
    
}

void CPUTest::op02(){ //LD (BC) A
    cpu.mmu->writeByte(2, 0);
    cpu.AF = 0x0300;
    cpu.BC = 0x10;
    cpu.step();

    QCOMPARE(int(cpu.mmu->readByte(0x10)), 3);

    cpu.PC = 0;
    cpu.AF = 0;
    cpu.BC = 0;


}

void CPUTest::op03(){ //INC B
    cpu.mmu->writeByte(3, 0);
    cpu.BC = 4;
    cpu.step();

    QCOMPARE(int(cpu.BC), 5);

    cpu.BC = 0;
    cpu.PC = 0;

}

void CPUTest::op04(){ //INC BC
    cpu.mmu->writeByte(4,0);
    setHighByte(cpu.BC, 4);
    cpu.step();

    QCOMPARE(int(highByte(cpu.BC)), 5);

    cpu.PC = 0;
    cpu.BC = 0;
}
