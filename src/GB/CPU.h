#ifndef CPU_H
#define CPU_H

#include <functional>
#include <memory>
#include "MMU.h"

namespace GBEmu{
    class CPU{

        public:
            //the state of the CPU, all in one neat structure
            struct State{

                struct{
                    byte A, B, C, D, H, L, F;
                    word PC, SP;
                } registers;

                struct{
                    int cyclesSinceLastInstruction, totalCycles;
                } clock;

            }; 

            CPU(const MMUPtr &mmu)
                : mmu(mmu), state({0, 0})
                {}

            const State &getState() const; 
            void step();


        private:
            MMUPtr mmu;
            State state;
            std::array<std::function<void (void)>, 256> opCodes;
            void init();
    };

    typedef std::shared_ptr<CPU> CPUPtr;
}

#endif
