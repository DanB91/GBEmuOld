#include "CPU.h"

namespace GBEmu{

    const CPU::State &CPU::getState() const{
        return state;
    }

    void CPU::step(){
        Opcode op = opcodes[mmu->readByte(state.registers.PC)];
        op();
        state.clock.cyclesSinceLastInstruction = op.cycles;
        state.registers.PC++;

    }

    void CPU::reset(){
        state = {};
    }

    


}
