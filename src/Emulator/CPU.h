#ifndef CPU_H
#define CPU_H


#include "MMU.h"


namespace GBEmu{
class CPU{

    //inner type definitions
public:
    //the state of the CPU, all in one neat structure
    struct State{

        struct{
            byte A = 0, B = 0, C = 0, D = 0, E = 0, H = 0, L = 0, F = 0;
            word PC = 0, SP = 0;
        } registers;

        struct{
            int cyclesSinceLastInstruction = 0, totalCycles = 0;
        } clock;


    };
private:
    //represents a single instruction
    class Op{

    public:
        Op(std::function<void (void)> op, int cycles);
        Op();

        void operator()() const; //execute instruction
        int getCycles() const noexcept; //get cycles this instruction takes

    private:

        std::function<void (void)> operation;
        int cycles;
        bool isImplemented; //if not implemented, this opcode is not executed
    };



//rest of class definition
public:

    CPU();

    const State &getState() const noexcept;
    const MMU &getMMU() const noexcept;
    void step();
    void reset();
    void loadROM(const std::string &romFileName);


private:
    MMU mmu;
    State state;
    std::array<Op, 256> opcodes;
};

}

#endif
