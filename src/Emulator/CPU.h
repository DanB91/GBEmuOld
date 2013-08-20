#ifndef CPU_H
#define CPU_H


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

    CPU()
    {}

    const State &getState() const noexcept;
    void step();
    void reset();
    void loadROM(const std::string &romFileName);


private:

    MMU mmu;
    State state;
    std::array<Op, 256> opcodes = {{
                                             Op([](){}, 4)
                                         }};
};

}

#endif
