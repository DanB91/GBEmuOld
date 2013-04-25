#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <string>
#include <memory>

#include "types.h"

namespace GBEmu{
    class Cartridge{
        public:

            Cartridge(const std::string &romFileName);
            byte readROM(word address) const;

        private:
            void loadROM(const std::string &romFileName);

            std::shared_ptr<byte> ROM;

    };


    typedef std::shared_ptr<Cartridge> CartridgePtr;
}
#endif
