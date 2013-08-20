#include "GameBoy.h"

using namespace GBEmu;

void GameBoy::loadROM(const std::string &romFileName){
    cpu.loadROM(romFileName);
    romLoaded = true;
}

const CPU::State &GameBoy::getCPUState() const noexcept{
    return cpu.getState();

}

void GameBoy::step(){
    cpu.step();
}

bool GameBoy::isROMLoaded() const noexcept{
    return romLoaded;
}
