#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <string>
#include <memory>
#include <vector>
#include "types.h"

namespace GBEmu{
class Cartridge{
public:

    //constants
    static const int CartType = 0x147;
    static const int MaxROMAddress = 0x7FFF;
    static const int  NintendoLogoOffset = 0x104; //offset into ROM where logo is located
    static const int NintendoLogoSize = 48; //number of bytes in nintendo logo

    Cartridge();

    byte readROM(word address) const;
    byte readRAM(word address) const;

    void writeROM(byte value, word address);
    void writeRAM(byte value, word address);

    int getCartType() const noexcept;
    const std::vector<byte> &getROM() const noexcept ;


    void loadROM(const std::string &romFileName);

private:
    std::vector<byte> ROM;


};


typedef std::shared_ptr<Cartridge> CartridgePtr;
}
#endif
