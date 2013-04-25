#include "Cartridge.h"
#include "GBEmuExceptions.h"
#include <fstream>

using namespace GBEmu;

Cartridge::Cartridge(const std::string &romFileName){
    loadROM(romFileName);
}


void Cartridge::loadROM(const std::string &romFileName){

   
    
    std::ifstream file(romFileName, std::ios::in | std::ios::binary | std::ios::ate);
    int fileSize;

    if(!file.is_open()){
        throw FileNotFoundException(romFileName);
    }

    fileSize = file.tellg();
    ROM = std::shared_ptr<byte>(new byte[fileSize]); //allocate space for ROM in memory

    file.seekg(0, std::ios::beg);
    file.read((char*)ROM.get(), fileSize); //read ROM into memory
    

    file.close();






}
