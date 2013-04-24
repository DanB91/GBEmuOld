#include <fstream>
#include "GBEmuExceptions.h"
#include "MMU.h"


using namespace GBEmu;

MMU::~MMU(){
    delete[] this->ROM;
}

unsigned char MMU::readByte(unsigned short address) const{
    unsigned char byte = 0;

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


void MMU::writeByte(unsigned char value, unsigned short address){
}


unsigned short MMU::readWord(unsigned short address) const{
    return 0;
}

void MMU::writeWord(unsigned short value, unsigned short address){
}

void MMU::loadROM(const std::string &romFileName){

    if(this->ROM != nullptr){ //if there is a ROM loaded, delete it from memory
        delete[] this->ROM;
        this->ROM = nullptr;
    }
    
    std::ifstream file(romFileName, std::ios::in | std::ios::binary | std::ios::ate);
    int fileSize;

    if(!file.is_open()){
        throw FileNotFoundException(romFileName);
    }

    fileSize = file.tellg();
    this->ROM = new unsigned char[fileSize]; //allocate space for ROM in memory

    file.seekg(0, std::ios::beg);
    file.read((char*)this->ROM, fileSize); //read ROM into memory

    file.close();






}


