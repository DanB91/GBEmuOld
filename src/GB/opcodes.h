#define OPCODES { \
   /*NOP*/ [&](){state.clock.cyclesSinceLastInstruction = 4;}, \
}
