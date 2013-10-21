#include "CPU.h"


using namespace GBEmu;


CPU::UPtr CPU::makeCPU()
{
    return UPtr(new CPU(MMU::makeMMU()));
}

CPU::CPU(MMU::UPtr m)
    :mmu(std::move(m)),
      opcodes()

{
    initOpcodes();
}


const MMU &CPU::getMMU() const noexcept{
    return *mmu;
}

byte CPU::getA() const noexcept{
    return A;
}

byte CPU::getB() const noexcept{
    return B;
}

byte CPU::getC() const noexcept{
    return C;
}

byte CPU::getD() const noexcept{
    return D;
}

byte CPU::getE() const noexcept{
    return E;
}

byte CPU::getF() const noexcept{
    return F;
}

byte CPU::getH() const noexcept{
    return H;
}

byte CPU::getL() const noexcept{
    return L;
}


word CPU::getAF() const noexcept{
    return (A << 8) | F;
}

word CPU::getBC() const noexcept{
    return (B << 8) | C;
}

word CPU::getDE() const noexcept{
    return (D << 8) | E;
}

word CPU::getHL() const noexcept{
    return (H << 8) | L;
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




