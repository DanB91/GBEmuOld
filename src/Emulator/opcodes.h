#ifndef OPCODE_H
#define OPCODE_H

#include <functional>
namespace GBEmu {


//represents a single opcode
class Op{

public:
    Op(std::function<void (void)> op, int cycles)
        : operation(op), cycles(cycles), isImplemented(true)
    {}

    Op()
        :isImplemented(false)
    {}  //will remove eventually

    void operator()() const{
        if(isImplemented){
            operation();
        }

    }

    int getCycles() const noexcept{
        return cycles;
    }

private:

    std::function<void (void)> operation;
    int cycles;
    bool isImplemented; //if not implemented, this opcode is not executed
};

}

#endif
