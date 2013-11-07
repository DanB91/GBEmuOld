#ifndef OPCODES_INLINE_H
#define OPCODES_INLINE_H
#include "CPU.h"

using namespace GBEmu;

inline void CPU::setFlag(Flag flag){
    F |= static_cast<byte>(flag);
}

inline void CPU::clearFlag(Flag flag){
    F &= ~static_cast<byte>(flag);
}

inline bool CPU::isFlagSet(Flag flag){
    return (F & static_cast<byte>(flag)) != 0;
}


//loads 16 bit immediate
inline void  CPU::load16BitImmediate(byte &destHigh, byte &destLow){
    destHigh = mmu->readByte(PC + 2);
    destLow = mmu->readByte(PC + 1);
}

//increment 16 bit value
inline void CPU::increment16Bit(byte &high, byte &low){
    word w = wordFromBytes(high, low);
    w++;
    high = highByte(w);
    low = lowByte(w);
}

//decrement 16 bit values
inline void CPU::decrement16Bit(byte &high, byte &low){
    word w = wordFromBytes(high, low);
    w--;
    high = highByte(w);
    low = lowByte(w);
}

//incrememnt 8 bit values
inline void CPU::increment8Bit(byte &value){
    value++;

    if(value == 0)
        setFlag(Flag::Z);

    clearFlag(Flag::N);

    if((value & 0xF) == 0)
        setFlag(Flag::H);
}

//decrement 8 bit value
inline void CPU::decrement8Bit(byte &value){
    value--;

    if(value == 0)
        setFlag(Flag::Z);

    setFlag(Flag::N);

    if((value & 0xF) == 0xF)
        setFlag(Flag::H);
}


inline void CPU::rotateLeft(byte &value){
    if(value & 0x80)
        setFlag(Flag::C);
    else
        clearFlag(Flag::C);

    value = (value << 1) | ((value >> 7) & 1);

    clearFlag(Flag::N);
    clearFlag(Flag::H);
    clearFlag(Flag::Z);
}

inline void CPU::rotateRight(byte &value)
{
    if(value & 1){
        setFlag(Flag::C);
    } else{
        clearFlag(Flag::C);
    }

    value = (value >> 1) | ((value << 7) & 0x80);

    clearFlag(Flag::N);
    clearFlag(Flag::H);
    clearFlag(Flag::Z);
}

void CPU::rotateLeftThroughCarry(byte &value)
{
    byte temp = (value << 1) | ((F & static_cast<byte>(Flag::C)) ? 1 : 0);

    if(value & 0x80)
        setFlag(Flag::C);
    else
        clearFlag(Flag::C);

    value = temp;

    clearFlag(Flag::N);
    clearFlag(Flag::H);
    clearFlag(Flag::Z);

}

void CPU::rotateRightThroughCarry(byte &value)
{
    byte temp = ((F & static_cast<byte>(Flag::C)) ? 0x80 : 0) | (value >> 1) ;

    if(value & 0x1)
        setFlag(Flag::C);
    else
        clearFlag(Flag::C);

    value = temp;

    clearFlag(Flag::N);
    clearFlag(Flag::H);
    clearFlag(Flag::Z);
}

inline void CPU::addHL(word addend){
    int result = getHL() + addend;

    clearFlag(Flag::N);

    //carry from 15th bit
    if(result & 0x10000){
        setFlag(Flag::C);
    }

    //carry from 11th bit
    if((getHL() ^ addend ^ (result & 0xFFFF)) & 0x1000){
        setFlag(Flag::H);
    }

    H = highByte(result);
    L = lowByte(result);

}

inline void CPU::jumpIfClear8Bit(Flag flag, byte value){
    if(!isFlagSet(flag)){
        PC += static_cast<int8_t>(value);
        performedAction = true;
    } else{
        performedAction = false;
    }
}

inline void CPU::decimalAdjust(byte &value)
{
    unsigned result = static_cast<unsigned>(value);
    
    if(!isFlagSet(Flag::N)){ //if addition was used
        if(isFlagSet(Flag::H) || (result & 0xF) > 9){ //adjust low nibble
            result += 0x6;
        }

        if(isFlagSet((Flag::C)) || (result & 0xF0) > 0x90){ //adjust high nibble
            result += 0x60;
        }

    } else{ //subtraction used
       if(isFlagSet(Flag::H)){
           result = (result - 6) & 0xFF;
       }

       if(isFlagSet(Flag::C)){
           result -= 0x60;
       }

    }

    if(result & 0x100){
        setFlag(Flag::C);
    }

    clearFlag(Flag::H);

    if((result & 0xFF) == 0){
        setFlag(Flag::Z);
    } else{
        clearFlag(Flag::Z);
    }

    value = result;
}

inline void CPU::jumpIfSet8Bit(Flag flag, byte value){
    if(isFlagSet(flag)){
        PC += static_cast<int8_t>(value);
        performedAction =  true;
    } else{
        performedAction = false;
    }
}




#endif // OPCODES_INLINE_H
