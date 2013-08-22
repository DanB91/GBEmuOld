#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <string>
#include "CPU.h"
#include "CPUDebugInfo.h"

namespace GBEmu{
class GameBoy{

public:

    GameBoy();
    const CPU &getCPU() const noexcept;

    void step(); //steps through one instruction
    void loadROM(const std::string &romFileName);
    bool isROMLoaded() const noexcept;


private:
    CPU cpu;
    bool romLoaded;




};

}

#endif
