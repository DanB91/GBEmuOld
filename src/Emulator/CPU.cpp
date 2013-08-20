#include "CPU.h"

namespace GBEmu{

const CPU::State &CPU::getState() const noexcept{
    return state;
}

void CPU::step(){

    const Op &op =  opcodes[mmu.readByte(state.registers.PC)];

    op(); //execute opcode
    state.clock.cyclesSinceLastInstruction = op.getCycles(); //how many cycles did this operation take?

    state.registers.PC++; //go to next instruction
}

void CPU::reset(){
    state = State();
}

void CPU::loadROM(const std::string &romFileName){
    mmu.loadROM(romFileName);
}



}
