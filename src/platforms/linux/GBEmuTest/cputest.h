#ifndef CPUTEST_H
#define CPUTEST_H

#include "AutoTest.h"
#include "CPU.h"
#include <array>

using namespace GBEmu;

class FakeMMU : public MMU{
public:
    byte readByte(word address) const override{
        return fakeRAM[address];
    }

    void writeByte(byte value, word address) override{
        fakeRAM[address] = value;
    }

    word readWord(word address) const override{
        return wordFromBytes(fakeRAM[address + 1], fakeRAM[address]);
    }

    void writeWord(word value, word address) override{
        fakeRAM[address] = lowByte(value);
        fakeRAM[address + 1] = highByte(value);
    }

private:
    std::array<byte,0xFFFF> fakeRAM;

};

class CPUTest : public QObject
{
    Q_OBJECT

public:
    CPUTest();

private slots:
    void ldNND16();
    void ldNToMemory();
    void incN();
    void incValAtHL();
    void incNN();
    void incSP();
    void decNN();
    void decValAtHL();
    void decN();
    void ldN();
    void ldValAtHL();
    void rlca();
    void rla();
    void rrca();
    void rra();
    void ldNNSP();
    void addHL();
    void addHLHL();
    void ldNFromMem();
    void jrr8();
    void jumpIfFlagIsClearR8();
    void decimalAdjustA();
    void jumpIfFlagIsSetR8();
    void complementA();
    void loadSP();
    void setCarry();
    void invertCarry();
    void ops40toBF();


private:

    CPU cpu;

    void resetCPU();
    //helpers for ops40toBF
    void loadRegToReg(std::map<int, byte *> &registerMap, int opcode);
    void addToA(std::map<int, byte *> &registerMap, int opcode);
    void addToAWithCarry(std::map<int, byte *> &registerMap, int opcode);
    void subtractFromA(std::map<int, byte *> &registerMap, int opcode);
    void subtractFromAWithCarry(std::map<int, byte *> &registerMap, int opcode);
    void andToA(std::map<int, byte *> &registerMap, int opcode);
    void xorToA(std::map<int, byte *> &registerMap, int opcode);
    void orToA(std::map<int, byte *> &registerMap, int opcode);
    void compareToA(std::map<int, byte *> &registerMap, int opcode);


};

DECLARE_TEST(CPUTest)

#endif // CPUTEST_H
