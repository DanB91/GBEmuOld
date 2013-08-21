#ifndef CPUDEBUGINFO_H
#define CPUDEBUGINFO_H

#include "CPU.h"



/*
 * Contains the state of the CPU that can be accessed by the GUI.  It returns string versions
 * of values in registers and other such stuff.
 */
namespace GBEmu{
class CPUDebugInfo
{
public:
    CPUDebugInfo(CPU *cpu)
        :cpu(cpu)
    {}

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
    CPU *cpu;
};


}
#endif // CPUDEBUGINFO_H
