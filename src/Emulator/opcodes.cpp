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
                             addToHL(getBC());
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
                             addToHL(getDE());
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
                   Op([&](){ //1D DEC E
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
                   Op([&](){ //29 ADD HL, HL
                             addToHL(getHL());
                   }, 8, 1),
                   Op([&](){ //2A LD A, (HL+)
                             A = mmu->readByte(getHL());
                             increment16Bit(H, L); //increment HL
                   },8, 1),
                   Op([&](){ //2B DEC HL
                             decrement16Bit(H, L);
                   }, 8, 1),
                   Op([&](){ //2C INC L
                             increment8Bit(L);
                   }, 4, 1),
                   Op([&](){ //2D DEC L
                             decrement8Bit(L);
                   }, 4, 1),
                   Op([&](){ //2E LD L, d8
                             L = mmu->readByte(PC + 1);
                   }, 8, 2),
                   Op([&](){ //2F CPL
                             complement(A);
                   }, 4, 1),


                   Op([&](){ //30 JR NC, r8
                             jumpIfClear8Bit(Flag::C, mmu->readByte(PC + 1));
                   }, 12, 8, 2),
                   Op([&](){ //31 LD SP, NN
                             SP = mmu->readWord(PC + 1);
                   },12, 3),

                   Op([&](){ //32 LD (HL-), A
                             mmu->writeByte(A, getHL());
                             decrement16Bit(H, L); //decrement HL

                   },8, 1),
                   Op([&](){ //33 INC SP
                             SP++;
                   }, 8, 1),
                   Op([&](){ //34 INC (HL)
                             byte b = mmu->readByte(getHL());
                             increment8Bit(b);
                             mmu->writeByte(b, getHL());
                   }, 12, 1),
                   Op([&](){ //35 DEC (HL)
                             byte b = mmu->readByte(getHL());
                             decrement8Bit(b);
                             mmu->writeByte(b, getHL());
                   }, 12, 1),

                   Op([&](){ //36 LD (HL), d8
                             mmu->writeByte(mmu->readByte(PC + 1), getHL());

                   }, 12, 2),

                   Op([&](){ //37 SCF
                             setFlag(Flag::C);
                             clearFlag(Flag::N);
                             clearFlag(Flag::H);

                   }, 4, 1),

                   Op([&](){ //38 JR C, r8
                             jumpIfSet8Bit(Flag::C, mmu->readByte(PC + 1));
                   }, 12, 8, 2),

                   Op([&](){ //39 ADD HL, SP
                             addToHL(SP); //need to add test
                   }, 8, 1),

                   Op([&](){ //3A LD A, (HL-)
                             A = mmu->readByte(getHL());
                             decrement16Bit(H, L); //decrement HL
                   },8, 1),

                   Op([&](){ //3B DEC SP
                             SP--;
                   }, 8, 1),

                   Op([&](){ //3C INC A
                             increment8Bit(A);
                   }, 4, 1),

                   Op([&](){ //3D DEC A
                             decrement8Bit(A);
                   }, 4, 1),

                   Op([&](){ //3E LD A, d8
                             A = mmu->readByte(PC + 1);
                   }, 8, 2),

                   Op([&](){ //3F CCF
                             if(isFlagSet(Flag::C)){
                                 clearFlag(Flag::C);
                             }
                             else{
                                 setFlag(Flag::C);
                             }

                             clearFlag(Flag::N);
                             clearFlag(Flag::H);

                   }, 4, 1),

                   Op([&](){ //40 LD B, B
                       B = B;
                   }, 4, 1),

                   Op([&](){ //41 LD B, C
                       B = C;
                   }, 4, 1),

                   Op([&](){ //42 LD B, D
                       B = D;
                   }, 4, 1),

                   Op([&](){ //43 LD B, E
                       B = E;
                   }, 4, 1),

                   Op([&](){ //44 LD B, H
                       B = H;
                   }, 4, 1),

                   Op([&](){ //45 LD B, L
                       B = L;
                   }, 4, 1),

                   Op([&](){ //46 LD B, (HL)
                             B = mmu->readByte(getHL());
                   }, 8, 1),

                   Op([&](){ //47 LD B, A
                       B = A;
                   }, 4, 1),

                   Op([&](){ //48 LD C, B
                       C = B;
                   }, 4, 1),

                   Op([&](){ //49 LD C, C
                       C = C;
                   }, 4, 1),

                   Op([&](){ //4A LD C, D
                       C = D;
                   }, 4, 1),

                   Op([&](){ //4B LD C, E
                       C = E;
                   }, 4, 1),

                   Op([&](){ //4C LD C, H
                       C = H;
                   }, 4, 1),

                   Op([&](){ //4D LD C, L
                       C = L;
                   }, 4, 1),

                   Op([&](){ //4E LD C, (HL)
                             C = mmu->readByte(getHL());
                   }, 8, 1),

                   Op([&](){ //4F LD C, A
                       C = A;
                   }, 4, 1),

                   Op([&](){ //50 LD D, B
                       D = B;
                   }, 4, 1),

                   Op([&](){ //51 LD D, C
                       D = C;
                   }, 4, 1),

                   Op([&](){ //52 LD D, D
                       D = D;
                   }, 4, 1),

                   Op([&](){ //53 LD D, E
                       D = E;
                   }, 4, 1),

                   Op([&](){ //54 LD D, H
                       D = H;
                   }, 4, 1),

                   Op([&](){ //55 LD D, L
                       D = L;
                   }, 4, 1),

                   Op([&](){ //56 LD D, (HL)
                             D = mmu->readByte(getHL());
                   }, 8, 1),

                   Op([&](){ //57 LD D, A
                       D = A;
                   }, 4, 1),

                   Op([&](){ //58 LD E, B
                       E = B;
                   }, 4, 1),

                   Op([&](){ //59 LD E, C
                       E = C;
                   }, 4, 1),

                   Op([&](){ //5A LD E, D
                       E = D;
                   }, 4, 1),

                   Op([&](){ //5B LD E, E
                       E = E;
                   }, 4, 1),

                   Op([&](){ //5C LD E, H
                       E = H;
                   }, 4, 1),

                   Op([&](){ //5D LD E, L
                       E = L;
                   }, 4, 1),

                   Op([&](){ //5E LD E, (HL)
                             E = mmu->readByte(getHL());
                   }, 8, 1),

                   Op([&](){ //5F LD E, A
                       E = A;
                   }, 4, 1),

                   Op([&](){ //60 LD H, B
                       H = B;
                   }, 4, 1),

                   Op([&](){ //61 LD H, C
                       H = C;
                   }, 4, 1),

                   Op([&](){ //62 LD H, D
                       H = D;
                   }, 4, 1),

                   Op([&](){ //63 LD H, E
                       H = E;
                   }, 4, 1),

                   Op([&](){ //64 LD H, H
                       H = H;
                   }, 4, 1),

                   Op([&](){ //65 LD H, L
                       H = L;
                   }, 4, 1),

                   Op([&](){ //66 LD H, (HL)
                             H = mmu->readByte(getHL());
                   }, 8, 1),

                   Op([&](){ //67 LD H, A
                       H = A;
                   }, 4, 1),

                   Op([&](){ //68 LD L, B
                       L = B;
                   }, 4, 1),

                   Op([&](){ //69 LD L, C
                       L = C;
                   }, 4, 1),

                   Op([&](){ //6A LD L, D
                       L = D;
                   }, 4, 1),

                   Op([&](){ //6B LD L, E
                       L = E;
                   }, 4, 1),

                   Op([&](){ //6C LD L, H
                       L = H;
                   }, 4, 1),

                   Op([&](){ //6D LD L, L
                       L = L;
                   }, 4, 1),

                   Op([&](){ //6E LD L, (HL)
                             L = mmu->readByte(getHL());
                   }, 8, 1),

                   Op([&](){ //6F LD L, A
                       L = A;
                   }, 4, 1),

                   Op([&](){ //70 LD (HL), B
                             mmu->writeByte(B, getHL());
                   }, 8, 1),

                   Op([&](){ //71 LD (HL), C
                       mmu->writeByte(C, getHL());
                   }, 8, 1),

                   Op([&](){ //72 LD (HL), D
                       mmu->writeByte(D, getHL());
                   }, 8, 1),

                   Op([&](){ //73 LD (HL), E
                       mmu->writeByte(E, getHL());
                   }, 8, 1),

                   Op([&](){ //74 LD (HL), H
                       mmu->writeByte(H, getHL());
                   }, 8, 1),

                   Op([&](){ //75 LD (HL), L
                       mmu->writeByte(L, getHL());
                   }, 8, 1),

                   Op([&](){ //76 HALT
                        //will be implemented later
                   }, 8, 1),

                   Op([&](){ //77 LD (HL), A
                       mmu->writeByte(A, getHL());
                   }, 8, 1),

                   Op([&](){ //78 LD A, B
                       A = B;
                   }, 4, 1),

                   Op([&](){ //79 LD A, C
                       A = C;
                   }, 4, 1),

                   Op([&](){ //7A LD A, D
                       A = D;
                   }, 4, 1),

                   Op([&](){ //7B LD A, E
                       A = E;
                   }, 4, 1),

                   Op([&](){ //7C LD A, H
                       A = H;
                   }, 4, 1),

                   Op([&](){ //7D LD A, L
                       A = L;
                   }, 4, 1),

                   Op([&](){ //7E LD A, (HL)
                             A = mmu->readByte(getHL());
                   }, 8, 1),

                   Op([&](){ //7F LD A, A
                       A = A;
                   }, 4, 1),

                   Op([&](){ //80 ADD A, B
                       addToA(B);
                   }, 4, 1),

                   Op([&](){ //81 ADD A, C
                       addToA(C);
                   }, 4, 1),

                   Op([&](){ //82 ADD A, D
                       addToA(D);
                   }, 4, 1),

                   Op([&](){ //83 ADD A, E
                       addToA(E);
                   }, 4, 1),

                   Op([&](){ //84 ADD A, H
                       addToA(H);
                   }, 4, 1),

                   Op([&](){ //85 ADD A, L
                       addToA(L);
                   }, 4, 1),

                   Op([&](){ //86 ADD A, (HL)
                             addToA(mmu->readByte(getHL()));
                   }, 8, 1),

                   Op([&](){ //87 ADD A, A
                             addToA(A);
                   }, 4, 1),

                   Op([&](){ //88 ADC A, B
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             addToA(B + carry);
                   }, 4, 1),

                   Op([&](){ //89 ADC A, C
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             addToA(C + carry);
                   }, 4, 1),

                   Op([&](){ //8A ADC A, D
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             addToA(D + carry);
                   }, 4, 1),

                   Op([&](){ //8B ADC A, E
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             addToA(E + carry);
                   }, 4, 1),

                   Op([&](){ //8C ADC A, H
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             addToA(H + carry);
                   }, 4, 1),

                   Op([&](){ //8D ADC A, L
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             addToA(L + carry);
                   }, 4, 1),

                   Op([&](){ //8E ADC A, (HL)
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             addToA(mmu->readByte(getHL()) + carry);
                   }, 8, 1),

                   Op([&](){ //8F ADC A, A
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             addToA(A + carry);
                   }, 4, 1),

                   Op([&](){ //90 SUB B
                       subtractFromA(B);
                   }, 4, 1),

                   Op([&](){ //91 SUB C
                       subtractFromA(C);;
                   }, 4, 1),

                   Op([&](){ //92 SUB D
                       subtractFromA(D);;
                   }, 4, 1),

                   Op([&](){ //93 SUB E
                       subtractFromA(E);;
                   }, 4, 1),

                   Op([&](){ //94 SUB H
                       subtractFromA(H);;
                   }, 4, 1),

                   Op([&](){ //95 SUB L
                       subtractFromA(L);
                   }, 4, 1),

                   Op([&](){ //96 SUB (HL)
                             subtractFromA(mmu->readByte(getHL()));
                   }, 8, 1),

                   Op([&](){ //97 SUB A
                             subtractFromA(A);
                   }, 4, 1),

                   Op([&](){ //98 SBC B
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             subtractFromA(B + carry);
                   }, 4, 1),

                   Op([&](){ //99 SBC C
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             subtractFromA(C + carry);
                   }, 4, 1),

                   Op([&](){ //9A SBC D
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             subtractFromA(D + carry);
                   }, 4, 1),

                   Op([&](){ //9B SBC E
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             subtractFromA(E + carry);
                   }, 4, 1),

                   Op([&](){ //9C SBC H
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             subtractFromA(H + carry);
                   }, 4, 1),

                   Op([&](){ //9D SBC L
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             subtractFromA(L + carry);
                   }, 4, 1),

                   Op([&](){ //9E SBC (HL)
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             subtractFromA(mmu->readByte(getHL()) + carry);
                   }, 8, 1),

                   Op([&](){ //9F SBC A
                             int carry = isFlagSet(Flag::C) ? 1 : 0;
                             subtractFromA(A + carry);
                   }, 4, 1),

                   Op([&](){ //A0 AND B
                           andToA(B);
                           }, 4, 1),

                   Op([&](){ //A1 AND C
                           andToA(C);
                           }, 4, 1),

                   Op([&](){ //A2 AND D
                           andToA(D);
                           }, 4, 1),

                   Op([&](){ //A3 AND E
                           andToA(E);
                           }, 4, 1),

                   Op([&](){ //A4 AND H
                           andToA(H);
                           }, 4, 1),

                   Op([&](){ //A5 AND L
                           andToA(L);
                           }, 4, 1),

                   Op([&](){ //A6 AND (HL)
                           andToA(mmu->readByte(getHL()));
                           }, 8, 1),

                   Op([&](){ //A7 AND A
                           andToA(A);
                           }, 4, 1),



               }};
}
