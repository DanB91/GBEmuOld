#ifndef MMU_H
#define MMU_H

#include <string>
#include <array>
#include "types.h"
#include "Cartridge.h"


/*
 * Represents the memeory management unit of the Game Boy
 *
 */
namespace GBEmu{
class MMU{
public:

    MMU();

    byte readByte(word address) const;
    void writeByte(byte value, word address);

    word readWord(word address) const;
    void writeWord(word value, word address);

    void loadROM(const std::string &romFileName);

    void leaveBIOS() noexcept;  //goes out of BIOS mode


private:
    Cartridge cart;
    bool inBIOS;
    std::array<byte, 8192> workingRAM; //internal game boy ram
    std::array<byte, 128> zeroPageRAM; //"fast" ram mapped at the end of the ram
    std::array<byte, 256> BIOS; //holds the bios program
};


}


#endif
