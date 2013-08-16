#include "GameBoy.h"

using namespace GBEmu;


const CPU::State &GameBoy::getCPUState() const noexcept{
    return cpu->getState();

}

void GameBoy::step(){
    cpu->step();
}
