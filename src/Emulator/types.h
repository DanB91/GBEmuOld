#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

namespace GBEmu{

    typedef uint8_t byte;

    //big-endian 2-byte value
    class word{
        public:
            inline  word(uint16_t value) noexcept
                :value(value)
            {}

            inline word(byte h, byte l)

            {
                value = (h << 8) | l;
            }

            inline  word() noexcept
                :value(0)
            {}


            inline operator uint16_t&() noexcept{
                return value;
            }

            inline byte high(){
                return (value >> 8) & 0xFF;
            }

            inline byte low(){
                return value & 0xFF;
            }

        private:
            uint16_t value;




    };

}

#endif

