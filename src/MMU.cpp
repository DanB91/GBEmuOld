#include <fstream>
#include "GBEmuExceptions.h"
#include "MMU.h"


using namespace GBEmu;

void MMU::leaveBIOS(){
    inBIOS = false;
}


byte MMU::readByte(word address) const{
    byte value = 0;


    switch(address & 0xF000){
        //ROM Bank 0
        case 0:
            if(this->inBIOS && address < 0x100){
                value = BIOS[address];
            } else {
                value = cart->readROM(address);
            }
            break;

        case 0x1000: case 0x2000: case 0x3000:

            //ROM Bank 1
        case 0x4000: case 0x5000: case 0x6000: case 0x7000:
            value = cart->readROM(address);
            break;

        case 0x8000: case 0x9000:
            //GPU vram, not implemented yet
            throw GBEmuException("GPU VRAM not implemented yet");
            break;

            //cart RAM
        case 0xA000: case 0xB000:
            value = cart->readRAM(address);
            break;

            //internal RAM
        case 0xC000: case 0xD000:

            //mirror
        case 0xE000:
            value = workingRAM[address & 0x1FFF];
            break;

        case 0xF000:

            switch(address & 0xF00){
                
                // Working RAM mirror
                case 0x000: case 0x100: case 0x200: case 0x300:
                case 0x400: case 0x500: case 0x600: case 0x700:
                case 0x800: case 0x900: case 0xA00: case 0xB00:
                case 0xC00: case 0xD00:
                    value =  workingRAM[address & 0x1FFF];
                    break;

                case 0xE00:
                    //GPU OAM not implemented yet
                    throw GBEmuException("GPU OAM not implemented yet");
                    break;

                case 0xF00:
                    if(address >= 0xFF80){
                        value = zeroPageRAM[address & 0x7F];
                    } else{
                        throw GBEmuException("IO ports not implemented yet");
                    }
            }

            break;

        default:
            throw GBEmuException("This should be unreachable");
    }


    return value;
}


void MMU::writeByte(byte value, word address){
}


word MMU::readWord(word address) const{
    return readByte(address) | (readByte(address + 1) << 8);
}

void MMU::writeWord(word value, word address){
}




