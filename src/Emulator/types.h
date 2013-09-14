#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

namespace GBEmu{

typedef uint8_t byte;
typedef uint16_t word;

inline byte lowByte(word w){
    return w & 0xFF;
}

inline byte highByte(word w){
    return (w >> 8) & 0xFF;
}

inline word wordFromBytes(byte high, byte low){
    return (high << 8) | low;
}

inline void setHighByte(word &w, byte b){
    w = (b << 8) |(w & 0xFF);
}

}

#endif

