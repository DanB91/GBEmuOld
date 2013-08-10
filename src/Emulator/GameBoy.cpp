#include "GameBoy.h"

using namespace GBEmu;


const CPU::State &GameBoy::getCPUState() const{
    return cpu->getState();
}

void GameBoy::step(){
    cpu->step();
}
