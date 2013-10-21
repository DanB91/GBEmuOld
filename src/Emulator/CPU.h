#ifndef CPU_H
#define CPU_H


#include "MMU.h"

class CPUTest;

namespace GBEmu{
class CPU{
    friend class ::CPUTest;

public:
    typedef std::unique_ptr<CPU> UPtr;

    static UPtr makeCPU();

    CPU(MMU::UPtr m);

    const MMU &getMMU() const noexcept;

    byte getA() const noexcept;
    byte getB() const noexcept;
    byte getC() const noexcept;
    byte getD() const noexcept;
    byte getE() const noexcept;
    byte getF() const noexcept;
    byte getH() const noexcept;
    byte getL() const noexcept;

    word getAF() const noexcept;
    word getBC() const noexcept;
    word getDE() const noexcept;
    word getHL() const noexcept;
    word getSP() const noexcept;
    word getPC() const noexcept;

    int getCyclesSinceLastInstruction() const noexcept;
    int getTotalCycles() const noexcept;

    void step();
    void loadROM(const std::string &romFileName);



private:

    //represents a single instruction
    class Op{

    public:

        Op(std::function<void (void)> op, int cycles, int size);
        Op();

        void operator()() const; //execute instruction
        int getCycles() const noexcept; //get cycles this instruction takes
        int getSize() const noexcept; //get size of instruction

    private:

        std::function<void (void)> operation;
        int cycles;
        bool isImplemented; //if not implemented, this opcode is not executed
        int size;  //size of instruction in bytes
    };

    enum class Flag : byte{
        Z = 0x80,
        N = 0x40,
        H = 0x20,
        C = 0x10
    };

    MMU::UPtr mmu;
    std::array<Op, 256> opcodes;

    //8-bit registers
    byte A, B, C, D, E, F, H, L;
    //16-bit registers
    word PC, SP;

    //clock
    int cyclesSinceLastInstruction = 0, totalCycles = 0;


    //private helper methods
    void setFlag(Flag flag);
    void clearFlag(Flag flag);
    void load16BitImmediate(byte &destHigh, byte &destLow);
    void increment16Bit(byte &high, byte &low);
    void decrement16Bit(byte &high, byte &low);
    void increment8Bit(byte &value);
    void decrement8Bit(byte &value);
    void rotateLeft(byte &value);
    void rotateRight(byte &value);
    void addHL(word addend);


};

}

#endif
