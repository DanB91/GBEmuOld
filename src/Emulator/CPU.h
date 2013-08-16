#ifndef CPU_H
#define CPU_H

#include <functional>
#include <memory>
#include "MMU.h"
#include "opcodes.h"

namespace GBEmu{
class CPU{

public:
    //definitions

    //the state of the CPU, all in one neat structure
    struct State{

        struct{
            byte A = 0, B = 0, C = 0, D = 0, H = 0, L = 0, F = 0;
            word PC = 0, SP = 0;
        } registers;

        struct{
            int cyclesSinceLastInstruction = 0, totalCycles = 0;
        } clock;


    };




    //methods

    CPU(const MMUPtr &mmu)
        : mmu(mmu)
    {}

    const State &getState() const noexcept;
    void step();
    void reset();


private:
    MMUPtr mmu;
    State state;
    const std::array<OpcodePtr, 256> opcodes = {{
                                                    OP([](){}, 4)
                                                }};
};

typedef std::shared_ptr<CPU> CPUPtr;
}

#endif
