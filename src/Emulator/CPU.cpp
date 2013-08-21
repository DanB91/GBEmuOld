#include "CPU.h"

namespace GBEmu{

CPU::CPU()
    :opcodes({{

        Op([](){}, 4)

    }})
{}
const CPU::State &CPU::getState() const noexcept{
    return state;
}

const MMU &CPU::getMMU() const noexcept{
    return mmu;
}

void CPU::step(){

    const Op &op =  opcodes[mmu.readByte(state.registers.PC)];

    op(); //execute opcode
    state.clock.cyclesSinceLastInstruction = op.getCycles(); //how many cycles did this operation take?

    state.registers.PC++; //go to next instruction

    if(state.registers.PC == 0x100){
        mmu.leaveBIOS();
    }
}

void CPU::reset(){
    state = State();
}

void CPU::loadROM(const std::string &romFileName){
    mmu.loadROM(romFileName);
}


//Op implementation
CPU::Op::Op(std::function<void (void)> op, int cycles)
    : operation(op), cycles(cycles), isImplemented(true)
{}

CPU::Op::Op()
    :isImplemented(false)
{}  //will remove eventually

//execute opcode
void CPU::Op::operator()() const{
    if(isImplemented){
        operation();
    }

}

int CPU::Op::getCycles() const noexcept{
    return cycles;
}



}
