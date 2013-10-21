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
                  Op([&](){ //1 LD BC, NN
        load16BitImmediate(D, E);
    },
    12, 3)
                  }};
}
