#include <fstream>
#include "GBEmuExceptions.h"
#include "MMU.h"


using namespace GBEmu;

MMU::~MMU(){
    delete[] this->ROM;
}

byte MMU::readByte(word address) const{
    byte byte = 0;

    //make sure there is actually a game in memory before trying to read from it
    if(this->ROM == nullptr){
        throw GBEmuException("ROM not loaded into memory");
    }

    switch(address & 0xF000){
        //ROM Bank 0
        case 0:
            if(this->inBIOS && address < 0x100){
                byte = this->BIOS[address];
            } else {
                byte = this->ROM[address];
            }
            break;

        case 0x1000: case 0x2000: case 0x3000:
        
        //ROM Bank 1
        case 0x4000: case 0x5000: case 0x6000: case 0x7000:
            byte = this->ROM[address];
            break;

            
    }

    return byte;
}


void MMU::writeByte(byte value, word address){
}


word MMU::readWord(word address) const{
    return 0;
}

void MMU::writeWord(word value, word address){
}




