#ifndef SCREEN_H
#define SCREEN_H

#include <array>

namespace GBEmu{
class Screen
{
public:
    static const int HEIGHT = 144;
    static const int WIDTH = 160;

    enum class Pixel{
        WHITE,
        LIGHT,
        DARK,
        BLACK
    };

    const Pixel &getPixelAt(int x, int y) const noexcept;

    Screen();

private:
    std::array<Pixel, HEIGHT * WIDTH> screen;
};
}

#endif // SCREEN_H
