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
      :cart(new Cartridge(fileName)),
        mmu(new MMU(cart)),
        cpu(new CPU(mmu))
    {}

    void step(); //steps through one instruction
    const CPU::State &getCPUState() const noexcept;

  private:
    CartridgePtr cart;
    MMUPtr mmu;
    CPUPtr cpu;

  };

  typedef std::shared_ptr<GameBoy> GameBoyPtr;
}

#endif
