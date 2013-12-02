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
        QCOMPARE(int(cpu.PC), 3);


        resetCPU();
    }


}

void CPUTest::ldNToMemory(){ //LD (BC) A

    std::vector<std::tuple<byte&, byte&, QString, int>> testConfigurations {// bool tests if HL should be
                                                        std::tuple<byte&, byte&, QString, int>(cpu.C, cpu.A, tr("nothing"), 0x2),
                                                        std::tuple<byte&, byte&, QString, int>(cpu.E, cpu.A, tr("nothing"), 0x12),
                                                        std::tuple<byte&, byte&, QString, int>(cpu.L, cpu.A, tr("increment"), 0x22),
                                                        std::tuple<byte&, byte&, QString, int>(cpu.L, cpu.A, tr("decrement"), 0x32)


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

void CPUTest::incSP()
{
    cpu.mmu->writeByte(0x33, 0);
    cpu.SP = 0xAAFF;
    cpu.step();

    QCOMPARE(int(cpu.SP), 0xAB00);
    QCOMPARE(cpu.cyclesSinceLastInstruction, 8);
    QCOMPARE(int(cpu.PC), 1);
    resetCPU();

}


void CPUTest::incN(){ //INC N
    std::unordered_map<byte*, int> registersToOpcodes = {
        {&cpu.B, 4},
        {&cpu.C, 0xC},
        {&cpu.D, 0x14},
        {&cpu.E, 0x1C},
        {&cpu.H, 0x24},
        {&cpu.L, 0x2C},
        {&cpu.A, 0x3C},

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

void CPUTest::incValAtHL()
{
    cpu.L = 3;
    cpu.mmu->writeByte(0x34, 0);
    cpu.mmu->writeByte(4, 3);
    cpu.step();

    QCOMPARE(int(cpu.mmu->readByte(3)), 5);
    QCOMPARE(int(cpu.F), 0); //flags should be zero
    resetCPU();

    //test zero flag
    cpu.L = 3;
    cpu.mmu->writeByte(0x34, 0);
    cpu.mmu->writeByte(0xFF, 3);
    cpu.step();

    QCOMPARE(int(cpu.mmu->readByte(3)), 0);
    QCOMPARE(int(cpu.F), int(Flag::Z | Flag::H)); //Z and H flag should be set

    resetCPU();

    //test half carry flag
    cpu.L = 3;
    cpu.mmu->writeByte(0x34, 0);
    cpu.mmu->writeByte(0xF, 3);
    cpu.step();

    QCOMPARE(int(cpu.mmu->readByte(3)), 0x10);
    QCOMPARE(int(cpu.F), int(Flag::H)); //H flag should be set

    QCOMPARE(cpu.cyclesSinceLastInstruction, 12);


    resetCPU();


}



void CPUTest::decN()
{
    std::unordered_map<byte*, int> registersToOpcodes = {
        {&cpu.B, 5},
        {&cpu.C, 0xD},
        {&cpu.D, 0x15},
        {&cpu.E, 0x1D},
        {&cpu.H, 0x25},
        {&cpu.L, 0x2D},
        {&cpu.A, 0x3D}
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
                                               std::tuple<byte&, byte&, int>(cpu.D, cpu.E, 0x1B),
                                               std::tuple<byte&, byte&, int>(cpu.H, cpu.L, 0x2B)
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

void CPUTest::decValAtHL()
{
    cpu.L = 3;
    cpu.mmu->writeByte(0x35, 0);
    cpu.mmu->writeByte(4, 3);
    cpu.step();

    QCOMPARE(int(cpu.mmu->readByte(3)), 3);
    QCOMPARE(int(cpu.F), int(Flag::N)); //N should be set
    resetCPU();

    //test zero flag
    cpu.L = 3;
    cpu.mmu->writeByte(0x35, 0);
    cpu.mmu->writeByte(0x1, 3);
    cpu.step();

    QCOMPARE(int(cpu.mmu->readByte(3)), 0);
    QCOMPARE(int(cpu.F), int(Flag::Z | Flag::N)); //Z and N flag should be set

    resetCPU();

    //test half carry flag
    cpu.L = 3;
    cpu.mmu->writeByte(0x35, 0);
    cpu.mmu->writeByte(0x10, 3);
    cpu.step();

    QCOMPARE(int(cpu.mmu->readByte(3)), 0xF);
    QCOMPARE(int(cpu.F), int(Flag::H | Flag::N)); //H and N flag should be set

    QCOMPARE(cpu.cyclesSinceLastInstruction, 12);


    resetCPU();
}

void CPUTest::ldN(){

    std::vector<std::tuple<byte*, int>> registersToOpcodes {
                                        std::tuple<byte*, int>(&cpu.B, 6),
                                        std::tuple<byte*, int>(&cpu.C, 0xE),
                                        std::tuple<byte*, int>(&cpu.D, 0x16),
                                        std::tuple<byte*, int>(&cpu.E, 0x1E),
                                        std::tuple<byte*, int>(&cpu.H, 0x26),
                                        std::tuple<byte*, int>(&cpu.L, 0x2E),
                                        std::tuple<byte*, int>(&cpu.A, 0x3E),
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

void CPUTest::ldValAtHL()
{
    cpu.L = 3;
    cpu.mmu->writeWord(0x4536, 0);
    cpu.step();

    QCOMPARE(int(cpu.mmu->readByte(3)), 0x45);
    QCOMPARE(cpu.cyclesSinceLastInstruction, 12);
    QCOMPARE(int(cpu.PC), 2);
    resetCPU();


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

void CPUTest::addHLHL()
{

    std::vector<std::tuple<byte*, byte*, int>> registersToOpcodes {
                                               std::tuple<byte*, byte*, int>(&cpu.H, &cpu.L, 0x29)
};

    for(auto &registerAndOpcode : registersToOpcodes){
        word sum;
        testAddHLFlag(0x0802, 0x0802, Flag::H);
        testAddHLFlag(0xFF02, 0xFF02, Flag::H | Flag::C);
        testAddHLFlag(0x0101, 0x0101, 0);
        resetCPU();

    }
}

void CPUTest::ldNFromMem()
{
    std::vector<std::tuple<byte*, byte*, QString, int>> testConfigurations {
                                                        std::tuple<byte*, byte*, QString, int>(&cpu.A, &cpu.C, tr(""),0xA),
                                                        std::tuple<byte*, byte*, QString, int>(&cpu.A, &cpu.E, tr(""), 0x1A),
                                                        std::tuple<byte*, byte*, QString, int>(&cpu.A, &cpu.L, tr("increment"), 0x2A),
                                                        std::tuple<byte*, byte*, QString, int>(&cpu.A, &cpu.L, tr("decrement"), 0x3A)
};
    for(auto &tc : testConfigurations){
        *std::get<1>(tc) = 0x45;
        cpu.mmu->writeByte(std::get<3>(tc), 0); //write opcode
        cpu.mmu->writeByte(0x55, 0x45); //write 0x55 to address
        cpu.step();

        QCOMPARE(int(*std::get<0>(tc)), 0x55);
        QCOMPARE(cpu.cyclesSinceLastInstruction, 8);

        if(std::get<2>(tc) == tr("decrement")){
            QCOMPARE(int(*std::get<1>(tc)), 0x44);
        } else if(std::get<2>(tc) == tr("increment")){
            QCOMPARE(int(*std::get<1>(tc)), 0x46);
        }

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

        cpu.mmu->writeByte(int(tc), 0x57); //write opcode
        cpu.mmu->writeByte(-2, 0x58); //we should stay at the same place
        cpu.step();

        QCOMPARE(int(cpu.PC), 0x57);
        QCOMPARE(cpu.cyclesSinceLastInstruction, 12);


        resetCPU();

    }

}

void CPUTest::jumpIfFlagIsClearR8()
{
    std::vector<std::tuple<Flag, int>> testConfigurations {
                                       std::tuple<Flag, int>(Flag::Z, 0x20),
                                       std::tuple<Flag, int>(Flag::C, 0x30)
};
    for(auto &tc : testConfigurations){
        cpu.mmu->writeByte(std::get<1>(tc), 0); //write opcode
        cpu.mmu->writeByte(0x55, 1); //we want to jump by 0x55 bytes
        cpu.step();

        QCOMPARE(int(cpu.PC), 0x57);
        QCOMPARE(cpu.cyclesSinceLastInstruction, 12);

        cpu.mmu->writeByte(std::get<1>(tc), 0x57); //write opcode
        cpu.mmu->writeByte(-2, 0x58); //we should stay at the same place
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
                                       std::tuple<Flag, int>(Flag::Z, 0x28),
                                       std::tuple<Flag, int>(Flag::C, 0x38)
};
    for(auto &tc : testConfigurations){
        cpu.mmu->writeByte(std::get<1>(tc), 0); //write opcode
        cpu.mmu->writeByte(0x55, 1); //we want to jump by 0x55 bytes
        cpu.F = static_cast<byte>(std::get<0>(tc));
        cpu.step();

        QCOMPARE(int(cpu.PC), 0x57);
        QCOMPARE(cpu.cyclesSinceLastInstruction, 12);

        cpu.mmu->writeByte(std::get<1>(tc), 0x57); //write opcode
        cpu.mmu->writeByte(-2, 0x58); //we should stay at the same place
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

void CPUTest::complementA()
{
    cpu.A = 0;
    cpu.mmu->writeByte(0x2F, 0);
    cpu.step();

    QCOMPARE(int(cpu.A), 255);
    FLAGSET(Flag::H | Flag::N);
    resetCPU();

}

void CPUTest::loadSP()
{
    cpu.mmu->writeByte(0x31, 0);
    cpu.mmu->writeWord(0x3000, 1);
    cpu.step();

    QCOMPARE(int(cpu.SP), 0x3000);
    QCOMPARE(int(cpu.cyclesSinceLastInstruction), 12);
    QCOMPARE(int(cpu.PC), 3);
    resetCPU();


}

void CPUTest::setCarry()
{
    cpu.mmu->writeByte(0x37, 0);
    cpu.F = Flag::Z | Flag::N | Flag::H;
    cpu.step();

    FLAGSET(Flag::C | Flag::Z); //C should be set and Z should not be affected
    QCOMPARE(cpu.cyclesSinceLastInstruction, 4);
    QCOMPARE(int(cpu.PC), 1);
    resetCPU();
}


void CPUTest::invertCarry()
{
    cpu.mmu->writeByte(0x3F, 0);
    cpu.F = Flag::Z | Flag::N | Flag::H;
    cpu.step();

    FLAGSET(Flag::C | Flag::Z); //C should be set and Z should not be affected
    resetCPU();

    cpu.mmu->writeByte(0x3F, 0);
    cpu.F = Flag::Z | Flag::N | Flag::H | Flag::C;
    cpu.step();

    FLAGSET(Flag::Z); //C should be inverted and Z should not be affected


    QCOMPARE(cpu.cyclesSinceLastInstruction, 4);
    QCOMPARE(int(cpu.PC), 1);
    resetCPU();
}

void CPUTest::ops40toBF()
{

    std::map<int, byte*> registerMap = {
        {0, &cpu.B},
        {1, &cpu.C},
        {2, &cpu.D},
        {3, &cpu.E},
        {4, &cpu.H},
        {5, &cpu.L},
        {7, &cpu.A}
    };

    for(int i = 0x40; i < 0xBF; i++){


        if(i >= 0x40 && i < 0x80){
            loadRegToReg(registerMap, i);
        }
        else if(i >= 0x80 && i < 0x88){
            addToA(registerMap, i);
        }
        else if(i >= 0x88 && i < 0x90){
            addToAWithCarry(registerMap, i);
        }
        else if(i >= 0x90 && i < 0x98){
            subtractFromA(registerMap, i);
        }
        else if(i >= 0x98 && i < 0xA0){
            subtractFromAWithCarry(registerMap, i);
        }

        resetCPU();
    }
}


void CPUTest::loadRegToReg(std::map<int, byte *> &registerMap, int opcode)
{

    byte testValue = 0x40;
    byte hValue = 0x3;

    bool usedHL = false;


    if(opcode == 0x76){ //halt instruction
        return;
    }

    if((opcode & 7) != 6){ //source is register
        *registerMap[opcode & 7] = testValue;
    } else{ //source is (HL)
        cpu.H = hValue;
        cpu.mmu->writeByte(testValue, cpu.getHL());
        usedHL = true;
    }

    cpu.mmu->writeByte(opcode, 0);
    cpu.step();

    if(((opcode >> 3) & 7) != 6){
        QCOMPARE(int(*registerMap[(opcode >> 3) & 7]), int(testValue));

        if(usedHL){
            QCOMPARE(cpu.cyclesSinceLastInstruction, 8);
        } else{
            QCOMPARE(cpu.cyclesSinceLastInstruction, 4);
        }

    } else {
        QCOMPARE(int(cpu.mmu->readByte(cpu.getHL())), int(testValue));
        QCOMPARE(cpu.cyclesSinceLastInstruction, 8);
    }




}

void CPUTest::addToA(std::map<int, byte *> &registerMap, int opcode)
{
    byte testValue = 0x80;
    byte hValue = 0x3;
    bool usedHL = false;

    cpu.A = 0x80;

    if((opcode & 7) != 6){ //source is register
        *registerMap[opcode & 7] = testValue;
    } else{ //source is (HL)
        cpu.H = hValue;
        cpu.mmu->writeByte(testValue, cpu.getHL());
        usedHL = true;
    }

    cpu.mmu->writeByte(opcode, 0);
    cpu.step();

    QCOMPARE(int(cpu.A), 0); //overflow
    FLAGSET(Flag::C | Flag::Z);

    resetCPU();

    testValue = 0x8;
    cpu.A = 0x8;

    if(!usedHL){
        *registerMap[opcode & 7] = testValue;
    } else{
        cpu.H = hValue;
        cpu.mmu->writeByte(testValue, cpu.getHL());
    }

    cpu.mmu->writeByte(opcode, 0);
    cpu.step();

    QCOMPARE(int(cpu.A), 0x10); //half carry
    FLAGSET(Flag::H);
    
    
    if(usedHL){
        QCOMPARE(cpu.cyclesSinceLastInstruction, 8);
    } else{
        QCOMPARE(cpu.cyclesSinceLastInstruction, 4);
    }




}

void CPUTest::addToAWithCarry(std::map<int, byte *> &registerMap, int opcode)
{
    byte testValue = 0x80;
    byte hValue = 0x3;
    bool usedHL = false;

    cpu.A = 0x80;

    if((opcode & 7) != 6){ //source is register
        *registerMap[opcode & 7] = testValue;
    } else{ //source is (HL)
        cpu.H = hValue;
        cpu.mmu->writeByte(testValue, cpu.getHL());
        usedHL = true;
    }

    cpu.mmu->writeByte(opcode, 0);
    cpu.step();

    QCOMPARE(int(cpu.A), 0); //overflow
    FLAGSET(Flag::C | Flag::Z);


    testValue = 0x10;

    if(!usedHL){
        *registerMap[opcode & 7] = testValue;
    } else{
        cpu.H = hValue;
        cpu.mmu->writeByte(testValue, cpu.getHL());
    }

    cpu.PC = 0;

    cpu.mmu->writeByte(opcode, 0);
    cpu.step();

    if(opcode == 0x8F){
        QCOMPARE(int(cpu.A), 0x21); //special case for ADC A,A since register A will double
    } else{
        QCOMPARE(int(cpu.A), 0x11); //answer will be plus 1 since carry was set
    }

    FLAGSET(Flag::None); //0 + 0x11 does not have a carry


    if(usedHL){
        QCOMPARE(cpu.cyclesSinceLastInstruction, 8);
    } else{
        QCOMPARE(cpu.cyclesSinceLastInstruction, 4);
    }
}

void CPUTest::subtractFromA(std::map<int, byte *> &registerMap, int opcode)
{
    byte testValue = 5;
    byte hValue = 0x3;
    bool usedHL = false;

    cpu.A = 3;

    if((opcode & 7) != 6){ //source is register
        *registerMap[opcode & 7] = testValue;
    } else{ //source is (HL)
        cpu.H = hValue;
        cpu.mmu->writeByte(testValue, cpu.getHL());
        usedHL = true;
    }

    cpu.mmu->writeByte(opcode, 0);
    cpu.step();

    if(opcode == 0x97){
        QCOMPARE(int(cpu.A), 0); //SUB A will be 0
        FLAGSET(Flag::Z | Flag::N);
    } else{
        QCOMPARE(int(cpu.A), 0xFE); //overflow.  0xFE represents -2 in 8-bit form
        FLAGSET(Flag::C | Flag::N | Flag::H);
    }
    resetCPU();

    testValue = 0x8;
    cpu.A = 0x10;

    if(!usedHL){
        *registerMap[opcode & 7] = testValue;
    } else{
        cpu.H = hValue;
        cpu.mmu->writeByte(testValue, cpu.getHL());
    }

    cpu.mmu->writeByte(opcode, 0);
    cpu.step();

    if(opcode == 0x97){
        QCOMPARE(int(cpu.A), 0); //SUB A will be 0
        FLAGSET(Flag::Z | Flag::N);
    } else{
        QCOMPARE(int(cpu.A), 0x8); //borrow from bit 4
        FLAGSET(Flag::H | Flag::N);
    }


    if(usedHL){
        QCOMPARE(cpu.cyclesSinceLastInstruction, 8);
    } else{
        QCOMPARE(cpu.cyclesSinceLastInstruction, 4);
    }

}

void CPUTest::subtractFromAWithCarry(std::map<int, byte *> &registerMap, int opcode)
{
    byte testValue = 5;
    byte hValue = 0x3;
    bool usedHL = false;

    cpu.A = 3;

    if((opcode & 7) != 6){ //source is register
        *registerMap[opcode & 7] = testValue;
    } else{ //source is (HL)
        cpu.H = hValue;
        cpu.mmu->writeByte(testValue, cpu.getHL());
        usedHL = true;
    }

    cpu.mmu->writeByte(opcode, 0);
    cpu.step();

    if(opcode == 0x9F){
        QCOMPARE(int(cpu.A), 0); //SUB A will be 0
        FLAGSET(Flag::Z | Flag::N);
    } else{
        QCOMPARE(int(cpu.A), 0xFE); //overflow
        FLAGSET(Flag::C | Flag::N | Flag::H);
    }



    testValue = 0x10;

    if(!usedHL){
        *registerMap[opcode & 7] = testValue;
    } else{
        cpu.H = hValue;
        cpu.mmu->writeByte(testValue, cpu.getHL());
    }

    cpu.PC = 0;

    cpu.mmu->writeByte(opcode, 0);
    cpu.step();

    if(opcode == 0x9F){
        QCOMPARE(int(cpu.A), 0); //special case for ADC A,A since register A will be 0
        FLAGSET(Flag::Z | Flag::N);
    } else{
        QCOMPARE(int(cpu.A), 0xED); //answer will be minus 1 since carry was set
        FLAGSET(Flag::N);
    }



    if(usedHL){
        QCOMPARE(cpu.cyclesSinceLastInstruction, 8);
    } else{
        QCOMPARE(cpu.cyclesSinceLastInstruction, 4);
    }
}





