#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <string>
#include <memory>
#include <vector>
#include "types.h"

namespace GBEmu{
    class Cartridge{
        public:

            Cartridge(const std::string &romFileName);
            
            byte readROM(word address) const;
            byte readRAM(word address) const;

            void writeROM(word address, byte value);
            void writeRAM(word address, byte value);
            
            int getCartType() const;
            const std::vector<byte> &getROM() const ;

        private:
            void loadROM(const std::string &romFileName);

            std::vector<byte> ROM;

    };


    typedef std::shared_ptr<Cartridge> CartridgePtr;
}
#endif
