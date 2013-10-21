#include "CPU.h"
#include "opcodes_inline.h"

using namespace GBEmu;


CPU::UPtr CPU::makeCPU()
{
    return UPtr(new CPU(MMU::makeMMU()));
}

CPU::CPU(MMU::UPtr m)
    :mmu(std::move(m)),
      opcodes({{
              Op([](){}, 4, 1), //0 NOP

              Op([&](){ //1 LD BC, NN
    load16BitImmediate(B, C);
},
12, 3),
              Op([&](){ //2 LD (BC), A
    mmu->writeByte(A, getBC());
},8, 1),
              Op([&](){ //3 INC BC
    increment16Bit(B, C);
}, 8, 1),
              Op([&](){ //4 INC B
    increment8Bit(B);
}, 4, 1),
              Op([&](){ //5 DEC B
    decrement8Bit(B);
}, 4, 1),
              Op([&](){ //6 LD B, d8
    B = mmu->readByte(PC + 1);
}, 8, 2),
              Op([&](){ //7 RLCA
    rotateLeft(A);
}, 4, 1),
              Op([&](){ //8 LD (nn), SP
    mmu->writeWord(SP, mmu->readWord(PC + 1));
}, 20, 3),
              Op([&](){ //9 ADD HL, BC
    addHL(getBC());
}, 8, 1),
              Op([&](){ //A LD A, (BC)
    A = mmu->readByte(getBC());
}, 8, 1),
              Op([&](){ //B DEC BC
    decrement16Bit(B, C);
}, 8, 1),
              Op([&](){ //C INC C
    increment8Bit(C);
}, 4, 1),
              Op([&](){ //D INC C
    decrement8Bit(C);
}, 4, 1),
              Op([&](){ //E LD C, d8
    C = mmu->readByte(PC + 1);
}, 8, 2),
              Op([&](){ //F RRCA
    rotateRight(A);
}, 4, 1)
              }})

{}


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




