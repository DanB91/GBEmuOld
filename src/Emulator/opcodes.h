#ifndef OPCODE_H
#define OPCODE_H

#include <memory>

//represents a single opcode
struct Opcode{
  std::function<void (void)> operation;
  int cycles;

  Opcode(std::function<void (void)> op, int cycles)
    : operation(op), cycles(cycles)
  {}

  void operator()(){
    operation();
  }
};
typedef std::shared_ptr<Opcode> OpcodePtr;

#define OP(op, cycles) OpcodePtr(new Opcode(op, cycles))

#define OPCODES {{ \
    /*NOP*/ OP([](){}, 4), \
}}


#endif
