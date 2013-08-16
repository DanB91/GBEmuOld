#ifndef CPUSTATUS_H
#define CPUSTATUS_H

#include <QMainWindow>
#include "Emulator/GameBoy.h"

namespace Ui {
class CPUStatus;
}

class CPUStatus : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CPUStatus(QWidget *parent = 0, GBEmu::GameBoyPtr gb = nullptr);
    ~CPUStatus();
    
private:
    Ui::CPUStatus *ui;
    GBEmu::GameBoyPtr gameBoy;
};

#endif // CPUSTATUS_H
