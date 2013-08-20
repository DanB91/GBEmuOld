#ifndef CPUSTATUS_H
#define CPUSTATUS_H

#include <QMainWindow>
#include "Emulator/GameBoy.h"

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

private:
    Ui::CPUControlWindow *ui;
    GBEmu::GameBoy *gameBoy;
};

#endif // CPUSTATUS_H
