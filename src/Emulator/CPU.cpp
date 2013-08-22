#include "CPU.h"

using namespace GBEmu;

static inline void LD(byte &register1, byte value1, byte &register2, byte value2){
    register1 = value1;
    register2 = value2;
}

CPU::CPU()
    :opcodes({{
             Op([](){}, 4, 1), //NOP
             Op([&](){ //LD BC, NN
    LD(state.registers.C, mmu.readByte(state.registers.PC + 1),
       state.registers.B, mmu.readByte(state.registers.PC + 2));
},
12, 3)

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
    state.clock.totalCycles +=  op.getCycles();

    state.registers.PC += op.getSize(); //go to next instruction

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
CPU::Op::Op(std::function<void (void)> op, int cycles, int size)
    : operation(op), cycles(cycles), isImplemented(true), size(size)
{}

CPU::Op::Op()
    :cycles(0), isImplemented(false), size(1)
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

int CPU::Op::getSize() const noexcept{
    return size;
}




