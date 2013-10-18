#include "Screen.h"

using namespace GBEmu;



const Screen::Pixel &Screen::getPixelAt(int x, int y) const noexcept
{
    return screen[WIDTH * x + y];
}

Screen::Screen()
{
}
