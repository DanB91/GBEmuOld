#ifndef GPU_H
#define GPU_H

class GPU
{
public:
    GPU();

<<<<<<< HEAD
    /**
     * @brief step steps the GPU
     * @param numCycles the number of cycles the CPU has done since last instruction
     * @return true if should draw to screen, else false
     */
=======
>>>>>>> a3a03e973497b104abfc443a1a45aff163377c6a
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
