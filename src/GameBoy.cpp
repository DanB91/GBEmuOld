#include "GameBoy.h"

using namespace GBEmu;

void GameBoy::loadROM(const std::string &fileName){
    cart = CartridgePtr(new Cartridge(fileName));
    mmu = MMUPtr(new MMU(cart));
}
