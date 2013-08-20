#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <string>
#include "CPU.h"

namespace GBEmu{
  class GameBoy{

  public:
    GameBoy()
        : romLoaded(false)
    {}

    void step(); //steps through one instruction
    const CPU::State &getCPUState() const noexcept;
    void loadROM(const std::string &romFileName);
    bool isROMLoaded() const noexcept;

  private:
    CPU cpu;
    bool romLoaded;

  };

}

#endif
