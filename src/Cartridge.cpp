#include "Cartridge.h"
#include "GBEmuExceptions.h"
#include <fstream>

#define CART_TYPE 0x147

using namespace GBEmu;

Cartridge::Cartridge(const std::string &romFileName){
    loadROM(romFileName);
}
//getters
int Cartridge::getCartType() const{
    return ROM[CART_TYPE];
}

const std::vector<byte> &Cartridge::getROM() const {
    return ROM;
}



//loads rom file into memory and loads the cartidge type
//currently, only ROMs of type (no MBC) are supported
void Cartridge::loadROM(const std::string &romFileName){

   
    
    std::ifstream file(romFileName, std::ios::in | std::ios::binary | std::ios::ate);
    int fileSize;

    if(!file.is_open()){
        throw FileNotFoundException(romFileName);
    }
    
    //read filesize
    fileSize = file.tellg(); 
    ROM.reserve(fileSize);
    file.seekg(0, std::ios::beg);
    
    file.read((char*)ROM.data(), fileSize); //read ROM into memory

    if(ROM[CART_TYPE] != 0){
        throw GBEmuException("ROM with no MBC only supported now");
    } 

    file.close();






}
