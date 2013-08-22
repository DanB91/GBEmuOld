#ifndef CPUSTATUS_H
#define CPUSTATUS_H

#include <QMainWindow>
#include "Emulator/GameBoy.h"
#include "Emulator/CPUDebugInfo.h"

namespace Ui {
class CPUControlWindow;
}

class CPUControlWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CPUControlWindow(QWidget *parent = 0, GBEmu::GameBoy *gb = nullptr);
    ~CPUControlWindow();

private slots:
    void indicateROMIsLoaded();
    void indicateROMIsNotLoaded();
    void updateData();

    void on_step_clicked();

private:
    Ui::CPUControlWindow *ui;
    GBEmu::GameBoy *gameBoy;
    GBEmu::CPUDebugInfo cpuInfo;
};

#endif // CPUSTATUS_H
