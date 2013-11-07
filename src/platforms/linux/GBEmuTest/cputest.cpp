#include "cputest.h"
#include <QDebug>
#include <unordered_map>

enum Flag : byte{
    Z = 0x80,
    N = 0x40,
    H = 0x20,
    C = 0x10,
    None = 0
};

#define FLAGSET(flag) QCOMPARE(int(cpu.F), int(flag))

void CPUTest::resetCPU(){
    cpu.A = cpu.B = cpu.C = cpu.D = cpu.E = cpu.F = cpu.H = cpu.L = cpu.PC = cpu.SP = 0;

    for(int i = 0; i < 0xFFFF; i++){
        cpu.mmu->writeByte(0, i);
    }
}


CPUTest::CPUTest()
        :cpu(MMU::UPtr(new FakeMMU))
{

}

void CPUTest::ldNND16(){

    std::vector<std::tuple<byte&, byte&, int>> testConfigurations {
                                               std::tuple<byte&, byte&, int>(cpu.B, cpu.C, 0x1),
                                               std::tuple<byte&, byte&, int>(cpu.D, cpu.E, 0x11),
                                               std::tuple<byte&, byte&, int>(cpu.H, cpu.L, 0x21)
};
    for(auto &tc : testConfigurations){
        cpu.mmu->writeByte(std::get<2>(tc), 0);
        cpu.mmu->writeWord(0x300, 1);
        cpu.step();

        QCOMPARE(int(std::get<0>(tc)), 0x3);
        QCOMPARE(int(std::get<1>(tc)), 0);
        QCOMPARE(cpu.cyclesSinceLastInstruction, 12);

        resetCPU();
    }


}

void CPUTest::ldNToMemory(){ //LD (BC) A

    std::vector<std::tuple<byte&, byte&, QString, int>> testConfigurations {// bool tests if HL should be
                                                     std::tuple<byte&, byte&, QString, int>(cpu.C, cpu.A, tr("nothing"), 0x2),
                                                     std::tuple<byte&, byte&, QString, int>(cpu.E, cpu.A, tr("nothing"), 0x12),
                                                     std::tuple<byte&, byte&, QString, int>(cpu.L, cpu.A, tr("increment"), 0x22)


};
    for(auto &tc : testConfigurations){
        cpu.mmu->writeByte(std::get<3>(tc), 0);
        std::get<1>(tc) = 3;
        std::get<0>(tc) = 0x10;
        cpu.step();

        QCOMPARE(int(cpu.mmu->readByte(0x10)), 3);
        QCOMPARE(cpu.cyclesSinceLastInstruction, 8);

        if(std::get<2>(tc) == tr("decrement")){
            QCOMPARE(int(std::get<0>(tc)), 0xF);
        } else if(std::get<2>(tc) == tr("increment")){
            QCOMPARE(int(std::get<0>(tc)), 0x11);
        }



        resetCPU();
    }


}

void CPUTest::incNN(){ //INC BC
    std::vector<std::tuple<byte&, byte&, int>> testConfigurations {
                                               std::tuple<byte&, byte&, int>(cpu.B, cpu.C, 0x3),
                                               std::tuple<byte&, byte&, int>(cpu.D, cpu.E, 0x13),
                                               std::tuple<byte&, byte&, int>(cpu.H, cpu.L, 0x23)
};
    for(auto &tc : testConfigurations){
        cpu.mmu->writeByte(std::get<2>(tc), 0);
        std::get<0>(tc) = 0xAA;
        std::get<1>(tc) = 0xFF;
        cpu.step();

        QCOMPARE(int(std::get<0>(tc)), 0xAB);
        QCOMPARE(int(std::get<1>(tc)), 0);
        QCOMPARE(cpu.cyclesSinceLastInstruction, 8);



        resetCPU();
    }

}


void CPUTest::incN(){ //INC N
    std::unordered_map<byte*, int> registersToOpcodes = {
            {&cpu.B, 4},
            {&cpu.C, 0xC},
            {&cpu.D, 0x14},
            {&cpu.E, 0x1C},
        {&cpu.H, 0x24},

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

        QCOMPARE(cpu.cyclesSinceLastInstruction, 4);


        resetCPU();
    }



}



void CPUTest::decN()
{
    std::unordered_map<byte*, int> registersToOpcodes = {
        {&cpu.B, 5},
        {&cpu.C, 0xD},
        {&cpu.D, 0x15},
        {&cpu.E, 0x1D},
        {&cpu.H, 0x25}
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

        QCOMPARE(cpu.cyclesSinceLastInstruction, 4);


        resetCPU();
    }

}

void CPUTest::decNN(){
    std::vector<std::tuple<byte&, byte&, int>> testConfigurations {
                                               std::tuple<byte&, byte&, int>(cpu.B, cpu.C, 0xB),
                                               std::tuple<byte&, byte&, int>(cpu.D, cpu.E, 0x1B)
};
    for(auto &tc : testConfigurations){
        std::get<0>(tc) = 0;
        std::get<1>(tc) = 0;
        cpu.mmu->writeByte(std::get<2>(tc), 0);
        cpu.step();

        QCOMPARE(int(std::get<0>(tc)), 0xFF);
        QCOMPARE(int(std::get<1>(tc)), 0xFF);
        QCOMPARE(cpu.cyclesSinceLastInstruction, 8);

        resetCPU();
    }

}

void CPUTest::ldN(){

    std::vector<std::tuple<byte*, int>> registersToOpcodes {
                                               std::tuple<byte*, int>(&cpu.B, 6),
                                               std::tuple<byte*, int>(&cpu.C, 0xE),
                                               std::tuple<byte*, int>(&cpu.D, 0x16),
                                               std::tuple<byte*, int>(&cpu.E, 0x1E),
                                               std::tuple<byte*, int>(&cpu.H, 0x26),
};


    for(auto &registerAndOpcode : registersToOpcodes){
        cpu.mmu->writeByte(std::get<1>(registerAndOpcode), 0);
        cpu.mmu->writeByte(0x45, 1);
        cpu.step();

        QCOMPARE(int(*std::get<0>(registerAndOpcode)), int(0x45));
        QCOMPARE(cpu.cyclesSinceLastInstruction, 8);


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
    QCOMPARE(cpu.cyclesSinceLastInstruction, 4);


    resetCPU();

}

void CPUTest::rla()
{

    cpu.mmu->writeByte(0x17, 0);
    cpu.A = 0x85;

    cpu.step();

    QCOMPARE(int(cpu.A), 0xA);
    QCOMPARE(int(cpu.F), int(Flag::C));
    QCOMPARE(cpu.cyclesSinceLastInstruction, 4);


    resetCPU();

}


void CPUTest::rra()
{

    cpu.mmu->writeByte(0x1F, 0);
    cpu.A = 0x5;

    cpu.step();

    QCOMPARE(int(cpu.A), 0x2);
    QCOMPARE(int(cpu.F), int(Flag::C));
    QCOMPARE(cpu.cyclesSinceLastInstruction, 4);


    resetCPU();

}

void CPUTest::rrca()
{

    cpu.mmu->writeByte(0xF, 0);
    cpu.A = 0x5;

    cpu.step();

    QCOMPARE(int(cpu.A), 0x82);
    QCOMPARE(int(cpu.F), int(Flag::C));
    QCOMPARE(cpu.cyclesSinceLastInstruction, 4);


    resetCPU();

}

void CPUTest::ldNNSP(){
    cpu.mmu->writeByte(0x8, 0);
    cpu.mmu->writeWord(0x7844, 1);
    cpu.SP = 0x4568;

    cpu.step();

    QCOMPARE(int(cpu.mmu->readWord(0x7844)), 0x4568);
    QCOMPARE(cpu.cyclesSinceLastInstruction, 20);


    resetCPU();


}

#define testAddHLFlag(hl, nn, flag) \
    sum = word(hl) + word(nn); \
    cpu.mmu->writeByte(std::get<2>(registerAndOpcode), 0);\
    *std::get<0>(registerAndOpcode) = highByte(nn); \
    *std::get<1>(registerAndOpcode) = lowByte(nn); \
    cpu.H = highByte(hl); \
    cpu.L = lowByte(hl); \
    cpu.step(); \
    QCOMPARE(int(cpu.H), int(highByte(sum))); \
    QCOMPARE(int(cpu.L), int(lowByte(sum))); \
    QCOMPARE(cpu.cyclesSinceLastInstruction, 8); \
    FLAGSET(flag); \
    resetCPU()


void CPUTest::addHL()
{
    std::vector<std::tuple<byte*, byte*, int>> registersToOpcodes {
                                               std::tuple<byte*, byte*, int>(&cpu.B, &cpu.C, 9),
                                               std::tuple<byte*, byte*, int>(&cpu.D, &cpu.E, 0x19)
};

    for(auto &registerAndOpcode : registersToOpcodes){
        word sum;
        testAddHLFlag(0x0101, 0x0F02, Flag::H);
        testAddHLFlag(0x0101, 0xFF02, Flag::H | Flag::C);
        testAddHLFlag(0x0101, 0xF002, 0);
        resetCPU();

    }
}

void CPUTest::ldNFromMem()
{
    std::vector<std::tuple<byte*, byte*, int>> testConfigurations {
                                               std::tuple<byte*, byte*, int>(&cpu.A, &cpu.C, 0xA),
                                               std::tuple<byte*, byte*, int>(&cpu.A, &cpu.E, 0x1A)
};
    for(auto &tc : testConfigurations){
        *std::get<1>(tc) = 0x45;
        cpu.mmu->writeByte(std::get<2>(tc), 0); //write opcode
        cpu.mmu->writeByte(0x55, 0x45); //write 0x55 to address
        cpu.step();

        QCOMPARE(int(*std::get<0>(tc)), 0x55);
        QCOMPARE(cpu.cyclesSinceLastInstruction, 8);

        resetCPU();

    }


}

void CPUTest::jrr8()
{
    std::vector<int> testConfigurations {
                                       0x18
};
    for(auto &tc : testConfigurations){
        cpu.mmu->writeByte(tc, 0); //write opcode
        cpu.mmu->writeByte(0x55, 1); //we want to jump by 0x55 bytes
        cpu.step();

        QCOMPARE(int(cpu.PC), 0x57);
        QCOMPARE(cpu.cyclesSinceLastInstruction, 12);


        resetCPU();

    }

}

void CPUTest::jumpIfFlagIsClearR8()
{
    std::vector<std::tuple<Flag, int>> testConfigurations {
                                       std::tuple<Flag, int>(Flag::Z, 0x20)
};
    for(auto &tc : testConfigurations){
        cpu.mmu->writeByte(std::get<1>(tc), 0); //write opcode
        cpu.mmu->writeByte(0x55, 1); //we want to jump by 0x55 bytes
        cpu.step();

        QCOMPARE(int(cpu.PC), 0x57);
        QCOMPARE(cpu.cyclesSinceLastInstruction, 12);
        resetCPU();

        //test when flag is not clear
        cpu.mmu->writeByte(std::get<1>(tc), 0); //write opcode
        cpu.mmu->writeByte(0x55, 1); //we want to jump by 0x55 bytes
        cpu.F = static_cast<byte>(std::get<0>(tc));
        cpu.step();

        QCOMPARE(int(cpu.PC), 0x2);
        QCOMPARE(cpu.cyclesSinceLastInstruction, 8);
        resetCPU();



    }
}

void CPUTest::decimalAdjustA(){
    //will write the test case soon....
}

void CPUTest::jumpIfFlagIsSetR8(){

std::vector<std::tuple<Flag, int>> testConfigurations {
                                   std::tuple<Flag, int>(Flag::Z, 0x28)
};
for(auto &tc : testConfigurations){
    cpu.mmu->writeByte(std::get<1>(tc), 0); //write opcode
    cpu.mmu->writeByte(0x55, 1); //we want to jump by 0x55 bytes
    cpu.F = static_cast<byte>(std::get<0>(tc));
    cpu.step();

    QCOMPARE(int(cpu.PC), 0x57);
    QCOMPARE(cpu.cyclesSinceLastInstruction, 12);
    resetCPU();

    //test when flag is not set
    cpu.mmu->writeByte(std::get<1>(tc), 0); //write opcode
    cpu.mmu->writeByte(0x55, 1); //we want to jump by 0x55 bytes

    cpu.step();

    QCOMPARE(int(cpu.PC), 0x2);
    QCOMPARE(cpu.cyclesSinceLastInstruction, 8);
    resetCPU();



}

}




