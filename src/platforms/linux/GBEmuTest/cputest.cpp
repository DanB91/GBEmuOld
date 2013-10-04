#include "cputest.h"
#include <QDebug>
#include <unordered_map>

enum Flag{
    Z = 0x80,
    N = 0x40,
    H = 0x20,
    C = 0x10
};

void CPUTest::resetCPU(){
    cpu.A = cpu.B = cpu.C = cpu.D = cpu.E = cpu.F = cpu.H = cpu.L = cpu.PC = cpu.SP = 0;

}


CPUTest::CPUTest()
    :cpu(MMU::UPtr(new FakeMMU))
{

}

void CPUTest::op01(){ //LD BC d16

    cpu.mmu->writeByte(1, 0);
    cpu.mmu->writeWord(0x300, 1);
    cpu.step();

    QVERIFY(cpu.getBC() == 0x300);

    resetCPU();
    
    
}

void CPUTest::op02(){ //LD (BC) A
    cpu.mmu->writeByte(2, 0);
    cpu.A = 3;
    cpu.C = 0x10;
    cpu.step();

    QCOMPARE(int(cpu.mmu->readByte(0x10)), 3);

    resetCPU();


}


void CPUTest::incN(){ //INC N
    std::unordered_map<byte*, int> registersToOpcodes = {
        {&cpu.B, 4}
    };

    for(auto &registerAndOpcode : registersToOpcodes){
        //test no flags
        cpu.mmu->writeByte(registerAndOpcode.second, 0);
        *registerAndOpcode.first = 4;
        cpu.step();

        QCOMPARE(int(*registerAndOpcode.first), 5);
        QCOMPARE(int(cpu.F), 0); //flags should be zero

        resetCPU();

        //test zero flag
        cpu.mmu->writeByte(registerAndOpcode.second, 0);
        *registerAndOpcode.first = 0xFF;
        cpu.step();

        QCOMPARE(int(*registerAndOpcode.first), 0);
        QCOMPARE(int(cpu.F), int(Flag::Z | Flag::H)); //Z and H flag should be set

        resetCPU();

        //test half carry flag
        cpu.mmu->writeByte(registerAndOpcode.second, 0);
        *registerAndOpcode.first = 0xF;
        cpu.step();

        QCOMPARE(int(*registerAndOpcode.first), 0x10);
        QCOMPARE(int(cpu.F), int(Flag::H)); //H flag should be set

        resetCPU();
    }



}

void CPUTest::incNN(){ //INC BC
    cpu.mmu->writeByte(3,0);
    cpu.C = 4;
    cpu.step();

    QCOMPARE(int(cpu.C), 5);

    resetCPU();
}

void CPUTest::decN()
{
    std::unordered_map<byte*, int> registersToOpcodes = {
        {&cpu.B, 5}
    };

    for(auto &registerAndOpcode : registersToOpcodes){
        //test no flags
        cpu.mmu->writeByte(registerAndOpcode.second, 0);
        *registerAndOpcode.first = 4;
        cpu.step();

        QCOMPARE(int(*registerAndOpcode.first), 3);
        QCOMPARE(int(cpu.F), int(Flag::N)); //N should be set

        resetCPU();

        //test zero flag
        cpu.mmu->writeByte(registerAndOpcode.second, 0);
        *registerAndOpcode.first = 1;
        cpu.step();

        QCOMPARE(int(*registerAndOpcode.first), 0);
        QCOMPARE(int(cpu.F), int(Flag::Z | Flag::N)); //Z and N flag should be set

        resetCPU();

        //test half carry flag
        cpu.mmu->writeByte(registerAndOpcode.second, 0);
        *registerAndOpcode.first = 0x10;
        cpu.step();

        QCOMPARE(int(*registerAndOpcode.first), 0xF);
        QCOMPARE(int(cpu.F), int(Flag::H | Flag::N)); //H and N flag should be set

        resetCPU();
    }

}

void CPUTest::ldN(){
    std::unordered_map<byte*, int> registersToOpcodes = {
        {&cpu.B, 6}
    };


    for(auto &registerAndOpcode : registersToOpcodes){
        cpu.mmu->writeByte(registerAndOpcode.second, 0);
        cpu.mmu->writeByte(0x45, 1);
        cpu.step();

        QCOMPARE(int(*registerAndOpcode.first), int(0x45));

        resetCPU();
    }

}

void CPUTest::rlca()
{
    cpu.mmu->writeByte(0x7, 0);
    cpu.A = 0x85;

    cpu.step();

    QCOMPARE(int(cpu.A), 0xB);
    QCOMPARE(int(cpu.F), int(Flag::C));

}
