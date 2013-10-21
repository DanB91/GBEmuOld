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
    void op01();
    void op02();
    void incN();
    void incNN();
    void decNN();
    void decN();
    void ldN();
    void rlca();
    void rrca();
    void ldNNSP();
    void addHL();
    void ldNFromMem();

private:
    CPU cpu;

    void resetCPU();

};

DECLARE_TEST(CPUTest)

#endif // CPUTEST_H
