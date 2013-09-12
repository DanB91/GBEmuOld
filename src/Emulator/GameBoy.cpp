#include "GameBoy.h"
#include "GBEmuExceptions.h"

using namespace GBEmu;

GameBoy::GameBoy()
    : romLoaded(false),
      cpu(CPU::makeCPU())
{}

void GameBoy::loadROM(const std::string &romFileName){
    cpu->loadROM(romFileName);
    romLoaded = true;
}

const CPU &GameBoy::getCPU() const noexcept{
    return *cpu;

}


void GameBoy::step(){
    if(romLoaded){
        cpu->step();
    } else{
        throw ROMNotLoadedException(); //should not step until ROM is loaded
    }
}

bool GameBoy::isROMLoaded() const noexcept{
    return romLoaded;
}
