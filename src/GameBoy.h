#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <string>
#include "MMU.h"
#include "Cartridge.h"

namespace GBEmu{
    class GameBoy{

        public:
            GameBoy()
                :isRunning(false)
            {}

            void loadROM(const std::string &fileName);
            void start(); //starts the emulator
            void reset(); //resets all values back to default, but keeps the ROM loaded
            void pause();

        private:
            CartridgePtr cart;
            MMUPtr mmu;
            bool isRunning;

    };
}

#endif
