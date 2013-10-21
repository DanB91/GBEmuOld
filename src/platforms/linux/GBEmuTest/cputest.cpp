#include "cputest.h"
#include <QDebug>
#include <unordered_map>

enum Flag : byte{
    Z = 0x80,
    N = 0x40,
    H = 0x20,
    C = 0x10
};

#define FLAGSET(flag) QCOMPARE(int(cpu.F), int(flag))

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
        {&cpu.B, 4},
        {&cpu.C, 0xC}
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
        {&cpu.B, 5},
        {&cpu.C, 0xD}
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

void CPUTest::decNN(){
    std::vector<std::tuple<byte&, byte&, int>> testConfigurations {
                                               std::tuple<byte&, byte&, int>(cpu.B, cpu.C, 0xB)
};
    for(auto &tc : testConfigurations){
        std::get<0>(tc) = 0;
        std::get<1>(tc) = 0;
        cpu.mmu->writeByte(std::get<2>(tc), 0);
        cpu.step();

        QCOMPARE(int(cpu.getBC()), 0xFFFF);
        resetCPU();
    }

}

void CPUTest::ldN(){
    std::unordered_map<byte*, int> registersToOpcodes = {
        {&cpu.B, 6},
        {&cpu.C, 0xE}
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

    resetCPU();

}

void CPUTest::rrca()
{

    cpu.mmu->writeByte(0xF, 0);
    cpu.A = 0x5;

    cpu.step();

    QCOMPARE(int(cpu.A), 0x82);
    QCOMPARE(int(cpu.F), int(Flag::C));

    resetCPU();

}

void CPUTest::ldNNSP(){
    cpu.mmu->writeByte(0x8, 0);
    cpu.mmu->writeWord(0x7844, 1);
    cpu.SP = 0x4568;

    cpu.step();

    QCOMPARE(int(cpu.mmu->readWord(0x7844)), 0x4568);

    resetCPU();


}

#define testAddHLFlag(hl, nn, flag) \
    sum = word(hl) + word(nn); \
    *std::get<0>(registerAndOpcode) = highByte(nn); \
    *std::get<1>(registerAndOpcode) = lowByte(nn); \
    cpu.H = highByte(hl); \
    cpu.L = lowByte(hl); \
    cpu.step(); \
    QCOMPARE(int(cpu.H), int(highByte(sum))); \
    QCOMPARE(int(cpu.L), int(lowByte(sum))); \
    FLAGSET(flag); \
    resetCPU()


void CPUTest::addHL()
{
    std::vector<std::tuple<byte*, byte*, int>> registersToOpcodes {
                                               std::tuple<byte*, byte*, int>(&cpu.B, &cpu.C, 9)
};

    for(auto &registerAndOpcode : registersToOpcodes){
        word sum;
        cpu.mmu->writeByte(std::get<2>(registerAndOpcode), 0);
        testAddHLFlag(0x0101, 0x0F02, Flag::H);
        testAddHLFlag(0x0101, 0xFF02, Flag::H | Flag::C);
        testAddHLFlag(0x0101, 0xF002, 0);
        resetCPU();

    }
}

void CPUTest::ldNFromMem()
{
    std::vector<std::tuple<byte*, byte*, int>> testConfigurations {
                                               std::tuple<byte*, byte*, int>(&cpu.A, &cpu.C, 0xA)
};
    for(auto &tc : testConfigurations){
        *std::get<1>(tc) = 0x45;
        cpu.mmu->writeByte(std::get<2>(tc), 0); //write opcode
        cpu.mmu->writeByte(0x55, 0x45); //write 0x55 to address
        cpu.step();

        QCOMPARE(int(*std::get<0>(tc)), 0x55);
        resetCPU();

    }


}


