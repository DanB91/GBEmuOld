

#include "CPUDebugInfo.h"
#include "GBEmuExceptions.h"
#include <sstream>

using namespace GBEmu;

std::string toString(int val){
    std::stringstream ss;
    ss << std::hex << val;

    return ss.str();
}


std::string CPUDebugInfo::getA() const noexcept{
    return toString(cpu->getState().registers.A);
}

std::string CPUDebugInfo::getB() const noexcept{
    return toString(cpu->getState().registers.B);
}

std::string CPUDebugInfo::getC() const noexcept{
    return toString(cpu->getState().registers.C);
}

std::string CPUDebugInfo::getD() const noexcept{
    return toString(cpu->getState().registers.D);
}

std::string CPUDebugInfo::getE() const noexcept{
    return toString(cpu->getState().registers.E);
}

std::string CPUDebugInfo::getF() const noexcept{
    return toString(cpu->getState().registers.F);
}

std::string CPUDebugInfo::getH() const noexcept{
    return toString(cpu->getState().registers.H);
}

std::string CPUDebugInfo::getL() const noexcept{
    return toString(cpu->getState().registers.L);
}

std::string CPUDebugInfo::getSP() const noexcept{
    return toString(cpu->getState().registers.SP);
}

std::string CPUDebugInfo::getPC() const noexcept{
    return toString(cpu->getState().registers.PC);
}

std::string CPUDebugInfo::getTotalCycles() const noexcept{
    return toString(cpu->getState().clock.totalCycles);
}

std::string CPUDebugInfo::getCyclesSinceLastInstruction() const noexcept{
    return toString(cpu->getState().clock.cyclesSinceLastInstruction);
}

std::string CPUDebugInfo::getCurrentInstruction() const noexcept{
    byte instruction;

    try{
        instruction = cpu->getMMU().readByte(cpu->getState().registers.PC);
    } catch (GBEmuException &){
        return "N/A";
    }

    return toString(instruction);
}


