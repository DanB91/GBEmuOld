#include "CPU.h"

using namespace GBEmu;


CPU::UPtr CPU::makeCPU()
{
    return UPtr(new CPU(MMU::makeMMU()));
}

CPU::CPU(MMU::UPtr m)
    :mmu(std::move(m)),
      opcodes({{
              Op([](){}, 4, 1), //NOP
              Op([&](){ //LD BC, NN
    BC = mmu->readWord(PC + 1);

},
12, 3),
              Op([&](){ //LD (BC), A
    mmu->writeByte(highByte(AF), BC);
},8, 1),
              Op([&](){ // INC BC
    BC++;
}, 8, 1),
              Op([&](){ //INC B
    setHighByte(BC, highByte(BC) + 1);
}, 8, 1),


              }})

{}


MMU &CPU::getMMU() const noexcept{
    return *mmu;
}

word CPU::getAF() const noexcept{
    return AF;
}

word CPU::getBC() const noexcept{
    return BC;
}

word CPU::getDE() const noexcept{
    return DE;
}

word CPU::getHL() const noexcept{
    return HL;
}

word CPU::getSP() const noexcept{
    return SP;
}

word CPU::getPC() const noexcept{
    return PC;
}

int CPU::getCyclesSinceLastInstruction() const noexcept{
    return cyclesSinceLastInstruction;
}

int CPU::getTotalCycles() const noexcept{
    return totalCycles;
}

void CPU::step(){

    const Op &op =  opcodes[mmu->readByte(PC)];


    op(); //execute opcode
    cyclesSinceLastInstruction = op.getCycles(); //how many cycles did this operation take?
    totalCycles +=  op.getCycles();

    PC += op.getSize(); //go to next instruction

    if(PC == 0x100){
        mmu->leaveBIOS();
    }
}


void CPU::loadROM(const std::string &romFileName){
    mmu->loadROM(romFileName);
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




