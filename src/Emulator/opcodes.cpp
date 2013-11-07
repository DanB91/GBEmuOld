#include "CPU.h"
#include "opcodes_inline.h"

void CPU::initOpcodes(){
    opcodes = {{
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
                   }, 4, 1),
                   Op([&](){ //10 STOP 0
                             //will be implemented later
                   }, 4, 2),
                   Op([&](){ //11 LD BC, NN
                             load16BitImmediate(D, E);
                   },12, 3),
                   Op([&](){ //12 LD (DE), A
                             mmu->writeByte(A, getDE());
                   },8, 1),
                   Op([&](){ //13 INC DE
                             increment16Bit(D, E);
                   }, 8, 1),
                   Op([&](){ //14 INC D
                             increment8Bit(D);
                   }, 4, 1),
                   Op([&](){ //15 DEC D
                             decrement8Bit(D);
                   }, 4, 1),
                   Op([&](){ //16 LD D, d8
                             D = mmu->readByte(PC + 1);
                   }, 8, 2),
                   Op([&](){ //17 RLA
                             rotateLeftThroughCarry(A);
                   }, 4, 1),
                   Op([&](){ //18 JR r8
                             PC += static_cast<int8_t>(mmu->readByte(PC + 1));
                   }, 12, 2),
                   Op([&](){ //19 ADD HL, DE
                             addHL(getDE());
                   }, 8, 1),
                   Op([&](){ //1A LD A, (DE)
                             A = mmu->readByte(getDE());
                   }, 8, 1),
                   Op([&](){ //1B DEC DE
                             decrement16Bit(D, E);
                   }, 8, 1),
                   Op([&](){ //1C INC E
                             increment8Bit(E);
                   }, 4, 1),
                   Op([&](){ //1D INC E
                             decrement8Bit(E);
                   }, 4, 1),
                   Op([&](){ //1E LD E, d8
                             E = mmu->readByte(PC + 1);
                   }, 8, 2),
                   Op([&](){ //1F RCA
                             rotateRightThroughCarry(A);
                   }, 4, 1),
                   Op([&](){ //20 JR NZ, r8
                             jumpIfClear8Bit(Flag::Z, mmu->readByte(PC + 1));
                   }, 12, 8, 2),
                   Op([&](){ //21 LD HL, NN
                             load16BitImmediate(H, L);
                   },12, 3),

                   Op([&](){ //22 LD (HL+), A
                             mmu->writeByte(A, getHL());
                             increment16Bit(H, L); //increment HL

                   },8, 1),
                   Op([&](){ //23 INC HL
                             increment16Bit(H, L);
                   }, 8, 1),
                   Op([&](){ //24 INC H
                             increment8Bit(H);
                   }, 4, 1),
                   Op([&](){ //25 DEC H
                             decrement8Bit(H);
                   }, 4, 1),
                   Op([&](){ //26 LD H, d8
                             H = mmu->readByte(PC + 1);
                   }, 8, 2),
                   Op([&](){ //27 DAA
                             decimalAdjust(A);
                   }, 4, 1),
                   Op([&](){ //28 JR Z, r8
                             jumpIfSet8Bit(Flag::Z, mmu->readByte(PC + 1));
                   }, 12, 8, 2),

               }};
}
