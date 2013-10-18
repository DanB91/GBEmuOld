#include "GPU.h"

static bool handleHBlank(){
    return false;
}


GPU::GPU()
    :mode(HBLANK), scanlineNumber(0), modeClock(0)
{
}

bool GPU::step(int numCycles)
{
    modeClock += numCycles;

    switch (mode) {
    case HBLANK:
        return handleHBlank();
        break;
    default:
        return false;
        break;
    }
}
