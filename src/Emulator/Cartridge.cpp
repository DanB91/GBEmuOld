#include "Cartridge.h"
#include "GBEmuExceptions.h"
#include <array>
#include <fstream>



using namespace GBEmu;

static void verifyROM(const std::vector<byte>&);

Cartridge::Cartridge()
{}

//getters
int Cartridge::getCartType() const noexcept{
    return ROM[CartType];
}

const std::vector<byte> &Cartridge::getROM() const noexcept{
    return ROM;
}

//reads a byte from the ROM (not RAM)
byte Cartridge::readROM(word address) const{
    
    //bounds checking
    if(address > MaxROMAddress){
        throw GBEmuException("ROM index out of bounds");
    }

    return ROM[address];
}

//reads a byte from the ROM (not RAM)
byte Cartridge::readRAM(word address) const{
    throw GBEmuException("External RAM not yet implemented");
}


void Cartridge::writeROM(byte value, word address){
    throw GBEmuException("MBC not implemnted now");
}

void Cartridge::writeRAM(byte value, word address){
    throw GBEmuException("External RAM not yet implemented");
}
//loads rom file into memory and loads the cartidge type
//currently, only ROMs of type (no MBC) are supported
void Cartridge::loadROM(const std::string &romFileName){


    
    std::ifstream file(romFileName, std::ios::in | std::ios::binary | std::ios::ate);
    std::streamoff fileSize;

    if(!file.is_open()){
        throw FileNotFoundException(romFileName);
    }
    
    //read filesize
    fileSize = file.tellg();
    ROM.reserve(fileSize);
    file.seekg(0, std::ios::beg);
    
    file.read((char*)ROM.data(), fileSize); //read ROM into memory

    verifyROM(ROM);

    file.close();


}

//verifies if the ROM is a valid GB ROM
//throws exception, otherwise
static void verifyROM(const std::vector<byte> &ROM){
    std::array<byte,Cartridge::NintendoLogoSize> scrollingNintendoLogo =
    {{
         0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D,
         0x00, 0x0B, 0x03, 0x73, 0x00, 0x83,
         0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08,
         0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
         0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD,
         0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63,
         0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC,
         0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
     }};

    for(unsigned i = 0; i < scrollingNintendoLogo.size(); i++){
        if(ROM[i + Cartridge::NintendoLogoOffset] != scrollingNintendoLogo[i]){
            throw GBEmuException("Not a valid GB ROM");
        }
    }
    
    if(ROM[Cartridge::CartType] != 0){
        throw GBEmuException("ROM with no MBC only supported, for now");
    }
}
