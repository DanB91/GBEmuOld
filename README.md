GBEmu
=====

Game Boy emulator written in C++.  

So far:

-Graphics have not been worked on yet.  I am currently implementing and testing all opcodes for the CPU.

-You can only compile it on Linux by using qmake on src/platforms/linux/GBEmu/GBEmu.pro.

-Only ROMS without MBC are supported.

-Once compiled, you can load the ROM and then use the CPU Status window to step though each opcode. As opcodes are added, 
    the registers should update correctly.  This is about all the functionality the GUI has, for now.

