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
                    byte A, B, C, D, H, L, F;
                    word PC, SP;
                } registers;

                struct{
                    int cyclesSinceLastInstruction, totalCycles;
                } clock;

            }; 

            //represents a single opcode
            struct Opcode{
                std::function<void (void)> operation;
                int cycles;

                Opcode(std::function<void (void)> op, int cycles)
                    : operation(op), cycles(cycles)
                {}

                Opcode(){};  //will remove

                void operator()(){
                    operation();
                }

            };

            //methods

            CPU(const MMUPtr &mmu)
                : mmu(mmu), state({}),
                opcodes({
                        Opcode([](){}, 4)
                        })
                {}

            const State &getState() const; 
            void step();
            void reset();


        private:
            MMUPtr mmu;
            State state;
            const std::array<Opcode, 256> opcodes;
    };

    typedef std::shared_ptr<CPU> CPUPtr;
}

#endif
