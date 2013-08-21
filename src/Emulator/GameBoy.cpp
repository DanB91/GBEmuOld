#include "GameBoy.h"

using namespace GBEmu;

GameBoy::GameBoy()
    : romLoaded(false), cpuDebugInfo(&cpu)
{}

void GameBoy::loadROM(const std::string &romFileName){
    cpu.loadROM(romFileName);
    romLoaded = true;
}

const CPU::State &GameBoy::getCPUState() const noexcept{
    return cpu.getState();

}

const CPUDebugInfo &GameBoy::getCPUDebugInfo() const noexcept{
    return cpuDebugInfo;
}

void GameBoy::step(){
    cpu.step();
}

bool GameBoy::isROMLoaded() const noexcept{
    return romLoaded;
}
