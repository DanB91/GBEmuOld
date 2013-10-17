#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <string>
#include "CPU.h"
#include "CPUDebugInfo.h"

namespace GBEmu{
class GameBoy{

public:
    static const int SCREEN_HEIGHT = 144;
    static const int SCREEN_LENGTH = 160;

    GameBoy();
    const CPU &getCPU() const noexcept;

    void step(); //steps through one instruction
    void loadROM(const std::string &romFileName);
    bool isROMLoaded() const noexcept;


private:
    bool romLoaded;
    CPU::UPtr cpu;





};

}

#endif
