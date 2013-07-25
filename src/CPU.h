#ifndef CPU_H
#define CPU_H

#include <functional>
#include "MMU.h"

namespace GBEmu{
    class CPU{

        public:
            CPU(const MMUPtr &mmu)
                : mmu(mmu)
            {}

            void step();


        private:
            MMUPtr mmu;

            struct{
                byte A, B, C, D, H, L, F;
                word PC, SP;
            } registers;


            struct{
                int cyclesSinceLastInstruction, totalCycles;
            } clock;

            std::array<std::function<void (void)>, 256> opCodes;

            void init();
    };
}

#endif
