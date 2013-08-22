#ifndef CPUDEBUGINFO_H
#define CPUDEBUGINFO_H

#include "GameBoy.h"



/*
 * Contains the state of the CPU that can be accessed by the GUI.  It returns string versions
 * of values in registers and other such stuff.
 */
namespace GBEmu{

class GameBoy;

class CPUDebugInfo
{
public:
    CPUDebugInfo(GameBoy *gameBoy);

    std::string getA() const noexcept;
    std::string getB() const noexcept;
    std::string getC() const noexcept;
    std::string getD() const noexcept;
    std::string getE() const noexcept;
    std::string getF() const noexcept;
    std::string getH() const noexcept;
    std::string getL() const noexcept;
    std::string getSP() const noexcept;
    std::string getPC() const noexcept;
    std::string getCurrentInstruction() const noexcept;
    std::string getTotalCycles() const noexcept;
    std::string getCyclesSinceLastInstruction() const noexcept;



private:
    GameBoy *gameBoy;
};


}
#endif // CPUDEBUGINFO_H
