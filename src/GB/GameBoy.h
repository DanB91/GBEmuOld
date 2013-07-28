#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <string>
#include <memory>
#include "MMU.h"
#include "Cartridge.h"
#include "CPU.h"

namespace GBEmu{
    class GameBoy{

        public:
            GameBoy(const std::string &fileName)
                :isRunning(false),
                cart(new Cartridge(fileName)),
                mmu(new MMU(cart)),
                cpu(new CPU(mmu))
            {}
           
            void start(); //starts the emulator
            void reset(); //resets all values back to default, but keeps the ROM loaded
            void pause();

            const CPU::State &getCPUState() const;

        private:
            bool isRunning;
            CartridgePtr cart;
            MMUPtr mmu;
            CPUPtr cpu;

    };

    typedef std::shared_ptr<GameBoy> GameBoyPtr;
}

#endif
