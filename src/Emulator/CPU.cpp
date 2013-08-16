#include "CPU.h"

namespace GBEmu{

    const CPU::State &CPU::getState() const noexcept{
        return state;
    }

    void CPU::step(){

        OpcodePtr op =  opcodes[mmu->readByte(state.registers.PC)];

        if(op){
            op->execute();
            state.clock.cyclesSinceLastInstruction = op->cycles;

       }
        state.registers.PC++;



    }

    void CPU::reset(){
        state = State();
    }

    


}
