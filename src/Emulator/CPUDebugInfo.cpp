

#include "CPUDebugInfo.h"
#include "GBEmuExceptions.h"
#include <sstream>

using namespace GBEmu;

std::string toString(int val){
    std::stringstream ss;
    ss << std::hex << val;

    return ss.str();
}

CPUDebugInfo::CPUDebugInfo(GameBoy *gb)
        :gameBoy(gb)
    {}

std::string CPUDebugInfo::getA() const noexcept{
    return toString(gameBoy->getCPU().getState().registers.A);
}

std::string CPUDebugInfo::getB() const noexcept{
    return toString(gameBoy->getCPU().getState().registers.B);
}

std::string CPUDebugInfo::getC() const noexcept{
    return toString(gameBoy->getCPU().getState().registers.C);
}

std::string CPUDebugInfo::getD() const noexcept{
    return toString(gameBoy->getCPU().getState().registers.D);
}

std::string CPUDebugInfo::getE() const noexcept{
    return toString(gameBoy->getCPU().getState().registers.E);
}

std::string CPUDebugInfo::getF() const noexcept{
    return toString(gameBoy->getCPU().getState().registers.F);
}

std::string CPUDebugInfo::getH() const noexcept{
    return toString(gameBoy->getCPU().getState().registers.H);
}

std::string CPUDebugInfo::getL() const noexcept{
    return toString(gameBoy->getCPU().getState().registers.L);
}

std::string CPUDebugInfo::getSP() const noexcept{
    return toString(gameBoy->getCPU().getState().registers.SP);
}

std::string CPUDebugInfo::getPC() const noexcept{
    return toString(gameBoy->getCPU().getState().registers.PC);
}

std::string CPUDebugInfo::getTotalCycles() const noexcept{
    return toString(gameBoy->getCPU().getState().clock.totalCycles);
}

std::string CPUDebugInfo::getCyclesSinceLastInstruction() const noexcept{
    return toString(gameBoy->getCPU().getState().clock.cyclesSinceLastInstruction);
}

std::string CPUDebugInfo::getCurrentInstruction() const noexcept{

    if(gameBoy->isROMLoaded()){
        return toString(gameBoy->getCPU().getMMU().readByte(gameBoy->getCPU().getState().registers.PC));
    } else {
        return "N/A";
    }
}




