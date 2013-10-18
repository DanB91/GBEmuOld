#ifndef GPU_H
#define GPU_H

class GPU
{
public:
    GPU();

    /**
     * @brief step steps the GPU
     * @param numCycles the number of cycles the CPU has done since last instruction
     * @return true if should draw to screen, else false
     */
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
