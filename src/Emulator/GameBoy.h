#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <string>
#include "CPU.h"
#include "CPUDebugInfo.h"

namespace GBEmu{
class GameBoy{

public:

    GameBoy();
    const CPU::State &getCPUState() const noexcept;
    const CPUDebugInfo &getCPUDebugInfo() const noexcept;

    void step(); //steps through one instruction
    void loadROM(const std::string &romFileName);
    bool isROMLoaded() const noexcept;


private:
    CPU cpu;
    bool romLoaded;
    CPUDebugInfo cpuDebugInfo;




};

}

#endif
