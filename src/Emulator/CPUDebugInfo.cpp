

#include "CPUDebugInfo.h"
#include "GBEmuExceptions.h"
#include <sstream>

using namespace GBEmu;

static std::string toString(word val){
    std::stringstream ss;
    ss << std::hex << val;

    return ss.str();
}

CPUDebugInfo::CPUDebugInfo(GameBoy *gb)
        :gameBoy(gb)
    {}

std::string CPUDebugInfo::getA() const noexcept{
    return toString(highByte(gameBoy->getCPU().getAF()));
}

std::string CPUDebugInfo::getB() const noexcept{
    return toString(highByte(gameBoy->getCPU().getBC()));
}

std::string CPUDebugInfo::getC() const noexcept{
    return toString(lowByte(gameBoy->getCPU().getBC()));
}

std::string CPUDebugInfo::getD() const noexcept{
    return toString(highByte(gameBoy->getCPU().getDE()));
}

std::string CPUDebugInfo::getE() const noexcept{
    return toString(lowByte(gameBoy->getCPU().getDE()));
}

std::string CPUDebugInfo::getF() const noexcept{
    return toString(lowByte(gameBoy->getCPU().getAF()));
}

std::string CPUDebugInfo::getH() const noexcept{
    return toString(highByte(gameBoy->getCPU().getHL()));
}

std::string CPUDebugInfo::getL() const noexcept{
    return toString(lowByte(gameBoy->getCPU().getHL()));
}

std::string CPUDebugInfo::getSP() const noexcept{
    return toString(gameBoy->getCPU().getSP());
}

std::string CPUDebugInfo::getPC() const noexcept{
    return toString(gameBoy->getCPU().getPC());
}

std::string CPUDebugInfo::getTotalCycles() const noexcept{
    return toString(gameBoy->getCPU().getTotalCycles());
}

std::string CPUDebugInfo::getCyclesSinceLastInstruction() const noexcept{
    return toString(gameBoy->getCPU().getCyclesSinceLastInstruction());
}

std::string CPUDebugInfo::getCurrentInstruction() const noexcept{

    if(gameBoy->isROMLoaded()){
        return toString(gameBoy->getCPU().getMMU().readByte(gameBoy->getCPU().getPC()));
    } else {
        return "N/A";
    }
}




