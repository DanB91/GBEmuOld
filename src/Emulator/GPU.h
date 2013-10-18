#ifndef GPU_H
#define GPU_H

class GPU
{
public:
    GPU();

    bool step(int numCycles);

private:
    enum{
        HBLANK = 0,
        VBLANK = 1,
        OAM = 2,
        VRAM = 3
    } mode;

    int scanlineNumber;
    int modeClock;
};

#endif // GPU_H
