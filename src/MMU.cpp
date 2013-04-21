#include <fstream>
#include "GBEmuExceptions.h"
#include "MMU.h"


using namespace GBEmu;

MMU::~MMU(){
    delete[] this->ROM;
}

unsigned char MMU::readByte(unsigned short address) const{
    return 0;
}


void MMU::writeByte(unsigned char value, unsigned short address){
}


unsigned short MMU::readWord(unsigned short address) const{
    return 0;
}

void MMU::writeWord(unsigned short value, unsigned short address){
}

void MMU::loadROM(const std::string &romFileName){
    
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


